#include "lcd_panel_conf.h"
#include "stm32u5xx_hal.h"

/* Values taken from 5_U599_lvgl MX_LTDC_Init() in main.c.
 * No PLLSAI — pixel clock is configured by HAL_LTDC_MspInit via PLL3.
 * PLL3: M=1, N=23, R=8 → ~33 MHz pixel clock for 800x480. */
const LCD_PanelConfig_t lcd_panel_50_v1 = {
    .HSPolarity = LTDC_HSPOLARITY_AL,
    .VSPolarity = LTDC_VSPOLARITY_AL,
    .DEPolarity = LTDC_DEPOLARITY_AL,
    .PCPolarity = LTDC_PCPOLARITY_IPC,

    .HorizontalSync = 7,
    .VerticalSync = 7,
    .AccumulatedHBP = 14,
    .AccumulatedVBP = 19,
    .AccumulatedActiveW = 814,
    .AccumulatedActiveH = 499,
    .TotalWidth = 862,
    .TotalHeight = 511,

    .ImageWidth = 800,
    .ImageHeight = 480,
    .PixelFormat = LTDC_PIXEL_FORMAT_RGB565,
};
