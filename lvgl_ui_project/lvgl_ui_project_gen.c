/**
 * @file lvgl_ui_project_gen.c
 */

/*********************
 *      INCLUDES
 *********************/

#include "lvgl_ui_project.h"

#if defined(LV_USE_XML) && LV_USE_XML
#endif /* LV_USE_XML */

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void check_font(lv_font_t ** font, const char * name);

/**********************
 *  STATIC VARIABLES
 **********************/

static uint32_t lvgl_ui_project_target = LVGL_UI_PROJECT_COMPILE_TARGET;

/*----------------
 * Translations
 *----------------*/

#ifndef LV_EDITOR_PREVIEW
    static const char * translation_languages[] = {"en", "de", NULL};
    static const char * translation_tags[] = {"dog", "cat", "house", NULL};
    static const char * translation_texts[] = {
        "This is a dog", "Das ist ein Hund", /* dog */
        "A curious little cat", "Eine neugierige kleine Katze", /* cat */
        "The house is cozy and warm", "Das Haus ist gemütlich und warm", /* house */
    };
#endif

/**********************
 *  GLOBAL VARIABLES
 **********************/

/*--------------------
 *  Permanent screens
 *-------------------*/

lv_obj_t * home = NULL;
lv_obj_t * rooms = NULL;
lv_obj_t * settings = NULL;

/*----------------
 * Fonts
 *----------------*/

lv_font_t * font_display;
extern lv_font_t font_display_data;
lv_font_t * font_h1;
extern lv_font_t font_h1_data;
lv_font_t * font_h2;
extern lv_font_t font_h2_data;
lv_font_t * font_body;
extern lv_font_t font_body_data;
lv_font_t * font_small;
extern lv_font_t font_small_data;

/*----------------
 * Images
 *----------------*/

/* Targets: any */
const void * icon_house = NULL;
extern const void * icon_house_data;
const void * icon_layout_grid = NULL;
extern const void * icon_layout_grid_data;
const void * icon_settings = NULL;
extern const void * icon_settings_data;
const void * icon_flame = NULL;
extern const void * icon_flame_data;
const void * icon_snowflake = NULL;
extern const void * icon_snowflake_data;
const void * icon_sun_snow = NULL;
extern const void * icon_sun_snow_data;
const void * icon_power = NULL;
extern const void * icon_power_data;
const void * icon_fan = NULL;
extern const void * icon_fan_data;
const void * icon_droplets = NULL;
extern const void * icon_droplets_data;
const void * icon_cloud_sun = NULL;
extern const void * icon_cloud_sun_data;
const void * icon_thermometer = NULL;
extern const void * icon_thermometer_data;
const void * icon_sun = NULL;
extern const void * icon_sun_data;
const void * icon_info = NULL;
extern const void * icon_info_data;
const void * icon_sofa = NULL;
extern const void * icon_sofa_data;
const void * icon_bed_double = NULL;
extern const void * icon_bed_double_data;
const void * icon_cooking_pot = NULL;
extern const void * icon_cooking_pot_data;
const void * icon_monitor = NULL;
extern const void * icon_monitor_data;
const void * img_logo_winstar = NULL;
extern const void * img_logo_winstar_data;
const void * img_logo_lvgl = NULL;
extern const void * img_logo_lvgl_data;
const void * img_logo_winstar_small = NULL;
extern const void * img_logo_winstar_small_data;
const void * img_logo_lvgl_small = NULL;
extern const void * img_logo_lvgl_small_data;
const void * img_splash = NULL;
extern const void * img_splash_data;

/*----------------
 * Global styles
 *----------------*/

lv_style_t style_screen;
lv_style_t style_card;
lv_style_t style_box;
lv_style_t style_button;
lv_style_t style_button_pressed;
lv_style_t style_button_checked;
lv_style_t style_icon;
lv_style_t style_icon_muted;
lv_style_t style_icon_on_accent;
lv_style_t style_text_muted;
lv_style_t style_text_title;
lv_style_t style_text_caption;

/*----------------
 * Subjects
 *----------------*/

