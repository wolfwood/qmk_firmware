/* Copyright 2022 wolfwood
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

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  M_BRACES  = SAFE_RANGE, // modifier controlled bracket pair
  M_BRPM, // bracket
  M_CBPM, // curly brace
  M_ABPM, // angle crace
  M_PRPM, // parens
  M_SQPM, // single quote
  M_DQPM, // dopple quote
  M_BSDEL, // shifted BS is delete
  M_CCCV, // copy paste
};

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
    _MBO,
    _ALB,
    _MO2,
};

#if defined MH_AUTO_BUTTONS && defined PS2_MOUSE_ENABLE && defined MOUSEKEY_ENABLE
void mouse_mode(bool);

static uint16_t mh_auto_buttons_timer;
extern int tp_buttons; // mousekey button state set in action.c and used in ps2_mouse.c

#endif

static uint16_t copy_paste_timer;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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

    const uint8_t mods = get_mods();
    const uint8_t oneshot_mods = get_oneshot_mods();

    switch (keycode) {
    case M_BRACES:  // Types [], {}, or <> and puts cursor between braces.
    case M_BRPM:
    case M_CBPM:
    case M_ABPM:
    case M_PRPM:
    case M_SQPM:
    case M_DQPM:
      if (record->event.pressed) {
	clear_mods();  // Temporarily disable mods.
	clear_oneshot_mods();

	if (keycode == M_DQPM) {
	  SEND_STRING("\"\"");
	}else if(keycode == M_SQPM || (keycode == M_DQPM && (mods | oneshot_mods) & MOD_MASK_SHIFT)) {
	  SEND_STRING("''");
	}else if (keycode == M_CBPM || (mods | oneshot_mods) & MOD_MASK_SHIFT) {
	  SEND_STRING("{}");
	} else if (keycode == M_BRPM || (mods | oneshot_mods) & MOD_MASK_CTRL) {
	  SEND_STRING("()");
	} else if (keycode == M_ABPM || (mods | oneshot_mods) & MOD_MASK_ALT) {
	  SEND_STRING("<>");
	} else {
	  SEND_STRING("[]");
	}
	tap_code(KC_LEFT);  // Move cursor between braces.
	//SEND_STRING(SS_TAP(X_LEFT));
	set_mods(mods);  // Restore mods.
      }
      return false;
    case M_CCCV:
      if (record->event.pressed) {
	copy_paste_timer = timer_read();
      } else {
	if (timer_elapsed(copy_paste_timer) > TAPPING_TERM) { // Hold to copy
	  //tap_code16(LCTL(KC_C));
	  tap_code(KC_COPY);
	} else { // Tap to paste
	  //tap_code16(LCTL(KC_V));
	  tap_code(KC_PASTE);
	}
      }
      return false;
    }

    return true;
}

#if defined MH_AUTO_BUTTONS && defined PS2_MOUSE_ENABLE && defined MOUSEKEY_ENABLE
void ps2_mouse_moved_user(report_mouse_t *mouse_report) {
  if (mh_auto_buttons_timer) {
    mh_auto_buttons_timer = timer_read();
  } else {
    if (!tp_buttons && !IS_LAYER_ON(_ALB) && !IS_LAYER_ON(_MO2)) {
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
