/**
 * @file temp_dial_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "temp_dial_gen.h"
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

static void temp_dial_lv_arc_0_style_arc_color_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void temp_dial_lv_label_0_hidden_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void temp_dial_lv_label_0_style_text_color_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void temp_dial_lv_label_1_hidden_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void temp_dial_lv_label_1_style_text_color_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void temp_dial_lv_label_2_hidden_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void temp_dial_lv_label_2_style_text_color_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void temp_dial_lv_label_3_hidden_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void temp_dial_lv_label_3_style_text_color_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void temp_dial_temp_value_1_hidden_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void temp_dial_temp_value_2_hidden_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void temp_dial_temp_value_3_hidden_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void temp_dial_temp_value_4_hidden_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void temp_dial_set_subject_cb(lv_event_t * e);
static void temp_dial_set_subject_cb_2(lv_event_t * e);

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * temp_dial_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");

    static lv_style_t style_dial_track;
    static lv_style_t style_dial_indicator;
    static lv_style_t style_dial_knob;
    static lv_style_t style_step_button;

    static bool style_inited = false;

    if (!style_inited) {
        /*Init all styles*/
        lv_style_init(&style_dial_track);
        lv_style_init(&style_dial_indicator);
        lv_style_init(&style_dial_knob);
        lv_style_init(&style_step_button);

        lv_style_set_arc_width(&style_dial_track, ARC_WIDTH);
        lv_style_set_arc_color(&style_dial_track, COLOR_PANEL_HIGH);
        lv_style_set_arc_opa(&style_dial_track, (255 * 100 / 100));
        lv_style_set_arc_rounded(&style_dial_track, true);
        lv_style_set_bg_opa(&style_dial_track, 0);
        lv_style_set_pad_all(&style_dial_track, 0);
        lv_style_set_arc_width(&style_dial_indicator, ARC_WIDTH);
        lv_style_set_arc_rounded(&style_dial_indicator, true);
        lv_style_set_bg_color(&style_dial_knob, COLOR_TEXT);
        lv_style_set_bg_opa(&style_dial_knob, (255 * 100 / 100));
        lv_style_set_pad_all(&style_dial_knob, 6);
        lv_style_set_radius(&style_dial_knob, RADIUS_ROUND);
        lv_style_set_shadow_width(&style_dial_knob, 12);
        lv_style_set_shadow_opa(&style_dial_knob, (255 * 40 / 100));
        lv_style_set_shadow_color(&style_dial_knob, lv_color_hex(0x000000));
        lv_style_set_width(&style_step_button, TOUCH_MIN);
        lv_style_set_height(&style_step_button, TOUCH_MIN);
        lv_style_set_radius(&style_step_button, RADIUS_ROUND);
        lv_style_set_text_font(&style_step_button, font_h1);

        style_inited = true;
    }


    lv_obj_t * the_root = NULL;

    #if LVGL_UI_PROJECT_CHECK_COMPILE_TARGET(LVGL_UI_PROJECT_TARGET_ALL)
    if (lvgl_ui_project_check_target(LVGL_UI_PROJECT_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(parent);
        lv_obj_set_name_static(lv_obj_0, "temp_dial_#");
        lv_obj_set_width(lv_obj_0, DIAL_CARD_WIDTH);
        lv_obj_set_height(lv_obj_0, lv_pct(100));
        lv_obj_set_scrollable(lv_obj_0, false);

        lv_obj_add_style(lv_obj_0, &style_card, 0);
        lv_obj_t * lv_arc_0 = lv_arc_create(lv_obj_0);
        lv_obj_set_width(lv_arc_0, DIAL_SIZE);
        lv_obj_set_height(lv_arc_0, DIAL_SIZE);
        lv_obj_set_align(lv_arc_0, LV_ALIGN_TOP_MID);
        lv_arc_set_rotation(lv_arc_0, 135);
        lv_arc_set_bg_start_angle(lv_arc_0, 0);
        lv_arc_set_bg_end_angle(lv_arc_0, 270);
        lv_arc_set_min_value(lv_arc_0, 160);
        lv_arc_set_max_value(lv_arc_0, 300);
        lv_arc_bind_value(lv_arc_0, subject_temp_target);
        lv_subject_add_observer_obj(subject_accent, temp_dial_lv_arc_0_style_arc_color_binding_cb, lv_arc_0, NULL);
        lv_obj_add_style(lv_arc_0, &style_dial_track, 0);
        lv_obj_add_style(lv_arc_0, &style_dial_indicator, LV_PART_INDICATOR);
        lv_obj_add_style(lv_arc_0, &style_dial_knob, LV_PART_KNOB);
        lv_obj_t * lv_obj_1 = lv_obj_create(lv_arc_0);
        lv_obj_set_width(lv_obj_1, LV_SIZE_CONTENT);
        lv_obj_set_height(lv_obj_1, LV_SIZE_CONTENT);
        lv_obj_set_align(lv_obj_1, LV_ALIGN_CENTER);
        lv_obj_set_flex_flow(lv_obj_1, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_cross_place(lv_obj_1, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_add_style(lv_obj_1, &style_box, 0);
        lv_obj_t * lv_label_0 = lv_label_create(lv_obj_1);
        lv_label_set_text(lv_label_0, "HEATING TO");
        lv_subject_add_observer_obj(subject_mode, temp_dial_lv_label_0_hidden_binding_cb, lv_label_0, NULL);
        lv_obj_set_style_text_font(lv_label_0, font_small, 0);
        lv_subject_add_observer_obj(subject_accent, temp_dial_lv_label_0_style_text_color_binding_cb, lv_label_0, NULL);

        lv_obj_t * lv_label_1 = lv_label_create(lv_obj_1);
        lv_label_set_text(lv_label_1, "COOLING TO");
        lv_subject_add_observer_obj(subject_mode, temp_dial_lv_label_1_hidden_binding_cb, lv_label_1, NULL);
        lv_obj_set_style_text_font(lv_label_1, font_small, 0);
        lv_subject_add_observer_obj(subject_accent, temp_dial_lv_label_1_style_text_color_binding_cb, lv_label_1, NULL);

        lv_obj_t * lv_label_2 = lv_label_create(lv_obj_1);
        lv_label_set_text(lv_label_2, "KEEP AT");
        lv_subject_add_observer_obj(subject_mode, temp_dial_lv_label_2_hidden_binding_cb, lv_label_2, NULL);
        lv_obj_set_style_text_font(lv_label_2, font_small, 0);
        lv_subject_add_observer_obj(subject_accent, temp_dial_lv_label_2_style_text_color_binding_cb, lv_label_2, NULL);

        lv_obj_t * lv_label_3 = lv_label_create(lv_obj_1);
        lv_label_set_text(lv_label_3, "SYSTEM OFF");
        lv_subject_add_observer_obj(subject_mode, temp_dial_lv_label_3_hidden_binding_cb, lv_label_3, NULL);
        lv_obj_set_style_text_font(lv_label_3, font_small, 0);
        lv_subject_add_observer_obj(subject_accent, temp_dial_lv_label_3_style_text_color_binding_cb, lv_label_3, NULL);

        lv_obj_t * temp_value_0 = temp_value_create(lv_obj_1, subject_temp_target, false);
        lv_obj_set_style_text_font(temp_value_0, font_display, 0);
        lv_obj_set_style_margin_ver(temp_value_0, SPACE_SM, 0);

        lv_obj_t * lv_obj_2 = lv_obj_create(lv_obj_1);
        lv_obj_set_width(lv_obj_2, LV_SIZE_CONTENT);
        lv_obj_set_height(lv_obj_2, LV_SIZE_CONTENT);
        lv_obj_set_flex_flow(lv_obj_2, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_pad_gap(lv_obj_2, SPACE_XS, 0);
        lv_obj_set_style_flex_cross_place(lv_obj_2, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_add_style(lv_obj_2, &style_box, 0);
        lv_obj_t * lv_label_4 = lv_label_create(lv_obj_2);
        lv_label_set_text(lv_label_4, "Now");

        lv_obj_t * temp_value_1 = temp_value_create(lv_obj_2, subject_temp_living, false);
        lv_subject_add_observer_obj(subject_room, temp_dial_temp_value_1_hidden_binding_cb, temp_value_1, NULL);

        lv_obj_t * temp_value_2 = temp_value_create(lv_obj_2, subject_temp_bedroom, false);
        lv_subject_add_observer_obj(subject_room, temp_dial_temp_value_2_hidden_binding_cb, temp_value_2, NULL);

        lv_obj_t * temp_value_3 = temp_value_create(lv_obj_2, subject_temp_kitchen, false);
        lv_subject_add_observer_obj(subject_room, temp_dial_temp_value_3_hidden_binding_cb, temp_value_3, NULL);

        lv_obj_t * temp_value_4 = temp_value_create(lv_obj_2, subject_temp_office, false);
        lv_subject_add_observer_obj(subject_room, temp_dial_temp_value_4_hidden_binding_cb, temp_value_4, NULL);

        lv_obj_add_style(lv_obj_2, &style_text_muted, 0);

        lv_obj_t * lv_obj_3 = lv_obj_create(lv_obj_0);
        lv_obj_set_width(lv_obj_3, LV_SIZE_CONTENT);
        lv_obj_set_height(lv_obj_3, LV_SIZE_CONTENT);
        lv_obj_set_align(lv_obj_3, LV_ALIGN_BOTTOM_MID);
        lv_obj_set_flex_flow(lv_obj_3, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_pad_gap(lv_obj_3, SPACE_XL * 2, 0);
        lv_obj_add_style(lv_obj_3, &style_box, 0);
        lv_obj_t * lv_button_0 = lv_button_create(lv_obj_3);
        lv_obj_add_style(lv_button_0, &style_button, 0);
        lv_obj_add_style(lv_button_0, &style_step_button, 0);
        lv_obj_add_style(lv_button_0, &style_button_pressed, LV_STATE_PRESSED);
        lv_obj_t * lv_label_5 = lv_label_create(lv_button_0);
        lv_label_set_text(lv_label_5, "−");
        lv_obj_set_align(lv_label_5, LV_ALIGN_CENTER);

        lv_obj_add_event_cb(lv_button_0, temp_dial_set_subject_cb, LV_EVENT_CLICKED, NULL);

        lv_obj_t * lv_button_1 = lv_button_create(lv_obj_3);
        lv_obj_add_style(lv_button_1, &style_button, 0);
        lv_obj_add_style(lv_button_1, &style_step_button, 0);
        lv_obj_add_style(lv_button_1, &style_button_pressed, LV_STATE_PRESSED);
        lv_obj_t * lv_label_6 = lv_label_create(lv_button_1);
        lv_label_set_text(lv_label_6, "+");
        lv_obj_set_align(lv_label_6, LV_ALIGN_CENTER);

        lv_obj_add_event_cb(lv_button_1, temp_dial_set_subject_cb_2, LV_EVENT_CLICKED, NULL);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void temp_dial_lv_arc_0_style_arc_color_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    lv_obj_set_style_arc_color(obj, lv_subject_get_color(subject_accent), LV_PART_INDICATOR);
}

static void temp_dial_lv_label_0_hidden_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    lv_obj_set_hidden(obj, lv_subject_get_int(subject_mode) != 1);
}

static void temp_dial_lv_label_0_style_text_color_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    lv_obj_set_style_text_color(obj, lv_subject_get_color(subject_accent), 0);
}

static void temp_dial_lv_label_1_hidden_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    lv_obj_set_hidden(obj, lv_subject_get_int(subject_mode) != 2);
}

static void temp_dial_lv_label_1_style_text_color_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    lv_obj_set_style_text_color(obj, lv_subject_get_color(subject_accent), 0);
}

static void temp_dial_lv_label_2_hidden_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    lv_obj_set_hidden(obj, lv_subject_get_int(subject_mode) != 3);
}

static void temp_dial_lv_label_2_style_text_color_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    lv_obj_set_style_text_color(obj, lv_subject_get_color(subject_accent), 0);
}