lv_subject_t * subject_temp_target;
lv_subject_t * subject_temp_living;
lv_subject_t * subject_temp_bedroom;
lv_subject_t * subject_temp_kitchen;
lv_subject_t * subject_temp_office;
lv_subject_t * subject_temp_outdoor;
lv_subject_t * subject_humidity;
lv_subject_t * subject_time;
lv_subject_t * subject_mode;
lv_subject_t * subject_fan;
lv_subject_t * subject_room;
lv_subject_t * subject_unit_f;
lv_subject_t * subject_brightness;
lv_subject_t * subject_accent;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lvgl_ui_project_init_gen(const char * asset_path)
{
    /* When running from the editor the theme set from the XML should overwrite this */
#if !defined(LV_EDITOR_PREVIEW)
#if LV_USE_THEME_SIMPLE
    lv_display_t * disp = lv_display_get_default();
    lv_theme_t * th = lv_theme_simple_init(disp);
    lv_display_set_theme(disp, th);
#else
    LV_LOG_WARN("Simple theme is selected in project.xml but LV_USE_THEME_SIMPLE is disabled");
#endif
#endif /*LV_EDITOR_PREVIEW*/


    /*----------------
     * Fonts
     *----------------*/

    /* Targets: any */

    #if LVGL_UI_PROJECT_CHECK_COMPILE_TARGET(LVGL_UI_PROJECT_TARGET_ALL)
    if (lvgl_ui_project_check_target(LVGL_UI_PROJECT_TARGET_ALL)) {
        if (!font_display) {
            /* font_display */
            /* get font 'font_display' from a C array */
            font_display = &font_display_data;

        }
        if (!font_h1) {
            /* font_h1 */
            /* get font 'font_h1' from a C array */
            font_h1 = &font_h1_data;

        }
        if (!font_h2) {
            /* font_h2 */
            /* get font 'font_h2' from a C array */
            font_h2 = &font_h2_data;

        }
        if (!font_body) {
            /* font_body */
            /* get font 'font_body' from a C array */
            font_body = &font_body_data;

        }
        if (!font_small) {
            /* font_small */
            /* get font 'font_small' from a C array */
            font_small = &font_small_data;

        }
    }
    #endif

    /*----------------
     * Images
     *----------------*/

    /* Targets: any */
    #if LVGL_UI_PROJECT_CHECK_COMPILE_TARGET(LVGL_UI_PROJECT_TARGET_ALL)
    if (lvgl_ui_project_check_target(LVGL_UI_PROJECT_TARGET_ALL)) {
        /* icon_house */
        if (!icon_house) {
            icon_house = &icon_house_data;
        }
        /* icon_layout_grid */
        if (!icon_layout_grid) {
            icon_layout_grid = &icon_layout_grid_data;
        }
        /* icon_settings */
        if (!icon_settings) {
            icon_settings = &icon_settings_data;
        }
        /* icon_flame */
        if (!icon_flame) {
            icon_flame = &icon_flame_data;
        }
        /* icon_snowflake */
        if (!icon_snowflake) {
            icon_snowflake = &icon_snowflake_data;
        }
        /* icon_sun_snow */
        if (!icon_sun_snow) {
            icon_sun_snow = &icon_sun_snow_data;
        }
        /* icon_power */
        if (!icon_power) {
            icon_power = &icon_power_data;
        }
        /* icon_fan */
        if (!icon_fan) {
            icon_fan = &icon_fan_data;
        }
        /* icon_droplets */
        if (!icon_droplets) {
            icon_droplets = &icon_droplets_data;
        }
        /* icon_cloud_sun */
        if (!icon_cloud_sun) {
            icon_cloud_sun = &icon_cloud_sun_data;
        }
        /* icon_thermometer */
        if (!icon_thermometer) {
            icon_thermometer = &icon_thermometer_data;
        }
        /* icon_sun */
        if (!icon_sun) {
            icon_sun = &icon_sun_data;
        }
        /* icon_info */
        if (!icon_info) {
            icon_info = &icon_info_data;
        }
        /* icon_sofa */
        if (!icon_sofa) {
            icon_sofa = &icon_sofa_data;
        }
        /* icon_bed_double */
        if (!icon_bed_double) {
            icon_bed_double = &icon_bed_double_data;
        }
        /* icon_cooking_pot */
        if (!icon_cooking_pot) {
            icon_cooking_pot = &icon_cooking_pot_data;
        }
        /* icon_monitor */
        if (!icon_monitor) {
            icon_monitor = &icon_monitor_data;
        }
        /* img_logo_winstar */
        if (!img_logo_winstar) {
            img_logo_winstar = &img_logo_winstar_data;
        }
        /* img_logo_lvgl */
        if (!img_logo_lvgl) {
            img_logo_lvgl = &img_logo_lvgl_data;
        }
        /* img_logo_winstar_small */
        if (!img_logo_winstar_small) {
            img_logo_winstar_small = &img_logo_winstar_small_data;
        }
        /* img_logo_lvgl_small */
        if (!img_logo_lvgl_small) {
            img_logo_lvgl_small = &img_logo_lvgl_small_data;
        }
        /* img_splash */
        if (!img_splash) {
            img_splash = &img_splash_data;
        }
    }
    #endif

    /*----------------
     * Global styles
     *----------------*/

    static bool style_inited = false;

    if (!style_inited) {
        static const lv_style_prop_t style_button_trans_props[] = {LV_STYLE_BG_COLOR, LV_STYLE_TEXT_COLOR, LV_STYLE_IMAGE_RECOLOR, 0};
        static lv_style_transition_dsc_t style_button_trans_dsc;


        /*Init all styles*/
        lv_style_init(&style_screen);
        lv_style_init(&style_card);
        lv_style_init(&style_box);
        lv_style_init(&style_button);
        lv_style_init(&style_button_pressed);
        lv_style_init(&style_button_checked);
        lv_style_init(&style_icon);
        lv_style_init(&style_icon_muted);
        lv_style_init(&style_icon_on_accent);
        lv_style_init(&style_text_muted);
        lv_style_init(&style_text_title);
        lv_style_init(&style_text_caption);

        lv_style_set_bg_color(&style_screen, COLOR_BG);
        lv_style_set_bg_opa(&style_screen, (255 * 100 / 100));
        lv_style_set_text_color(&style_screen, COLOR_TEXT);
        lv_style_set_text_font(&style_screen, font_body);
        lv_style_set_pad_all(&style_screen, 0);
        lv_style_set_bg_color(&style_card, COLOR_PANEL);
        lv_style_set_bg_opa(&style_card, (255 * 100 / 100));
        lv_style_set_border_color(&style_card, COLOR_BORDER);
        lv_style_set_border_width(&style_card, 1);
        lv_style_set_border_opa(&style_card, (255 * 100 / 100));
        lv_style_set_radius(&style_card, RADIUS_CARD);
        lv_style_set_pad_all(&style_card, SPACE_LG);
        lv_style_set_bg_opa(&style_box, 0);
        lv_style_set_border_width(&style_box, 0);
        lv_style_set_pad_all(&style_box, 0);
        lv_style_set_radius(&style_box, 0);
        lv_style_set_shadow_width(&style_box, 0);
        lv_style_set_bg_color(&style_button, COLOR_PANEL_HIGH);
        lv_style_set_bg_opa(&style_button, (255 * 100 / 100));
        lv_style_set_radius(&style_button, RADIUS_BUTTON);
        lv_style_set_shadow_width(&style_button, 0);
        lv_style_set_border_width(&style_button, 0);
        lv_style_set_text_color(&style_button, COLOR_TEXT);
        lv_style_set_text_font(&style_button, font_small);
        lv_style_set_pad_all(&style_button, SPACE_SM);
        lv_style_transition_dsc_init(&style_button_trans_dsc, style_button_trans_props, lv_anim_path_linear, 150, 0, NULL);
        lv_style_set_transition(&style_button, &style_button_trans_dsc);
        lv_style_set_recolor(&style_button_pressed, lv_color_hex(0xffffff));
        lv_style_set_recolor_opa(&style_button_pressed, (255 * 12 / 100));
        lv_style_set_text_color(&style_button_checked, COLOR_ON_ACCENT);
        lv_style_set_image_recolor(&style_icon, COLOR_TEXT);
        lv_style_set_image_recolor_opa(&style_icon, (255 * 100 / 100));
        lv_style_set_image_recolor(&style_icon_muted, COLOR_TEXT_MUTED);
        lv_style_set_image_recolor(&style_icon_on_accent, COLOR_ON_ACCENT);
        lv_style_set_text_color(&style_text_muted, COLOR_TEXT_MUTED);
        lv_style_set_text_font(&style_text_title, font_h2);
        lv_style_set_text_font(&style_text_caption, font_small);
        lv_style_set_text_color(&style_text_caption, COLOR_TEXT_MUTED);

        style_inited = true;
    }

    /*----------------
     * Subjects
     *----------------*/
    subject_temp_target = lv_subject_create(LV_SUBJECT_TYPE_INT);
    lv_subject_set_min_value_int(subject_temp_target, 160);
    lv_subject_set_max_value_int(subject_temp_target, 300);
    lv_subject_set_int(subject_temp_target, 215);
    subject_temp_living = lv_subject_create(LV_SUBJECT_TYPE_INT);
    lv_subject_set_min_value_int(subject_temp_living, -400);
    lv_subject_set_max_value_int(subject_temp_living, 600);
    lv_subject_set_int(subject_temp_living, 214);
    subject_temp_bedroom = lv_subject_create(LV_SUBJECT_TYPE_INT);
    lv_subject_set_min_value_int(subject_temp_bedroom, -400);
    lv_subject_set_max_value_int(subject_temp_bedroom, 600);
    lv_subject_set_int(subject_temp_bedroom, 192);
    subject_temp_kitchen = lv_subject_create(LV_SUBJECT_TYPE_INT);
    lv_subject_set_min_value_int(subject_temp_kitchen, -400);
    lv_subject_set_max_value_int(subject_temp_kitchen, 600);
    lv_subject_set_int(subject_temp_kitchen, 226);
    subject_temp_office = lv_subject_create(LV_SUBJECT_TYPE_INT);
    lv_subject_set_min_value_int(subject_temp_office, -400);
    lv_subject_set_max_value_int(subject_temp_office, 600);
    lv_subject_set_int(subject_temp_office, 208);
    subject_temp_outdoor = lv_subject_create(LV_SUBJECT_TYPE_INT);
    lv_subject_set_min_value_int(subject_temp_outdoor, -400);
    lv_subject_set_max_value_int(subject_temp_outdoor, 600);
    lv_subject_set_int(subject_temp_outdoor, -35);
    subject_humidity = lv_subject_create(LV_SUBJECT_TYPE_INT);
    lv_subject_set_min_value_int(subject_humidity, 0);
    lv_subject_set_max_value_int(subject_humidity, 100);
    lv_subject_set_int(subject_humidity, 42);
    static char subject_time_buf[UI_SUBJECT_STRING_LENGTH];
    static char subject_time_prev_buf[UI_SUBJECT_STRING_LENGTH];
    subject_time = lv_subject_create(LV_SUBJECT_TYPE_STRING);
    lv_subject_set_string_buffer_static(subject_time, subject_time_buf, subject_time_prev_buf, UI_SUBJECT_STRING_LENGTH);
    lv_subject_set_string(subject_time, "18:42");
    subject_mode = lv_subject_create(LV_SUBJECT_TYPE_INT);
    lv_subject_set_min_value_int(subject_mode, 0);
    lv_subject_set_max_value_int(subject_mode, 3);
    lv_subject_set_int(subject_mode, 1);
    subject_fan = lv_subject_create(LV_SUBJECT_TYPE_INT);
    lv_subject_set_min_value_int(subject_fan, 0);
    lv_subject_set_max_value_int(subject_fan, 3);
    lv_subject_set_int(subject_fan, 0);
    subject_room = lv_subject_create(LV_SUBJECT_TYPE_INT);
    lv_subject_set_min_value_int(subject_room, 0);
    lv_subject_set_max_value_int(subject_room, 3);
    lv_subject_set_int(subject_room, 0);
    subject_unit_f = lv_subject_create(LV_SUBJECT_TYPE_INT);
    lv_subject_set_min_value_int(subject_unit_f, 0);
    lv_subject_set_max_value_int(subject_unit_f, 1);
    lv_subject_set_int(subject_unit_f, 0);
    subject_brightness = lv_subject_create(LV_SUBJECT_TYPE_INT);
    lv_subject_set_min_value_int(subject_brightness, 10);
    lv_subject_set_max_value_int(subject_brightness, 100);
    lv_subject_set_int(subject_brightness, 80);
    subject_accent = lv_subject_create(LV_SUBJECT_TYPE_COLOR);
    lv_subject_set_color(subject_accent, lv_color_hex(0xFF8A3D));

    /*----------------
     * Translations
     *----------------*/

    #ifndef LV_EDITOR_PREVIEW
        lv_translation_add_static(translation_languages, translation_tags, translation_texts);
        lv_translation_set_language(translation_languages[0]);
    #endif

#if defined(LV_USE_XML) && LV_USE_XML
    /* Register widgets */

    /* Check all fonts / default if needed. This prevents fonts that are used in one target but
       defined in another from causing assertion failures during rendering of the Preview. */
    check_font(&font_display, "font_display");
    check_font(&font_h1, "font_h1");
    check_font(&font_h2, "font_h2");
    check_font(&font_body, "font_body");
    check_font(&font_small, "font_small");

    /* Register fonts */
    lv_xml_register_font(NULL, "font_display", font_display);
    lv_xml_register_font(NULL, "font_h1", font_h1);
    lv_xml_register_font(NULL, "font_h2", font_h2);
    lv_xml_register_font(NULL, "font_body", font_body);
    lv_xml_register_font(NULL, "font_small", font_small);

    /* Register subjects */
    lv_xml_register_subject(NULL, "subject_temp_target", subject_temp_target);
    lv_xml_register_subject(NULL, "subject_temp_living", subject_temp_living);
    lv_xml_register_subject(NULL, "subject_temp_bedroom", subject_temp_bedroom);
    lv_xml_register_subject(NULL, "subject_temp_kitchen", subject_temp_kitchen);
    lv_xml_register_subject(NULL, "subject_temp_office", subject_temp_office);
    lv_xml_register_subject(NULL, "subject_temp_outdoor", subject_temp_outdoor);
    lv_xml_register_subject(NULL, "subject_humidity", subject_humidity);
    lv_xml_register_subject(NULL, "subject_time", subject_time);
    lv_xml_register_subject(NULL, "subject_mode", subject_mode);
    lv_xml_register_subject(NULL, "subject_fan", subject_fan);
    lv_xml_register_subject(NULL, "subject_room", subject_room);
    lv_xml_register_subject(NULL, "subject_unit_f", subject_unit_f);
    lv_xml_register_subject(NULL, "subject_brightness", subject_brightness);
    lv_xml_register_subject(NULL, "subject_accent", subject_accent);

    /* Register callbacks */

    /* Register easing callbacks */
#endif

    /* Register all the global assets so that they won't be created again when globals.xml is parsed.
     * While running in the editor skip this step to update the preview when the XML changes */
#if defined(LV_USE_XML) && LV_USE_XML && !defined(LV_EDITOR_PREVIEW)
    /* Register images */
    lv_xml_register_image(NULL, "icon_house", icon_house);
    lv_xml_register_image(NULL, "icon_layout_grid", icon_layout_grid);
    lv_xml_register_image(NULL, "icon_settings", icon_settings);
    lv_xml_register_image(NULL, "icon_flame", icon_flame);
    lv_xml_register_image(NULL, "icon_snowflake", icon_snowflake);
    lv_xml_register_image(NULL, "icon_sun_snow", icon_sun_snow);
    lv_xml_register_image(NULL, "icon_power", icon_power);
    lv_xml_register_image(NULL, "icon_fan", icon_fan);
    lv_xml_register_image(NULL, "icon_droplets", icon_droplets);
    lv_xml_register_image(NULL, "icon_cloud_sun", icon_cloud_sun);
    lv_xml_register_image(NULL, "icon_thermometer", icon_thermometer);
    lv_xml_register_image(NULL, "icon_sun", icon_sun);
    lv_xml_register_image(NULL, "icon_info", icon_info);
    lv_xml_register_image(NULL, "icon_sofa", icon_sofa);
    lv_xml_register_image(NULL, "icon_bed_double", icon_bed_double);
    lv_xml_register_image(NULL, "icon_cooking_pot", icon_cooking_pot);
    lv_xml_register_image(NULL, "icon_monitor", icon_monitor);
    lv_xml_register_image(NULL, "img_logo_winstar", img_logo_winstar);
    lv_xml_register_image(NULL, "img_logo_lvgl", img_logo_lvgl);
    lv_xml_register_image(NULL, "img_logo_winstar_small", img_logo_winstar_small);
    lv_xml_register_image(NULL, "img_logo_lvgl_small", img_logo_lvgl_small);
    lv_xml_register_image(NULL, "img_splash", img_splash);
#endif

#if !defined(LV_USE_XML) || LV_USE_XML == 0
    /*--------------------
     *  Permanent screens
     *-------------------*/
    /* If XML is enabled it's assumed that the permanent screens are created
     * manually from XML using lv_xml_create() */
    /* Create all the permanent screens first so that they can reference each other */
    home = lv_obj_create(NULL);
    rooms = lv_obj_create(NULL);
    settings = lv_obj_create(NULL);

    home_create();
    rooms_create();
    settings_create();
#endif
}

void lvgl_ui_project_set_target(uint32_t target)
{
    lvgl_ui_project_target = target;
}

uint32_t lvgl_ui_project_get_target(void)
{
    return lvgl_ui_project_target;
}

bool lvgl_ui_project_check_target(uint32_t target)
{
    return (lvgl_ui_project_target & target) ? true : false;
}

/* Callbacks */

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void check_font(lv_font_t ** font, const char * name)
{
    if (!(*font)) {
        *font = (lv_font_t *)LV_FONT_DEFAULT;
        LV_LOG_WARN("font `%s` was not set. Using `LV_FONT_DEFAULT` instead", name);
    }
}