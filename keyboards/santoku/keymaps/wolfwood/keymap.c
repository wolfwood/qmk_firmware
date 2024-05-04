/* Copyright 2022 Tye (@tyetye)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Current features of this keymap for the Santoku keyboard:
 Trackpoint speed and acceleration settings are adjustable on-the-fly from the Function layer.
 Trackpoint drag scroll speed is adjustable on-the-fly from the Function layer.
 Mouse input from the Trackpoint is smoothed and scaled in realtime (through the features noted above).
 Combos provide easy web browser tab navigation with only the right hand (no reaching for ctrl-blah).
 Home row mod keys (SHFT, CTL, ALT, GUI).
 TAPALTTB for easy switching to open windows using just one key (an improvement on the "Super Alt Tab" example code from the QMK docs).
 "Caps Word" feature intelligently turns off CAPSLOCK when a non alphnumberic key is pressed (wonderful QMK feature).
 Just for fun: QMK's WPM feature is available on the OLED screen.
 Traditional shift keys in the lower corners are togglable (on or off). This helps the user to ease the transition to home row mods while still allowing the user to be productive during crunch time.

 * Desired TODOs:
 Write to memory so Trackpoint speed and scroll settings stick between keyboard reboots
 IN PROGRESS. Improve SuperAltTab feature so that holding down the key *does not* move to the next window but keeps Alt pressed. Window gets selected *only* after timeout (~1000ms).
 -- This will allow the user to "look through" the AltTab choices without having to worry about quickly selecting one because of the timeout.
 -- But will still also allow the user to easily tap the key once and quickly toggle between the two most recent windows.
 Update the mouse pointer smoothing code to use integer math instead of floating point math. This will probably require some clever log lookup tables but could save up to 1000 bytes in the compiled hex.
 IN TESTING. Change the scroll wheel to use QMK's Pointing Device feature instead of MouseKeys. In theory, this will make the scroll wheel movement smoother because Mouse Keys expect a held down keyswitch instead of a clicky rotary encoder.
 Create a dedicated "help" screen. This will take a lot of bytes because of raw text. Still uncertain how to approach this.
 Add sidescroll ability to the scrollwheel.
 Slowly make options to test the transition to a 36 key layout (make alternatives to the outer columns)
 -- Make the logo a global variable instead of static in the function (to see if it affects compile size or the compiler is smart enough to incorporate it from the beginning (before the function is ever called?)
 -- Make ALTTAB delay variable and add ALTTAB timeout setting to settings page (yet another reason to have a dedicated settings page.
 -- Add custom Santoku logo to the OLED.

*/

#include QMK_KEYBOARD_H
#include "santoku.h"
#include <stdbool.h>   // This is just to get rid of the linter warning
#include <stdint.h>   // This is just to get rid of the linter warning

// Santoku keymap set up
enum santoku_layers {
  _QWERTY,
  /*_TARMAKDH1,
    _TARMAKDH1B,
    _TARMAKDH2,
    _TARMAKDH3,
    _TARMAKDH4,
    _TARMAKDH5,*/
    _COLEMAKDH,
    _SYMBOL,
    _NAVIGATION,
    _FUNCTION,
    _MOUSE
};

enum santoku_keycodes {
    DEC_ACCL = SAFE_RANGE,
    INC_ACCL,
    DEC_SPED,
    INC_SPED,
    DEC_DRGS,
    INC_DRGS,
    TAPALTTB,
    A_B_TEST,

    BRACES
};

#define ___x___ XXXXXXX


