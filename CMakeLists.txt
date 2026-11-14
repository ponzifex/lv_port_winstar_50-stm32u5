cmake_minimum_required(VERSION 3.22)

# LVGL port for the Winstar 5" Smart Display (STM32U599, 800x480).
# Build with STM32CubeCLT (arm-none-eabi-gcc, CMake, Ninja), see README.md.

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_PROJECT_NAME lv_port_winstar_50-stm32u5)
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/gcc-arm-none-eabi.cmake")

set(CMAKE_C_FLAGS_DEBUG "-O0 -g3")
set(CMAKE_C_FLAGS_RELEASE "-Os -g3")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")
set(CMAKE_CXX_FLAGS_RELEASE "-Os -g3")
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

project(${CMAKE_PROJECT_NAME})
enable_language(C ASM)

# Override the Windows-GCC link rules that are invalid for arm-none-eabi ld.
# Must come after enable_language(), which sets them on Windows hosts.
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS   "" CACHE INTERNAL "" FORCE)
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "" CACHE INTERNAL "" FORCE)
set(CMAKE_C_LINK_FLAGS                  "" CACHE INTERNAL "" FORCE)
set(CMAKE_CXX_LINK_FLAGS                "" CACHE INTERNAL "" FORCE)
set(CMAKE_C_LINK_EXECUTABLE
    "<CMAKE_C_COMPILER> <FLAGS> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>"
    CACHE INTERNAL "" FORCE)
set(CMAKE_CXX_LINK_EXECUTABLE
    "<CMAKE_CXX_COMPILER> <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>"
    CACHE INTERNAL "" FORCE)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T \"${CMAKE_CURRENT_SOURCE_DIR}/STM32U599ZITXQ_FLASH.ld\"")

add_executable(${CMAKE_PROJECT_NAME})
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES OUTPUT_NAME "firmware" SUFFIX ".elf")

# ---------------------------------------------------------------------------
# Options
# ---------------------------------------------------------------------------
# APP_BENCHMARK=ON runs lv_demo_benchmark() instead of the LVGL Pro UI
option(APP_BENCHMARK "Run the LVGL benchmark demo instead of the UI" OFF)
if(APP_BENCHMARK)
    add_compile_definitions(APP_BENCHMARK=1)
endif()

# LVGL's built-in STM32 LTDC driver, double-buffered direct mode
add_compile_definitions(LV_PORT_USE_ST_LTDC=1)

# ---------------------------------------------------------------------------
# LVGL (git submodule, release/v9.6)
# ---------------------------------------------------------------------------
set(LVGL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lvgl")
set(LV_BUILD_CONF_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Core/Inc/lv_conf.h" CACHE STRING "" FORCE)
add_subdirectory(${LVGL_DIR} ${CMAKE_BINARY_DIR}/lvgl)

# STM32CubeMX generated sources (HAL, ThreadX, startup)
add_subdirectory(cmake/stm32cubemx)

# lvgl's NeoChrom glue includes stm32u5xx_hal.h
target_link_libraries(lvgl PRIVATE stm32cubemx)

# ---------------------------------------------------------------------------
# UI: the LVGL Pro project in lvgl_ui_project/ (export it with Ctrl+E first).
# Its generated CMakeLists.txt builds the UI as the library `lib-ui`.
# ---------------------------------------------------------------------------
add_subdirectory(lvgl_ui_project ${CMAKE_BINARY_DIR}/lvgl_ui_project)
target_link_libraries(lib-ui PUBLIC lvgl)

# ---------------------------------------------------------------------------
# Application sources
# ---------------------------------------------------------------------------
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    bsp/lv_port_display.c          # LTDC setup + lv_st_ltdc display
    Core/Src/lcd_panel_conf.c      # panel timings
    bsp/touch/ts_core.c            # touch stack
    bsp/touch/ili2130.c
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    Core/Inc
    bsp
    bsp/touch
    .
    ${LVGL_DIR}/libs/nema_gfx/include/cortex_m33
)

target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${LVGL_DIR}/libs/nema_gfx/lib/core/cortex_m33_revC/gcc
)

list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

# lvgl and the NemaGFX library in a group: lvgl's NeoChrom glue needs symbols
# from libnemagfx, and the link order is not reliable otherwise.
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx
    lib-ui
    -Wl,--start-group
    lvgl
    nemagfx-float-abi-hard
    -Wl,--end-group
)

if(APP_BENCHMARK AND TARGET lvgl_demos)
    target_link_libraries(${CMAKE_PROJECT_NAME} lvgl_demos)
endif()
