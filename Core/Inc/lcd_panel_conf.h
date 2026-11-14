#ifndef LCD_PANEL_CONF_H
#define LCD_PANEL_CONF_H

#include "stm32u5xx_hal.h"

/**
 * @brief Structure to hold LCD panel specific parameters
 * This allows dynamic switching between different hardware versions/panels.
 */
typedef struct {
    /* LTDC Polarity */
    uint32_t HSPolarity;
    uint32_t VSPolarity;
    uint32_t DEPolarity;
    uint32_t PCPolarity;

    /* LTDC Timings */
    uint16_t HorizontalSync;
    uint16_t VerticalSync;
    uint16_t AccumulatedHBP;
    uint16_t AccumulatedVBP;
    uint16_t AccumulatedActiveW;
    uint16_t AccumulatedActiveH;
    uint16_t TotalWidth;
    uint16_t TotalHeight;

    /* Layer Configuration */
    uint16_t ImageWidth;
    uint16_t ImageHeight;
    uint32_t PixelFormat;
} LCD_PanelConfig_t;

/* Available configurations */
extern const LCD_PanelConfig_t lcd_panel_50_v1; /* 5.0" Panel */

#endif /* LCD_PANEL_CONF_H */
