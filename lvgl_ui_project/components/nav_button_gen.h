/**
 * @file nav_button_gen.h
 */

#ifndef LVGL_PRO_NAV_BUTTON_GEN_H
#define LVGL_PRO_NAV_BUTTON_GEN_H

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

lv_obj_t * nav_button_create(lv_obj_t * parent, const void * icon, bool active);
/**
 * Set the `active` property of a nav_button, and notify everything bound to it.
 * @param obj       pointer to a nav_button, or to any widget inside one
 * @param active  the new value
 */
void nav_button_set_active(lv_obj_t * obj, int32_t active);

/**
 * Get the current `active` property of a nav_button.
 * @param obj       pointer to a nav_button, or to any widget inside one
 * @return          the current value, or 0 if `obj` is not in a nav_button
 */
int32_t nav_button_get_active(lv_obj_t * obj);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LVGL_PRO_NAV_BUTTON_GEN_H*/