#ifndef __ILI2130_H
#define __ILI2130_H

#include "ts_driver.h"
#include "main.h"   /* provides GPIO_TypeDef and I2C_HandleTypeDef from the HAL */
#include <stdint.h>

/* Touch controller I2C address: 7-bit 0x41 = 8-bit 0x82 */
#define ILI2130_I2C_ADDR  0x82

/*
 * Report format variant.  Call ili2130_set_protocol() during init.
 *
 * ILI2130_PROTO_HID   — standard HID-over-I2C (7.0" H747 panels and others
 *                        whose IC firmware uses report-ID + tip-switch).
 *                        Default — no extra call needed for these targets.
 *
 * ILI2130_PROTO_COUNT — compact format (10.1" F746 panels and others whose IC
 *                        firmware uses a touch-count byte and packed coordinates).
 *                        Also call ili2130_set_int_gpio() and configure the
 *                        CTP_INT pin as INPUT + PULLUP in your GPIO init.
 */
typedef enum {
    ILI2130_PROTO_HID   = 0,
    ILI2130_PROTO_COUNT = 1,
} ili2130_proto_t;

extern ts_driver_t ili2130_driver;

/* ── Configuration — call before ts_init() ── */
void ili2130_set_screen_size(uint16_t w, uint16_t h);
void ili2130_set_i2c_handle(I2C_HandleTypeDef *h);
void ili2130_set_protocol(ili2130_proto_t proto);
void ili2130_set_int_gpio(GPIO_TypeDef *port, uint16_t pin);  /* required for PROTO_COUNT */

/* ── Debug state — updated every poll ── */
extern uint8_t  ili2130_dbg_i2c_ok;   /* 1 = last I2C read succeeded */
extern uint8_t  ili2130_dbg_buf0;     /* HID: report ID (0x48=valid)  | COUNT: touch count */
extern uint8_t  ili2130_dbg_buf1;     /* HID: tip-switch + point ID   | COUNT: X high byte */
extern uint8_t  ili2130_dbg_buf2;     /* HID: X low byte              | COUNT: X low byte  */
extern uint8_t  ili2130_dbg_buf3;     /* HID: X high byte             | COUNT: Y high byte */
extern uint8_t  ili2130_dbg_buf4;     /* HID: Y low byte              | COUNT: Y low byte  */
extern uint32_t ili2130_dbg_hal_err;  /* hi2c->ErrorCode: 0x04=NACK, 0x20=TIMEOUT, 0x01=BERR */

#endif /* __ILI2130_H */
