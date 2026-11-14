/**
 * @file fan_selector_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "fan_selector_gen.h"
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

static void fan_selector_choice_button_0_selected_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void fan_selector_set_subject_cb(lv_event_t * e);
static void fan_selector_choice_button_1_selected_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void fan_selector_set_subject_cb_2(lv_event_t * e);
static void fan_selector_choice_button_2_selected_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void fan_selector_set_subject_cb_3(lv_event_t * e);
static void fan_selector_choice_button_3_selected_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void fan_selector_set_subject_cb_4(lv_event_t * e);

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * fan_selector_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if LVGL_UI_PROJECT_CHECK_COMPILE_TARGET(LVGL_UI_PROJECT_TARGET_ALL)
    if (lvgl_ui_project_check_target(LVGL_UI_PROJECT_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(parent);
        lv_obj_set_name_static(lv_obj_0, "fan_selector_#");
        lv_obj_set_width(lv_obj_0, lv_pct(100));
        lv_obj_set_height(lv_obj_0, LV_SIZE_CONTENT);
        lv_obj_set_flex_flow(lv_obj_0, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_pad_gap(lv_obj_0, SPACE_SM, 0);

        lv_obj_add_style(lv_obj_0, &style_box, 0);
        lv_obj_t * choice_button_0 = choice_button_create(lv_obj_0, "Auto", lv_subject_get_int(subject_fan) == 0);
        lv_subject_add_observer_obj(subject_fan, fan_selector_choice_button_0_selected_binding_cb, choice_button_0, NULL);
        lv_obj_add_event_cb(choice_button_0, fan_selector_set_subject_cb, LV_EVENT_CLICKED, NULL);

        lv_obj_t * choice_button_1 = choice_button_create(lv_obj_0, "Low", lv_subject_get_int(subject_fan) == 1);
        lv_subject_add_observer_obj(subject_fan, fan_selector_choice_button_1_selected_binding_cb, choice_button_1, NULL);
        lv_obj_add_event_cb(choice_button_1, fan_selector_set_subject_cb_2, LV_EVENT_CLICKED, NULL);

        lv_obj_t * choice_button_2 = choice_button_create(lv_obj_0, "Med", lv_subject_get_int(subject_fan) == 2);
        lv_subject_add_observer_obj(subject_fan, fan_selector_choice_button_2_selected_binding_cb, choice_button_2, NULL);
        lv_obj_add_event_cb(choice_button_2, fan_selector_set_subject_cb_3, LV_EVENT_CLICKED, NULL);

        lv_obj_t * choice_button_3 = choice_button_create(lv_obj_0, "High", lv_subject_get_int(subject_fan) == 3);
        lv_subject_add_observer_obj(subject_fan, fan_selector_choice_button_3_selected_binding_cb, choice_button_3, NULL);
        lv_obj_add_event_cb(choice_button_3, fan_selector_set_subject_cb_4, LV_EVENT_CLICKED, NULL);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void fan_selector_choice_button_0_selected_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    choice_button_set_selected(obj, lv_subject_get_int(subject_fan) == 0);
}

static void fan_selector_set_subject_cb(lv_event_t * e)
{
    LV_UNUSED(e);
    lv_subject_set_int(subject_fan, 0);
}

static void fan_selector_choice_button_1_selected_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    choice_button_set_selected(obj, lv_subject_get_int(subject_fan) == 1);
}

static void fan_selector_set_subject_cb_2(lv_event_t * e)
{
    LV_UNUSED(e);
    lv_subject_set_int(subject_fan, 1);
}

static void fan_selector_choice_button_2_selected_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    choice_button_set_selected(obj, lv_subject_get_int(subject_fan) == 2);
}

static void fan_selector_set_subject_cb_3(lv_event_t * e)
{
    LV_UNUSED(e);
    lv_subject_set_int(subject_fan, 2);
}

static void fan_selector_choice_button_3_selected_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    choice_button_set_selected(obj, lv_subject_get_int(subject_fan) == 3);
}

static void fan_selector_set_subject_cb_4(lv_event_t * e)
{
    LV_UNUSED(e);
    lv_subject_set_int(subject_fan, 3);
}

