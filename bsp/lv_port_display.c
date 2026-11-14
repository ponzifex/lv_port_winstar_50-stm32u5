#include "lv_port_display.h"
#include "lcd_panel_conf.h"
#include "stm32u5xx_hal.h"
#include <string.h>

/*********************
 *      EXTERNS
 *********************/
extern LTDC_HandleTypeDef hltdc;
extern DMA2D_HandleTypeDef hdma2d;

/*********************
 *  RENDER STRATEGY (selected per target via lv_port_display.h)
 *
 *  LV_PORT_USE_VSYNC_FLIP (4.3-U599):
 *      DIRECT mode with two full-screen framebuffers in internal SRAM that
 *      double as the LTDC scan-out buffers.  LVGL re-renders only invalidated
 *      regions; on the last area of each refresh the finished buffer is shown
 *      by an LTDC page-flip scheduled for the next vertical blank.
 *
 *  Default:
 *      FULL mode.  LVGL renders the whole frame into one of two SRAM buffers
 *      and DMA2D copies it into a single fixed SRAM framebuffer.
 *********************/

static lv_display_t *g_disp;

static void ltdc_hardware_init(const LCD_PanelConfig_t *config);

/* LV_PORT_USE_ST_LTDC (CMake option, 5.0-U599): same DIRECT mode + two
 * framebuffers + vblank page-flip as LV_PORT_USE_VSYNC_FLIP, but the flush
 * logic is LVGL's built-in driver (src/drivers/display/st_ltdc) instead of
 * hand-written code. Needs USE_HAL_LTDC_REGISTER_CALLBACKS = 1U in the HAL
 * conf, since lv_st_ltdc registers its own LTDC reload callback. */
#if defined(LV_PORT_USE_ST_LTDC) && LV_PORT_USE_ST_LTDC
#define PORT_TWO_FRAMEBUFFERS 1
#elif defined(LV_PORT_USE_VSYNC_FLIP) && LV_PORT_USE_VSYNC_FLIP
#define PORT_TWO_FRAMEBUFFERS 1
#else
#define PORT_TWO_FRAMEBUFFERS 0
#endif

/* ======================================================================== */
#if PORT_TWO_FRAMEBUFFERS
/* ======================================================================== */

#define FB_PX     (SCREEN_WIDTH * SCREEN_HEIGHT)
#define FB_BYTES  (FB_PX * 2)

/* Two full-screen framebuffers. fb_a always lives in SRAM5 (Display RAM,
 * 0x201A0000) via the .display_fb NOLOAD linker section.
 *
 * fb_b defaults to the same section/bank, but a target can redirect it
 * elsewhere by defining LV_PORT_FB_B_SECTION (in its lv_port_display.h)
 * before this file is compiled — e.g. 800x480 targets don't have room for
 * two 750KB buffers in SRAM5 (832KB total), so fb_b is placed in a
 * different NOLOAD section mapped into freed SRAM1-3 space instead.
 * To revert: remove the LV_PORT_FB_B_SECTION define in the target's
 * lv_port_display.h — fb_b falls back to SRAM5 like every other target. */
#ifndef LV_PORT_FB_B_SECTION
#define LV_PORT_FB_B_SECTION ".display_fb"
#endif

static uint16_t fb_a[FB_PX] __attribute__((section(".display_fb"), aligned(32)));
static uint16_t fb_b[FB_PX] __attribute__((section(LV_PORT_FB_B_SECTION), aligned(32)));

#if defined(LV_PORT_USE_ST_LTDC) && LV_PORT_USE_ST_LTDC

void lv_port_disp_init(const LCD_PanelConfig_t *config)
{
    lv_memzero(fb_a, FB_BYTES);
    lv_memzero(fb_b, FB_BYTES);

    /* LTDC starts scanning fb_a. lv_st_ltdc takes resolution and color
     * format from hltdc.LayerCfg[0], so the layer must be configured first. */
    ltdc_hardware_init(config);

    /* DIRECT mode, double-buffered: LVGL flips buffers at vertical blank. */
    g_disp = lv_st_ltdc_create_direct(fb_a, fb_b, 0);
}

#else /* LV_PORT_USE_VSYNC_FLIP: hand-written flush */

static void flip_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map);

void lv_port_disp_init(const LCD_PanelConfig_t *config)
{
    lv_memzero(fb_a, FB_BYTES);
    lv_memzero(fb_b, FB_BYTES);

    ltdc_hardware_init(config); /* LTDC starts scanning fb_a */

    g_disp = lv_display_create(SCREEN_WIDTH, SCREEN_HEIGHT);
    lv_display_set_flush_cb(g_disp, flip_flush);
    lv_display_set_color_format(g_disp, LV_COLOR_FORMAT_RGB565);

    /* DIRECT mode: LVGL keeps both full-screen buffers complete and re-renders
     * only invalidated regions into the active one. */
    lv_display_set_buffers(g_disp, fb_a, fb_b, FB_BYTES,
                           LV_DISPLAY_RENDER_MODE_DIRECT);
}

/* LTDC register-reload interrupt: the page-flip scheduled for vertical blank
 * has taken effect; the previously displayed buffer is now free for rendering. */
void HAL_LTDC_ReloadEventCallback(LTDC_HandleTypeDef *h)
{
    (void)h;
    lv_display_flush_ready(g_disp);
}

