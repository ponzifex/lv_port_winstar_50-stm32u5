# LVGL ported to the Winstar 5" Smart Display (STM32U599)

## Overview

A ready-to-use LVGL v9.6 project for the Winstar 5" Smart Display (WL0F00050000FGXAANA00):
an STM32U599 with an 800×480 RGB display, capacitive touch and 16 MB external flash.

- Display: LVGL's built-in STM32 LTDC driver (`lv_st_ltdc`), double-buffered direct mode.
- GPU: NeoChrom (GPU2D) through LVGL's NemaGFX draw unit.
- UI: an [LVGL Pro](https://lvgl.io/pro) project in `lvgl_ui_project/`. Edit it in the LVGL Pro Editor,
  export it, then build and flash. This repo ships with a smart thermostat demo UI.
- Build: CMake + Ninja with ST's command-line tools (STM32CubeCLT). No IDE needed.

## Buy

TODO: Winstar product link.

## Benchmark

Double-buffered direct mode with two full-screen RGB565 framebuffers in internal SRAM;
the buffers are swapped at vertical blank. The panel refreshes at about 52 Hz, which caps the
frame rate at about 51 FPS.

`lv_demo_benchmark`, LVGL v9.6, build with `-DAPP_BENCHMARK=ON`:

| Scene | FPS | Render (ms) |
| --- | --- | --- |
| Rectangles, images, arcs, scrolling | 51 | 0-15 |
| Moving wallpaper | 22 | 36 |
| Multiple labels | 25 | 19 |
| Widgets demo | 26 | 25 |
| **Average** | **43** | **12** |

## Specification

### CPU and Memory
- **MCU:** STM32U599ZIT6Q, Cortex-M33 at 160 MHz
- **RAM:** 2.5 MB internal
- **Flash:** 2 MB internal, 16 MB external (W25Q128JV, OCTOSPI, memory-mapped at 0x90000000)
- **GPU:** NeoChrom (GPU2D), Chrom-Art (DMA2D)

### Display and Touch
- **Resolution:** 800×480
- **Display Size:** 5.0"
- **Interface:** RGB (LTDC)
- **Color Depth:** 16-bit (RGB565)
- **DPI:** 187 px/inch
- **Touch Pad:** capacitive, ILI2130

## Getting started

### Hardware setup
- Power the board through its USB-C port.
- Connect an ST-Link to the 6-pin SWD header (top right, pin 1 at the bottom):
  1 VAPP (3.3 V sense), 2 SWCLK, 3 GND, 4 SWDIO, 5 NRST, 6 SWO.
- Power the board first, then connect the ST-Link to the PC.

### Software setup
- [STM32CubeCLT](https://www.st.com/en/development-tools/stm32cubeclt.html): GCC, CMake, Ninja and STM32CubeProgrammer in one installer.
- [LVGL Pro Editor](https://lvgl.io/pro) to edit the UI. The Community license is enough.

### Run the project
```
git clone --recursive https://github.com/ponzifex/lv_port_winstar_50-stm32u5.git
cd lv_port_winstar_50-stm32u5
build_and_flash.bat
```

To change the UI:
1. Open `lvgl_ui_project/` in the LVGL Pro Editor.
2. Edit the screens and components, then export the C code with **Ctrl+E**.
3. Run `build_and_flash.bat` again.

The firmware starts the UI in `Core/Src/app_threadx.c`:
```c
lvgl_ui_project_init("A:");
lv_screen_load(splash_create());   /* the first screen */
```
To start with another screen, change `splash_create()` to that screen's `<name>_create()`.

### Memory layout
- Code and LVGL in internal flash.
- Images and fonts of the UI in external flash (the `RESOURCE` region of the linker script).
  `build_and_flash.bat` programs both with the external loader in `tools/`.
- Two framebuffers (750 KB each) in internal SRAM.

### Debugging
- The LVGL performance monitor is in `Core/Inc/lv_conf.h` (`LV_USE_PERF_MONITOR`).
- Note: a hot-plug SWD connection (for example STM32CubeProgrammer in hot-plug mode) stops the
  board's interrupts, so the UI freezes. A reset or a re-flash fixes it.

## License

MIT, see [LICENSE](LICENSE). LVGL, the ST drivers (CMSIS, STM32U5 HAL) and ThreadX keep their
own licenses; `LICENSE` lists them.
