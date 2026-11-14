# Smart Thermostat Demo

## Goal

A demo UI for a wall-mounted smart home thermostat on the Winstar 5" touch display
(STM32U599, 800×480). The home owner sees the room temperature and sets the target
temperature, the mode and the fan speed. It also shows LVGL and Winstar at trade shows.

## Spec

Input: touch only. Look: dark, Inter font, Lucide icons. The accent color follows the
mode: orange for heat, blue for cool, teal for auto, grey for off.

### Screens

| Screen | Purpose | Main content |
| --- | --- | --- |
| `splash` | Brand intro at power-up | `splash_s.png` photo, Winstar and LVGL logos, fade in. Goes to `home` after about 2.5 s |
| `home` | Main control | Nav rail. Top bar: room name, outdoor weather, time. Large dial: target temperature (draggable arc, −/+ buttons by 0.5°), current room temperature. Mode buttons: heat, cool, auto, off. Fan speed: auto, low, med, high. Humidity is in the top bar |
| `rooms` | Pick the room | Nav rail. 2×2 grid of room cards: Living room, Bedroom, Kitchen, Office. Each shows its icon, name and current temperature. The selected room is highlighted |
| `settings` | Device settings | Nav rail. Units (°C / °F), display brightness slider, About card with the Winstar and LVGL logos and the hardware info |

### Flow

| From | To | Trigger |
| --- | --- | --- |
| `splash` | `home` | Timer, about 2.5 s, fade |
| any screen with the nav rail | `home`, `rooms`, `settings` | Tap the house, grid, or gear icon |
| `rooms` | `home` | Tap a room card. It also sets `subject_room` |

`home`, `rooms` and `settings` are permanent screens.

### Components

| Component | Used in | What it is |
| --- | --- | --- |
| `nav_rail` | home, rooms, settings | Vertical bar, 3 icon buttons. Variant `active`: home, rooms, settings |
| `top_bar` | home, rooms, settings | Title, outdoor temperature with weather icon, time |
| `temp_dial` | home | Arc, target value, current value, −/+ buttons |
| `mode_button` | home | Icon and label. Checked when `subject_mode` equals its value. Tap sets the mode |
| `fan_selector` | home | Segmented control for `subject_fan` |
| `info_tile` | top_bar | Icon and a `value` slot (humidity, outdoor temperature) |
| `choice_button` | fan_selector, settings | One option of a segmented control |
| `temp_value` | everywhere | Temperature readout in °C or °F from a 0.1 °C subject |
| `nav_button` | nav_rail | Icon button of the rail |
| `room_card` | rooms | Icon, name, temperature. Checked when selected |
| `settings_row` | settings | Title on the left, a slot for the control on the right |

### Subjects

Temperatures are `int` in tenths of a degree Celsius (215 = 21.5 °C), so no float
support is needed. The UI converts to °F for display.

| Subject | Type | Range | Default | Written by |
| --- | --- | --- | --- | --- |
| `subject_temp_target` | int | 160–300 | 215 | UI |
| `subject_temp_living` | int | −400–600 | 214 | Application |
| `subject_temp_bedroom` | int | −400–600 | 192 | Application |
| `subject_temp_kitchen` | int | −400–600 | 226 | Application |
| `subject_temp_office` | int | −400–600 | 208 | Application |
| `subject_temp_outdoor` | int | −400–600 | −35 | Application |
| `subject_humidity` | int | 0–100 % | 42 | Application |
| `subject_time` | string | | `18:42` | Application |
| `subject_mode` | int | 0 off, 1 heat, 2 cool, 3 auto | 1 | UI |
| `subject_fan` | int | 0 auto, 1 low, 2 med, 3 high | 0 | UI |
| `subject_room` | int | 0 living, 1 bedroom, 2 kitchen, 3 office | 0 | UI |
| `subject_unit_f` | int | 0 °C, 1 °F | 0 | UI |
| `subject_brightness` | int | 10–100 % | 80 | UI. The application sets the backlight from it |
| `subject_accent` | color | | heat orange | UI only. The home screen sets it from `subject_mode` |

No `<event_cb>` is planned. The application only reads and writes the subjects.

### Open questions

- One target temperature for all rooms, or one per room? This spec uses one.
- A light theme is not in scope.
- The time and weather come from the application. The demo shows the defaults.

---

A clean **LVGL Pro** project with nothing in it yet. Everything is set up, so you can
start adding your own screens and components right away.

## What's inside

- `project.xml`: Display targets and the LVGL version to build against
- `globals.xml`: The place for project-wide constants, colors, fonts, styles, and subjects
- `screens/`, `components/`, `widgets/`: Your UI files, one per XML file. Each folder has a
  README describing what belongs in it
- `images/`, `fonts/`: Assets, converted and compiled in by the Editor
- `sim/`: The built-in simulator, see [`sim/README.md`](sim/README.md)

## Where to start

Create your first screen in `screens/` (e.g. `screens/home.xml` with a `<screen>` root tag)
and watch it render live in the preview. **Ctrl+B** or the hammer icon exports the C code and
compiles it, **F5** runs it in the simulator.

If you would rather start from something that already works, create a project from the
**basic** template, or from any of the examples and tutorials on the Editor's launch screen.

## Learn more

Check out the docs at **<https://lvgl.io/docs/pro>**. These are the key pages to learn XML:

- [XML overview](https://lvgl.io/docs/pro/syntax/overview): Basics of the syntax
- [Components](https://lvgl.io/docs/pro/syntax/components), [Widgets](https://lvgl.io/docs/pro/syntax/widgets) and [Screens](https://lvgl.io/docs/pro/syntax/screens): The basic building blocks of a UI
- [Built-in widgets](https://lvgl.io/docs/pro/built_in_widgets): the XML API of `lv_obj`, `lv_button`, `lv_slider`, etc, and all the style properties
- [Styles](https://lvgl.io/docs/pro/syntax/styles) and [Constants](https://lvgl.io/docs/pro/syntax/constants): To make UIs more maintainable
- [Data binding](https://lvgl.io/docs/pro/syntax/data-binding): Connect the UI to your application data
- [Testing](https://lvgl.io/docs/pro/syntax/testing) and the [CLI](https://lvgl.io/docs/pro/cli): To validate your work automatically
- [AI integration](https://lvgl.io/docs/pro/ai): For agents to learn how to work effectively with LVGL Pro and the XML

The [**lvgl/lvgl_pro**](https://github.com/lvgl/lvgl_pro) repository is also worth checking. It contains examples, tutorials, and
[`lvgl_widgets_xml/`](https://github.com/lvgl/lvgl_pro/tree/master/lvgl_widgets_xml) with the XML schema of LVGL's built-in widgets.
Both humans and agents can check exactly which properties, enums, styles, and other elements are available. See
[lv_slider.xml](https://github.com/lvgl/lvgl_pro/blob/master/lvgl_widgets_xml/v9.6.0/lv_slider.xml) as an example.
AI agents can clone the whole repo or get only one file.