// Trackpoint/mouse pointer dynamic speed controls and GUI/OLED settings
uint8_t acceleration_setting        = 5;
float   acceleration_values[6]      = {0.6, 0.8, 1, 1.2, 1.4, 1.6};
uint8_t linear_reduction_setting    = 5;
float   linear_reduction_values[6]  = {2.4, 2.2, 2.0, 1.8, 1.6, 1.4};
uint8_t drag_scroll_speed_setting   = 4;
uint8_t drag_scroll_speed_values[6] = {8, 7, 6, 5, 4, 3};
char *  progress_bars[6]            = {"[=     ]", "[==    ]", "[===   ]", "[====  ]", "[===== ]", "[=PLAID]"};
uint8_t scroll_wheel_test_setting   = 0;
enum scroll_wheel_setting{
    DEFAULT,
    DEFAULT_FASTER,
    FANCY,
    FANCY2
};

// Shift + Backspace = Del
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_GUI, KC_BSPC, KC_DEL);
const key_override_t delete_thumb_override = ko_make_basic(MOD_MASK_GUI, LT(_NAVIGATION, KC_BSPC), KC_DEL);

// Shift + esc = ~

// GUI + esc = `

const key_override_t **key_overrides = (const key_override_t *[]){
  	&delete_key_override,
	&delete_thumb_override,
	NULL
};


// Combo stuff
enum combos {
  COMBO_FG,
  COMBO_TG,
  COMBO_HJ,
  COMBO_MN,
};

const uint16_t PROGMEM combo_fg[]       = {LCTL_T(KC_F), KC_G, COMBO_END};
const uint16_t PROGMEM combo_tg[]       = {LCTL_T(KC_T), KC_G, COMBO_END};
const uint16_t PROGMEM combo_hj[]        = {RCTL_T(KC_J), KC_H, COMBO_END};
const uint16_t PROGMEM combo_mn[]        = {RCTL_T(KC_N), KC_M, COMBO_END};

combo_t key_combos[] = {
  [COMBO_FG] = COMBO_ACTION(combo_fg),
  [COMBO_TG] = COMBO_ACTION(combo_tg),
  [COMBO_HJ] = COMBO_ACTION(combo_hj),
  [COMBO_MN] = COMBO_ACTION(combo_mn)
};

uint16_t COMBO_LEN = ARRAY_SIZE(key_combos);

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch (combo_index) {
    case COMBO_FG:
    case COMBO_TG:
      if (pressed) {
	tap_code16(KC_HOME);
      }
      break;
    case COMBO_HJ:
    case COMBO_MN:
      if (pressed) {
	tap_code16(KC_END);
      }
      break;
  }
}

