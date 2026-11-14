#ifndef TOUCH_H
#define TOUCH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include <stdbool.h>

typedef enum {
	NTP,
	CTP,
	RTP,
} Touch_Type;

// ---------------------- Setting ---------------------- //
extern   I2C_HandleTypeDef  hi2c3;
#define  TOUCH_TYPE         CTP

#define  CTP_RST_GPIO_PORT  CTP_RST_GPIO_Port
#define  CTP_RST_GPIO_PIN   CTP_RST_Pin
// ----------------------------------------------------- //

void touch_init(void);
bool touch_detect(int32_t *x, int32_t *y);

#ifdef __cplusplus
}
#endif

#endif /* TOUCH_H */
