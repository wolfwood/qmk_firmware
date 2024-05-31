/*
Copyright 2023 Morgan Venable @_claussen

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <stdbool.h>
#include <stdint.h>
//#include "quantum.h"


#define ACHORDION

#ifdef ACHORDION
#include "features/achordion.h"
#endif


#define HRM(		   \
  R1C, R1N, R1E, R1S, R1W, \
  R2C, R2N, R2E, R2S, R2W, \
  R3C, R3N, R3E, R3S, R3W, \
  R4C, R4N, R4E, R4S, R4W, \
			   \
  L1C, L1N, L1E, L1S, L1W, \
  L2C, L2N, L2E, L2S, L2W, \
  L3C, L3N, L3E, L3S, L3W, \
  L4C, L4N, L4E, L4S, L4W, \
			   \
  RTD, RTP, RTU, RTN, RTK, RTDD, \
  LTD, LTP, LTU, LTN, LTK, LTDD  \
	     )			 \
  LAYOUT(			 \
  RCTL_T(R1C), R1N, R1E, R1S, R1W, \
  RSFT_T(R2C), R2N, R2E, R2S, R2W, \
  RGUI_T(R3C), R3N, R3E, R3S, R3W, \
  RALT_T(R4C), R4N, R4E, R4S, R4W, \
				 \
  LCTL_T(L1C), L1N, L1E, L1S, L1W, \
  LSFT_T(L2C), L2N, L2E, L2S, L2W, \
  LGUI_T(L3C), L3N, L3E, L3S, L3W, \
  LALT_T(L4C), L4N, L4E, L4S, L4W, \
    				 \
  RTD, RTP, RTU, RTN, RTK, RTDD, \
  LTD, LTP, LTU, LTN, LTK, LTDD)

#define BRM(		   \
  R1C, R1N, R1E, R1S, R1W, \
  R2C, R2N, R2E, R2S, R2W, \
  R3C, R3N, R3E, R3S, R3W, \
  R4C, R4N, R4E, R4S, R4W, \
			   \
  L1C, L1N, L1E, L1S, L1W, \
  L2C, L2N, L2E, L2S, L2W, \
  L3C, L3N, L3E, L3S, L3W, \
  L4C, L4N, L4E, L4S, L4W, \
			   \
  RTD, RTP, RTU, RTN, RTK, RTDD, \
  LTD, LTP, LTU, LTN, LTK, LTDD  \
			   )	 \
  LAYOUT(					\
       R1C, R1N, R1E, RCTL_T(R1S), R1W,		\
       R2C, R2N, R2E, RSFT_T(R2S), R2W,		\
       R3C, R3N, R3E, RGUI_T(R3S), R3W,		\
       R4C, R4N, R4E, RALT_T(R4S), R4W,		\
    						\
       L1C, L1N, L1E, LCTL_T(L1S), L1W,		\
       L2C, L2N, L2E, LSFT_T(L2S), L2W,		\
       L3C, L3N, L3E, LGUI_T(L3S), L3W,		\
       L4C, L4N, L4E, LALT_T(L4S), L4W,		\
						\
       RTD, RTP, RTU, RTN, RTK, RTDD,		\
       LTD, LTP, LTU, LTN, LTK, LTDD)


// set to  HRM or BRM to control mod placement or to LAYOUT to disable
#define MODLAYOUT BRM


static uint32_t tp_recal_timer;

void keyboard_post_init_user(void) {
  // Customise these values if you need to debug the matrix
  //debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;

  tp_recal_timer = timer_read32();
}

enum my_keycodes {
 BRACES = SAFE_RANGE,
 SV_RECALIBRATE_POINTER,
};

const key_override_t delete_key_override = ko_make_basic(MOD_MASK_GUI, KC_BSPC, KC_DEL);

const key_override_t **key_overrides = (const key_override_t *[]){
  	&delete_key_override,
	NULL
};


enum combos {
  COMBO_SE,
};

const uint16_t PROGMEM combo_se[] = {LSFT_T(KC_S), RSFT(KC_E), COMBO_END};

combo_t key_combos[] = {
  [COMBO_SE] = COMBO_ACTION(combo_se),
};

int16_t COMBO_LEN = ARRAY_SIZE(key_combos);

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch (combo_index) {
    case COMBO_SE:
      caps_word_on();
      break;
  }
}


enum layer {
    NORMAL,
    NAS,
    NAV,
    FUNC,
    MBO,
    NUM_LAYERS
};

const uint16_t PROGMEM keymaps[NUM_LAYERS][MATRIX_ROWS][MATRIX_COLS] = {
    [NORMAL] = MODLAYOUT(
             /*Center           North           East            South           West*/
        /*R1*/ KC_N,            KC_L,           KC_ENTER,       KC_H,           KC_M,
        /*R2*/ KC_E,            KC_U,           BRACES,         KC_COMMA,       KC_J,
        /*R3*/ KC_I,            KC_Y,           KC_LGUI/**/,    KC_DOT,         KC_K,
        /*R4*/ KC_O,            KC_SEMICOLON,   KC_QUOT,        KC_SLASH,       KC_BSLS,

        /*L1*/ KC_T,            KC_P,           KC_G,           KC_D,           KC_SPACE,
        /*L2*/ KC_S,            KC_F,           KC_B,           KC_C,           KC_MINUS,
        /*L3*/ KC_R,            KC_W,           KC_V,           KC_X,           QK_GESC,
        /*L4*/ KC_A,            KC_Q,           KC_TAB,         KC_Z,           KC_BSPC,

        /*Down                  Inner (pad)     Upper (Mode)    O.Upper (nail)  OL (knuckle) Pushthrough*/
        /*RT*/ TT(NAS),         KC_ENTER,       TG(NAV),       KC_BSPC,        TT(NAV),     TG(NAS),
        /*LT*/ KC_LSFT,         KC_SPACE,       TG(NAV),       KC_TAB,         TT(NAV),     CW_TOGG
    ),

    [NAS] = MODLAYOUT(
             /*Center           North           East            South           West*/
	/*R1*/ KC_7,            KC_AMPR,        KC_UNDS,        KC_KP_PLUS,     KC_6,
        /*R2*/ KC_8,            KC_KP_ASTERISK, KC_COLON,       KC_COMMA,       KC_CIRCUMFLEX,
        /*R3*/ KC_9,            KC_LPRN,        KC_LGUI,        KC_DOT,         KC_SEMICOLON,
        /*R4*/ KC_0,            KC_RPRN,        XXXXXXX,        KC_QUES,        KC_RBRC,

        /*L1*/ KC_4,            KC_DOLLAR,      KC_5,           KC_MINUS,       KC_SLASH,
	/*L2*/ KC_3,            KC_HASH,        KC_GT,          KC_PERCENT,     KC_LT,
        /*L3*/ KC_2,            KC_AT,          XXXXXXX,        KC_X,           KC_ESC,
        /*L4*/ KC_1,            KC_EXCLAIM,     KC_TILDE,       KC_EQUAL,       KC_DEL,

        /*Down                  Inner           Upper           Outer Upper     Outer Lower  Pushthrough*/
        /*RT*/ _______,         _______,        _______,        _______,        _______,     _______,
        /*LT*/ _______,         _______,        _______,        _______,        _______,     _______
    ),

    [NAV] = LAYOUT(
             /*Center           North           East            South           West*/
        /*R1*/ KC_LEFT,         KC_WH_U,        KC_PGUP,        KC_MS_L,        LCTL(KC_LEFT),
        /*R2*/ KC_RGHT,         KC_WH_D,        KC_PGDN,        KC_MS_R,        LCTL(KC_RGHT),
        /*R3*/ KC_DOWN,         KC_WH_L,        KC_HOME,        KC_MS_D,        LCTL(KC_DOWN),
        /*R4*/ KC_UP,           KC_WH_R,        KC_END,         KC_MS_U,        LCTL(KC_UP),

        /*L1*/ KC_LCTL,         LCTL(KC_Y),     _______,        KC_PSTE,        XXXXXXX,
        /*L2*/ KC_LSFT,         LSFT(KC_INS),   XXXXXXX,        KC_COPY,        XXXXXXX,
        /*L3*/ KC_LGUI,         LCTL(KC_W),     XXXXXXX,        KC_CUT,         XXXXXXX,
        /*L4*/ KC_LALT,         KC_AGIN,        _______,        KC_UNDO,       _______,

        /*Down                  Inner           Upper           Outer Upper     Outer Lower  Pushthrough*/
        /*RT*/ _______,         _______,        _______,        _______,        _______,     _______,
        /*LT*/ _______,         _______,        _______,        _______,        _______,     _______
    ),

    [FUNC] = LAYOUT(
             /*Center           North           East            South           West*/
        /*R1*/ KC_HOME,         KC_UP,          KC_RIGHT,       KC_DOWN,        KC_LEFT,
        /*R2*/ XXXXXXX,         KC_F8,          XXXXXXX,        KC_F7,          KC_END,
        /*R3*/ KC_PSCR,         KC_F10,         KC_LGUI,        KC_F9,          KC_INS,
        /*R4*/ KC_PAUSE,        KC_PGUP,        KC_F12,         KC_PGDN,        KC_F11,

        /*L1*/ KC_HOME,         KC_UP,          KC_RIGHT,       KC_DOWN,        KC_LEFT,
        /*L2*/ XXXXXXX,         KC_F6,          XXXXXXX,        KC_F5,          XXXXXXX,
        /*L3*/ XXXXXXX,         KC_F4,          XXXXXXX,        KC_F3,          KC_ESC,
        /*L4*/ XXXXXXX,         KC_F2,          XXXXXXX,        KC_F1,          KC_DEL,

	/*Down                  Inner           Upper           Outer Upper     Outer Lower  Pushthrough*/
	/*RT*/ _______,         _______,        _______,        _______,        _______,     _______,
        /*LT*/ _______,         _______,        _______,        _______,        _______,     _______
    ),

    [MBO] = LAYOUT(
             /*Center           North           East            South           West*/
        /*R1*/ KC_TRNS,         KC_TRNS,        KC_TRNS,        KC_BTN1,        KC_TRNS,
        /*R2*/ KC_TRNS,         KC_TRNS,        KC_TRNS,        KC_BTN3,        KC_TRNS,
        /*R3*/ KC_TRNS,         KC_TRNS,        KC_TRNS,        KC_BTN2,        KC_TRNS,
        /*R4*/ KC_TRNS,        SV_RECALIBRATE_POINTER, KC_TRNS, KC_BTN1,        KC_TRNS,

        /*L1*/ KC_TRNS,         KC_TRNS,        KC_TRNS,        KC_BTN1,        KC_TRNS,
        /*L2*/ KC_TRNS,         KC_TRNS,        KC_TRNS,        KC_BTN3,        KC_TRNS,
        /*L3*/ KC_TRNS,         KC_TRNS,        KC_TRNS,        KC_BTN2,        KC_TRNS,
        /*L4*/ KC_TRNS,        SV_RECALIBRATE_POINTER, KC_TRNS, KC_BTN1,        KC_TRNS,

	/*RT*/ _______,         _______,        _______,        _______,        _______,     _______,
        /*LT*/ _______,         _______,        _______,        _______,        _______,     _______
    )
};