// Santoku keymap layout
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] ={
      {QK_GESC, KC_Q,         KC_W,         KC_E,                   KC_R,         KC_T,         KC_Y,            KC_U,            KC_I,         KC_O,         KC_P,            KC_QUOT},
      {KC_BSPC, RALT_T(KC_A), LGUI_T(KC_S), LSFT_T(KC_D),           LCTL_T(KC_F), KC_G,         KC_H,            RCTL_T(KC_J),    RSFT_T(KC_K), RGUI_T(KC_L), RALT_T(KC_SCLN), KC_ENT},
      {KC_TAB,  KC_Z,         KC_X,         LT(_SYMBOL,KC_C),       LT(_NAVIGATION,KC_V),KC_B,  KC_N,            LT(_SYMBOL,KC_M),KC_COMM,      KC_DOT,       KC_SLSH,         KC_BSLS},
      {___x___,  ___x___,      ___x___, LT(_NAVIGATION, KC_BSPC),LT(_SYMBOL, KC_SPC),LT(_FUNCTION, QK_GESC),  KC_TAB,LT(_SYMBOL, KC_ENT),KC_TAB,  ___x___,      ___x___,         ___x___}},

  /*[_TARMAKDH1] ={
      {_______,  _______,  _______,  KC_J,     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______},
      {_______,  _______,  _______,  _______,  _______,  _______,  KC_M,    RCTL_T(KC_N),RSFT_T(KC_E),_______,_______,_______},
      {_______,  _______,  _______,  _______,  _______,  _______,  KC_K,     LT(_SYMBOL,KC_H),
       _______,  _______,  _______,  _______},
      {___x___,  ___x___,  ___x___,  _______,  _______,  _______,  _______,  _______,  _______,  ___x___,  ___x___,  ___x___}} ,

    [_TARMAKDH1B] ={
      {_______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______},
      {_______,  _______,  _______,  _______,  _______,  _______,  KC_M,     _______,  _______,  _______,  _______,  _______},
      {_______,  _______,  _______,  _______,  _______,  _______,  _______,  LT(_SYMBOL,KC_H),     _______,  _______,  _______,  _______},
      {___x___,  ___x___,  ___x___,  _______,  _______,  _______,  _______,  _______,  _______,  ___x___,  ___x___,  ___x___}} ,

    [_TARMAKDH2] ={
      {_______,  _______,  _______,  KC_F,     _______,  KC_B,     _______,  _______,  _______,  _______,  _______,  _______},
      {_______,  _______,  _______,  _______,LCTL_T(KC_T),_______, _______,  _______,  _______,  _______,  _______,  _______},
      {_______,  _______,  _______,  _______,   LT(_NAVIGATION,KC_J), KC_V,  _______,  _______,  _______,  _______,  _______,  _______},
      {___x___,  ___x___,  ___x___,  _______,  _______,  _______,  _______,  _______,  _______,  ___x___,  ___x___,  ___x___}} ,

    [_TARMAKDH3] ={
      {_______,  _______,  _______,  _______,  KC_J,     _______,  _______,  _______,  _______,  _______,  _______,  _______},
      {_______,  _______,LGUI_T(KC_R),LSFT_T(KC_S),_______,_______,_______,  _______,  _______,  _______,  _______,  _______},
      {_______,  _______,  _______,  KC_D,     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______},
      {___x___,  ___x___,  ___x___,  _______,  _______,  _______,  _______,  _______,  _______,  ___x___,  ___x___,  ___x___}} ,

    [_TARMAKDH4] ={
      {_______,  _______,  _______,  _______,  KC_P,     _______,  KC_J,     _______,  _______,  KC_Y,     KC_SCLN,  _______},
      {_______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_O,     _______},
      {_______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______},
      {___x___,  ___x___,  ___x___,  _______,  _______,  _______,  _______,  _______,  _______,  ___x___,  ___x___,  ___x___}} ,

    [_TARMAKDH5] ={
      {_______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_L,     KC_U,     _______,  _______,  _______},
      {_______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_I,     _______,  _______},
      {_______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______},
      {___x___,  ___x___,  ___x___,  _______,  _______,  _______,  _______,  _______,  _______,  ___x___,  ___x___,  ___x___}} ,*/

    /*[_TARMAKDH3] ={
      {_______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______},
      {_______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______},
      {_______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______},
      {___x___,  ___x___,  ___x___,  _______,  _______,  _______,  _______,  _______,  _______,  ___x___,  ___x___,  ___x___}
      } ,*/

    [_COLEMAKDH] ={
      {QK_GESC, KC_Q,   KC_W,         KC_F,                   KC_P,         KC_B,         KC_J,            KC_L,            KC_U,         KC_Y,         KC_SCLN,         KC_QUOT},
      {KC_BSPC, RALT_T(KC_A), LGUI_T(KC_R), LSFT_T(KC_S),           LCTL_T(KC_T), KC_G,         KC_M,            RCTL_T(KC_N),    RSFT_T(KC_E), RGUI_T(KC_I), RALT_T(KC_O),    KC_ENT},
      {KC_TAB,  KC_Z,         KC_X,       LT(_SYMBOL,KC_C), LT(_NAVIGATION,KC_D), KC_V,         KC_K,           LT(_SYMBOL,KC_H), KC_COMM,      KC_DOT,       KC_SLSH,         KC_BSLS},
      {___x___,  ___x___,      ___x___, LT(_NAVIGATION, KC_BSPC),LT(_SYMBOL, KC_SPC),LT(_FUNCTION, KC_ESC),  KC_TAB,LT(_SYMBOL, KC_ENT),KC_TAB,  ___x___,      ___x___,         ___x___}},

    [_SYMBOL] =
    {/*SYMBOL*/
        {KC_GRV,  KC_EXLM,      KC_AT,        KC_HASH,      KC_DLR,       KC_PERC,  KC_CIRC, KC_AMPR,      KC_ASTR,      KC_LPRN,      KC_RPRN,      KC_MINUS},
        {_______, RALT_T(KC_1), LGUI_T(KC_2), LSFT_T(KC_3), LCTL_T(KC_4), KC_5,     KC_6,    RCTL_T(KC_7), RSFT_T(KC_8), RGUI_T(KC_9), RALT_T(KC_0), KC_EQL},
        {KC_TILD, KC_BSLS,      KC_UNDS,      KC_PLUS,      KC_LCBR,      KC_RCBR,  KC_LBRC, BRACES,      KC_COMM,      KC_DOT,       KC_SLSH,      KC_PIPE},
        {___x___, ___x___,      ___x___,      _______,      _______,      _______,  _______, _______,      _______,      ___x___,      ___x___,      ___x___}},

    [_NAVIGATION] =
    {/*NAVIGATION*/
      {TG(_NAVIGATION),XXXXXXX,XXXXXXX,XXXXXXX, XXXXXXX,  XXXXXXX,  KC_HOME,       KC_PGDN,       KC_PGUP,            KC_UP,                XXXXXXX, XXXXXXX},
        {KC_ESC,  KC_RALT,  KC_LGUI,  KC_LSFT,  KC_LCTL,  XXXXXXX,  KC_END,        KC_LEFT,       KC_RGHT,            KC_DOWN,                KC_UP, XXXXXXX},
        {_______, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, LCTL(KC_LEFT), LCTL(KC_RGHT),      LCTL(KC_DOWN),          LCTL(KC_UP), _______},
        {___x___, ___x___,  ___x___,  _______,  _______,  _______,  _______,       _______,       _______,            ___x___,              ___x___, ___x___}},

    [_FUNCTION] =
    {/*FUNCTION*/
      {TG(_COLEMAKDH), XXXXXXX,       DEC_ACCL, INC_ACCL, DEC_SPED, INC_SPED, DEC_DRGS, INC_DRGS, A_B_TEST,       XXXXXXX, XXXXXXX, XXXXXXX},
        {KC_ESC,  RALT_T(KC_F1), LGUI_T(KC_F2),          LSFT_T(KC_F3),          LCTL_T(KC_F4),     KC_F5,             KC_F6,                 RCTL_T(KC_F7),         RSFT_T(KC_F8), RGUI_T(KC_F9), RALT_T(KC_F10), XXXXXXX},
        {_______, XXXXXXX,       XXXXXXX,                XXXXXXX,                XXXXXXX,           XXXXXXX,           KC_F11,                KC_F12,                XXXXXXX,       XXXXXXX, XXXXXXX, _______},
        {___x___, ___x___,       ___x___,                KC_DEL,                 KC_SPC,            XXXXXXX,           XXXXXXX,               XXXXXXX,               QK_BOOT,       ___x___, ___x___, ___x___}},

    [_MOUSE] ={
      {_______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______},
      {_______,  _______,  KC_BTN2,  KC_BTN3,  KC_BTN1,  _______,  _______,  _______,  _______,  _______,  _______,  _______},
      {_______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______},
      {___x___,  ___x___,  ___x___,  _______,  _______,  _______,  _______,  _______,  _______,/*KC_BTN2,  KC_BTN1,  KC_BTN3,*/  ___x___,  ___x___,  ___x___}}
};

