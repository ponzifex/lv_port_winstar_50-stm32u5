#include "ltdc.h"
#include "bsp/brightness/brightness.h"

void LTCD_power_on_sequence(void)
{
  // Memory
  CLEAR_DISPLAY;
  // DISP
  HAL_GPIO_WritePin(LTDC_DISP_GPIO_PORT, LTDC_DISP_GPIO_PIN, GPIO_PIN_RESET);
  HAL_Delay(10);     // T1
  HAL_GPIO_WritePin(LTDC_DISP_GPIO_PORT, LTDC_DISP_GPIO_PIN, GPIO_PIN_SET);
  HAL_Delay(250);    // T2
  // Backlight
  Brightness.control(LIGHT_ON);
}

void LTCD_power_off_sequence(void)
{
  // Backlight
  Brightness.control(LIGHT_OFF);
  // DISP
  HAL_GPIO_WritePin(LTDC_DISP_GPIO_PORT, LTDC_DISP_GPIO_PIN, GPIO_PIN_SET);
  HAL_Delay(5);      // T0
  HAL_GPIO_WritePin(LTDC_DISP_GPIO_PORT, LTDC_DISP_GPIO_PIN, GPIO_PIN_RESET);
  HAL_Delay(80);     // T1
  // Memory
  CLEAR_DISPLAY;
}

void color_display(uint8_t r, uint8_t g, uint8_t b)
{
	uint32_t cur_addr = DISPLAY_MEM_ADDR,
			 end_addr = DISPLAY_MEM_ADDR + DISPLAY_MEM_SIZE;

	while (cur_addr != end_addr)
	{
		memset((void*)cur_addr++, b, 1);
		memset((void*)cur_addr++, g, 1);
		memset((void*)cur_addr++, r, 1);
	}
}
