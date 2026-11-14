/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ltdc.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern PCD_HandleTypeDef hpcd_USB_OTG_HS;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define USBX_APP_THREAD_MEM_STACK_SIZE (1 * 1024)
#define USBX_CLASS_TOTAL_MEM_STACK_SIZE ((8 * 1024) + (2 * (USBX_CLASS_THREAD_MEM_STACK_SIZE + 16)))
#define FILEX_APP_THREAD_MEM_STACK_SIZE (2 * 1024)
#define FILEX_TOTAL_MEM_POOL_SIZE (FILEX_APP_THREAD_MEM_STACK_SIZE + 16)
#define USBX_TOTAL_MEM_POOL_SIZE (USBX_CLASS_TOTAL_MEM_STACK_SIZE + (USBX_APP_THREAD_MEM_STACK_SIZE + 16) + 16)
#define THREADX_APP_THREAD_MEM_STACK_SIZE (32 * 1024)
#define THREADX_TOTAL_MEM_POOL_SIZE (THREADX_APP_THREAD_MEM_STACK_SIZE + 16)
#define TOUCHGFX_APP_THREAD_MEM_STACK_SIZE (4 * 1024)
#define USBX_CLASS_THREAD_MEM_STACK_SIZE (1 * 1024)
#define TOUCHGFX_TOTAL_MEM_POOL_SIZE (TOUCHGFX_APP_THREAD_MEM_STACK_SIZE + 16)
#define CTP_SCL_Pin GPIO_PIN_0
#define CTP_SCL_GPIO_Port GPIOC
#define CTP_SDA_Pin GPIO_PIN_1
#define CTP_SDA_GPIO_Port GPIOC
#define CTP_RST_Pin GPIO_PIN_2
#define CTP_RST_GPIO_Port GPIOC
#define CTP_INT_Pin GPIO_PIN_3
#define CTP_INT_GPIO_Port GPIOC
#define USART2_DE_Pin GPIO_PIN_1
#define USART2_DE_GPIO_Port GPIOA
#define SPI1_NSS_Pin GPIO_PIN_4
#define SPI1_NSS_GPIO_Port GPIOA
#define USB_OTG_HS_ID_Pin GPIO_PIN_10
#define USB_OTG_HS_ID_GPIO_Port GPIOA
#define SWDI_Pin GPIO_PIN_13
#define SWDI_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define LTDC_DISP_Pin GPIO_PIN_4
#define LTDC_DISP_GPIO_Port GPIOD
#define BUZZER_Pin GPIO_PIN_5
#define BUZZER_GPIO_Port GPIOD
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define BL_EN_Pin GPIO_PIN_8
#define BL_EN_GPIO_Port GPIOB
#define VBL_Pin GPIO_PIN_9
#define VBL_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* Enable initial test mode */
//#define INITIAL_TEST_MODE
//#define USE_SD_CARD         /* The SD Card must be inserted before power on, otherwise the program execution will fail. */
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