/*
void pointing_device_init_user(void) {
    set_auto_mouse_layer(_MOUSE); // only required if AUTO_MOUSE_DEFAULT_LAYER is not set to index of <mouse_layer>
    set_auto_mouse_enable(true);         // always required before the auto mouse feature will work
}
*/

//#if defined MH_AUTO_BUTTONS && defined PS2_MOUSE_ENABLE && defined MOUSEKEY_ENABLE
void mouse_mode(bool);

static uint16_t mh_auto_buttons_timer;
extern int tp_buttons; // mousekey button state set in action.c and used in ps2_mouse.c

//#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  //#if defined MH_AUTO_BUTTONS && defined PS2_MOUSE_ENABLE && defined MOUSEKEY_ENABLE
  if (mh_auto_buttons_timer) {
    switch (keycode) {
    case KC_BTN1:
    case KC_BTN2:
    case KC_BTN3:
    case KC_WBAK:
    case KC_WFWD:
      break;
    default:
      mouse_mode(false);
    }
  }
  //#endif

  const uint8_t mods = get_mods();
  //const uint8_t oneshot_mods = get_oneshot_mods();

  switch (keycode) {
        case BRACES:
	  if (record->event.pressed) {
	    //clear_oneshot_mods();  // Temporarily disable mods.
	    unregister_mods(MOD_MASK_CSAG);
	    if ((mods /*| oneshot_mods*/) & MOD_MASK_CTRL) {
	      if ((mods /*| oneshot_mods*/) & MOD_MASK_SHIFT) {
		SEND_STRING("''");
	      } else {
		SEND_STRING("\"\"");
	      }
	    } else if ((mods /*| oneshot_mods*/) & MOD_MASK_ALT) {
	      SEND_STRING("<>");
	    } else if ((mods /*| oneshot_mods*/) & MOD_MASK_GUI) {
	      SEND_STRING("()");
	    } else if ((mods /*| oneshot_mods*/) & MOD_MASK_SHIFT) {
		SEND_STRING("{}");
	    } else {
	      SEND_STRING("[]");
	    }
	    tap_code(KC_LEFT);  // Move cursor between braces.
	    register_mods(mods);  // Restore mods.
	  }
	  return false;

        case DEC_ACCL:
            if (record->event.pressed) {
                if (acceleration_setting > 0) {
                    acceleration_setting--;
                }
            }
            return true; // Let QMK send the press/release events
            break;

        case INC_ACCL:
            if (record->event.pressed) {
                if (acceleration_setting < 5) {
                    acceleration_setting++;
                }
            }
            return true; // Let QMK send the press/release events
            break;

        case DEC_SPED:
            if (record->event.pressed) {
                if (linear_reduction_setting > 0) {
                    linear_reduction_setting--;
                }
            }
            return true; // Let QMK send the press/release events
            break;

        case INC_SPED:
            if (record->event.pressed) {
                if (linear_reduction_setting < 5) {
                    linear_reduction_setting++;
                }
            }
            return true; // Let QMK send the press/release events
            break;

        case DEC_DRGS:
            if (record->event.pressed) {
                if (drag_scroll_speed_setting > 0) {
                    drag_scroll_speed_setting--;
                }
            }
            return true; // Let QMK send the press/release events
            break;

        case INC_DRGS:
            if (record->event.pressed) {
                if (drag_scroll_speed_setting < 5) {
                    drag_scroll_speed_setting++;
                }
            }
            return true; // Let QMK send the press/release events
            break;

        case A_B_TEST:
            if (record->event.pressed) {
                scroll_wheel_test_setting++;
                if (scroll_wheel_test_setting > FANCY2) {
                    scroll_wheel_test_setting = 0;
                }
            }
            return true;
            break;
    }
    return true;
}

