/*
******************************************************************************
**
**  File        : LinkerScript.ld
**
**  Author      : STM32CubeIDE
**
**  Abstract    : Linker script for STM32U599xI Device from STM32U5 series
**                      2048Kbytes FLASH
**                      2512Kbytes SRAM
**                including external flash
**                      16Mbytes QSPI
**
**                Set heap size, stack size and stack location according
**                to application requirements.
**
**                Set memory bank area and size if external memory is used.
**
**  Target      : STMicroelectronics STM32
**
**  Distribution: The file is distributed as is without any warranty
**                of any kind.
**
*****************************************************************************
** @attention
**
** Copyright (c) 2024 STMicroelectronics.
** All rights reserved.
**
** This software is licensed under terms that can be found in the LICENSE file
** in the root directory of this software component.
** If no LICENSE file comes with this software, it is provided AS-IS.
**
*****************************************************************************
*/

/* Entry Point */
ENTRY(Reset_Handler)

/* Highest address of the user mode stack */
_estack = ORIGIN(SRAM) + LENGTH(SRAM); /* end of "SRAM" Ram type memory */

_Min_Heap_Size = 0x1000; /* required amount of heap */
_Min_Stack_Size = 0x1000; /* required amount of stack */
_Min_TX_Heap_Size = 0x10000; /* required amount of heap for ThreadX */

/* Memories definition */
MEMORY
{
  /* SRAM1 ~ SRAM5 (SRAM5 used to DISPLAY) */
  SRAM      (rwx) : ORIGIN = 0x20000000, LENGTH = 768K+64K+832K     /* include SRAM1 ~ SRAM3 */
  SRAM4     (rwx) : ORIGIN = 0x28000000, LENGTH = 16K
  SRAM5     (rwx) : ORIGIN = 0x201A0000, LENGTH = 832K   /* Display framebuffers */
  
  FLASH     (rx)  : ORIGIN = 0x08000000, LENGTH = 2048K
  
  /* QSPI (used to RESOURCE) */
  RESOURCE  (rx)  : ORIGIN = 0x90000000, LENGTH = 16M
}

/* Sections */
SECTIONS
{
  /* The startup code into "FLASH" Rom type memory */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector)) /* Startup code */
    . = ALIGN(4);
  } >FLASH

  /* The program code and other data into "FLASH" Rom type memory */
  .text :
  {
    . = ALIGN(4);
    *(.text)           /* .text sections (code) */
    *(.text*)          /* .text* sections (code) */
    *(.glue_7)         /* glue arm to thumb code */
    *(.glue_7t)        /* glue thumb to arm code */
    *(.eh_frame)

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(4);
    _etext = .;        /* define a global symbols at end of code */
  } >FLASH

  /* Constant data into "FLASH" Rom type memory */
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
    . = ALIGN(4);
  } >FLASH

  .ARM.extab (READONLY) : /* The READONLY keyword is only supported in GCC11 and later, remove it if using GCC10 or earlier. */
  {
    . = ALIGN(4);
    *(.ARM.extab* .gnu.linkonce.armextab.*)
    . = ALIGN(4);
  } >FLASH
  .ARM (READONLY) : /* The READONLY keyword is only supported in GCC11 and later, remove it if using GCC10 or earlier. */
  {
    . = ALIGN(4);
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
    . = ALIGN(4);
  } >FLASH

  .preinit_array (READONLY) : /* The READONLY keyword is only supported in GCC11 and later, remove it if using GCC10 or earlier. */
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
    . = ALIGN(4);
  } >FLASH

  .init_array (READONLY) : /* The READONLY keyword is only supported in GCC11 and later, remove it if using GCC10 or earlier. */
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
    . = ALIGN(4);
  } >FLASH

  .fini_array (READONLY) : /* The READONLY keyword is only supported in GCC11 and later, remove it if using GCC10 or earlier. */
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
    . = ALIGN(4);
  } >FLASH

  /* Used by the startup to initialize data */
  _sidata = LOADADDR(.data);

  /* Initialized data sections into "SRAM" Ram type memory */
  .data :
  {
    . = ALIGN(4);
    _sdata = .;        /* create a global symbol at data start */
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */
    *(.RamFunc)        /* .RamFunc sections */
    *(.RamFunc*)       /* .RamFunc* sections */

    . = ALIGN(4);
    _edata = .;        /* define a global symbol at data end */
  } >SRAM AT> FLASH

  /* Uninitialized data section into "SRAM" Ram type memory */
  . = ALIGN(4);
  .bss :
  {
    /* This is used by the startup in order to initialize the .bss section */
    _sbss = .;         /* define a global symbol at bss start */
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(4);
    _ebss = .;         /* define a global symbol at bss end */
    __bss_end__ = _ebss;
  } >SRAM

  /* User_heap_stack section, used to check that there is enough "SRAM" Ram type memory left */
  ._user_heap_stack :
  {
    . = ALIGN(8);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
  } >SRAM
  
  /* Added dynamic memory allocation for ThreadX RTOS into "SRAM" RAM type memory */
  ._threadx_heap :
  {
    . = ALIGN(8);
    __RAM_segment_used_end__ = .;
    . = . + _Min_TX_Heap_Size;
    . = ALIGN(8);
  } >SRAM

  /* Remove information from the compiler libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

  .ARM.attributes 0 : { *(.ARM.attributes) }
  
  /* LVGL display framebuffers in dedicated Display RAM (SRAM5).
   * NOTE: exact-match *(.display_fb) only — do NOT use the *(.display_fb*)
   * wildcard here, it would also greedily match .display_fb2 below (since
   * this block is placed first) and pull fb_b back into SRAM5, overflowing
   * it. That's exactly what caused the SRAM5 overflow the first time this
   * was written. */
  .display_fb (NOLOAD) :
  {
    . = ALIGN(32);
    *(.display_fb)
    . = ALIGN(32);
  } >SRAM5

  /* Second VSYNC-flip framebuffer (fb_b, ~750KB) for this target's 800x480
   * display — doesn't fit alongside fb_a in SRAM5 (832KB total), so it's
   * placed in freed SRAM1-3 space instead, right after every other SRAM
   * allocation (.data/.bss/heap/stack/ThreadX heap above) so the linker
   * can never overlap it with them. See LV_PORT_FB_B_SECTION in
   * lv_port_display.h for how this gets selected/reverted. Safe to leave
   * in place even if unused (VSYNC flip disabled) — an empty NOLOAD
   * section costs nothing. */
  .display_fb2 (NOLOAD) :
  {
    . = ALIGN(32);
    *(.display_fb2)
    *(.display_fb2*)
    . = ALIGN(32);
  } >SRAM

  ExtFlashSection        : { *(ExtFlashSection)        } >RESOURCE
  TextFlashSection       : { *(TextFlashSection)       } >RESOURCE
  FontFlashSection       : { *(FontFlashSection)       } >RESOURCE
  FontSearchFlashSection : { *(FontSearchFlashSection) } >RESOURCE

  /* LVGL large const data (image bitmaps marked with LV_ATTRIBUTE_LARGE_CONST)
   * stored in external QSPI flash, memory-mapped at 0x90000000. */
  .resource              : { *(.resource) *(.resource*) } >RESOURCE
}
