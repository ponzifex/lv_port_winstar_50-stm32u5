#ifndef LTDC_H
#define LTDC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include <string.h>

// ---------------------- Setting ---------------------- //
#define  DISPLAY_WIDTH           800
#define  DISPLAY_HEIGHT          480
#define  DISPLAY_COLOR           3       // RGB888
#define  DISPLAY_MEM_ADDR        ((uint32_t)0x201A0000)
#define  DISPLAY_MEM_SIZE        (DISPLAY_WIDTH * DISPLAY_HEIGHT * DISPLAY_COLOR)

#define  LTDC_DISP_GPIO_PORT     LTDC_DISP_GPIO_Port
#define  LTDC_DISP_GPIO_PIN      LTDC_DISP_Pin
// ----------------------------------------------------- //

#define  CLEAR_DISPLAY           memset((void*)DISPLAY_MEM_ADDR, 0x00, DISPLAY_MEM_SIZE)
#define  HIGH_DISPLAY            memset((void*)DISPLAY_MEM_ADDR, 0xFF, DISPLAY_MEM_SIZE)

void LTCD_power_on_sequence(void);
void LTCD_power_off_sequence(void);

void color_display(uint8_t r, uint8_t g, uint8_t b);

#ifdef __cplusplus
}
#endif

#endif /* LTDC_H */