void matrix_scan_user(void) {
  if (mh_auto_buttons_timer && (timer_elapsed(mh_auto_buttons_timer) > MH_AUTO_BUTTONS_TIMEOUT)) {
    if (!tp_buttons) {
      mouse_mode(false);
  #if defined CONSOLE_ENABLE
      print("mh_auto_buttons: off\n");
  #endif
    }
  }
}

void mouse_mode(bool on) {
  if (on) {
    layer_on(MH_AUTO_BUTTONS_LAYER);
    mh_auto_buttons_timer = timer_read();
  } else {
    layer_off(MH_AUTO_BUTTONS_LAYER);
    mh_auto_buttons_timer = 0;
  }
}

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    static bool show_vanity_text = true;
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
        0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F,
        0x90, 0x91, 0x92, 0x93, 0x94, 0xA0, 0xA1, 0xA2,
        0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA,
        0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2,
        0xB3, 0xB4, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5,
        0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD,
        0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00};
    if (show_vanity_text) {
        uint32_t vanity_timeout = 10000;
        oled_write_P(qmk_logo, false);
        oled_write_ln_P(PSTR("        by Tye"), false);
        oled_write_ln_P(PSTR("   gestaltinput.com"), false);
        oled_write_ln_P(PSTR(""), false);
        oled_write_ln_P(PSTR("     Hello, World"), false);
        if (timer_read() > vanity_timeout) {
            show_vanity_text = false;
        }
    }
    else {
        switch (get_highest_layer(layer_state)) {
            case _QWERTY:
                if ((host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK))) {
                    oled_write_P(PSTR("      Caps Lock     \n"), true);
                } else if ( is_caps_word_on() ) {
                    oled_write_P(PSTR("      Caps Word     \n"), true);
                } else {
                    oled_write_P(PSTR("       QWERTY\n"), false);
                }
                oled_write_P(PSTR("WPM:"), false);
                //oled_write(get_u8_str(get_current_wpm(), ' '), false);
                oled_write_ln_P(PSTR(""), false);
                oled_write_ln_P(PSTR("TB  qwert | yuiop\\"), false);
                oled_write_ln_P(PSTR("ES  asdfg | hjkl;'"), false);
                oled_write_ln_P(PSTR("SH  zxcvb | nm,./"), false);
                oled_write_P(qmk_logo, false);
                break;

            case _COLEMAKDH:
                oled_write_P(PSTR("       Colemak    \n"), true);
                oled_write_ln_P(PSTR(""), false);
                oled_write_ln_P(PSTR(""), false);
                oled_write_ln_P(PSTR(""), false);
                oled_write_ln_P(PSTR(""), false);
                oled_write_ln_P(PSTR(""), false);
                oled_write_ln_P(PSTR(""), false);
                oled_write_ln_P(PSTR(""), false);
                break;

	    case _SYMBOL:
                oled_write_P(PSTR("       Symbol       \n"), true);
                oled_write_ln_P(PSTR(""), false);
                oled_write_ln_P(PSTR(" `  !@#$% | ^&*()-"), false);
                oled_write_ln_P(PSTR("ES  12345 | 67890="), false);
                oled_write_ln_P(PSTR("SH  \\_+{} | [],./"), false);
                oled_write_ln_P(PSTR(""), false);
                oled_write_ln_P(PSTR(""), false);
                oled_write_ln_P(PSTR(""), false);
                break;

            case _NAVIGATION:
                oled_write_P(PSTR("      Navigation    \n"), true);
                oled_write_ln_P(PSTR(""), false);
                oled_write_ln_P(PSTR("   | HM PD PU EN"), false);
                oled_write_ln_P(PSTR("   | << vv ^^ >>"), false);
                oled_write_ln_P(PSTR("   | D[ D] D+ D-"), false);
                oled_write_ln_P(PSTR(""), false);
                oled_write_ln_P(PSTR(""), false);
                oled_write_ln_P(PSTR(""), false);
                break;

            case _MOUSE:
                oled_write_P(PSTR("       Mouse      \n"), true);
                oled_write_ln_P(PSTR(""), false);
                oled_write_ln_P(PSTR(""), false);
                oled_write_ln_P(PSTR(""), false);
                oled_write_ln_P(PSTR(""), false);
                oled_write_ln_P(PSTR(""), false);
                oled_write_ln_P(PSTR(""), false);
                oled_write_ln_P(PSTR(""), false);
                break;

	    case _FUNCTION:
                oled_write_P(PSTR(" Function & Settings\n"), true);
                oled_write_P(PSTR("SCROLLWHEEL TEST:"), false);
                oled_write(get_u8_str(scroll_wheel_test_setting, ' '), false);
                oled_write_ln_P(PSTR(""), false);
                oled_write_ln_P(PSTR("     -+-+ | -+A"), false);
                oled_write_ln_P(PSTR("ES F12345 | 67890"), false);
                oled_write_ln_P(PSTR("CL F      | ab"), false);
                oled_write_P(PSTR("TP Accl W/E "), false);
                oled_write_ln(progress_bars[acceleration_setting], false);
                oled_write_P(PSTR("TP Spd  R/T "), false);
                oled_write_ln(progress_bars[linear_reduction_setting], false);
                oled_write_P(PSTR("TP Scrl Y/U "), false);
                oled_write_ln(progress_bars[drag_scroll_speed_setting], false);
                break;

            default:
                oled_write_ln_P(PSTR("Undefined"), false);
        }
    }

    return false;
}
#endif


