/* Copyright 2021 wolfwood
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
#include QMK_KEYBOARD_H

// XXX figure out how to unify copy paste in firefox, terminal, tmux, emacs
// XXX figure out how to unify paging in browser, terminal, tmux, man, less, emacs

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    // from DM: F# keys, numpad, [] {} and other displaced or harder to reach symbols
    //_SYM,
    // copypaste, pgup/down home end ? media/volume?
    //_NAV,
    // copypaste? mousekeys? scrolling?
    //_MOUSE,
    // Mouse Buttons Only (on thumbs leaving letters alone) stick copy/paste somewhere?
    _MBO
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT_right_hand(
		     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_EQL,
		     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSLS,
		     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  RCTL_T(KC_QUOT),
		     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSPC,
		               KC_UP,
		     KC_LEFT,  KC_ENT,   KC_RGHT,
		               KC_DOWN,
		     KC_TILD,            KC_GRV,
		     KC_GESC,  KC_ENT,   KC_TAB
    ),
    /*[_FN] = LAYOUT(
        QMKBEST, QMKURL,  _______,
            RESET,    XXXXXXX
	    )*/
    [_MBO] = LAYOUT_right_hand(
		     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
		     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
		     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
		     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
		               KC_TRNS,
		     KC_TRNS,  KC_TRNS,  KC_TRNS,
		               KC_TRNS,
		     KC_WBAK,            KC_WFWD,
		     KC_BTN2,  KC_BTN1,  KC_BTN3
    ),
};

#if defined MH_AUTO_BUTTONS && defined PS2_MOUSE_ENABLE && defined MOUSEKEY_ENABLE
void mouse_mode(bool);

static uint16_t mh_auto_buttons_timer;
extern int tp_buttons; // mousekey button state set in action.c and used in ps2_mouse.c

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QMKBEST:
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING("QMK is the best thing ever!");
            } else {
                // when keycode QMKBEST is released
            }
            break;
        case QMKURL:
            if (record->event.pressed) {
                // when keycode QMKURL is pressed
                SEND_STRING("https://qmk.fm/\n");
            } else {
                // when keycode QMKURL is released
            }
            break;
    }

#if defined MH_AUTO_BUTTONS && defined PS2_MOUSE_ENABLE && defined MOUSEKEY_ENABLE
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
#endif
    return true;
}

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
