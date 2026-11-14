/**
 * @file info_tile_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "info_tile_gen.h"
#include "../lvgl_ui_project.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/***********************
 *  STATIC VARIABLES
 **********************/

/***********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * info_tile_create(lv_obj_t * parent, const void * icon)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if LVGL_UI_PROJECT_CHECK_COMPILE_TARGET(LVGL_UI_PROJECT_TARGET_ALL)
    if (lvgl_ui_project_check_target(LVGL_UI_PROJECT_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(parent);
        lv_obj_set_name_static(lv_obj_0, "info_tile_#");
        lv_obj_set_width(lv_obj_0, LV_SIZE_CONTENT);
        lv_obj_set_height(lv_obj_0, LV_SIZE_CONTENT);
        lv_obj_set_flex_flow(lv_obj_0, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_pad_gap(lv_obj_0, SPACE_SM, 0);
        lv_obj_set_style_flex_cross_place(lv_obj_0, LV_FLEX_ALIGN_CENTER, 0);

        lv_obj_add_style(lv_obj_0, &style_box, 0);
        lv_obj_t * lv_image_0 = lv_image_create(lv_obj_0);
        lv_image_set_src(lv_image_0, icon);
        lv_obj_add_style(lv_image_0, &style_icon, 0);
        lv_obj_add_style(lv_image_0, &style_icon_muted, 0);

        lv_obj_t * value = lv_obj_create(lv_obj_0);
        lv_obj_set_name(value, "value");
        lv_obj_set_width(value, LV_SIZE_CONTENT);
        lv_obj_set_height(value, LV_SIZE_CONTENT);
        lv_obj_add_style(value, &style_box, 0);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

lv_obj_t * info_tile_get_value(lv_obj_t *parent)
{
    return lv_obj_find_by_name(parent, "value");
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

