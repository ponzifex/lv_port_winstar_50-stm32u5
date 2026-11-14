@echo off
rem Build the firmware and flash it to the Winstar 5" Smart Display through an ST-Link.
rem Needs STM32CubeCLT (GCC, CMake, Ninja, STM32CubeProgrammer):
rem https://www.st.com/en/development-tools/stm32cubeclt.html
rem Export the UI first: open lvgl_ui_project in LVGL Pro and press Ctrl+E.
rem
rem   build_and_flash.bat          build and flash
rem   build_and_flash.bat build    only build

setlocal
cd /d "%~dp0"

if "%STM32CLT_PATH%"=="" (
    echo STM32CLT_PATH is not set. Install STM32CubeCLT, then open a new terminal.
    exit /b 1
)
set "PATH=%STM32CLT_PATH%\GNU-tools-for-STM32\bin;%STM32CLT_PATH%\CMake\bin;%STM32CLT_PATH%\Ninja\bin;%STM32CLT_PATH%\STM32CubeProgrammer\bin;%PATH%"

if not exist lvgl_ui_project\lvgl_ui_project_gen.c (
    echo The UI is not exported yet. Open lvgl_ui_project in LVGL Pro and press Ctrl+E.
    exit /b 1
)

echo === Build ===
if not exist build\build.ninja cmake -G Ninja -S . -B build -DCMAKE_BUILD_TYPE=Release || exit /b 1
cmake --build build || exit /b 1

if /i "%1"=="build" exit /b 0

echo === Flash ===
rem The external loader programs the 16 MB OSPI flash, where the images and fonts are.
STM32_Programmer_CLI -c port=SWD freq=4000 mode=UR -el tools\W25Q128JV_STM32U599-SmartDisplay.stldr -w build\firmware.elf -v -hardRst || exit /b 1
echo === Done ===
