#ifndef __BUZZER_H__
#define __BUZZER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "stm32u5xx_hal.h"

/* Exported constants --------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef enum {

  BUZZER_ON = 0x00,
  BUZZER_OFF,

} eBUZZER_CONTROL_t;

typedef struct {

  uint16_t high;   // Duration for BUZZER_ON in 10ms units
  uint16_t low;    // Duration for BUZZER_OFF in 10ms units
  uint16_t cycle;  // Number of cycles to repeat

} Buzzer_Param_t;

typedef struct {

  uint16_t high;   // Reload duration for BUZZER_ON in 10ms units
  uint16_t low;    // Reload duration for BUZZER_OFF in 10ms units
  uint16_t cycle;  // Reload number of cycles to repeat

} Buzzer_Reload_Param_t;

/* Exported functions prototypes ---------------------------------------------*/
typedef struct {

  int32_t ( *const init )( void );

  void ( *const control )( eBUZZER_CONTROL_t buzzer_ctrl );

  void ( *const process )( void );

  int32_t ( *const setEnPin )( GPIO_TypeDef *gpio_en, uint16_t pin_en );

  void ( *const setParam )( uint16_t high, uint16_t low, uint16_t cycle );

  void ( *const reload )( void );

} BUZZER_API_Typedef;

/* Exported macro ------------------------------------------------------------*/

/* Exported variables -----------------------------------------------------------*/

extern const BUZZER_API_Typedef Buzzer;

#ifdef __cplusplus
}
#endif

#endif /* __BUZZER_H__ */