void ps2_mouse_moved_user(report_mouse_t *mouse_report) {
    if (mh_auto_buttons_timer) {
    mh_auto_buttons_timer = timer_read();
  } else {
      if (!tp_buttons/* && !IS_LAYER_ON(_ALB) && !IS_LAYER_ON(_MO2)*/) {
      mouse_mode(true);
  #if defined CONSOLE_ENABLE
      print("mh_auto_buttons: on\n");
  #endif
    }
  }
    // The math below turns the Trackpoint x and y reports (movements) into a vector and scales the vector with some trigonometry.
    // This allows the user to dynamically adjust the mouse cursor sensitivity to their liking.
    // It also results in arguably smoother movement than just multiplying the x and y values by some fixed value.
    if (mouse_report->x != 0 || mouse_report->y != 0) {
        float hypotenuse        = sqrt((mouse_report->x * mouse_report->x) + (mouse_report->y * mouse_report->y));
        float scaled_hypotenuse = pow(hypotenuse, acceleration_values[acceleration_setting]) / linear_reduction_values[linear_reduction_setting];
        float angle             = atan2(mouse_report->y, mouse_report->x);
        mouse_report->x += (scaled_hypotenuse * cos(angle));
        mouse_report->y += (scaled_hypotenuse * sin(angle));
    }
    // Drag scrolling with the Trackpoint is reported so often that it makes the feature is unusable without slowing it down.
    // The below code only reports when the counter is evenly divisible by the chosen integer speed.
    static uint16_t drag_scroll_counter = 0;
    drag_scroll_counter == 40320 ? drag_scroll_counter = 0 : drag_scroll_counter++ ; // Because 8!==40320 (allows clean mod divisibility and avoids scrolling surge when resetting to 0)
    if ((mouse_report->v != 0 || mouse_report->h != 0) && drag_scroll_counter % drag_scroll_speed_values[drag_scroll_speed_setting] != 0) {
        mouse_report->v = 0;
        mouse_report->h = 0;
    }
}


