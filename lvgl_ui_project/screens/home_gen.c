/**
 * @file home_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "home_gen.h"
#include "../lvgl_ui_project.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
    /* One bit per `{…}` trigger, so only a false-to-true edge fires */
    uint8_t set_subject_event_lv_obj_0_prev : 1;
    uint8_t set_subject_event_lv_obj_0_2_prev : 1;
    uint8_t set_subject_event_lv_obj_0_3_prev : 1;
    uint8_t set_subject_event_lv_obj_0_4_prev : 1;
} home_t;

/***********************
 *  STATIC VARIABLES
 **********************/

/***********************
 *  STATIC PROTOTYPES
 **********************/

static void home_destroy_instance(home_t * inst);
static void home_delete_cb(lv_event_t * e);
/* Private event code for a condition trigger. One per XML element, never per
 * instance, so it cannot run away. */
static lv_event_code_t home_set_subject_event_trigger_code;
/* Private event code for a condition trigger. One per XML element, never per
 * instance, so it cannot run away. */
static lv_event_code_t home_set_subject_event_trigger_code_2;
/* Private event code for a condition trigger. One per XML element, never per
 * instance, so it cannot run away. */
static lv_event_code_t home_set_subject_event_trigger_code_3;
/* Private event code for a condition trigger. One per XML element, never per
 * instance, so it cannot run away. */
