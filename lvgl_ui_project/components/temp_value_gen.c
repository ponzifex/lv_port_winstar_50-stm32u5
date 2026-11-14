/**
 * @file temp_value_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "temp_value_gen.h"
#include "../lvgl_ui_project.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
    /* <prop type="subject">: owned by the caller, stored, never deleted */
    lv_subject_t * temp;
} temp_value_t;

/***********************
 *  STATIC VARIABLES
 **********************/

/***********************
 *  STATIC PROTOTYPES
 **********************/

static void temp_value_destroy_instance(temp_value_t * inst);
static void temp_value_delete_cb(lv_event_t * e);
static void temp_value_lv_label_0_text_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void temp_value_lv_label_1_text_binding_cb(lv_observer_t * observer, lv_subject_t * subject);

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * temp_value_create(lv_obj_t * parent, lv_subject_t * temp, bool whole)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    temp_value_t * inst = lv_malloc(sizeof(temp_value_t));
    lv_memzero(inst, sizeof(temp_value_t));
    inst->temp = temp;

    #if LVGL_UI_PROJECT_CHECK_COMPILE_TARGET(LVGL_UI_PROJECT_TARGET_ALL)
    if (lvgl_ui_project_check_target(LVGL_UI_PROJECT_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(parent);
        lv_obj_set_name_static(lv_obj_0, "temp_value_#");
        lv_obj_set_width(lv_obj_0, LV_SIZE_CONTENT);
        lv_obj_set_height(lv_obj_0, LV_SIZE_CONTENT);

        lv_obj_add_style(lv_obj_0, &style_box, 0);
        lv_obj_t * lv_label_0 = lv_label_create(lv_obj_0);
        lv_obj_set_hidden(lv_label_0, whole);
        lv_subject_add_observer_obj(subject_unit_f, temp_value_lv_label_0_text_binding_cb, lv_label_0, inst);
        lv_subject_add_observer_obj(inst->temp, temp_value_lv_label_0_text_binding_cb, lv_label_0, inst);

        lv_obj_t * lv_label_1 = lv_label_create(lv_obj_0);
        lv_obj_set_hidden(lv_label_1, !whole);
        lv_subject_add_observer_obj(subject_unit_f, temp_value_lv_label_1_text_binding_cb, lv_label_1, inst);
        lv_subject_add_observer_obj(inst->temp, temp_value_lv_label_1_text_binding_cb, lv_label_1, inst);

        the_root = lv_obj_0;
    }
    #endif

    if(the_root) lv_obj_add_event_cb(the_root, temp_value_delete_cb, LV_EVENT_DELETE, inst);
    else temp_value_destroy_instance(inst); /* no target matched, so nothing owns it */

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void temp_value_destroy_instance(temp_value_t * inst)
{
    lv_free(inst);
}

static void temp_value_delete_cb(lv_event_t * e)
{
    temp_value_destroy_instance(lv_event_get_user_data(e));
}

static void temp_value_lv_label_0_text_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    temp_value_t * inst = lv_observer_get_user_data(observer);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    char eval_buf_1[LV_XML_EVAL_STRING_BUF_SIZE];
    char eval_buf_2[LV_XML_EVAL_STRING_BUF_SIZE];
    lv_snprintf(eval_buf_1, sizeof(eval_buf_1), "%d%s", (int)((lv_subject_get_int(inst->temp) * 9 / 5 + 325) / 10), "°");
    lv_snprintf(eval_buf_2, sizeof(eval_buf_2), "%d%s%d%s", (int)(lv_subject_get_int(inst->temp) / 10), ".", (int)(lv_subject_get_int(inst->temp) % 10), "°");
    lv_label_set_text(obj, lv_subject_get_int(subject_unit_f) ? eval_buf_1 : eval_buf_2);
}

static void temp_value_lv_label_1_text_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    temp_value_t * inst = lv_observer_get_user_data(observer);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    char eval_buf_1[LV_XML_EVAL_STRING_BUF_SIZE];
    char eval_buf_2[LV_XML_EVAL_STRING_BUF_SIZE];
    lv_snprintf(eval_buf_1, sizeof(eval_buf_1), "%d%s", (int)((lv_subject_get_int(inst->temp) * 9 / 5 + 325) / 10), "°");
    lv_snprintf(eval_buf_2, sizeof(eval_buf_2), "%d%s", (int)(lv_subject_get_int(inst->temp) / 10), "°");
    lv_label_set_text(obj, lv_subject_get_int(subject_unit_f) ? eval_buf_1 : eval_buf_2);
}

