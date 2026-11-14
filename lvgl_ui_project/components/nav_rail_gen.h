/**
 * @file nav_rail_gen.h
 */

#ifndef LVGL_PRO_NAV_RAIL_GEN_H
#define LVGL_PRO_NAV_RAIL_GEN_H

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

typedef enum {
    NAV_RAIL_ACTIVE_HOME = 0,
    NAV_RAIL_ACTIVE_ROOMS = 1,
    NAV_RAIL_ACTIVE_SETTINGS = 2
} nav_rail_active_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

lv_obj_t * nav_rail_create(lv_obj_t * parent);
/**
 * Set the `active` variant of a nav_rail.
 * @param obj       pointer to a nav_rail, or to any widget inside one
 * @param active  the option to switch to
 */
void nav_rail_set_active(lv_obj_t * obj, nav_rail_active_t active);

/**
 * Get the current `active` variant of a nav_rail.
 * @param obj       pointer to a nav_rail, or to any widget inside one
 * @return          the current option, or the first one if `obj` is not in a nav_rail
 */
nav_rail_active_t nav_rail_get_active(lv_obj_t * obj);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LVGL_PRO_NAV_RAIL_GEN_H*/