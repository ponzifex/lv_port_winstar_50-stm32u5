/**
 * @file settings_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "settings_gen.h"
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

static void settings_choice_button_0_selected_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void settings_set_subject_cb(lv_event_t * e);
static void settings_choice_button_1_selected_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void settings_set_subject_cb_2(lv_event_t * e);
static void settings_lv_slider_0_style_bg_color_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void settings_lv_label_0_text_binding_cb(lv_observer_t * observer, lv_subject_t * subject);

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * settings_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");

    static bool screen_created = false;
    if (screen_created) {
        LV_LOG_WARN("`settings` is already initialized as a permanent screen. Returning with no change.");
        return settings;
    }

    static lv_style_t style_slider_track;
    static lv_style_t style_slider_knob;

    static bool style_inited = false;

    if (!style_inited) {
        /*Init all styles*/
        lv_style_init(&style_slider_track);
        lv_style_init(&style_slider_knob);

        lv_style_set_bg_color(&style_slider_track, COLOR_PANEL_HIGH);
        lv_style_set_bg_opa(&style_slider_track, (255 * 100 / 100));
        lv_style_set_radius(&style_slider_track, RADIUS_ROUND);
        lv_style_set_bg_color(&style_slider_knob, COLOR_TEXT);
        lv_style_set_bg_opa(&style_slider_knob, (255 * 100 / 100));
        lv_style_set_pad_all(&style_slider_knob, 8);
        lv_style_set_radius(&style_slider_knob, RADIUS_ROUND);

        style_inited = true;
    }


    lv_obj_t * the_root = NULL;

    #if LVGL_UI_PROJECT_CHECK_COMPILE_TARGET(LVGL_UI_PROJECT_TARGET_ALL)
    if (lvgl_ui_project_check_target(LVGL_UI_PROJECT_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = settings;
        lv_obj_set_name_static(lv_obj_0, "settings_#");
        lv_obj_set_flex_flow(lv_obj_0, LV_FLEX_FLOW_ROW);
        lv_obj_set_scrollable(lv_obj_0, false);

        lv_obj_add_style(lv_obj_0, &style_screen, 0);
        lv_obj_t * nav_rail_0 = nav_rail_create(lv_obj_0);
        nav_rail_set_active(nav_rail_0, NAV_RAIL_ACTIVE_SETTINGS);

        lv_obj_t * lv_obj_1 = lv_obj_create(lv_obj_0);
        lv_obj_set_flex_grow(lv_obj_1, 1);
        lv_obj_set_height(lv_obj_1, lv_pct(100));
        lv_obj_set_flex_flow(lv_obj_1, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_scrollable(lv_obj_1, false);
        lv_obj_set_style_pad_all(lv_obj_1, SPACE_XL, 0);
        lv_obj_set_style_pad_gap(lv_obj_1, SPACE_LG, 0);
        lv_obj_add_style(lv_obj_1, &style_box, 0);
        top_bar_create(lv_obj_1, "Settings");

        lv_obj_t * settings_row_0 = settings_row_create(lv_obj_1, "Temperature units", "Used on every screen");
        lv_obj_t * settings_row_0_control = settings_row_get_control(settings_row_0);
        if (settings_row_0_control) {
        lv_obj_t * choice_button_0 = choice_button_create(settings_row_0_control, "°C", lv_subject_get_int(subject_unit_f) == 0);
        lv_obj_set_width(choice_button_0, 88);
        lv_obj_set_flex_grow(choice_button_0, 0);
        lv_subject_add_observer_obj(subject_unit_f, settings_choice_button_0_selected_binding_cb, choice_button_0, NULL);
        lv_obj_add_event_cb(choice_button_0, settings_set_subject_cb, LV_EVENT_CLICKED, NULL);

        lv_obj_t * choice_button_1 = choice_button_create(settings_row_0_control, "°F", lv_subject_get_int(subject_unit_f) == 1);
        lv_obj_set_width(choice_button_1, 88);
        lv_obj_set_flex_grow(choice_button_1, 0);
        lv_subject_add_observer_obj(subject_unit_f, settings_choice_button_1_selected_binding_cb, choice_button_1, NULL);
        lv_obj_add_event_cb(choice_button_1, settings_set_subject_cb_2, LV_EVENT_CLICKED, NULL);
        } else {
        LV_LOG_WARN("`control` slot of `settings_row_0` doesn't exist");
        }

        lv_obj_t * settings_row_1 = settings_row_create(lv_obj_1, "Display brightness", "Backlight level");
        lv_obj_t * settings_row_1_control = settings_row_get_control(settings_row_1);
        if (settings_row_1_control) {
        lv_obj_t * lv_slider_0 = lv_slider_create(settings_row_1_control);
        lv_obj_set_width(lv_slider_0, 240);
        lv_obj_set_height(lv_slider_0, 10);
        lv_slider_set_min_value(lv_slider_0, 10);
        lv_slider_set_max_value(lv_slider_0, 100);
        lv_slider_bind_value(lv_slider_0, subject_brightness);
        lv_subject_add_observer_obj(subject_accent, settings_lv_slider_0_style_bg_color_binding_cb, lv_slider_0, NULL);
        lv_obj_add_style(lv_slider_0, &style_slider_track, 0);
        lv_obj_add_style(lv_slider_0, &style_slider_track, LV_PART_INDICATOR);
        lv_obj_add_style(lv_slider_0, &style_slider_knob, LV_PART_KNOB);

        lv_obj_t * lv_label_0 = lv_label_create(settings_row_1_control);
        lv_subject_add_observer_obj(subject_brightness, settings_lv_label_0_text_binding_cb, lv_label_0, NULL);
        lv_obj_set_width(lv_label_0, 56);
        lv_obj_set_style_text_align(lv_label_0, LV_TEXT_ALIGN_RIGHT, 0);
        } else {
        LV_LOG_WARN("`control` slot of `settings_row_1` doesn't exist");
        }

        lv_obj_t * lv_obj_2 = lv_obj_create(lv_obj_1);
        lv_obj_set_width(lv_obj_2, lv_pct(100));
        lv_obj_set_flex_grow(lv_obj_2, 1);
        lv_obj_set_flex_flow(lv_obj_2, LV_FLEX_FLOW_ROW);
        lv_obj_set_scrollable(lv_obj_2, false);
        lv_obj_set_style_pad_gap(lv_obj_2, SPACE_XL, 0);
        lv_obj_set_style_flex_cross_place(lv_obj_2, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_add_style(lv_obj_2, &style_card, 0);
        lv_obj_t * lv_obj_3 = lv_obj_create(lv_obj_2);
        lv_obj_set_width(lv_obj_3, LV_SIZE_CONTENT);
        lv_obj_set_height(lv_obj_3, LV_SIZE_CONTENT);
        lv_obj_set_flex_flow(lv_obj_3, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_pad_gap(lv_obj_3, SPACE_MD, 0);
        lv_obj_set_style_flex_cross_place(lv_obj_3, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_add_style(lv_obj_3, &style_box, 0);
        lv_obj_t * lv_image_0 = lv_image_create(lv_obj_3);
        lv_image_set_src(lv_image_0, img_logo_winstar);

        lv_obj_t * lv_obj_4 = lv_obj_create(lv_obj_2);
        lv_obj_set_flex_grow(lv_obj_4, 1);
        lv_obj_set_height(lv_obj_4, LV_SIZE_CONTENT);
        lv_obj_set_flex_flow(lv_obj_4, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_pad_gap(lv_obj_4, SPACE_XS, 0);
        lv_obj_add_style(lv_obj_4, &style_box, 0);
        lv_obj_t * lv_label_1 = lv_label_create(lv_obj_4);
        lv_label_set_text(lv_label_1, "Smart Thermostat Demo");
        lv_obj_set_style_text_font(lv_label_1, font_h2, 0);

        lv_obj_t * lv_label_2 = lv_label_create(lv_obj_4);
        lv_label_set_text(lv_label_2, "Winstar 5\" touch display · 800×480");
        lv_obj_add_style(lv_label_2, &style_text_muted, 0);

        lv_obj_t * lv_label_3 = lv_label_create(lv_obj_4);
        lv_label_set_text(lv_label_3, "STM32U599 · LVGL 9.6");
        lv_obj_add_style(lv_label_3, &style_text_muted, 0);

        lv_obj_t * lv_image_1 = lv_image_create(lv_obj_4);
        lv_image_set_src(lv_image_1, img_logo_lvgl);
        lv_obj_set_style_margin_top(lv_image_1, SPACE_MD, 0);

        the_root = lv_obj_0;
    }
    #endif

    if (the_root) screen_created = true;

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void settings_choice_button_0_selected_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    choice_button_set_selected(obj, lv_subject_get_int(subject_unit_f) == 0);
}

static void settings_set_subject_cb(lv_event_t * e)
{
    LV_UNUSED(e);
    lv_subject_set_int(subject_unit_f, 0);
}

static void settings_choice_button_1_selected_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    choice_button_set_selected(obj, lv_subject_get_int(subject_unit_f) == 1);
}

static void settings_set_subject_cb_2(lv_event_t * e)
{
    LV_UNUSED(e);
    lv_subject_set_int(subject_unit_f, 1);
}

static void settings_lv_slider_0_style_bg_color_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    lv_obj_set_style_bg_color(obj, lv_subject_get_color(subject_accent), LV_PART_INDICATOR);
}

static void settings_lv_label_0_text_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    char eval_buf_1[LV_XML_EVAL_STRING_BUF_SIZE];
    lv_snprintf(eval_buf_1, sizeof(eval_buf_1), "%d%s", (int)(lv_subject_get_int(subject_brightness)), "%");
    lv_label_set_text(obj, eval_buf_1);
}

