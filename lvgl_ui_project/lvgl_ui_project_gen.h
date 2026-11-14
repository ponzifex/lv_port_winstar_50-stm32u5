/**
 * @file lvgl_ui_project_gen.h
 */

#ifndef LVGL_PRO_LVGL_UI_PROJECT_GEN_H
#define LVGL_PRO_LVGL_UI_PROJECT_GEN_H

#ifndef UI_SUBJECT_STRING_LENGTH
#define UI_SUBJECT_STRING_LENGTH 256
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif

#if defined(LV_USE_XML) && LV_USE_XML
    #include "lv_xml/lv_xml.h"
#endif



/* Prototypes for target functions, needed by responsive const definitions */

void lvgl_ui_project_set_target(uint32_t target);
uint32_t lvgl_ui_project_get_target(void);
bool lvgl_ui_project_check_target(uint32_t target);

/*********************
 *      DEFINES
 *********************/

#define LVGL_UI_PROJECT_TARGET_UNDEFINED  (0 << 1)
#define LVGL_UI_PROJECT_TARGET_TARGET1    (1 << 1)
#define LVGL_UI_PROJECT_TARGET_ALL        0x0FFFFFFF

/* By default compile for all targets, allowing to switch to any targets at runtime */
#ifndef LVGL_UI_PROJECT_COMPILE_TARGET
#define LVGL_UI_PROJECT_COMPILE_TARGET LVGL_UI_PROJECT_TARGET_ALL
#endif

#define LVGL_UI_PROJECT_CHECK_COMPILE_TARGET(target) (LVGL_UI_PROJECT_COMPILE_TARGET & (target) ? 1 : 0)

/**
 * Smallest gap
 */
#define SPACE_XS (4)
/**
 * Small gap
 */
#define SPACE_SM (8)
/**
 * Default gap
 */
#define SPACE_MD (12)
/**
 * Gap between cards
 */
#define SPACE_LG (16)
/**
 * Screen padding
 */
#define SPACE_XL (24)
/**
 * Card corner radius
 */
#define RADIUS_CARD (20)
/**
 * Button corner radius
 */
#define RADIUS_BUTTON (14)
/**
 * Pill and circle radius
 */
#define RADIUS_ROUND (1000)
/**
 * Width of the left navigation rail
 */
#define NAV_RAIL_WIDTH (88)
/**
 * Square nav button
 */
#define NAV_BUTTON_SIZE (60)
/**
 * Height of the top bar
 */
#define TOP_BAR_HEIGHT (48)
/**
 * Smallest touch target
 */
#define TOUCH_MIN (56)
/**
 * Width of the dial card on home
 */
#define DIAL_CARD_WIDTH (340)
/**
 * Diameter of the target temperature arc
 */
#define DIAL_SIZE (290)
/**
 * Stroke of the dial arc
 */
#define ARC_WIDTH (18)
/**
 * Screen background
 */
#define COLOR_BG (lv_color_hex(0x0E1117))
/**
 * Card and nav rail background
 */
#define COLOR_PANEL (lv_color_hex(0x181C24))
/**
 * Button on a card
 */
#define COLOR_PANEL_HIGH (lv_color_hex(0x232935))
/**
 * Thin card border
 */
#define COLOR_BORDER (lv_color_hex(0x2C3341))
/**
 * Primary text and icons
 */
#define COLOR_TEXT (lv_color_hex(0xE9ECF2))
/**
 * Secondary text and icons
 */
#define COLOR_TEXT_MUTED (lv_color_hex(0x8C95A6))
/**
 * Text and icons on an accent fill
 */
#define COLOR_ON_ACCENT (lv_color_hex(0x0E1117))
/**
 * Accent in heat mode
 */
#define COLOR_HEAT (lv_color_hex(0xFF8A3D))
/**
 * Accent in cool mode
 */
#define COLOR_COOL (lv_color_hex(0x4DA3FF))
/**
 * Accent in auto mode
 */
#define COLOR_AUTO (lv_color_hex(0x2EC4B6))
/**
 * Accent when the system is off
 */
#define COLOR_OFF (lv_color_hex(0x7A8394))


#ifndef LV_XML_EVAL_STRING_BUF_SIZE
    #define LV_XML_EVAL_STRING_BUF_SIZE 256
#endif