#if defined MH_AUTO_BUTTONS && defined PS2_MOUSE_ENABLE && defined MOUSEKEY_ENABLE
void mouse_mode(bool);

static uint16_t mh_auto_buttons_timer;
extern int tp_buttons; // mousekey button state set in action.c and used in ps2_mouse.c

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

      // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif

    tp_recal_timer = timer_read32();

#if defined MH_AUTO_BUTTONS && defined PS2_MOUSE_ENABLE && defined MOUSEKEY_ENABLE
    if (mh_auto_buttons_timer) {
      switch (keycode) {
      case KC_BTN1:
      case KC_BTN2:
      case KC_BTN3:
//      case KC_WBAK:
//      case KC_WFWD:
	break;
      default:
	mouse_mode(false);
      }
    }
#endif

#ifdef ACHORDION
    if (!process_achordion(keycode, record)) { return false; }
#endif

    const uint8_t mods = get_mods();

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
    case SV_RECALIBRATE_POINTER:
      recalibrate_pointer();
      return false;
    default:
      return true;
  }
};

#if defined MH_AUTO_BUTTONS && defined PS2_MOUSE_ENABLE && defined MOUSEKEY_ENABLE
void ps2_mouse_moved_user(report_mouse_t *mouse_report) {
  if (mh_auto_buttons_timer) {
    mh_auto_buttons_timer = timer_read();
  } else {
    if (!tp_buttons) {
      mouse_mode(true);
  #if defined CONSOLE_ENABLE
      print("mh_auto_buttons: on\n");
  #endif
    }
  }
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

  if (tp_recal_timer && (timer_elapsed32(tp_recal_timer) > TP_RECAL_TIMEOUT)) {
    recalibrate_pointer();
    tp_recal_timer = timer_read32();
  }

#ifdef ACHORDION
  achordion_task();
#endif
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

#endif // defined MH_AUTO_BUTTONS && defined PS2_MOUSE_ENABLE && #defined MOUSEKEY_ENABLE
