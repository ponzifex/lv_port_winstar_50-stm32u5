#ifndef LV_PORT_DISPLAY_H
#define LV_PORT_DISPLAY_H

#include "lvgl.h"
#include "lcd_panel_conf.h"

#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   480

/* VSYNC flip requires two full-screen framebuffers (2 x 750 KB at 800x480
 * RGB565 = 1.5MB), which exceeds SRAM5 alone (832 KB). After measuring real
 * LVGL heap usage with LV_USE_MEM_MONITOR (peak ~174-248KB, well under the
 * old blind 1MB LV_MEM_SIZE), LV_MEM_SIZE was cut to 384KB, freeing ~640KB
 * back to SRAM1-3 (995KB free total there). SRAM1-3 and SRAM5 are
 * physically contiguous in the address map (SRAM5 starts immediately after
 * SRAM1-3 ends: 0x201A0000 = 0x20000000 + 1664KB) and both are reachable by
 * the LTDC AHB master per the U5 bus matrix, so the second framebuffer
 * (fb_b) is placed in that freed SRAM1-3 space via LV_PORT_FB_B_SECTION
 * (see lv_port_display.c and the .display_fb2 section in the linker
 * script) instead of SRAM5, which only has room for one buffer.
 *
 * TO REVERT to the old tearing/rolling-redraw FULL+DMA2D-copy behavior:
 *   1. Comment out (or delete) the two #define lines below.
 *   2. Remove the .display_fb2 section from STM32U599ZITXQ_FLASH.ld
 *      (safe to leave — it'll just sit unused if LV_PORT_USE_VSYNC_FLIP
 *      is undefined, since fb_b's __attribute__((section(...))) becomes
 *      dead code and nothing references .display_fb2 anymore).
 * That's it — lv_port_display.c's #if/#else already contains the
 * complete fallback implementation, unchanged. */
#define LV_PORT_USE_VSYNC_FLIP  1
#define LV_PORT_FB_B_SECTION    ".display_fb2"

/**
 * @brief Initialize the LVGL display port with a specific panel configuration.
 * @param config Pointer to the panel configuration structure.
 */
void lv_port_disp_init(const LCD_PanelConfig_t *config);

#endif /* LV_PORT_DISPLAY_H */
