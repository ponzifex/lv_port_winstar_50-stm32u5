#include "ts_core.h"
#include <stddef.h>

static ts_driver_t *current_driver = NULL;
static uint16_t current_addr = 0;

/* FT5x26 scaling parameters — set by ts_set_ft5_range() */
uint16_t ts_ft5_x_max  = 1272;  /* safe default (3.9" values) */
uint16_t ts_ft5_y_max  = 767;
uint16_t ts_ft5_disp_w = 480;
uint16_t ts_ft5_disp_h = 128;

void ts_set_ft5_range(uint16_t x_max, uint16_t y_max, uint16_t disp_w, uint16_t disp_h)
{
    ts_ft5_x_max  = x_max;
    ts_ft5_y_max  = y_max;
    ts_ft5_disp_w = disp_w;
    ts_ft5_disp_h = disp_h;
}

ts_status_t ts_init(ts_driver_t *driver, uint16_t i2c_addr) {
    if (driver == NULL) return TS_ERROR;
    
    current_driver = driver;
    current_addr = i2c_addr;
    
    if (current_driver->Init) {
        current_driver->Init(current_addr);
    }
    
    return TS_OK;
}

ts_status_t ts_get_state(ts_state_t *state) {
    if (current_driver == NULL || state == NULL) return TS_ERROR;

    state->pressed = false;

    if (current_driver->DetectTouch(current_addr)) {
        uint16_t tx, ty;
        if (current_driver->GetXY(current_addr, &tx, &ty)) {
            state->x = tx;
            state->y = ty;
            state->pressed = true;
        }
    }

    return TS_OK;
}
