/* Includes ------------------------------------------------------------------*/
#include "brightness.h"

#define MaxTrueDuty 92
#define MinTrueDuty 20

/* Private typedef -----------------------------------------------------------*/
typedef struct {

  uint8_t brightnessLevel;

  GPIO_TypeDef *gpio_en;

  uint16_t pin_en;

  TIM_HandleTypeDef *htim;

  uint32_t tim_ch;

} Brightness_Object_t;

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static int32_t Brightness_Init( void );
static int32_t Brightness_SetTimerCH( TIM_HandleTypeDef *htim, uint32_t tim_ch );
static int32_t Brightness_SetEnPin( GPIO_TypeDef *gpio_en, uint16_t pin_en );
static int32_t Brightness_Set( uint8_t level );
static void Brightness_Control ( eBACKLIGHT_CONTROL_t bl_ctrl );

/* Private variables ---------------------------------------------------------*/
static Brightness_Object_t brightness_obj = {

  .brightnessLevel = 100, // Default brightness level

};

/* Exported variables --------------------------------------------------------*/
const BRIGHTNESS_API_Typedef Brightness = {

  .init       = Brightness_Init,
  .set        = Brightness_Set,
  .control    = Brightness_Control,
  .setTimerCH = Brightness_SetTimerCH,
  .setEnPin   = Brightness_SetEnPin,

};

/* Private user code ---------------------------------------------------------*/
static int32_t Brightness_Init( void )
{
  brightness_obj.brightnessLevel = 50; // Initialize to default value

  return 0;
}

static int32_t Brightness_SetTimerCH( TIM_HandleTypeDef *htim, uint32_t tim_ch )
{
  brightness_obj.htim = htim;

  brightness_obj.tim_ch = tim_ch;

  return 0;
}

static int32_t Brightness_SetEnPin( GPIO_TypeDef *gpio_en, uint16_t pin_en )
{
  brightness_obj.gpio_en = gpio_en;

  brightness_obj.pin_en = pin_en;

  return 0;
}

static void Brightness_Set_Duty ( uint8_t d )
{
  d = ( d > 100 ) ? 100 : d;
  d = 100 - d;
  d = ( ( MaxTrueDuty - MinTrueDuty ) * d ) / 100 + MinTrueDuty;

  __HAL_TIM_SET_COMPARE( brightness_obj.htim, brightness_obj.tim_ch, d );
}

static int32_t Brightness_Set( uint8_t level )
{
  if( brightness_obj.brightnessLevel == level )
    return -1;

  Brightness_Set_Duty( level );

  brightness_obj.brightnessLevel = level;

  return 0; // Success
}

static void Brightness_Control ( eBACKLIGHT_CONTROL_t bl_ctrl )
{
  switch( bl_ctrl )
  {
    case LIGHT_ON:
      HAL_GPIO_WritePin( brightness_obj.gpio_en, brightness_obj.pin_en, GPIO_PIN_SET ); // Set the EN pin of BL driver IC to high, enable it
      Brightness_Set_Duty( brightness_obj.brightnessLevel );
      HAL_TIM_PWM_Start( brightness_obj.htim, brightness_obj.tim_ch );

    break;

    case LIGHT_OFF:
    default:

      HAL_TIM_PWM_Stop( brightness_obj.htim, brightness_obj.tim_ch );
      Brightness_Set( 0 );
      HAL_GPIO_WritePin( brightness_obj.gpio_en, brightness_obj.pin_en, GPIO_PIN_RESET ); // Set the EN pin of BL driver IC to low, disable it

    break;
  }

}

