/**
 * @file choice_button_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "choice_button_gen.h"
#include "../lvgl_ui_project.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
    /* <prop bindable="true">: a create() parameter AND an owned subject */
    lv_subject_t * selected;
} choice_button_t;

/***********************
 *  STATIC VARIABLES
 **********************/

/***********************
 *  STATIC PROTOTYPES
 **********************/

static uint32_t choice_button_get_instance_event;
static void choice_button_get_instance_cb(lv_event_t * e);
static choice_button_t * choice_button_get_instance(lv_obj_t * obj);
static void choice_button_destroy_instance(choice_button_t * inst);
static void choice_button_delete_cb(lv_event_t * e);
static void choice_button_lv_button_0_checked_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void choice_button_lv_button_0_style_bg_color_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void choice_button_lv_label_0_style_text_color_binding_cb(lv_observer_t * observer, lv_subject_t * subject);

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * choice_button_create(lv_obj_t * parent, const char * text, bool selected)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    if(choice_button_get_instance_event == 0) choice_button_get_instance_event = lv_event_register_id();
    choice_button_t * inst = lv_malloc(sizeof(choice_button_t));
    lv_memzero(inst, sizeof(choice_button_t));
    inst->selected = lv_subject_create(LV_SUBJECT_TYPE_INT);
    lv_subject_set_int(inst->selected, selected);

    #if LVGL_UI_PROJECT_CHECK_COMPILE_TARGET(LVGL_UI_PROJECT_TARGET_ALL)
    if (lvgl_ui_project_check_target(LVGL_UI_PROJECT_TARGET_ALL)) {
        lv_obj_t * lv_button_0 = lv_button_create(parent);
        lv_obj_set_name_static(lv_button_0, "choice_button_#");
        lv_obj_add_event_cb(lv_button_0, choice_button_get_instance_cb, choice_button_get_instance_event, inst);
        lv_obj_set_height(lv_button_0, TOUCH_MIN);
        lv_obj_set_flex_grow(lv_button_0, 1);
        lv_subject_add_observer_obj(inst->selected, choice_button_lv_button_0_checked_binding_cb, lv_button_0, inst);
        lv_subject_add_observer_obj(subject_accent, choice_button_lv_button_0_style_bg_color_binding_cb, lv_button_0, NULL);

        lv_obj_add_style(lv_button_0, &style_button, 0);
        lv_obj_add_style(lv_button_0, &style_button_pressed, LV_STATE_PRESSED);
        lv_obj_add_style(lv_button_0, &style_button_checked, LV_STATE_CHECKED);
        lv_obj_t * lv_label_0 = lv_label_create(lv_button_0);
        lv_label_set_text(lv_label_0, text);
        lv_obj_set_align(lv_label_0, LV_ALIGN_CENTER);
        lv_subject_add_observer_obj(inst->selected, choice_button_lv_label_0_style_text_color_binding_cb, lv_label_0, inst);

        the_root = lv_button_0;
    }
    #endif

    if(the_root) lv_obj_add_event_cb(the_root, choice_button_delete_cb, LV_EVENT_DELETE, inst);
    else choice_button_destroy_instance(inst); /* no target matched, so nothing owns it */

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

void choice_button_set_selected(lv_obj_t * obj, int32_t selected)
{
    choice_button_t * inst = choice_button_get_instance(obj);
    if(inst) lv_subject_set_int(inst->selected, selected);
}

int32_t choice_button_get_selected(lv_obj_t * obj)
{
    choice_button_t * inst = choice_button_get_instance(obj);
    return inst ? (int32_t)lv_subject_get_int(inst->selected) : (int32_t)0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void choice_button_get_instance_cb(lv_event_t * e)
{
    void ** out = lv_event_get_param(e);
    *out = lv_event_get_user_data(e);
}

static choice_button_t * choice_button_get_instance(lv_obj_t * obj)
{
    choice_button_t * inst = NULL;
    for(lv_obj_t * o = obj; o && !inst; o = lv_obj_get_parent(o)) {
        lv_obj_send_event(o, choice_button_get_instance_event, &inst);
    }
    return inst;
}

static void choice_button_destroy_instance(choice_button_t * inst)
{
    lv_subject_delete(inst->selected);
    lv_free(inst);
}

static void choice_button_delete_cb(lv_event_t * e)
{
    choice_button_destroy_instance(lv_event_get_user_data(e));
}

static void choice_button_lv_button_0_checked_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    choice_button_t * inst = lv_observer_get_user_data(observer);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    lv_obj_set_checked(obj, lv_subject_get_int(inst->selected));
}

static void choice_button_lv_button_0_style_bg_color_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    lv_obj_set_style_bg_color(obj, lv_subject_get_color(subject_accent), LV_STATE_CHECKED);
}

static void choice_button_lv_label_0_style_text_color_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    choice_button_t * inst = lv_observer_get_user_data(observer);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    lv_obj_set_style_text_color(obj, lv_subject_get_int(inst->selected) ? COLOR_ON_ACCENT : COLOR_TEXT, 0);
}