static void temp_dial_lv_label_3_hidden_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    lv_obj_set_hidden(obj, lv_subject_get_int(subject_mode) != 0);
}

static void temp_dial_lv_label_3_style_text_color_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    lv_obj_set_style_text_color(obj, lv_subject_get_color(subject_accent), 0);
}

static void temp_dial_temp_value_1_hidden_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    lv_obj_set_hidden(obj, lv_subject_get_int(subject_room) != 0);
}

static void temp_dial_temp_value_2_hidden_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    lv_obj_set_hidden(obj, lv_subject_get_int(subject_room) != 1);
}

static void temp_dial_temp_value_3_hidden_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    lv_obj_set_hidden(obj, lv_subject_get_int(subject_room) != 2);
}

static void temp_dial_temp_value_4_hidden_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    lv_obj_set_hidden(obj, lv_subject_get_int(subject_room) != 3);
}

static void temp_dial_set_subject_cb(lv_event_t * e)
{
    LV_UNUSED(e);
    lv_subject_set_int(subject_temp_target, lv_subject_get_int(subject_temp_target) - 5);
}

static void temp_dial_set_subject_cb_2(lv_event_t * e)
{
    LV_UNUSED(e);
    lv_subject_set_int(subject_temp_target, lv_subject_get_int(subject_temp_target) + 5);
}

