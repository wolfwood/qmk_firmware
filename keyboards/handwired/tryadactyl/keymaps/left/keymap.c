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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT_left_hand(
		     KC_MINS,        KC_1,     KC_2,     KC_3,     KC_4,     KC_5,
		     KC_RBRC,        KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,
		     LCTL_T(KC_LBRC),KC_A,     KC_S,     KC_D,     KC_F,     KC_G,
		     KC_LSPO,        KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,
		                                                   ALT_T(KC_UP),
		                                         SFT_T(KC_LEFT),  KC_SPC,   CTL_T(KC_RGHT),
		                                                   GUI_T(KC_DOWN),
   		                                         KC_UNDS,            TG(_MO2),
		                                         KC_BSPC,  KC_SPC,   M_BRACES
    ),
    /*[_FN] = LAYOUT(
        QMKBEST, QMKURL,  _______,
            RESET,    XXXXXXX
	    )*/
    [_MBO] = LAYOUT_left_hand(
		     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
		     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
		     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
		     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
		                                             KC_TRNS,
		                                   KC_TRNS,  KC_TRNS,  KC_TRNS,
		                                             KC_TRNS,
		                                   KC_WBAK,            KC_WFWD,
		                                   KC_BTN3,  KC_BTN1,  KC_BTN2
    ),
    [_ALB] = LAYOUT_left_hand(
		     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
		     KC_TRNS,  KC_I,     KC_LSFT,  KC_D,     KC_W,     KC_TRNS,
		     KC_TRNS,  KC_S,     KC_LALT,  KC_R,     KC_Q,     KC_E,
		     KC_TRNS,  KC_A,     KC_GRV,   KC_F,     KC_SPC,   KC_TRNS,
		                                             KC_F1,
		                                   KC_F3,    KC_F1,    KC_F4,
 		                                             KC_F2,
		                                   KC_4,            TG(_ALB),
		                                   KC_1,     KC_2,     KC_3
    ),
    [_MO2] = LAYOUT_left_hand(
		     KC_V,    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
		     KC_P,    KC_TAB,   KC_X,     KC_LALT,  KC_6,     KC_TRNS,
		     KC_L,    KC_LCTL,  KC_LSFT,  KC_BTN2,  KC_BTN1,  KC_2,
		     KC_ESC,  KC_SPC,   KC_GRV,   KC_V,     KC_R,     KC_0,
		                                             KC_W,
		                                   KC_A,     KC_X,    KC_D,
 		                                             KC_S,
		                                   KC_TRNS,            KC_TRNS,
		                                   KC_TRNS,  KC_TRNS,  KC_TRNS
    ),
};
