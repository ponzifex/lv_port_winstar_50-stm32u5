/**
 * @file splash_gen.h
 */

#ifndef LVGL_PRO_SPLASH_GEN_H
#define LVGL_PRO_SPLASH_GEN_H

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
    SPLASH_TIMELINE_TIMELINE_INTRO = 0,
    _SPLASH_TIMELINE_CNT = 1
}splash_timeline_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/



lv_obj_t * splash_create(void);

/**
 * Get a timeline of a splash
 * @param obj          pointer to a splash component
 * @param timeline_id  ID of the timeline
 * @return             pointer to the timeline or NULL if not found
 */
lv_anim_timeline_t * splash_get_timeline(lv_obj_t * obj, splash_timeline_t timeline_id);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LVGL_PRO_SPLASH_GEN_H*/