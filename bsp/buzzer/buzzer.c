/* Includes ------------------------------------------------------------------*/
#include "buzzer.h"

/* Private typedef -----------------------------------------------------------*/
typedef struct {

  GPIO_TypeDef *gpio_en;

  uint16_t pin_en;

  uint16_t high;   // Remaining time for BUZZER_ON in 10ms units
  uint16_t low;    // Remaining time for BUZZER_OFF in 10ms units
  uint16_t cycle;  // Remaining cycles to repeat

  Buzzer_Reload_Param_t reloadParam; // Reload parameters

} Buzzer_Object_t;

/* Private function prototypes -----------------------------------------------*/
static int32_t Buzzer_Init( void );
static int32_t Buzzer_SetEnPin( GPIO_TypeDef *gpio_en, uint16_t pin_en );
static void Buzzer_Control( eBUZZER_CONTROL_t buzzer_ctrl );
static void Buzzer_Process( void );
static void Buzzer_SetParam( uint16_t high, uint16_t low, uint16_t cycle );
static void Buzzer_Reload( void );

/* Private variables ---------------------------------------------------------*/
static Buzzer_Object_t buzzer_obj = {

  .high = 0,
  .low = 0,
  .cycle = 0,

  .reloadParam = { .high = 0, .low = 0, .cycle = 0 },

};

/* Exported variables --------------------------------------------------------*/
const BUZZER_API_Typedef Buzzer = {

  .init       = Buzzer_Init,
  .control    = Buzzer_Control,
  .process    = Buzzer_Process,
  .setEnPin   = Buzzer_SetEnPin,
  .setParam   = Buzzer_SetParam,
  .reload     = Buzzer_Reload,

};

/* Private user code ---------------------------------------------------------*/
static int32_t Buzzer_Init( void )
{
  buzzer_obj.high = 0;
  buzzer_obj.low = 0;
  buzzer_obj.cycle = 0;

  buzzer_obj.reloadParam.high = 0;
  buzzer_obj.reloadParam.low = 0;
  buzzer_obj.reloadParam.cycle = 0;

  return 0;
}

static int32_t Buzzer_SetEnPin( GPIO_TypeDef *gpio_en, uint16_t pin_en )
{
  buzzer_obj.gpio_en = gpio_en;

  buzzer_obj.pin_en = pin_en;

  return 0;
}

static void Buzzer_Control( eBUZZER_CONTROL_t buzzer_ctrl )
{
  switch( buzzer_ctrl )
  {
    case BUZZER_ON:
      HAL_GPIO_WritePin( buzzer_obj.gpio_en, buzzer_obj.pin_en, GPIO_PIN_SET ); // Enable buzzer
    break;

    case BUZZER_OFF:
    default:
      HAL_GPIO_WritePin( buzzer_obj.gpio_en, buzzer_obj.pin_en, GPIO_PIN_RESET ); // Disable buzzer
    break;
  }
}

static void Buzzer_SetParam( uint16_t high, uint16_t low, uint16_t cycle )
{
  buzzer_obj.high = high;
  buzzer_obj.low = low;
  buzzer_obj.cycle = cycle;

  buzzer_obj.reloadParam.high = high;
  buzzer_obj.reloadParam.low = low;
  buzzer_obj.reloadParam.cycle = cycle;
}

static void Buzzer_Reload( void )
{
  buzzer_obj.high = buzzer_obj.reloadParam.high;
  buzzer_obj.low = buzzer_obj.reloadParam.low;
  buzzer_obj.cycle = buzzer_obj.reloadParam.cycle;
}

static void Buzzer_Process( void )
{
  static uint32_t lastTick = 0;

  if( ( HAL_GetTick() - lastTick ) < 10 )
    return;

  lastTick = HAL_GetTick();

  if( buzzer_obj.cycle == 0 )
    return;

  if( buzzer_obj.high > 0 )
  {
    buzzer_obj.high--;

    Buzzer_Control( BUZZER_ON );

    return;
  }

  if( buzzer_obj.low > 0 )
  {
    buzzer_obj.low--;

    Buzzer_Control( BUZZER_OFF );

    return;
  }

  if( buzzer_obj.cycle )
  {
    buzzer_obj.cycle--;

    buzzer_obj.high = buzzer_obj.reloadParam.high;
    buzzer_obj.low  = buzzer_obj.reloadParam.low;

    Buzzer_Control( BUZZER_OFF );
  }
}
