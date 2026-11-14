#include "ili2130.h"
#include "main.h"

extern I2C_HandleTypeDef hi2c3;
static I2C_HandleTypeDef *s_hi2c = &hi2c3;  /* override with ili2130_set_i2c_handle() */

/* ── Protocol selection ── */
static ili2130_proto_t  s_proto    = ILI2130_PROTO_HID;   /* default: 7.0" H747 panels */
static GPIO_TypeDef    *s_int_port = NULL;                 /* INT pin — set for PROTO_COUNT */
static uint16_t         s_int_pin  = 0;

void ili2130_set_protocol(ili2130_proto_t proto)
{
    s_proto = proto;
}

void ili2130_set_int_gpio(GPIO_TypeDef *port, uint16_t pin)
{
    s_int_port = port;
    s_int_pin  = pin;
}

/* ── Debug state: updated every poll, readable from touch_tracer / debugger ── */
uint8_t  ili2130_dbg_i2c_ok  = 0;
uint8_t  ili2130_dbg_buf0    = 0;
uint8_t  ili2130_dbg_buf1    = 0;
uint8_t  ili2130_dbg_buf2    = 0;
uint8_t  ili2130_dbg_buf3    = 0;
uint8_t  ili2130_dbg_buf4    = 0;
uint32_t ili2130_dbg_hal_err = 0;

/*
 * Two ILI2130 panel firmware variants are supported:
 *
 * ILI2130_PROTO_HID  — standard HID-over-I2C (7.0" H747 and similar panels)
 *   buf[0]   Report ID, expect 0x48 for a valid touch report
 *   buf[1]   bit6 = tip switch (1 = finger down), bits5:0 = point ID (0 = first finger)
 *   buf[2:3] X coordinate, little-endian 16-bit, range 0x0000–0x3FFF
 *   buf[4:5] Y coordinate, little-endian 16-bit, range 0x0000–0x3FFF
 *   Lift detection: tip switch goes to 0 inside the report
 *
 * ILI2130_PROTO_COUNT — compact format (10.1" F746 and similar panels)
 *   buf[0]   Touch count (0 = no touch, 1 = one finger)
 *   buf[1]   bits7:6 = event flags, bits5:0 = X coordinate high byte
 *   buf[2]   X coordinate low byte
 *   buf[3]   bits7:6 = event flags, bits5:0 = Y coordinate high byte
 *   buf[4]   Y coordinate low byte
 *   Lift detection: requires INT pin gating — IC keeps buf[0]=1 at the last
 *   position after lift; only asserting INT LOW for new reports.
 *   Configure with ili2130_set_int_gpio() and set CTP_INT as INPUT + PULLUP.
 */

#define ILI2130_REG         0x10
#define ILI2130_BUF_SIZE    64
#define ILI2130_RAW_MAX     0x4000u   /* 14-bit raw coordinate range */

#define ILI2130_REPORT_ID   0x48
#define ILI2130_TIP_SWITCH  0x40
#define ILI2130_POINT_ID    0x3F

/* Screen dimensions — set per-target via ili2130_set_screen_size() */
static uint16_t s_screen_w = 480;
static uint16_t s_screen_h = 272;

void ili2130_set_screen_size(uint16_t w, uint16_t h)
{
    s_screen_w = w;
    s_screen_h = h;
}

void ili2130_set_i2c_handle(I2C_HandleTypeDef *h)
{
    s_hi2c = h;
}

static uint8_t s_buf[ILI2130_BUF_SIZE];
static bool    s_last_touch = false;

static HAL_StatusTypeDef ili2130_Init(uint16_t addr)
{
    (void)addr;
    /* Hardware reset */
    HAL_GPIO_WritePin(CTP_RST_GPIO_Port, CTP_RST_Pin, GPIO_PIN_RESET);
    HAL_Delay(20);
    HAL_GPIO_WritePin(CTP_RST_GPIO_Port, CTP_RST_Pin, GPIO_PIN_SET);
    HAL_Delay(200);
    return HAL_OK;
}

static bool ili2130_DetectTouch(uint16_t addr)
{
    /* PROTO_COUNT panels keep buf[0] non-zero at the last touch position after
     * the finger lifts (stale data).  Gate reads on the INT pin so we only
     * process a report when the IC has actually asserted one (INT LOW).
     * PROTO_HID panels reliably clear the tip-switch bit on lift, so they do
     * not need INT gating — but it is harmless if an INT pin is configured. */
    if (s_int_port != NULL &&
        HAL_GPIO_ReadPin(s_int_port, s_int_pin) == GPIO_PIN_SET) {
        s_last_touch = false;
        return false;
    }

    if (HAL_I2C_Mem_Read(s_hi2c, addr, ILI2130_REG,
                         I2C_MEMADD_SIZE_8BIT,
                         s_buf, ILI2130_BUF_SIZE, 20) != HAL_OK)
    {
        ili2130_dbg_i2c_ok  = 0;
        ili2130_dbg_hal_err = s_hi2c->ErrorCode;
        s_last_touch = false;
        return false;
    }

    ili2130_dbg_i2c_ok = 1;
    ili2130_dbg_buf0   = s_buf[0];
    ili2130_dbg_buf1   = s_buf[1];
    ili2130_dbg_buf2   = s_buf[2];
    ili2130_dbg_buf3   = s_buf[3];
    ili2130_dbg_buf4   = s_buf[4];

    if (s_proto == ILI2130_PROTO_HID) {
        /* Valid touch: correct report ID, tip switch set, point ID = 0 */
        if (s_buf[0] != ILI2130_REPORT_ID)    { s_last_touch = false; return false; }
        if (!(s_buf[1] & ILI2130_TIP_SWITCH)) { s_last_touch = false; return false; }
        if (s_buf[1] & ILI2130_POINT_ID)      { s_last_touch = false; return false; }
    } else {
        /* PROTO_COUNT: touch count in buf[0] */
        if (s_buf[0] == 0) { s_last_touch = false; return false; }
    }

    s_last_touch = true;
    return true;
}

static bool ili2130_GetXY(uint16_t addr, uint16_t *x, uint16_t *y)
{
    (void)addr;
    if (!s_last_touch) return false;

    uint16_t xr, yr;
    if (s_proto == ILI2130_PROTO_HID) {
        /* X = buf[2] (low) | buf[3] (high), Y = buf[4] (low) | buf[5] (high) */
        xr = (uint16_t)((uint16_t)s_buf[3] << 8) | s_buf[2];
        yr = (uint16_t)((uint16_t)s_buf[5] << 8) | s_buf[4];
    } else {
        /* X = buf[1] bits5:0 (high) | buf[2] (low), Y = buf[3] bits5:0 (high) | buf[4] (low) */
        xr = (uint16_t)(((uint16_t)(s_buf[1] & 0x3F) << 8) | s_buf[2]);
        yr = (uint16_t)(((uint16_t)(s_buf[3] & 0x3F) << 8) | s_buf[4]);
    }

    /* Scale raw 0..0x3FFF → screen pixels */
    *x = (uint16_t)((uint32_t)xr * s_screen_w / ILI2130_RAW_MAX);
    *y = (uint16_t)((uint32_t)yr * s_screen_h / ILI2130_RAW_MAX);
    return true;
}

ts_driver_t ili2130_driver = {
    .Init        = ili2130_Init,
    .DetectTouch = ili2130_DetectTouch,
    .GetXY       = ili2130_GetXY,
};