static lv_event_code_t home_set_subject_event_trigger_code_4;
static void home_set_subject_cb(lv_event_t * e);
static void home_lv_obj_0_set_subject_event_cond_cb(lv_observer_t * observer, lv_subject_t * subject);
static void home_set_subject_cb_2(lv_event_t * e);
static void home_lv_obj_0_set_subject_event_cond_cb_2(lv_observer_t * observer, lv_subject_t * subject);
static void home_set_subject_cb_3(lv_event_t * e);
static void home_lv_obj_0_set_subject_event_cond_cb_3(lv_observer_t * observer, lv_subject_t * subject);
static void home_set_subject_cb_4(lv_event_t * e);
static void home_lv_obj_0_set_subject_event_cond_cb_4(lv_observer_t * observer, lv_subject_t * subject);
static void home_top_bar_0_title_binding_cb(lv_observer_t * observer, lv_subject_t * subject);

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * home_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");

    static bool screen_created = false;
    if (screen_created) {
        LV_LOG_WARN("`home` is already initialized as a permanent screen. Returning with no change.");
        return home;
    }


    lv_obj_t * the_root = NULL;

    home_t * inst = lv_malloc(sizeof(home_t));
    lv_memzero(inst, sizeof(home_t));

    #if LVGL_UI_PROJECT_CHECK_COMPILE_TARGET(LVGL_UI_PROJECT_TARGET_ALL)
    if (lvgl_ui_project_check_target(LVGL_UI_PROJECT_TARGET_ALL)) {
        char eval_buf_1[LV_XML_EVAL_STRING_BUF_SIZE];

        lv_obj_t * lv_obj_0 = home;
        lv_obj_set_name_static(lv_obj_0, "home_#");
        lv_obj_set_flex_flow(lv_obj_0, LV_FLEX_FLOW_ROW);
        lv_obj_set_scrollable(lv_obj_0, false);

        lv_obj_add_style(lv_obj_0, &style_screen, 0);
        if(home_set_subject_event_trigger_code == 0) home_set_subject_event_trigger_code = lv_event_register_id();
        lv_obj_add_event_cb(lv_obj_0, home_set_subject_cb, home_set_subject_event_trigger_code, NULL);
        lv_subject_add_observer_obj(subject_mode, home_lv_obj_0_set_subject_event_cond_cb, lv_obj_0, inst);
        if(home_set_subject_event_trigger_code_2 == 0) home_set_subject_event_trigger_code_2 = lv_event_register_id();
        lv_obj_add_event_cb(lv_obj_0, home_set_subject_cb_2, home_set_subject_event_trigger_code_2, NULL);
        lv_subject_add_observer_obj(subject_mode, home_lv_obj_0_set_subject_event_cond_cb_2, lv_obj_0, inst);
        if(home_set_subject_event_trigger_code_3 == 0) home_set_subject_event_trigger_code_3 = lv_event_register_id();
        lv_obj_add_event_cb(lv_obj_0, home_set_subject_cb_3, home_set_subject_event_trigger_code_3, NULL);
        lv_subject_add_observer_obj(subject_mode, home_lv_obj_0_set_subject_event_cond_cb_3, lv_obj_0, inst);
        if(home_set_subject_event_trigger_code_4 == 0) home_set_subject_event_trigger_code_4 = lv_event_register_id();
        lv_obj_add_event_cb(lv_obj_0, home_set_subject_cb_4, home_set_subject_event_trigger_code_4, NULL);
        lv_subject_add_observer_obj(subject_mode, home_lv_obj_0_set_subject_event_cond_cb_4, lv_obj_0, inst);
        lv_obj_t * nav_rail_0 = nav_rail_create(lv_obj_0);
        nav_rail_set_active(nav_rail_0, NAV_RAIL_ACTIVE_HOME);

        lv_obj_t * lv_obj_1 = lv_obj_create(lv_obj_0);
        lv_obj_set_flex_grow(lv_obj_1, 1);
        lv_obj_set_height(lv_obj_1, lv_pct(100));
        lv_obj_set_flex_flow(lv_obj_1, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_scrollable(lv_obj_1, false);
        lv_obj_set_style_pad_all(lv_obj_1, SPACE_XL, 0);
        lv_obj_set_style_pad_gap(lv_obj_1, SPACE_LG, 0);
        lv_obj_add_style(lv_obj_1, &style_box, 0);
        lv_snprintf(eval_buf_1, sizeof(eval_buf_1), "%s%s%s%s", (lv_subject_get_int(subject_room) == 0 ? "Living room" : "") ? "true" : "false", (lv_subject_get_int(subject_room) == 1 ? "Bedroom" : "") ? "true" : "false", (lv_subject_get_int(subject_room) == 2 ? "Kitchen" : "") ? "true" : "false", (lv_subject_get_int(subject_room) == 3 ? "Office" : "") ? "true" : "false");
        lv_obj_t * top_bar_0 = top_bar_create(lv_obj_1, eval_buf_1);
        lv_subject_add_observer_obj(subject_room, home_top_bar_0_title_binding_cb, top_bar_0, NULL);

        lv_obj_t * lv_obj_2 = lv_obj_create(lv_obj_1);
        lv_obj_set_width(lv_obj_2, lv_pct(100));
        lv_obj_set_flex_grow(lv_obj_2, 1);
        lv_obj_set_flex_flow(lv_obj_2, LV_FLEX_FLOW_ROW);
        lv_obj_set_scrollable(lv_obj_2, false);
        lv_obj_set_style_pad_gap(lv_obj_2, SPACE_LG, 0);
        lv_obj_add_style(lv_obj_2, &style_box, 0);
        temp_dial_create(lv_obj_2);

        lv_obj_t * lv_obj_3 = lv_obj_create(lv_obj_2);
        lv_obj_set_flex_grow(lv_obj_3, 1);
        lv_obj_set_height(lv_obj_3, lv_pct(100));
        lv_obj_set_flex_flow(lv_obj_3, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_scrollable(lv_obj_3, false);
        lv_obj_set_style_pad_gap(lv_obj_3, SPACE_LG, 0);
        lv_obj_add_style(lv_obj_3, &style_box, 0);
        lv_obj_t * lv_obj_4 = lv_obj_create(lv_obj_3);
        lv_obj_set_width(lv_obj_4, lv_pct(100));
        lv_obj_set_flex_grow(lv_obj_4, 1);
        lv_obj_set_flex_flow(lv_obj_4, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_scrollable(lv_obj_4, false);
        lv_obj_set_style_pad_gap(lv_obj_4, SPACE_SM, 0);
        lv_obj_add_style(lv_obj_4, &style_card, 0);
        lv_obj_t * lv_label_0 = lv_label_create(lv_obj_4);
        lv_label_set_text(lv_label_0, "Mode");
        lv_obj_add_style(lv_label_0, &style_text_caption, 0);

        lv_obj_t * lv_obj_5 = lv_obj_create(lv_obj_4);
        lv_obj_set_width(lv_obj_5, lv_pct(100));
        lv_obj_set_flex_grow(lv_obj_5, 1);
        lv_obj_set_flex_flow(lv_obj_5, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_pad_gap(lv_obj_5, SPACE_SM, 0);
        lv_obj_add_style(lv_obj_5, &style_box, 0);
        mode_button_create(lv_obj_5, icon_flame, "Heat", 1);

        mode_button_create(lv_obj_5, icon_snowflake, "Cool", 2);

        lv_obj_t * lv_obj_6 = lv_obj_create(lv_obj_4);
        lv_obj_set_width(lv_obj_6, lv_pct(100));
        lv_obj_set_flex_grow(lv_obj_6, 1);
        lv_obj_set_flex_flow(lv_obj_6, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_pad_gap(lv_obj_6, SPACE_SM, 0);
        lv_obj_add_style(lv_obj_6, &style_box, 0);
        mode_button_create(lv_obj_6, icon_sun_snow, "Auto", 3);

        mode_button_create(lv_obj_6, icon_power, "Off", 0);

        lv_obj_t * lv_obj_7 = lv_obj_create(lv_obj_3);
        lv_obj_set_width(lv_obj_7, lv_pct(100));
        lv_obj_set_height(lv_obj_7, LV_SIZE_CONTENT);
        lv_obj_set_flex_flow(lv_obj_7, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_scrollable(lv_obj_7, false);
        lv_obj_set_style_pad_gap(lv_obj_7, SPACE_SM, 0);
        lv_obj_add_style(lv_obj_7, &style_card, 0);
        lv_obj_t * lv_label_1 = lv_label_create(lv_obj_7);
        lv_label_set_text(lv_label_1, "Fan");
        lv_obj_add_style(lv_label_1, &style_text_caption, 0);

        fan_selector_create(lv_obj_7);

        the_root = lv_obj_0;
    }
    #endif

    if(the_root) lv_obj_add_event_cb(the_root, home_delete_cb, LV_EVENT_DELETE, inst);
    else home_destroy_instance(inst); /* no target matched, so nothing owns it */

    if (the_root) screen_created = true;

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void home_destroy_instance(home_t * inst)
{
    lv_free(inst);
}

static void home_delete_cb(lv_event_t * e)
{
    home_destroy_instance(lv_event_get_user_data(e));
}

static void home_set_subject_cb(lv_event_t * e)
{
    LV_UNUSED(e);
    lv_subject_set_color(subject_accent, COLOR_OFF);
}

static void home_lv_obj_0_set_subject_event_cond_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    home_t * inst = lv_observer_get_user_data(observer);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    bool now = (lv_subject_get_int(subject_mode) == 0);
    if(now && !inst->set_subject_event_lv_obj_0_prev) lv_obj_send_event(obj, home_set_subject_event_trigger_code, NULL);
    inst->set_subject_event_lv_obj_0_prev = now;
}

static void home_set_subject_cb_2(lv_event_t * e)
{
    LV_UNUSED(e);
    lv_subject_set_color(subject_accent, COLOR_HEAT);
}

static void home_lv_obj_0_set_subject_event_cond_cb_2(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    home_t * inst = lv_observer_get_user_data(observer);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    bool now = (lv_subject_get_int(subject_mode) == 1);
    if(now && !inst->set_subject_event_lv_obj_0_2_prev) lv_obj_send_event(obj, home_set_subject_event_trigger_code_2, NULL);
    inst->set_subject_event_lv_obj_0_2_prev = now;
}

static void home_set_subject_cb_3(lv_event_t * e)
{
    LV_UNUSED(e);
    lv_subject_set_color(subject_accent, COLOR_COOL);
}

static void home_lv_obj_0_set_subject_event_cond_cb_3(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    home_t * inst = lv_observer_get_user_data(observer);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    bool now = (lv_subject_get_int(subject_mode) == 2);
    if(now && !inst->set_subject_event_lv_obj_0_3_prev) lv_obj_send_event(obj, home_set_subject_event_trigger_code_3, NULL);
    inst->set_subject_event_lv_obj_0_3_prev = now;
}

static void home_set_subject_cb_4(lv_event_t * e)
{
    LV_UNUSED(e);
    lv_subject_set_color(subject_accent, COLOR_AUTO);
}

static void home_lv_obj_0_set_subject_event_cond_cb_4(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    home_t * inst = lv_observer_get_user_data(observer);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    bool now = (lv_subject_get_int(subject_mode) == 3);
    if(now && !inst->set_subject_event_lv_obj_0_4_prev) lv_obj_send_event(obj, home_set_subject_event_trigger_code_4, NULL);
    inst->set_subject_event_lv_obj_0_4_prev = now;
}

static void home_top_bar_0_title_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    char eval_buf_1[LV_XML_EVAL_STRING_BUF_SIZE];
    lv_snprintf(eval_buf_1, sizeof(eval_buf_1), "%s%s%s%s", (lv_subject_get_int(subject_room) == 0 ? "Living room" : "") ? "true" : "false", (lv_subject_get_int(subject_room) == 1 ? "Bedroom" : "") ? "true" : "false", (lv_subject_get_int(subject_room) == 2 ? "Kitchen" : "") ? "true" : "false", (lv_subject_get_int(subject_room) == 3 ? "Office" : "") ? "true" : "false");
    top_bar_set_title(obj, eval_buf_1);
}

