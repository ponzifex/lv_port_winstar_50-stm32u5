/**
 * @file splash_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "splash_gen.h"
#include "../lvgl_ui_project.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
    /* Index is the <COMP>_TIMELINE_* enum. Kept here rather than the root's
     * user_data, which stays free for the user. */
    lv_anim_timeline_t ** timelines;
} splash_t;

/***********************
 *  STATIC VARIABLES
 **********************/

/***********************
 *  STATIC PROTOTYPES
 **********************/

static lv_anim_timeline_t * timeline_timeline_intro_create(lv_obj_t * obj);

static uint32_t splash_get_instance_event;
static void splash_get_instance_cb(lv_event_t * e);
static splash_t * splash_get_instance(lv_obj_t * obj);
static void splash_destroy_instance(splash_t * inst);
static void splash_delete_cb(lv_event_t * e);

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * splash_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    if(splash_get_instance_event == 0) splash_get_instance_event = lv_event_register_id();
    splash_t * inst = lv_malloc(sizeof(splash_t));
    lv_memzero(inst, sizeof(splash_t));

    #if LVGL_UI_PROJECT_CHECK_COMPILE_TARGET(LVGL_UI_PROJECT_TARGET_ALL)
    if (lvgl_ui_project_check_target(LVGL_UI_PROJECT_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
        lv_obj_set_name_static(lv_obj_0, "splash_#");
        lv_obj_add_event_cb(lv_obj_0, splash_get_instance_cb, splash_get_instance_event, inst);
        lv_obj_set_scrollable(lv_obj_0, false);
        lv_obj_set_style_bg_image_src(lv_obj_0, img_splash, 0);

        lv_obj_add_style(lv_obj_0, &style_screen, 0);
        lv_obj_t * logos = lv_obj_create(lv_obj_0);
        lv_obj_set_name(logos, "logos");
        lv_obj_set_x(logos, 72);
        lv_obj_set_y(logos, 104);
        lv_obj_set_width(logos, 282);
        lv_obj_set_height(logos, 196);
        lv_obj_set_flex_flow(logos, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_opa(logos, 0, 0);
        lv_obj_set_style_pad_gap(logos, SPACE_SM, 0);
        lv_obj_set_style_flex_main_place(logos, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(logos, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(logos, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_add_style(logos, &style_box, 0);
        lv_obj_t * lv_image_0 = lv_image_create(logos);
        lv_image_set_src(lv_image_0, img_logo_winstar_small);

        lv_obj_t * lv_label_0 = lv_label_create(logos);
        lv_label_set_text(lv_label_0, "powered by");
        lv_obj_add_style(lv_label_0, &style_text_caption, 0);

        lv_obj_t * lv_image_1 = lv_image_create(logos);
        lv_image_set_src(lv_image_1, img_logo_lvgl_small);

        lv_obj_add_screen_load_event(lv_obj_0, LV_EVENT_SCREEN_LOADED, home, LV_SCREEN_LOAD_ANIM_FADE_IN, 500, 2500);

        /* create animation timeline(s) */
        lv_anim_timeline_t ** at_array = lv_malloc(sizeof(lv_anim_timeline_t *) * _SPLASH_TIMELINE_CNT);
        at_array[SPLASH_TIMELINE_TIMELINE_INTRO] = timeline_timeline_intro_create(lv_obj_0);
        inst->timelines = at_array;

        lv_obj_add_play_timeline_event(lv_obj_0, LV_EVENT_SCREEN_LOADED, splash_get_timeline(lv_obj_0, SPLASH_TIMELINE_TIMELINE_INTRO), 0, false);

        the_root = lv_obj_0;
    }
    #endif

    if(the_root) lv_obj_add_event_cb(the_root, splash_delete_cb, LV_EVENT_DELETE, inst);
    else splash_destroy_instance(inst); /* no target matched, so nothing owns it */

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

lv_anim_timeline_t * splash_get_timeline(lv_obj_t * obj, splash_timeline_t timeline_id)
{
    if ((uint32_t)timeline_id >= _SPLASH_TIMELINE_CNT) {
        LV_LOG_WARN("splash has no timeline with %d ID", timeline_id);
        return NULL;
    }

    splash_t * inst = splash_get_instance(obj);
    return inst ? inst->timelines[timeline_id] : NULL;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/* Helper function to execute animations */
static void int_anim_exec_cb(lv_anim_t * a, int32_t v)
{
    uint32_t data = (lv_uintptr_t)lv_anim_get_user_data(a);
    lv_style_prop_t prop = data >> 24;
    lv_style_selector_t selector = data & 0x00ffffff;

    lv_style_value_t style_value;
    style_value.num = v;
    lv_obj_set_local_style_prop(a->var, prop, style_value, selector);
}

static lv_anim_timeline_t * timeline_timeline_intro_create(lv_obj_t * obj)
{
    lv_anim_timeline_t * at = lv_anim_timeline_create();
    lv_anim_timeline_t * at_to_merge = NULL;

    lv_anim_t a;
    uint32_t selector_and_prop;

    selector_and_prop = ((LV_STYLE_OPA & 0xff) << 24) | 0;
    lv_anim_init(&a);
    lv_anim_set_custom_exec_cb(&a, int_anim_exec_cb);
    lv_anim_set_var(&a, lv_obj_find_by_name(obj, "logos"));
    lv_anim_set_values(&a, 0, 255);
    lv_anim_set_duration(&a, 800);
    lv_anim_set_user_data(&a, (void *)((uintptr_t)selector_and_prop));
    lv_anim_set_path_cb(&a, lv_anim_path_ease_out);
    lv_anim_timeline_add(at, 0, &a);

    selector_and_prop = ((LV_STYLE_TRANSLATE_Y & 0xff) << 24) | 0;
    lv_anim_init(&a);
    lv_anim_set_custom_exec_cb(&a, int_anim_exec_cb);
    lv_anim_set_var(&a, lv_obj_find_by_name(obj, "logos"));
    lv_anim_set_values(&a, 12, 0);
    lv_anim_set_duration(&a, 800);
    lv_anim_set_user_data(&a, (void *)((uintptr_t)selector_and_prop));
    lv_anim_set_path_cb(&a, lv_anim_path_ease_out);
    lv_anim_timeline_add(at, 0, &a);

    return at;
}

static void splash_get_instance_cb(lv_event_t * e)
{
    void ** out = lv_event_get_param(e);
    *out = lv_event_get_user_data(e);
}

static splash_t * splash_get_instance(lv_obj_t * obj)
{
    splash_t * inst = NULL;
    for(lv_obj_t * o = obj; o && !inst; o = lv_obj_get_parent(o)) {
        lv_obj_send_event(o, splash_get_instance_event, &inst);
    }
    return inst;
}

static void splash_destroy_instance(splash_t * inst)
{
    if(inst->timelines) {
        for(uint32_t i = 0; i < 1; i++) lv_anim_timeline_delete(inst->timelines[i]);
        lv_free(inst->timelines);
    }
    lv_free(inst);
}

static void splash_delete_cb(lv_event_t * e)
{
    splash_destroy_instance(lv_event_get_user_data(e));
}

