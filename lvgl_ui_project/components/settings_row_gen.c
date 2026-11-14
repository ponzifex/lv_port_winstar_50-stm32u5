/**
 * @file settings_row_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "settings_row_gen.h"
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

lv_obj_t * settings_row_create(lv_obj_t * parent, const char * title, const char * subtitle)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if LVGL_UI_PROJECT_CHECK_COMPILE_TARGET(LVGL_UI_PROJECT_TARGET_ALL)
    if (lvgl_ui_project_check_target(LVGL_UI_PROJECT_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(parent);
        lv_obj_set_name_static(lv_obj_0, "settings_row_#");
        lv_obj_set_width(lv_obj_0, lv_pct(100));
        lv_obj_set_height(lv_obj_0, LV_SIZE_CONTENT);
        lv_obj_set_flex_flow(lv_obj_0, LV_FLEX_FLOW_ROW);
        lv_obj_set_scrollable(lv_obj_0, false);
        lv_obj_set_style_pad_gap(lv_obj_0, SPACE_XL, 0);
        lv_obj_set_style_flex_cross_place(lv_obj_0, LV_FLEX_ALIGN_CENTER, 0);

        lv_obj_add_style(lv_obj_0, &style_card, 0);
        lv_obj_t * lv_obj_1 = lv_obj_create(lv_obj_0);
        lv_obj_set_flex_grow(lv_obj_1, 1);
        lv_obj_set_height(lv_obj_1, LV_SIZE_CONTENT);
        lv_obj_set_flex_flow(lv_obj_1, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_pad_gap(lv_obj_1, SPACE_XS, 0);
        lv_obj_add_style(lv_obj_1, &style_box, 0);
        lv_obj_t * lv_label_0 = lv_label_create(lv_obj_1);
        lv_label_set_text(lv_label_0, title);
        lv_obj_set_style_text_font(lv_label_0, font_h2, 0);

        lv_obj_t * lv_label_1 = lv_label_create(lv_obj_1);
        lv_label_set_text(lv_label_1, subtitle);
        lv_obj_set_hidden(lv_label_1, ((subtitle) == NULL || (subtitle)[0] == '\0'));
        lv_obj_add_style(lv_label_1, &style_text_caption, 0);

        lv_obj_t * control = lv_obj_create(lv_obj_0);
        lv_obj_set_name(control, "control");
        lv_obj_set_width(control, LV_SIZE_CONTENT);
        lv_obj_set_height(control, LV_SIZE_CONTENT);
        lv_obj_set_flex_flow(control, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_pad_gap(control, SPACE_SM, 0);
        lv_obj_set_style_flex_cross_place(control, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_add_style(control, &style_box, 0);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

lv_obj_t * settings_row_get_control(lv_obj_t *parent)
{
    return lv_obj_find_by_name(parent, "control");
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

