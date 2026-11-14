/**
 * @file nav_button_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "nav_button_gen.h"
#include "../lvgl_ui_project.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
    /* <prop bindable="true">: a create() parameter AND an owned subject */
    lv_subject_t * active;
} nav_button_t;

/***********************
 *  STATIC VARIABLES
 **********************/

/***********************
 *  STATIC PROTOTYPES
 **********************/

static uint32_t nav_button_get_instance_event;
static void nav_button_get_instance_cb(lv_event_t * e);
static nav_button_t * nav_button_get_instance(lv_obj_t * obj);
static void nav_button_destroy_instance(nav_button_t * inst);
static void nav_button_delete_cb(lv_event_t * e);
static void nav_button_lv_button_0_checked_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void nav_button_lv_button_0_style_bg_color_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void nav_button_lv_image_0_style_image_recolor_binding_cb(lv_observer_t * observer, lv_subject_t * subject);

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * nav_button_create(lv_obj_t * parent, const void * icon, bool active)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    if(nav_button_get_instance_event == 0) nav_button_get_instance_event = lv_event_register_id();
    nav_button_t * inst = lv_malloc(sizeof(nav_button_t));
    lv_memzero(inst, sizeof(nav_button_t));
    inst->active = lv_subject_create(LV_SUBJECT_TYPE_INT);
    lv_subject_set_int(inst->active, active);

    #if LVGL_UI_PROJECT_CHECK_COMPILE_TARGET(LVGL_UI_PROJECT_TARGET_ALL)
    if (lvgl_ui_project_check_target(LVGL_UI_PROJECT_TARGET_ALL)) {
        lv_obj_t * lv_button_0 = lv_button_create(parent);
        lv_obj_set_name_static(lv_button_0, "nav_button_#");
        lv_obj_add_event_cb(lv_button_0, nav_button_get_instance_cb, nav_button_get_instance_event, inst);
        lv_obj_set_width(lv_button_0, NAV_BUTTON_SIZE);
        lv_obj_set_height(lv_button_0, NAV_BUTTON_SIZE);
        lv_subject_add_observer_obj(inst->active, nav_button_lv_button_0_checked_binding_cb, lv_button_0, inst);
        lv_obj_set_style_bg_opa(lv_button_0, 0, 0);
        lv_obj_set_style_bg_opa(lv_button_0, (255 * 100 / 100), LV_STATE_CHECKED);
        lv_subject_add_observer_obj(subject_accent, nav_button_lv_button_0_style_bg_color_binding_cb, lv_button_0, NULL);

        lv_obj_add_style(lv_button_0, &style_button, 0);
        lv_obj_add_style(lv_button_0, &style_button_pressed, LV_STATE_PRESSED);
        lv_obj_t * lv_image_0 = lv_image_create(lv_button_0);
        lv_image_set_src(lv_image_0, icon);
        lv_obj_set_align(lv_image_0, LV_ALIGN_CENTER);
        lv_subject_add_observer_obj(inst->active, nav_button_lv_image_0_style_image_recolor_binding_cb, lv_image_0, inst);
        lv_obj_add_style(lv_image_0, &style_icon, 0);

        the_root = lv_button_0;
    }
    #endif

    if(the_root) lv_obj_add_event_cb(the_root, nav_button_delete_cb, LV_EVENT_DELETE, inst);
    else nav_button_destroy_instance(inst); /* no target matched, so nothing owns it */

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

void nav_button_set_active(lv_obj_t * obj, int32_t active)
{
    nav_button_t * inst = nav_button_get_instance(obj);
    if(inst) lv_subject_set_int(inst->active, active);
}

int32_t nav_button_get_active(lv_obj_t * obj)
{
    nav_button_t * inst = nav_button_get_instance(obj);
    return inst ? (int32_t)lv_subject_get_int(inst->active) : (int32_t)0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void nav_button_get_instance_cb(lv_event_t * e)
{
    void ** out = lv_event_get_param(e);
    *out = lv_event_get_user_data(e);
}

static nav_button_t * nav_button_get_instance(lv_obj_t * obj)
{
    nav_button_t * inst = NULL;
    for(lv_obj_t * o = obj; o && !inst; o = lv_obj_get_parent(o)) {
        lv_obj_send_event(o, nav_button_get_instance_event, &inst);
    }
    return inst;
}

static void nav_button_destroy_instance(nav_button_t * inst)
{
    lv_subject_delete(inst->active);
    lv_free(inst);
}

static void nav_button_delete_cb(lv_event_t * e)
{
    nav_button_destroy_instance(lv_event_get_user_data(e));
}

static void nav_button_lv_button_0_checked_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    nav_button_t * inst = lv_observer_get_user_data(observer);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    lv_obj_set_checked(obj, lv_subject_get_int(inst->active));
}

static void nav_button_lv_button_0_style_bg_color_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    lv_obj_set_style_bg_color(obj, lv_subject_get_color(subject_accent), LV_STATE_CHECKED);
}

static void nav_button_lv_image_0_style_image_recolor_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    nav_button_t * inst = lv_observer_get_user_data(observer);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    lv_obj_set_style_image_recolor(obj, lv_subject_get_int(inst->active) ? COLOR_ON_ACCENT : COLOR_TEXT_MUTED, 0);
}

