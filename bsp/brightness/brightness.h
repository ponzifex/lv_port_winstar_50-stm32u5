#ifndef __BRIGHTNESS_H__
#define __BRIGHTNESS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "stm32u5xx_hal.h"

/* Exported constants --------------------------------------------------------*/
#define BRIGHTNESS_MAX 100
#define BRIGHTNESS_MIN 0

/* Exported types ------------------------------------------------------------*/
typedef enum {

  LIGHT_ON = 0x00,
  LIGHT_OFF,

}eBACKLIGHT_CONTROL_t;

/* Exported functions prototypes ---------------------------------------------*/
typedef struct {

  int32_t ( *const init )( void );

  int32_t ( *const set )( uint8_t level );

  void ( *const control )( eBACKLIGHT_CONTROL_t bl_ctrl );

  int32_t ( *const setTimerCH )( TIM_HandleTypeDef *htim, uint32_t tim_ch );

  int32_t ( *const setEnPin )( GPIO_TypeDef *gpio_en, uint16_t pin_en );

} BRIGHTNESS_API_Typedef;

/* Exported macro ------------------------------------------------------------*/

/* Exported variables -----------------------------------------------------------*/

extern const BRIGHTNESS_API_Typedef Brightness;

#ifdef __cplusplus
}
#endif

#endif /* __BRIGHTNESS_H__ */
