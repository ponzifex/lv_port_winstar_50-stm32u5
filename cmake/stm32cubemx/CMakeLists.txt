cmake_minimum_required(VERSION 3.22)
# Enable CMake support for ASM and C languages
enable_language(C ASM)
# STM32CubeMX generated symbols (macros)
set(MX_Defines_Syms
    TX_INCLUDE_USER_DEFINE_FILE
    TX_SINGLE_MODE_NON_SECURE=1
    USE_HAL_DRIVER
    STM32U599xx
    $<$<CONFIG:Debug>:DEBUG>
)

# STM32CubeMX generated include paths
set(MX_Include_Dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Inc/ExHardware
    ${CMAKE_CURRENT_SOURCE_DIR}/../../AZURE_RTOS/App
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/ST/threadx/common/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/ST/threadx/ports/cortex_m33/gnu/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/CMSIS/Device/ST/STM32U5xx/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/CMSIS/Include
)

# STM32CubeMX generated application sources
set(MX_Application_Src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../AZURE_RTOS/App/app_azure_rtos.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/tx_initialize_low_level.S
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/app_threadx.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/ospi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/stm32u5xx_it.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/stm32u5xx_hal_msp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/stm32u5xx_hal_timebase_tim.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/sysmem.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/syscalls.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../startup_stm32u599zitxq.s
    ${CMAKE_CURRENT_SOURCE_DIR}/../../bsp/buzzer/buzzer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../bsp/brightness/brightness.c
)

# STM32 HAL/LL Drivers
set(STM32_Drivers_Src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/system_stm32u5xx.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_tim.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_tim_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_cortex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_crc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_crc_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_i2c.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_i2c_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_rcc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_rcc_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_flash.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_flash_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_gpio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_dma.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_dma_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_exti.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_pwr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_pwr_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_gtzc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_icache.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_dcache.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_dma2d.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_gpu2d.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_ltdc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_ltdc_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_dsi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_ospi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_ll_dlyb.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_uart.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_uart_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_spi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_spi_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_pcd.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_pcd_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_ll_usb.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_sd.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_ll_sdmmc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/ExHardware/exflash.c
)

# ThreadX (Azure RTOS) — Cortex-M33 port ASMs + common kernel
set(ThreadX_Port_Src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/ST/threadx/ports/cortex_m33/gnu/src/tx_thread_context_restore.S
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/ST/threadx/ports/cortex_m33/gnu/src/tx_thread_context_save.S
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/ST/threadx/ports/cortex_m33/gnu/src/tx_thread_interrupt_control.S
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/ST/threadx/ports/cortex_m33/gnu/src/tx_thread_interrupt_disable.S
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/ST/threadx/ports/cortex_m33/gnu/src/tx_thread_interrupt_restore.S
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/ST/threadx/ports/cortex_m33/gnu/src/tx_thread_schedule.S
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/ST/threadx/ports/cortex_m33/gnu/src/tx_thread_stack_build.S
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/ST/threadx/ports/cortex_m33/gnu/src/tx_thread_system_return.S
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/ST/threadx/ports/cortex_m33/gnu/src/tx_timer_interrupt.S
)
file(GLOB_RECURSE ThreadX_Common_Src
    "${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/ST/threadx/common/src/*.c"
)

# Link directories setup
set(MX_LINK_DIRS

)
# Project static libraries
set(MX_LINK_LIBS
    STM32_Drivers
    ${TOOLCHAIN_LINK_LIBRARIES}
    ThreadX
)
# Interface library for includes and symbols
add_library(stm32cubemx INTERFACE)
target_include_directories(stm32cubemx INTERFACE ${MX_Include_Dirs})
target_compile_definitions(stm32cubemx INTERFACE ${MX_Defines_Syms})

# Create STM32_Drivers static library
add_library(STM32_Drivers OBJECT)
target_sources(STM32_Drivers PRIVATE ${STM32_Drivers_Src})
target_link_libraries(STM32_Drivers PUBLIC stm32cubemx)

# Create ThreadX static library
add_library(ThreadX OBJECT)
target_sources(ThreadX PRIVATE ${ThreadX_Port_Src} ${ThreadX_Common_Src})
target_link_libraries(ThreadX PUBLIC stm32cubemx)

# Add STM32CubeMX generated application sources to the project
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${MX_Application_Src})

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE ${MX_LINK_DIRS})

# Add libraries to the project
target_link_libraries(${CMAKE_PROJECT_NAME} ${MX_LINK_LIBS})

# Add the map file to the list of files to be removed with 'clean' target
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES ADDITIONAL_CLEAN_FILES ${CMAKE_PROJECT_NAME}.map)

# Validate that STM32CubeMX code is compatible with C standard
if((CMAKE_C_STANDARD EQUAL 90) OR (CMAKE_C_STANDARD EQUAL 99))
    message(ERROR "Generated code requires C11 or higher")
endif()
