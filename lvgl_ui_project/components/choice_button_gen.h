/**
 * @file choice_button_gen.h
 */

#ifndef LVGL_PRO_CHOICE_BUTTON_GEN_H
#define LVGL_PRO_CHOICE_BUTTON_GEN_H

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

lv_obj_t * choice_button_create(lv_obj_t * parent, const char * text, bool selected);
/**
 * Set the `selected` property of a choice_button, and notify everything bound to it.
 * @param obj       pointer to a choice_button, or to any widget inside one
 * @param selected  the new value
 */
void choice_button_set_selected(lv_obj_t * obj, int32_t selected);

/**
 * Get the current `selected` property of a choice_button.
 * @param obj       pointer to a choice_button, or to any widget inside one
 * @return          the current value, or 0 if `obj` is not in a choice_button
 */
int32_t choice_button_get_selected(lv_obj_t * obj);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LVGL_PRO_CHOICE_BUTTON_GEN_H*/