#ifdef ENCODER_ENABLE

/*
   The Trackpoint polling causes small delays in the keyboard/matrix polling.
   This shows up as minor tearing in the OLED redraw and
   scrollwheel spinning. The code in encoder_update_user is a quick and dirty
   attempt to try a few different methods to smooth out the variations in the
   scrollwheel readings. (It will *not* increase the actual polling rate)
*/
/*bool encoder_update_user(uint8_t index, bool clockwise) {

    // float step_values[10] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
    float step_values[10] = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.2, 0.2, 0.2};
    report_mouse_t currentReport = pointing_device_get_report();
    static uint16_t encoder_timer    = 0;
    static uint16_t timer_difference = 0;
    static uint16_t hard_delay_max       = 25;
    timer_difference = timer_elapsed(encoder_timer);
    if (timer_difference < hard_delay_max-10) {
        wait_ms(hard_delay_max-10 );
    }
    else if (timer_difference < hard_delay_max-5) {
        wait_ms(hard_delay_max-5 );
    }
    else if (timer_difference < hard_delay_max) {
        wait_ms(hard_delay_max);
    }
    static bool clockwise_previous = 0;
    if (timer_difference < 50 && clockwise != clockwise_previous) {
        clockwise = clockwise_previous;
    }

    if (scroll_wheel_test_setting == DEFAULT) {
        currentReport.v = .1 * (clockwise ? 1.0 : -1.0);
    }
    else if (scroll_wheel_test_setting == DEFAULT_FASTER) {
        currentReport.v = .2 * (clockwise ? 1.0 : -1.0);
    }
    else if (scroll_wheel_test_setting == FANCY) {
        currentReport.v = step_values[ timer_difference / 10] * (clockwise ? 1.0 : -1.0);
    }
    else if (scroll_wheel_test_setting == FANCY2) {
        clockwise ? tap_code(KC_WH_U) : tap_code(KC_WH_D);
    }
    pointing_device_set_report(currentReport);
    pointing_device_send();
    encoder_timer = timer_read();
    return true;
    }*/

