/**
 * @file room_card_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "room_card_gen.h"
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
    int32_t index_snapshot;
} room_card_t;

/***********************
 *  STATIC VARIABLES
 **********************/

/***********************
 *  STATIC PROTOTYPES
 **********************/

static void room_card_destroy_instance(room_card_t * inst);
static void room_card_delete_cb(lv_event_t * e);
static void room_card_lv_button_0_checked_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void room_card_lv_button_0_style_border_color_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void room_card_lv_obj_1_style_bg_color_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void room_card_lv_image_0_style_image_recolor_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void room_card_lv_label_0_hidden_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void room_card_lv_label_0_style_text_color_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void room_card_set_subject_cb(lv_event_t * e);

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * room_card_create(lv_obj_t * parent, const char * text, const void * icon, lv_subject_t * temp, int32_t index)
{
    LV_TRACE_OBJ_CREATE("begin");

    static lv_style_t style_room_icon;
    static lv_style_t style_room_card_checked;

    static bool style_inited = false;

    if (!style_inited) {
        /*Init all styles*/
        lv_style_init(&style_room_icon);
        lv_style_init(&style_room_card_checked);

        lv_style_set_width(&style_room_icon, 64);
        lv_style_set_height(&style_room_icon, 64);
        lv_style_set_radius(&style_room_icon, RADIUS_ROUND);
        lv_style_set_bg_color(&style_room_icon, COLOR_PANEL_HIGH);
        lv_style_set_bg_opa(&style_room_icon, (255 * 100 / 100));
        lv_style_set_border_width(&style_room_icon, 0);
        lv_style_set_pad_all(&style_room_icon, 0);
        lv_style_set_border_width(&style_room_card_checked, 2);

        style_inited = true;
    }


    lv_obj_t * the_root = NULL;

    room_card_t * inst = lv_malloc(sizeof(room_card_t));
    lv_memzero(inst, sizeof(room_card_t));
    inst->index_snapshot = index;

    #if LVGL_UI_PROJECT_CHECK_COMPILE_TARGET(LVGL_UI_PROJECT_TARGET_ALL)
    if (lvgl_ui_project_check_target(LVGL_UI_PROJECT_TARGET_ALL)) {
        lv_obj_t * lv_button_0 = lv_button_create(parent);
        lv_obj_set_name_static(lv_button_0, "room_card_#");
        lv_obj_set_flex_grow(lv_button_0, 1);
        lv_obj_set_height(lv_button_0, lv_pct(100));
        lv_obj_set_flex_flow(lv_button_0, LV_FLEX_FLOW_COLUMN);
        lv_subject_add_observer_obj(subject_room, room_card_lv_button_0_checked_binding_cb, lv_button_0, inst);
        lv_obj_set_style_flex_main_place(lv_button_0, LV_FLEX_ALIGN_SPACE_BETWEEN, 0);
        lv_subject_add_observer_obj(subject_accent, room_card_lv_button_0_style_border_color_binding_cb, lv_button_0, NULL);

        lv_obj_add_style(lv_button_0, &style_card, 0);
        lv_obj_add_style(lv_button_0, &style_room_card_checked, LV_STATE_CHECKED);
        lv_obj_add_style(lv_button_0, &style_button_pressed, LV_STATE_PRESSED);
        lv_obj_t * lv_obj_0 = lv_obj_create(lv_button_0);
        lv_obj_set_width(lv_obj_0, lv_pct(100));
        lv_obj_set_height(lv_obj_0, LV_SIZE_CONTENT);
        lv_obj_set_flex_flow(lv_obj_0, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_main_place(lv_obj_0, LV_FLEX_ALIGN_SPACE_BETWEEN, 0);
        lv_obj_set_style_flex_cross_place(lv_obj_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_add_style(lv_obj_0, &style_box, 0);
        lv_obj_t * lv_obj_1 = lv_obj_create(lv_obj_0);
        lv_subject_add_observer_obj(subject_room, room_card_lv_obj_1_style_bg_color_binding_cb, lv_obj_1, inst);
        lv_subject_add_observer_obj(subject_accent, room_card_lv_obj_1_style_bg_color_binding_cb, lv_obj_1, inst);
        lv_obj_add_style(lv_obj_1, &style_room_icon, 0);
        lv_obj_t * lv_image_0 = lv_image_create(lv_obj_1);
        lv_image_set_src(lv_image_0, icon);
        lv_obj_set_align(lv_image_0, LV_ALIGN_CENTER);
        lv_subject_add_observer_obj(subject_room, room_card_lv_image_0_style_image_recolor_binding_cb, lv_image_0, inst);
        lv_obj_add_style(lv_image_0, &style_icon, 0);

        lv_obj_t * lv_label_0 = lv_label_create(lv_obj_0);
        lv_label_set_text(lv_label_0, "Selected");
        lv_subject_add_observer_obj(subject_room, room_card_lv_label_0_hidden_binding_cb, lv_label_0, inst);
        lv_obj_set_style_text_font(lv_label_0, font_small, 0);
        lv_subject_add_observer_obj(subject_accent, room_card_lv_label_0_style_text_color_binding_cb, lv_label_0, NULL);

        lv_obj_t * lv_obj_2 = lv_obj_create(lv_button_0);
        lv_obj_set_width(lv_obj_2, lv_pct(100));
        lv_obj_set_height(lv_obj_2, LV_SIZE_CONTENT);
        lv_obj_set_flex_flow(lv_obj_2, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_main_place(lv_obj_2, LV_FLEX_ALIGN_SPACE_BETWEEN, 0);
        lv_obj_set_style_flex_cross_place(lv_obj_2, LV_FLEX_ALIGN_END, 0);
        lv_obj_add_style(lv_obj_2, &style_box, 0);
        lv_obj_t * lv_label_1 = lv_label_create(lv_obj_2);
        lv_label_set_text(lv_label_1, text);
        lv_obj_set_style_text_font(lv_label_1, font_h2, 0);

        lv_obj_t * temp_value_0 = temp_value_create(lv_obj_2, temp, false);
        lv_obj_set_style_text_font(temp_value_0, font_h1, 0);

        lv_obj_add_event_cb(lv_button_0, room_card_set_subject_cb, LV_EVENT_CLICKED, inst);
        lv_obj_add_screen_load_event(lv_button_0, LV_EVENT_CLICKED, home, LV_SCREEN_LOAD_ANIM_FADE_IN, 200, 0);

        the_root = lv_button_0;
    }
    #endif

    if(the_root) lv_obj_add_event_cb(the_root, room_card_delete_cb, LV_EVENT_DELETE, inst);
    else room_card_destroy_instance(inst); /* no target matched, so nothing owns it */

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void room_card_destroy_instance(room_card_t * inst)
{
    lv_free(inst);
}

static void room_card_delete_cb(lv_event_t * e)
{
    room_card_destroy_instance(lv_event_get_user_data(e));
}

static void room_card_lv_button_0_checked_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    room_card_t * inst = lv_observer_get_user_data(observer);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    lv_obj_set_checked(obj, lv_subject_get_int(subject_room) == inst->index_snapshot);
}

static void room_card_lv_button_0_style_border_color_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    lv_obj_set_style_border_color(obj, lv_subject_get_color(subject_accent), LV_STATE_CHECKED);
}

static void room_card_lv_obj_1_style_bg_color_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    room_card_t * inst = lv_observer_get_user_data(observer);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    lv_obj_set_style_bg_color(obj, lv_subject_get_int(subject_room) == inst->index_snapshot ? lv_subject_get_color(subject_accent) : COLOR_PANEL_HIGH, 0);
}

static void room_card_lv_image_0_style_image_recolor_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    room_card_t * inst = lv_observer_get_user_data(observer);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    lv_obj_set_style_image_recolor(obj, lv_subject_get_int(subject_room) == inst->index_snapshot ? COLOR_ON_ACCENT : COLOR_TEXT, 0);
}

static void room_card_lv_label_0_hidden_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    room_card_t * inst = lv_observer_get_user_data(observer);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    lv_obj_set_hidden(obj, lv_subject_get_int(subject_room) != inst->index_snapshot);
}

static void room_card_lv_label_0_style_text_color_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    lv_obj_set_style_text_color(obj, lv_subject_get_color(subject_accent), 0);
}

static void room_card_set_subject_cb(lv_event_t * e)
{
    room_card_t * inst = lv_event_get_user_data(e);
    lv_subject_set_int(subject_room, inst->index_snapshot);
}

