/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_threadx.c
  * @author  MCD Application Team
  * @brief   ThreadX applicative file
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

/* Includes ------------------------------------------------------------------*/
#include "app_threadx.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lvgl.h"
#include "lv_port_display.h"
#include "lcd_panel_conf.h"
#include "ts_core.h"
#include "ili2130.h"
#include "lvgl_ui_project/lvgl_ui_project.h"   /* UI exported from LVGL Pro */
#include "bsp/brightness/brightness.h"
#if APP_BENCHMARK
#include "demos/lv_demos.h"
#endif
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* LVGL task stack: 32 KB. The UI init creates all permanent screens in one
 * call; 8 KB overflows on complex hierarchies. */
#define LVGL_STACK_SIZE   (32 * 1024)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TX_THREAD tx_app_thread;
/* USER CODE BEGIN PV */
static const LCD_PanelConfig_t *active_panel_config = &lcd_panel_50_v1;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
static void ts_lvgl_read_cb(lv_indev_t *indev, lv_indev_data_t *data);
/* USER CODE END PFP */

/**
  * @brief  Application ThreadX Initialization.
  * @param memory_ptr: memory pointer
  * @retval int
  */
UINT App_ThreadX_Init(VOID *memory_ptr)
{
  UINT ret = TX_SUCCESS;
  TX_BYTE_POOL *byte_pool = (TX_BYTE_POOL*)memory_ptr;

  /* USER CODE BEGIN App_ThreadX_MEM_POOL */

  /* USER CODE END App_ThreadX_MEM_POOL */
  CHAR *pointer;

  /* Allocate the stack for tx app thread (LVGL_STACK_SIZE overrides the
   * 1 KB TX_APP_STACK_SIZE defined in app_threadx.h — LVGL needs at least 8 KB). */
  if (tx_byte_allocate(byte_pool, (VOID**) &pointer,
                       LVGL_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
  {
    return TX_POOL_ERROR;
  }
  /* Create tx app thread.  */
  if (tx_thread_create(&tx_app_thread, "tx app thread", tx_app_thread_entry, 0, pointer,
                       LVGL_STACK_SIZE, TX_APP_THREAD_PRIO, TX_APP_THREAD_PREEMPTION_THRESHOLD,
                       TX_APP_THREAD_TIME_SLICE, TX_APP_THREAD_AUTO_START) != TX_SUCCESS)
  {
    return TX_THREAD_ERROR;
  }

  /* USER CODE BEGIN App_ThreadX_Init */

  /* USER CODE END App_ThreadX_Init */

  return ret;
}
/**
  * @brief  Function implementing the tx_app_thread_entry thread.
  * @param  thread_input: Hardcoded to 0.
  * @retval None
  */
void tx_app_thread_entry(ULONG thread_input)
{
  /* USER CODE BEGIN tx_app_thread_entry */
  (void)thread_input;

  lv_init();
  lv_tick_set_cb(HAL_GetTick);

  /* Init LTDC and LVGL display buffers.
   * Must happen before enabling the display (DISP GPIO + backlight). */
  lv_port_disp_init(active_panel_config);

  /* Enable panel: replicate LTCD_power_on_sequence() without the CLEAR_DISPLAY
   * memset (which targets 0x201A0000, past the end of U599 SRAM).
   * DISP pin is already LOW from MX_GPIO_Init, so T1 (10ms) has elapsed during
   * peripheral init.  Assert DISP HIGH, wait T2 (250ms), then enable backlight. */
  HAL_GPIO_WritePin(LTDC_DISP_GPIO_Port, LTDC_DISP_Pin, GPIO_PIN_SET);
  HAL_Delay(250);    /* T2: panel requires 250ms before backlight is enabled */
  Brightness.control(LIGHT_ON);

  /* Touch controller — ILI2130 is command-based and does not ACK
   * HAL_I2C_IsDeviceReady, so ts_autodetect() cannot detect it. Init directly.
   * ILI2130 raw range is 0..16383; driver scales to screen pixels, defaulting
   * to 480x272 (4.3" panel) — update to actual screen size before init. */
  ili2130_set_screen_size(SCREEN_WIDTH, SCREEN_HEIGHT);
  ts_init(&ili2130_driver, ILI2130_I2C_ADDR);

  lv_indev_t *indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
  lv_indev_set_read_cb(indev, ts_lvgl_read_cb);

#if APP_BENCHMARK
  lv_demo_benchmark();   /* CMake -DAPP_BENCHMARK=ON */
#else
  /* The UI from LVGL Pro (lvgl_ui_project/, export it with Ctrl+E).
   * "A:" is the drive for file-based assets; this UI has none, all are compiled in. */
  lvgl_ui_project_init("A:");
  lv_screen_load(splash_create());   /* first screen; it loads home by itself */
#endif

  for (;;) {
    uint32_t wait = lv_timer_handler();
    if (wait > 10) wait = 10;
    if (wait < 1)  wait = 1;
    /* TX_TIMER_TICKS_PER_SECOND = 1000 → 1 tick = 1 ms, matches lv_timer_handler() ms. */
    tx_thread_sleep(wait);
  }
  /* USER CODE END tx_app_thread_entry */
}

  /**
  * @brief  Function that implements the kernel's initialization.
  * @param  None
  * @retval None
  */
void MX_ThreadX_Init(void)
{
  /* USER CODE BEGIN Before_Kernel_Start */

  /* USER CODE END Before_Kernel_Start */

  tx_kernel_enter();

  /* USER CODE BEGIN Kernel_Start_Error */

  /* USER CODE END Kernel_Start_Error */
}

/* USER CODE BEGIN 1 */
static void ts_lvgl_read_cb(lv_indev_t *indev, lv_indev_data_t *data)
{
  (void)indev;
  ts_state_t ts_state;

  if (ts_get_state(&ts_state) == TS_OK && ts_state.pressed) {
    data->state   = LV_INDEV_STATE_PRESSED;
    data->point.x = ts_state.x;
    data->point.y = ts_state.y;
  } else {
    data->state = LV_INDEV_STATE_RELEASED;
  }
}
/* USER CODE END 1 */