static void flip_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
    /* STM32U599 Cortex-M33 has no D-cache (__DCACHE_PRESENT not defined),
     * so no cache flush is needed before the LTDC page-flip. */
    if (!lv_display_flush_is_last(disp)) {
        lv_display_flush_ready(disp);
        return;
    }

    /* All dirty areas cleaned — flip to this buffer at the next vertical blank. */
    HAL_LTDC_SetAddress_NoReload(&hltdc, (uint32_t)px_map, 0);
    HAL_LTDC_Reload(&hltdc, LTDC_RELOAD_VERTICAL_BLANKING);
    /* lv_display_flush_ready() is deferred to HAL_LTDC_ReloadEventCallback. */
}

#endif /* LV_PORT_USE_ST_LTDC */

/* ======================================================================== */
#else  /* default: FULL mode + DMA2D copy to a fixed SRAM framebuffer */
/* ======================================================================== */

/* Single fixed framebuffer in SRAM5 (.display_fb NOLOAD section in linker script).
 * LTDC always reads from this address. */
static uint16_t display_fb[SCREEN_WIDTH * SCREEN_HEIGHT]
    __attribute__((section(".display_fb"), aligned(32)));

/* Partial-screen LVGL draw buffers (1/10 height) — keeps SRAM usage ~150 KB total
 * instead of 3×768 KB which overflows SRAM at 800×480. */
#define LV_BUF_LINES  (SCREEN_HEIGHT / 10)
static uint16_t lv_buf_1[SCREEN_WIDTH * LV_BUF_LINES] __attribute__((aligned(32)));
static uint16_t lv_buf_2[SCREEN_WIDTH * LV_BUF_LINES] __attribute__((aligned(32)));

static void my_display_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map);

void lv_port_disp_init(const LCD_PanelConfig_t *config)
{
    ltdc_hardware_init(config);

    g_disp = lv_display_create(SCREEN_WIDTH, SCREEN_HEIGHT);
    lv_display_set_flush_cb(g_disp, my_display_flush);
    lv_display_set_color_format(g_disp, LV_COLOR_FORMAT_RGB565);
    lv_display_set_buffers(g_disp, lv_buf_1, lv_buf_2, sizeof(lv_buf_1),
                           LV_DISPLAY_RENDER_MODE_PARTIAL);
}

static void my_display_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
    (void)disp;
    int32_t w = lv_area_get_width(area);
    int32_t h = lv_area_get_height(area);

    /* Copy the rendered strip to the LTDC framebuffer row by row.
     * DMA2D is avoided here: the HAL-init uses RGB888 mode and re-configuring
     * it for RGB565 partial copies is error-prone. CPU memcpy on M33 @ 160 MHz
     * copies a full 800-pixel row (1600 B) in < 5 µs — well within budget.
     * No D-cache on STM32U599, so no cache flush needed. */
    uint16_t *src = (uint16_t *)px_map;
    uint16_t *dst = &display_fb[area->y1 * SCREEN_WIDTH + area->x1];

    for (int32_t y = 0; y < h; y++) {
        memcpy(dst, src, (size_t)w * sizeof(uint16_t));
        src += w;
        dst += SCREEN_WIDTH;
    }

    lv_display_flush_ready(g_disp);
}

#endif /* PORT_TWO_FRAMEBUFFERS */

/*********************
 *   SHARED STATIC FUNCTIONS
 *********************/

static void ltdc_hardware_init(const LCD_PanelConfig_t *config)
{
    LTDC_LayerCfgTypeDef pLayerCfg = {0};

    /* Pixel clock (PLL3) is configured in HAL_LTDC_MspInit — no PLLSAI here. */

    hltdc.Instance = LTDC;
    hltdc.Init.HSPolarity = config->HSPolarity;
    hltdc.Init.VSPolarity = config->VSPolarity;
    hltdc.Init.DEPolarity = config->DEPolarity;
    hltdc.Init.PCPolarity = config->PCPolarity;
    hltdc.Init.HorizontalSync = config->HorizontalSync;
    hltdc.Init.VerticalSync = config->VerticalSync;
    hltdc.Init.AccumulatedHBP = config->AccumulatedHBP;
    hltdc.Init.AccumulatedVBP = config->AccumulatedVBP;
    hltdc.Init.AccumulatedActiveW = config->AccumulatedActiveW;
    hltdc.Init.AccumulatedActiveH = config->AccumulatedActiveH;
    hltdc.Init.TotalWidth = config->TotalWidth;
    hltdc.Init.TotalHeigh = config->TotalHeight;
    hltdc.Init.Backcolor.Blue = 0;
    hltdc.Init.Backcolor.Green = 0;
    hltdc.Init.Backcolor.Red = 0;
    if (HAL_LTDC_Init(&hltdc) != HAL_OK) {}

    pLayerCfg.WindowX0 = 0;
    pLayerCfg.WindowX1 = config->ImageWidth;
    pLayerCfg.WindowY0 = 0;
    pLayerCfg.WindowY1 = config->ImageHeight;
    pLayerCfg.PixelFormat = config->PixelFormat;
    pLayerCfg.Alpha = 255;
    pLayerCfg.Alpha0 = 0;
    pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
    pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
#if PORT_TWO_FRAMEBUFFERS
    pLayerCfg.FBStartAdress = (uint32_t)fb_a;
#else
    pLayerCfg.FBStartAdress = (uint32_t)display_fb;
#endif
    pLayerCfg.ImageWidth = config->ImageWidth;
    pLayerCfg.ImageHeight = config->ImageHeight;
    pLayerCfg.Backcolor.Blue = 0;
    pLayerCfg.Backcolor.Green = 0;
    pLayerCfg.Backcolor.Red = 0;
    if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK) {}
}