/**
 * Animation path of a style transition with a `bezier(…)` easing. The control
 * points come from the transition descriptor's `user_data`, as a transition
 * descriptor cannot store animation parameters itself.
 */
static inline int32_t lvgl_ui_project_style_transition_bezier_path_helper(const lv_anim_t * a)
{
    const lv_anim_bezier3_para_t * para = (const lv_anim_bezier3_para_t *)lv_anim_get_user_data(a);
    if(para == NULL) return lv_anim_path_linear(a);

    lv_anim_t a_tmp = *a;
    lv_anim_set_bezier3_param(&a_tmp, para->x1, para->y1, para->x2, para->y2);
    return lv_anim_path_custom_bezier3(&a_tmp);
}

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL VARIABLES
 **********************/

/*-------------------
 * Permanent screens
 *------------------*/

extern lv_obj_t * home;
extern lv_obj_t * rooms;
extern lv_obj_t * settings;

/*----------------
 * Global styles
 *----------------*/

extern lv_style_t style_screen;
extern lv_style_t style_card;
extern lv_style_t style_box;
extern lv_style_t style_button;
extern lv_style_t style_button_pressed;
extern lv_style_t style_button_checked;
extern lv_style_t style_icon;
extern lv_style_t style_icon_muted;
extern lv_style_t style_icon_on_accent;
extern lv_style_t style_text_muted;
extern lv_style_t style_text_title;
extern lv_style_t style_text_caption;

/*----------------
 * Fonts
 *----------------*/

/* Targets: any */
extern lv_font_t * font_display;
extern lv_font_t * font_h1;
extern lv_font_t * font_h2;
extern lv_font_t * font_body;
extern lv_font_t * font_small;


/*----------------
 * Images
 *----------------*/

/* Targets: any */
extern const void * icon_house;
extern const void * icon_layout_grid;
extern const void * icon_settings;
extern const void * icon_flame;
extern const void * icon_snowflake;
extern const void * icon_sun_snow;
extern const void * icon_power;
extern const void * icon_fan;
extern const void * icon_droplets;
extern const void * icon_cloud_sun;
extern const void * icon_thermometer;
extern const void * icon_sun;
extern const void * icon_info;
extern const void * icon_sofa;
extern const void * icon_bed_double;
extern const void * icon_cooking_pot;
extern const void * icon_monitor;
extern const void * img_logo_winstar;
extern const void * img_logo_lvgl;
extern const void * img_logo_winstar_small;
extern const void * img_logo_lvgl_small;
extern const void * img_splash;

/*----------------
 * Subjects
 *----------------*/

extern lv_subject_t * subject_temp_target;
extern lv_subject_t * subject_temp_living;
extern lv_subject_t * subject_temp_bedroom;
extern lv_subject_t * subject_temp_kitchen;
extern lv_subject_t * subject_temp_office;
extern lv_subject_t * subject_temp_outdoor;
extern lv_subject_t * subject_humidity;
extern lv_subject_t * subject_time;
extern lv_subject_t * subject_mode;
extern lv_subject_t * subject_fan;
extern lv_subject_t * subject_room;
extern lv_subject_t * subject_unit_f;
extern lv_subject_t * subject_brightness;
extern lv_subject_t * subject_accent;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/*----------------
 * Event Callbacks
 *----------------*/

/*----------------
 * Easing Callbacks
 *----------------*/

/**
 * Initialize the component library
 */

void lvgl_ui_project_init_gen(const char * asset_path);

/**********************
 *      MACROS
 **********************/

/**********************
 *   POST INCLUDES
 **********************/

/*Include all the widgets, components and screens of this library*/
#include "components/choice_button_gen.h"
#include "components/fan_selector_gen.h"
#include "components/info_tile_gen.h"
#include "components/mode_button_gen.h"
#include "components/nav_button_gen.h"
#include "components/nav_rail_gen.h"
#include "components/room_card_gen.h"
#include "components/settings_row_gen.h"
#include "components/temp_dial_gen.h"
#include "components/temp_value_gen.h"
#include "components/top_bar_gen.h"
#include "screens/home_gen.h"
#include "screens/rooms_gen.h"
#include "screens/settings_gen.h"
#include "screens/splash_gen.h"

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LVGL_PRO_LVGL_UI_PROJECT_GEN_H*/