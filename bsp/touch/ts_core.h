#ifndef __TS_CORE_H
#define __TS_CORE_H

#include "ts_driver.h"

typedef enum {
    TS_OK = 0,
    TS_ERROR = 1
} ts_status_t;

typedef struct {
    bool pressed;
    uint16_t x;
    uint16_t y;
} ts_state_t;

/**
 * @brief Set FT5x26 raw ADC range for coordinate scaling.
 *        Call once before ts_autodetect() in each target's main.c.
 *        Not needed for GT911 (which reports pixel coordinates directly).
 * @param x_max  Maximum raw X value from the touch IC (panel-specific)
 * @param y_max  Maximum raw Y value from the touch IC (panel-specific)
 * @param disp_w Display width in pixels  (e.g. SCREEN_WIDTH)
 * @param disp_h Display height in pixels (e.g. SCREEN_HEIGHT)
 */
void ts_set_ft5_range(uint16_t x_max, uint16_t y_max, uint16_t disp_w, uint16_t disp_h);

/**
 * @brief Initialize the touch system
 * @param driver Pointer to the driver implementation (e.g. &gt911_driver)
 * @param i2c_addr 8-bit I2C address
 */
ts_status_t ts_init(ts_driver_t *driver, uint16_t i2c_addr);

/**
 * @brief Get the current touch state (Standardized for LVGL)
 * @param state Pointer to state structure to fill
 * @return ts_status_t
 */
ts_status_t ts_get_state(ts_state_t *state);

#endif /* __TS_CORE_H */
