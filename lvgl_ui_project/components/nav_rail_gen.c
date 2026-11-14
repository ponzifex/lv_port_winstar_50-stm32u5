/**
 * @file nav_rail_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "nav_rail_gen.h"
#include "../lvgl_ui_project.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
    /* <variant>: the option index, so a binding can follow it */
    lv_subject_t * active;
} nav_rail_t;

/***********************
 *  STATIC VARIABLES
 **********************/

/***********************
 *  STATIC PROTOTYPES
 **********************/

static uint32_t nav_rail_get_instance_event;
static void nav_rail_get_instance_cb(lv_event_t * e);
static nav_rail_t * nav_rail_get_instance(lv_obj_t * obj);
static void nav_rail_destroy_instance(nav_rail_t * inst);
static void nav_rail_delete_cb(lv_event_t * e);
static void nav_rail_nav_button_0_active_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void nav_rail_nav_button_1_active_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void nav_rail_nav_button_2_active_binding_cb(lv_observer_t * observer, lv_subject_t * subject);

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * nav_rail_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    if(nav_rail_get_instance_event == 0) nav_rail_get_instance_event = lv_event_register_id();
    nav_rail_t * inst = lv_malloc(sizeof(nav_rail_t));
    lv_memzero(inst, sizeof(nav_rail_t));
    inst->active = lv_subject_create(LV_SUBJECT_TYPE_INT);
    lv_subject_set_int(inst->active, NAV_RAIL_ACTIVE_HOME);

    #if LVGL_UI_PROJECT_CHECK_COMPILE_TARGET(LVGL_UI_PROJECT_TARGET_ALL)
    if (lvgl_ui_project_check_target(LVGL_UI_PROJECT_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(parent);
        lv_obj_set_name_static(lv_obj_0, "nav_rail_#");
        lv_obj_add_event_cb(lv_obj_0, nav_rail_get_instance_cb, nav_rail_get_instance_event, inst);
        lv_obj_set_width(lv_obj_0, NAV_RAIL_WIDTH);
        lv_obj_set_height(lv_obj_0, lv_pct(100));
        lv_obj_set_flex_flow(lv_obj_0, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_scrollable(lv_obj_0, false);
        lv_obj_set_style_bg_color(lv_obj_0, COLOR_PANEL, 0);
        lv_obj_set_style_bg_opa(lv_obj_0, (255 * 100 / 100), 0);
        lv_obj_set_style_radius(lv_obj_0, 0, 0);
        lv_obj_set_style_border_width(lv_obj_0, 0, 0);
        lv_obj_set_style_pad_ver(lv_obj_0, SPACE_XL, 0);
        lv_obj_set_style_pad_gap(lv_obj_0, SPACE_XL, 0);
        lv_obj_set_style_flex_main_place(lv_obj_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(lv_obj_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(lv_obj_0, LV_FLEX_ALIGN_CENTER, 0);

        lv_obj_t * nav_button_0 = nav_button_create(lv_obj_0, icon_house, lv_subject_get_int(inst->active) == NAV_RAIL_ACTIVE_HOME);
        lv_subject_add_observer_obj(inst->active, nav_rail_nav_button_0_active_binding_cb, nav_button_0, inst);
        lv_obj_add_screen_load_event(nav_button_0, LV_EVENT_CLICKED, home, LV_SCREEN_LOAD_ANIM_FADE_IN, 200, 0);

        lv_obj_t * nav_button_1 = nav_button_create(lv_obj_0, icon_layout_grid, lv_subject_get_int(inst->active) == NAV_RAIL_ACTIVE_ROOMS);
        lv_subject_add_observer_obj(inst->active, nav_rail_nav_button_1_active_binding_cb, nav_button_1, inst);
        lv_obj_add_screen_load_event(nav_button_1, LV_EVENT_CLICKED, rooms, LV_SCREEN_LOAD_ANIM_FADE_IN, 200, 0);

        lv_obj_t * nav_button_2 = nav_button_create(lv_obj_0, icon_settings, lv_subject_get_int(inst->active) == NAV_RAIL_ACTIVE_SETTINGS);
        lv_subject_add_observer_obj(inst->active, nav_rail_nav_button_2_active_binding_cb, nav_button_2, inst);
        lv_obj_add_screen_load_event(nav_button_2, LV_EVENT_CLICKED, settings, LV_SCREEN_LOAD_ANIM_FADE_IN, 200, 0);

        the_root = lv_obj_0;
    }
    #endif

    if(the_root) lv_obj_add_event_cb(the_root, nav_rail_delete_cb, LV_EVENT_DELETE, inst);
    else nav_rail_destroy_instance(inst); /* no target matched, so nothing owns it */

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

void nav_rail_set_active(lv_obj_t * obj, nav_rail_active_t active)
{
    nav_rail_t * inst = nav_rail_get_instance(obj);
    if(inst) lv_subject_set_int(inst->active, active);
}

nav_rail_active_t nav_rail_get_active(lv_obj_t * obj)
{
    nav_rail_t * inst = nav_rail_get_instance(obj);
    return inst ? (nav_rail_active_t)lv_subject_get_int(inst->active) : (nav_rail_active_t)0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void nav_rail_get_instance_cb(lv_event_t * e)
{
    void ** out = lv_event_get_param(e);
    *out = lv_event_get_user_data(e);
}

static nav_rail_t * nav_rail_get_instance(lv_obj_t * obj)
{
    nav_rail_t * inst = NULL;
    for(lv_obj_t * o = obj; o && !inst; o = lv_obj_get_parent(o)) {
        lv_obj_send_event(o, nav_rail_get_instance_event, &inst);
    }
    return inst;
}

static void nav_rail_destroy_instance(nav_rail_t * inst)
{
    lv_subject_delete(inst->active);
    lv_free(inst);
}

static void nav_rail_delete_cb(lv_event_t * e)
{
    nav_rail_destroy_instance(lv_event_get_user_data(e));
}

static void nav_rail_nav_button_0_active_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    nav_rail_t * inst = lv_observer_get_user_data(observer);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    nav_button_set_active(obj, lv_subject_get_int(inst->active) == NAV_RAIL_ACTIVE_HOME);
}

static void nav_rail_nav_button_1_active_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    nav_rail_t * inst = lv_observer_get_user_data(observer);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    nav_button_set_active(obj, lv_subject_get_int(inst->active) == NAV_RAIL_ACTIVE_ROOMS);
}

static void nav_rail_nav_button_2_active_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    nav_rail_t * inst = lv_observer_get_user_data(observer);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    nav_button_set_active(obj, lv_subject_get_int(inst->active) == NAV_RAIL_ACTIVE_SETTINGS);
}

