/**
 * @file lvgl_ui_project.h
 */

#ifndef LVGL_PRO_LVGL_UI_PROJECT_H
#define LVGL_PRO_LVGL_UI_PROJECT_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      DEFINES
 *********************/

/* Target(s) select at startup: one or more LVGL_UI_PROJECT_TARGET_* values OR-ed together. */
#ifndef LVGL_UI_PROJECT_COMPILE_TARGET
#define LVGL_UI_PROJECT_COMPILE_TARGET LVGL_UI_PROJECT_TARGET_ALL
#endif

/*********************
 *      INCLUDES
 *********************/

#include "lvgl_ui_project_gen.h"

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL VARIABLES
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Initialize the component library
 */
void lvgl_ui_project_init(const char * asset_path);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LVGL_PRO_LVGL_UI_PROJECT_H*/