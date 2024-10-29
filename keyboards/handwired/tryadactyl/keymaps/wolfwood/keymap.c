// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "quantum.h"

// Santoku keymap set up
enum santoku_layers {
    _QWERTY,
    _TARMAKDH1,
    _TARMAKDH1B,
    _TARMAKDH2,
    _TARMAKDH3,
    _TARMAKDH4,
    _TARMAKDH5,
    _COLEMAKDH,
    _SYMBOL,
    _NAVIGATION,
    _FUNCTION,
    _MOUSE
};

enum keycodes {
    BRACES = SAFE_RANGE,
};

// Shift + Backspace = Del
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_GUI, KC_BSPC, KC_DEL);
const key_override_t delete_thumb_override = ko_make_basic(MOD_MASK_GUI, LT(_NAVIGATION, KC_BSPC), KC_DEL);

// Shift + esc = ~
//const key_override_t tilde_esc_override = ko_make_basic(MOD_MASK_SHIFT, LT(_FUNCTION, KC_ESC), S(KC_GRV));

// GUI + esc = `
//const key_override_t grave_esc_override = ko_make_basic(MOD_MASK_GUI, LT(_FUNCTION, KC_ESC), KC_GRV);

const key_override_t *key_overrides[] = {
  	&delete_key_override,
	&delete_thumb_override,
	//&tilde_esc_override,
	//&grave_esc_override,
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



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_4(
      KC_TAB,  KC_Q,         KC_W,         KC_E,                   KC_R,         KC_T,         KC_Y,            KC_U,            KC_I,         KC_O,         KC_P,            KC_MINS,
      KC_BSPC, RALT_T(KC_A), LGUI_T(KC_S), LSFT_T(KC_D),           LCTL_T(KC_F), KC_G,         KC_H,            RCTL_T(KC_J),    RSFT_T(KC_K), RGUI_T(KC_L), RALT_T(KC_SCLN), KC_ENT,
      QK_GESC, KC_Z,         KC_X,         LT(_SYMBOL,KC_C),       LT(_NAVIGATION,KC_V),KC_B,  KC_N,            LT(_SYMBOL,KC_M),KC_COMM,      KC_DOT,       KC_SLSH,         KC_QUOT,
      LT(_NAVIGATION, KC_BSPC),LT(_SYMBOL, KC_SPC),LT(_NAVIGATION, KC_BSPC),LT(_FUNCTION, QK_GESC),             CW_TOGG,KC_TAB,LT(_SYMBOL, KC_ENT),KC_TAB),

  [_SYMBOL] = LAYOUT_split_3x6_4(
        KC_GRV,  KC_EXLM,      KC_AT,        KC_HASH,      KC_DLR,       KC_PERC,  KC_CIRC, KC_AMPR,      KC_ASTR,      KC_LPRN,      KC_RPRN,      TG(_SYMBOL),
        _______, RALT_T(KC_1), LGUI_T(KC_2), LSFT_T(KC_3), LCTL_T(KC_4), KC_5,     KC_6,    RCTL_T(KC_7), RSFT_T(KC_8), RGUI_T(KC_9), RALT_T(KC_0), KC_EQL,
        KC_TILD, KC_BSLS,      KC_UNDS,      KC_PLUS,      KC_LCBR,      KC_RCBR,  KC_LBRC, KC_RBRC,      KC_COMM,      KC_DOT,       KC_SLSH,      KC_PIPE,
	_______,      _______,      _______,      _______,  _______, _______,      _______,      _______),

  [_NAVIGATION] = LAYOUT_split_3x6_4(
	TG(_NAVIGATION),XXXXXXX,XXXXXXX,XXXXXXX, XXXXXXX,  XXXXXXX,  KC_HOME,       KC_PGDN,       KC_PGUP,            KC_UP,                XXXXXXX, XXXXXXX,
        KC_ESC,  KC_RALT,  KC_LGUI,  KC_LSFT,  KC_LCTL,  XXXXXXX,  KC_END,        KC_LEFT,       KC_RGHT,            KC_DOWN,              KC_UP,   XXXXXXX,
        _______, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,       LCTL(KC_LEFT), LCTL(KC_RGHT),      LCTL(KC_DOWN),        LCTL(KC_UP), _______,
                               _______,      _______,      _______,      _______,  _______, _______,      _______,      _______),

  [_FUNCTION] = LAYOUT_split_3x6_4(
        TG(_TARMAKDH1), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_ESC, RALT_T(KC_F1), LGUI_T(KC_F2), LSFT_T(KC_F3), LCTL_T(KC_F4), KC_F5, KC_F6, RCTL_T(KC_F7), RSFT_T(KC_F8), RGUI_T(KC_F9), RALT_T(KC_F10), XXXXXXX,
        _______, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, KC_F11,  KC_F12,  XXXXXXX,        XXXXXXX, XXXXXXX, _______,
        XXXXXXX,KC_DEL,                 KC_SPC,            XXXXXXX,           XXXXXXX,               XXXXXXX,               QK_BOOT,XXXXXXX),

     /*
      * ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
      * │Tab│ Q │ W │ E │ R │ T │       │ Y │ U │ I │ O │ P │Bsp│
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │Ctl│ A │ S │ D │ F │ G │       │ H │ J │ K │ L │ ; │ ' │
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │Sft│ Z │ X │ C │ V │ B │       │ N │ M │ , │ . │ / │Sft│
      * └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
      *               ┌───┐                   ┌───┐
      *               │GUI├───┐           ┌───┤Alt│
      *               └───┤Bsp├───┐   ┌───┤Ent├───┘
      *                   └───┤   │   │   ├───┘
      *                       └───┘   └───┘

    [0] = LAYOUT_split_3x6_4(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
	                           KC_BSPC, KC_SPC, KC_BSPC, QK_GESC,           CW_TOGG, KC_TAB,  KC_ENT,  KC_TAB
    )*/
};
