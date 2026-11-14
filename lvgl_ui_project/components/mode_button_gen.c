/**
 * @file mode_button_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "mode_button_gen.h"
#include "../lvgl_ui_project.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
    /* A plain <prop> a binding froze. The runtime inlines it, because it
     * re-parses the view per instance; the generator compiles once, so the value
     * is kept here and read back in the callback. A plain field, not a subject:
     * nothing ever notifies on it. */
    int32_t value_snapshot;
} mode_button_t;

/***********************
 *  STATIC VARIABLES
 **********************/

/***********************
 *  STATIC PROTOTYPES
 **********************/

static void mode_button_destroy_instance(mode_button_t * inst);
static void mode_button_delete_cb(lv_event_t * e);
static void mode_button_lv_button_0_checked_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void mode_button_lv_button_0_style_bg_color_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void mode_button_lv_image_0_style_image_recolor_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void mode_button_lv_label_0_style_text_color_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void mode_button_set_subject_cb(lv_event_t * e);

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * mode_button_create(lv_obj_t * parent, const void * icon, const char * text, int32_t value)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    mode_button_t * inst = lv_malloc(sizeof(mode_button_t));
    lv_memzero(inst, sizeof(mode_button_t));
    inst->value_snapshot = value;

    #if LVGL_UI_PROJECT_CHECK_COMPILE_TARGET(LVGL_UI_PROJECT_TARGET_ALL)
    if (lvgl_ui_project_check_target(LVGL_UI_PROJECT_TARGET_ALL)) {
        lv_obj_t * lv_button_0 = lv_button_create(parent);
        lv_obj_set_name_static(lv_button_0, "mode_button_#");
        lv_obj_set_height(lv_button_0, lv_pct(100));
        lv_obj_set_flex_grow(lv_button_0, 1);
        lv_obj_set_flex_flow(lv_button_0, LV_FLEX_FLOW_COLUMN);
        lv_subject_add_observer_obj(subject_mode, mode_button_lv_button_0_checked_binding_cb, lv_button_0, inst);
        lv_obj_set_style_pad_gap(lv_button_0, SPACE_XS, 0);
        lv_obj_set_style_flex_main_place(lv_button_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(lv_button_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(lv_button_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_subject_add_observer_obj(subject_accent, mode_button_lv_button_0_style_bg_color_binding_cb, lv_button_0, NULL);

        lv_obj_add_style(lv_button_0, &style_button, 0);
        lv_obj_add_style(lv_button_0, &style_button_pressed, LV_STATE_PRESSED);
        lv_obj_add_style(lv_button_0, &style_button_checked, LV_STATE_CHECKED);
        lv_obj_t * lv_image_0 = lv_image_create(lv_button_0);
        lv_image_set_src(lv_image_0, icon);
        lv_subject_add_observer_obj(subject_mode, mode_button_lv_image_0_style_image_recolor_binding_cb, lv_image_0, inst);
        lv_obj_add_style(lv_image_0, &style_icon, 0);

        lv_obj_t * lv_label_0 = lv_label_create(lv_button_0);
        lv_label_set_text(lv_label_0, text);
        lv_subject_add_observer_obj(subject_mode, mode_button_lv_label_0_style_text_color_binding_cb, lv_label_0, inst);

        lv_obj_add_event_cb(lv_button_0, mode_button_set_subject_cb, LV_EVENT_CLICKED, inst);

        the_root = lv_button_0;
    }
    #endif

    if(the_root) lv_obj_add_event_cb(the_root, mode_button_delete_cb, LV_EVENT_DELETE, inst);
    else mode_button_destroy_instance(inst); /* no target matched, so nothing owns it */

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void mode_button_destroy_instance(mode_button_t * inst)
{
    lv_free(inst);
}

static void mode_button_delete_cb(lv_event_t * e)
{
    mode_button_destroy_instance(lv_event_get_user_data(e));
}

static void mode_button_lv_button_0_checked_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    mode_button_t * inst = lv_observer_get_user_data(observer);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    lv_obj_set_checked(obj, lv_subject_get_int(subject_mode) == inst->value_snapshot);
}

static void mode_button_lv_button_0_style_bg_color_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    lv_obj_set_style_bg_color(obj, lv_subject_get_color(subject_accent), LV_STATE_CHECKED);
}

static void mode_button_lv_image_0_style_image_recolor_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    mode_button_t * inst = lv_observer_get_user_data(observer);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    lv_obj_set_style_image_recolor(obj, lv_subject_get_int(subject_mode) == inst->value_snapshot ? COLOR_ON_ACCENT : COLOR_TEXT, 0);
}

static void mode_button_lv_label_0_style_text_color_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    mode_button_t * inst = lv_observer_get_user_data(observer);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    lv_obj_set_style_text_color(obj, lv_subject_get_int(subject_mode) == inst->value_snapshot ? COLOR_ON_ACCENT : COLOR_TEXT, 0);
}

static void mode_button_set_subject_cb(lv_event_t * e)
{
    mode_button_t * inst = lv_event_get_user_data(e);
    lv_subject_set_int(subject_mode, inst->value_snapshot);
}

