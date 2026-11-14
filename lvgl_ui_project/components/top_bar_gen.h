/**
 * @file top_bar_gen.h
 */

#ifndef LVGL_PRO_TOP_BAR_GEN_H
#define LVGL_PRO_TOP_BAR_GEN_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif

#if defined(LV_USE_XML) && LV_USE_XML
    #include "lv_xml/lv_xml.h"
#endif

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

lv_obj_t * top_bar_create(lv_obj_t * parent, const char * title);
/**
 * Set the `title` property of a top_bar, and notify everything bound to it.
 * @param obj       pointer to a top_bar, or to any widget inside one
 * @param title  the new value. It is copied, so it need not stay alive
 */
void top_bar_set_title(lv_obj_t * obj, const char * title);

/**
 * Get the current `title` property of a top_bar.
 * @param obj       pointer to a top_bar, or to any widget inside one
 * @return          the current value, or NULL if `obj` is not in a top_bar
 */
const char * top_bar_get_title(lv_obj_t * obj);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LVGL_PRO_TOP_BAR_GEN_H*/