bool encoder_update_user(uint8_t index, bool clockwise) {
    // float step_values[10] = {2.0, 2.0, 1.8, 1.8, 1.6, 1.6, 1.4, 1.4, 1.2, 1.0};
    // float step_values[10] = {3.0, 3.0, 3.0, 2.0, 2.0, 2.0, 1.0, 1.0, 1.0, 1.0};
    // float step_values[10] = {2.4, 2.2, 2.0, 1.8, 1.6, 1.4, 1.2, 1.0, 0.8, 0.6};
    // float step_values[10] = {1.0, 0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1};
    // float step_values[10] = {.65, .50, .55, 0.5, 0.45, 0.4, 0.35, 0.3, 0.25, 0.2};
    // float step_values[10] = { .35, 0.35, 0.30, 0.30, 0.25, 0.25, 0.20, 0.20, 0.15, 0.15};
    // float step_values[10] = { .30, 0.20, 0.20, 0.20, 0.20, 0.20, 0.10, 0.10, 0.10, 0.10};
    // float step_values[10] = { .40, .40, .35, 0.35, 0.30, 0.30, 0.25, 0.25, 0.20, 0.20};
    // float step_values[11] = {2.0, 1,8, 1.6, 1.4, 1.2, 1.0, 0.8, 0.6, 0.4, 0.2};
    // float step_values[10] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
    float step_values[10] = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.2, 0.2, 0.2};
    report_mouse_t currentReport = pointing_device_get_report();
    static uint16_t encoder_timer    = 0;
    static uint16_t timer_difference = 0;
    timer_difference = timer_elapsed(encoder_timer);
    if (timer_difference < 20) {
        wait_ms(20 - timer_difference);
    }
    static bool clockwise_previous = 0;
    if (timer_difference < 50 && clockwise != clockwise_previous) {
        clockwise = clockwise_previous;
    }

    if (scroll_wheel_test_setting == DEFAULT) {
        currentReport.v = .1 * (clockwise ? 1.0 : -1.0);
    }
    else if (scroll_wheel_test_setting == DEFAULT_FASTER) {
        currentReport.v = .2 * (clockwise ? 1.0 : -1.0);
    }
    else if (scroll_wheel_test_setting == FANCY) {
        currentReport.v = step_values[ timer_difference / 10] * (clockwise ? 1.0 : -1.0);
    }
    else if (scroll_wheel_test_setting == FANCY2) {
        clockwise ? tap_code(KC_WH_U) : tap_code(KC_WH_D);
    }
    pointing_device_set_report(currentReport);
    //pointing_device_send();
    encoder_timer = timer_read();
    return true;
}
#endif


void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable   = false;
    debug_matrix   = false;
    debug_keyboard = false;
    debug_mouse    = false;

}

//void ps2_mouse_init_user() {

//ps2_mouse_set_stream_mode();
//}
