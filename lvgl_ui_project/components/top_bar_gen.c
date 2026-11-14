/**
 * @file top_bar_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "top_bar_gen.h"
#include "../lvgl_ui_project.h"

/*********************
 *      DEFINES
 *********************/

/* A string subject needs a value buffer and a previous-value
 * buffer per instance. Mirrors LV_XML_INSTANCE_STRING_LEN in the runtime. */
#ifndef TOP_BAR_STRING_LEN
    #define TOP_BAR_STRING_LEN 256
#endif

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
    /* <prop bindable="true">: a create() parameter AND an owned subject */
    lv_subject_t * title;
    char title_buf[TOP_BAR_STRING_LEN];
    char title_prev_buf[TOP_BAR_STRING_LEN];
} top_bar_t;

/***********************
 *  STATIC VARIABLES
 **********************/

/***********************
 *  STATIC PROTOTYPES
 **********************/

static uint32_t top_bar_get_instance_event;
static void top_bar_get_instance_cb(lv_event_t * e);
static top_bar_t * top_bar_get_instance(lv_obj_t * obj);
static void top_bar_destroy_instance(top_bar_t * inst);
static void top_bar_delete_cb(lv_event_t * e);
static void top_bar_lv_label_0_text_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void top_bar_lv_label_1_text_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void top_bar_lv_label_2_text_binding_cb(lv_observer_t * observer, lv_subject_t * subject);

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * top_bar_create(lv_obj_t * parent, const char * title)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    if(top_bar_get_instance_event == 0) top_bar_get_instance_event = lv_event_register_id();
    top_bar_t * inst = lv_malloc(sizeof(top_bar_t));
    lv_memzero(inst, sizeof(top_bar_t));
    inst->title = lv_subject_create(LV_SUBJECT_TYPE_STRING);
    lv_subject_set_string_buffer_static(inst->title, inst->title_buf, inst->title_prev_buf, TOP_BAR_STRING_LEN);
    lv_subject_set_string(inst->title, title);

    #if LVGL_UI_PROJECT_CHECK_COMPILE_TARGET(LVGL_UI_PROJECT_TARGET_ALL)
    if (lvgl_ui_project_check_target(LVGL_UI_PROJECT_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(parent);
        lv_obj_set_name_static(lv_obj_0, "top_bar_#");
        lv_obj_add_event_cb(lv_obj_0, top_bar_get_instance_cb, top_bar_get_instance_event, inst);
        lv_obj_set_width(lv_obj_0, lv_pct(100));
        lv_obj_set_height(lv_obj_0, TOP_BAR_HEIGHT);
        lv_obj_set_flex_flow(lv_obj_0, LV_FLEX_FLOW_ROW);
        lv_obj_set_scrollable(lv_obj_0, false);
        lv_obj_set_style_pad_gap(lv_obj_0, SPACE_XL, 0);
        lv_obj_set_style_flex_cross_place(lv_obj_0, LV_FLEX_ALIGN_CENTER, 0);

        lv_obj_add_style(lv_obj_0, &style_box, 0);
        lv_obj_t * lv_label_0 = lv_label_create(lv_obj_0);
        lv_subject_add_observer_obj(inst->title, top_bar_lv_label_0_text_binding_cb, lv_label_0, inst);
        lv_obj_set_flex_grow(lv_label_0, 1);
        lv_obj_set_style_text_font(lv_label_0, font_h2, 0);

        lv_obj_t * info_tile_0 = info_tile_create(lv_obj_0, icon_droplets);
        lv_obj_t * info_tile_0_value = info_tile_get_value(info_tile_0);
        if (info_tile_0_value) {
        lv_obj_t * lv_label_1 = lv_label_create(info_tile_0_value);
        lv_subject_add_observer_obj(subject_humidity, top_bar_lv_label_1_text_binding_cb, lv_label_1, NULL);
        } else {
        LV_LOG_WARN("`value` slot of `info_tile_0` doesn't exist");
        }

        lv_obj_t * info_tile_1 = info_tile_create(lv_obj_0, icon_cloud_sun);
        lv_obj_t * info_tile_1_value = info_tile_get_value(info_tile_1);
        if (info_tile_1_value) {
        temp_value_create(info_tile_1_value, subject_temp_outdoor, true);
        } else {
        LV_LOG_WARN("`value` slot of `info_tile_1` doesn't exist");
        }

        lv_obj_t * lv_label_2 = lv_label_create(lv_obj_0);
        lv_subject_add_observer_obj(subject_time, top_bar_lv_label_2_text_binding_cb, lv_label_2, NULL);
        lv_obj_set_style_text_font(lv_label_2, font_h2, 0);

        the_root = lv_obj_0;
    }
    #endif

    if(the_root) lv_obj_add_event_cb(the_root, top_bar_delete_cb, LV_EVENT_DELETE, inst);
    else top_bar_destroy_instance(inst); /* no target matched, so nothing owns it */

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

void top_bar_set_title(lv_obj_t * obj, const char * title)
{
    top_bar_t * inst = top_bar_get_instance(obj);
    if(inst) lv_subject_set_string(inst->title, title);
}

const char * top_bar_get_title(lv_obj_t * obj)
{
    top_bar_t * inst = top_bar_get_instance(obj);
    return inst ? lv_subject_get_string(inst->title) : NULL;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void top_bar_get_instance_cb(lv_event_t * e)
{
    void ** out = lv_event_get_param(e);
    *out = lv_event_get_user_data(e);
}

static top_bar_t * top_bar_get_instance(lv_obj_t * obj)
{
    top_bar_t * inst = NULL;
    for(lv_obj_t * o = obj; o && !inst; o = lv_obj_get_parent(o)) {
        lv_obj_send_event(o, top_bar_get_instance_event, &inst);
    }
    return inst;
}

static void top_bar_destroy_instance(top_bar_t * inst)
{
    lv_subject_delete(inst->title);
    lv_free(inst);
}

static void top_bar_delete_cb(lv_event_t * e)
{
    top_bar_destroy_instance(lv_event_get_user_data(e));
}

static void top_bar_lv_label_0_text_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    top_bar_t * inst = lv_observer_get_user_data(observer);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    lv_label_set_text(obj, lv_subject_get_string(inst->title));
}

static void top_bar_lv_label_1_text_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    char eval_buf_1[LV_XML_EVAL_STRING_BUF_SIZE];
    lv_snprintf(eval_buf_1, sizeof(eval_buf_1), "%d%s", (int)(lv_subject_get_int(subject_humidity)), "%");
    lv_label_set_text(obj, eval_buf_1);
}

static void top_bar_lv_label_2_text_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    lv_label_set_text(obj, lv_subject_get_string(subject_time));
}

