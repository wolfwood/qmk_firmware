// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Santoku keymap set up
enum layers {
    _QWERTY,
    _COLEMAKDH,
    _SYMBOL,
    _NAVIGATION,
    _FUNCTION,
    _MOUSE
};

enum keycodes {
    BRACES = SAFE_RANGE,
    __nope_,
};

#define CTLnope LCTL_T(__nope_)
#define SFTnope LSFT_T(__nope_)
#define GUInope LGUI_T(__nope_)
#define ALTnope LALT_T(__nope_)

#define RCTLnop RCTL_T(__nope_)
#define RSFTnop RSFT_T(__nope_)
#define RGUInop RGUI_T(__nope_)
#define RALTnop RALT_T(__nope_)

// Shift + Backspace = Del
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_GUI, KC_BSPC, KC_DEL);
const key_override_t delete_thumb_override = ko_make_basic(MOD_MASK_GUI, LT(_NAVIGATION, KC_BSPC), KC_DEL);

// Shift + esc = ~
const key_override_t tilde_esc_override = ko_make_basic(MOD_MASK_SHIFT, LT(_FUNCTION, KC_ESC), S(KC_GRV));

// GUI + esc = `
const key_override_t grave_esc_override = ko_make_basic(MOD_MASK_GUI, LT(_FUNCTION, KC_ESC), KC_GRV);

const key_override_t *key_overrides[] = {
  	&delete_key_override,
        &delete_thumb_override,
	&tilde_esc_override,
	&grave_esc_override,
};

// Combo stuff
enum combos {
  COMBO_FG,
  COMBO_TG,
  COMBO_HJ,
  COMBO_MN,
  COMBO_IO,
  COMBO_UY,
  COMBO_NM,
  COMBO_WE,
  COMBO_RT,
};

const uint16_t PROGMEM combo_fg[] = {LCTL_T(KC_F), KC_G, COMBO_END};
const uint16_t PROGMEM combo_tg[] = {LCTL_T(KC_T), KC_G, COMBO_END};
const uint16_t PROGMEM combo_hj[] = {RCTL_T(KC_J), KC_H, COMBO_END};
const uint16_t PROGMEM combo_mn[] = {RCTL_T(KC_N), KC_M, COMBO_END};
const uint16_t PROGMEM combo_io[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM combo_uy[] = {KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM combo_nm[] = {KC_N, LT(_SYMBOL, KC_M), COMBO_END};
const uint16_t PROGMEM combo_we[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM combo_rt[] = {KC_R, KC_T, COMBO_END};

combo_t key_combos[] = {
  [COMBO_FG] = COMBO_ACTION(combo_fg),
  [COMBO_TG] = COMBO_ACTION(combo_tg),
  [COMBO_HJ] = COMBO_ACTION(combo_hj),
  [COMBO_MN] = COMBO_ACTION(combo_mn),
  [COMBO_IO] = COMBO_ACTION(combo_io),
  [COMBO_UY] = COMBO_ACTION(combo_uy),
  [COMBO_NM] = COMBO_ACTION(combo_nm),
  [COMBO_WE] = COMBO_ACTION(combo_we),
  [COMBO_RT] = COMBO_ACTION(combo_rt),
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
  case COMBO_NM:
    if (pressed) {
      keyrecord_t r;
      r.event.pressed = true;
      process_record_user(BRACES, &r);
    }
    break;
  case COMBO_WE:
  case COMBO_UY:
  case COMBO_RT:
    if (pressed) {
      tap_code16(KC_SPC);
    }
    break;
  }
}

#if defined MH_AUTO_BUTTONS && defined PS2_MOUSE_ENABLE && defined MOUSEKEY_ENABLE
void mouse_mode(bool);

static uint16_t mh_auto_buttons_timer;
extern int tp_buttons; // mousekey button state set in action.c and used in ps2_mouse.c
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#if defined MH_AUTO_BUTTONS && defined PS2_MOUSE_ENABLE && defined MOUSEKEY_ENABLE
  /*if (mh_auto_buttons_timer) {
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
    }*/
#endif

  const uint8_t mods = get_mods();
  //const uint8_t oneshot_mods = get_oneshot_mods();

  /*
    ^ is where the cursor is at the end
    left hand mods
    A G S C
    o o o o : [^]
    o o o x : "^"
    o o x o : {
    ^
    }
    o o x x : '^'
    o x o o : (^)
    o x o x : ()^
    o x x o : {^}
    o x x x : \"^\"
    x o o o : <^>
    x o o x : $(^) + capsword
    x o x o : {}^
    x o x x : ""^
    x x o o : |^|
    x x o x : ||^
    x x x o : `^`
    x x x x : \'^\'
   */

  switch (keycode) {
  case BRACES:
    if (record->event.pressed) {
      //clear_oneshot_mods();  // Temporarily disable mods.
      unregister_mods(MOD_MASK_CSAG);
      if ((mods /*| oneshot_mods*/) & MOD_MASK_CTRL) {
        if ((mods /*| oneshot_mods*/) & MOD_MASK_SHIFT) {
          if ((mods /*| oneshot_mods*/) & MOD_MASK_GUI) {
            if ((mods /*| oneshot_mods*/) & MOD_MASK_ALT) {
              SEND_STRING("\\'\\'" SS_TAP(X_LEFT) SS_TAP(X_LEFT));
            } else {
              SEND_STRING("\\\"\\\"" SS_TAP(X_LEFT) SS_TAP(X_LEFT));
            }
          } else {
            if ((mods /*| oneshot_mods*/) & MOD_MASK_ALT) {
              SEND_STRING("$()" SS_TAP(X_LEFT));
              caps_word_on();
            } else {
              SEND_STRING("''" SS_TAP(X_LEFT));
            }
          }
        } else {
          if ((mods /*| oneshot_mods*/) & MOD_MASK_GUI) {
            if ((mods /*| oneshot_mods*/) & MOD_MASK_ALT) {
              SEND_STRING("||");
            } else {
              SEND_STRING("()");
            }
          } else {
            if ((mods /*| oneshot_mods*/) & MOD_MASK_ALT) {
              SEND_STRING("\"\"");
            } else {
              SEND_STRING("\"\"" SS_TAP(X_LEFT));
            }
          }
        }
      } else if ((mods /*| oneshot_mods*/) & MOD_MASK_SHIFT) {
        if ((mods /*| oneshot_mods*/) & MOD_MASK_GUI) {
          if ((mods /*| oneshot_mods*/) & MOD_MASK_ALT) {
            SEND_STRING("``" SS_TAP(X_LEFT));
          } else {
            SEND_STRING("{}" SS_TAP(X_LEFT));
          }
        } else {
          if ((mods /*| oneshot_mods*/) & MOD_MASK_ALT) {
            SEND_STRING("{}");
          } else {
            SEND_STRING("{}" SS_TAP(X_LEFT) "\n" SS_TAP(X_UP) SS_TAP(X_END) "\n\t");
          }
        }
      } else if ((mods /*| oneshot_mods*/) & MOD_MASK_GUI) {
        if ((mods /*| oneshot_mods*/) & MOD_MASK_ALT) {
          SEND_STRING("||" SS_TAP(X_LEFT));
        } else {
          SEND_STRING("()" SS_TAP(X_LEFT));
        }
      } else if ((mods /*| oneshot_mods*/) & MOD_MASK_ALT) {
        SEND_STRING("<>" SS_TAP(X_LEFT));
      } else {
        SEND_STRING("[]" SS_TAP(X_LEFT));
      }
      register_mods(mods);  // Restore mods.
    }
    return false;
    // implement mod-tap for macro
  case CTLnope:
  case SFTnope:
  case GUInope:
  case ALTnope:
  case RCTLnop:
  case RSFTnop:
  case RGUInop:
  case RALTnop:
    if (!record->tap.count || !record->event.pressed) {
        break;
    }
    // fall through to handle nope
  case __nope_:
    if (IS_LAYER_ON(MH_AUTO_BUTTONS_LAYER)) {
      layer_off(MH_AUTO_BUTTONS_LAYER/*get_highest_layer(layer_state)*/);
    }
    return true;
  }

  return true;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_2_3x6_1(
      QK_GESC, KC_UNDS,                                                                                                                                      KC_MINS,         KC_EQL,
      KC_TAB,  KC_Q,         KC_W,         KC_E,                   KC_R,         KC_T,         KC_Y,            KC_U,            KC_I,         KC_O,         KC_P,            KC_QUOT,
      KC_BSPC, LALT_T(KC_A), LGUI_T(KC_S), LSFT_T(KC_D),           LCTL_T(KC_F), KC_G,         KC_H,            RCTL_T(KC_J),    RSFT_T(KC_K), RGUI_T(KC_L), RALT_T(KC_SCLN), KC_ENT,
      QK_GESC, KC_Z, LT(_FUNCTION,KC_X), LT(_SYMBOL,KC_C), LT(_NAVIGATION,KC_V), KC_B,         KC_N,   LT(_SYMBOL,KC_M),LT(_NAVIGATION,KC_COMM),LT(_FUNCTION,KC_DOT),KC_SLSH, KC_BSLS,
                                                                   KC_SPC,                                      KC_ENT),

[_COLEMAKDH] = LAYOUT_split_2_3x6_1(
        QK_GESC, KC_UNDS,                                                                                                                                      KC_MINS,         KC_EQL,
        KC_TAB,  KC_Q,         KC_W,         KC_F,                   KC_P,         KC_B,         KC_J,            KC_L,            KC_U,         KC_Y,         KC_SCLN,         KC_QUOT,
        KC_BSPC, LALT_T(KC_A), LGUI_T(KC_R), LSFT_T(KC_S),           LCTL_T(KC_T), KC_G,         KC_M,            RCTL_T(KC_N),    RSFT_T(KC_E), RGUI_T(KC_I), RALT_T(KC_O),    KC_ENT,
        QK_GESC, KC_Z, LT(_FUNCTION,KC_X), LT(_SYMBOL,KC_C), LT(_NAVIGATION,KC_D), KC_V,         KC_K, LT(_SYMBOL,KC_H),LT(_NAVIGATION,KC_COMM),LT(_FUNCTION,KC_DOT),KC_SLSH,   KC_BSLS,
                                                                     KC_SPC,                                      KC_ENT),

  [_SYMBOL] = LAYOUT_split_2_3x6_1(
        _______, _______,                                                                                                             _______,      _______,
        _______, KC_EXLM,      KC_AT,        KC_HASH,      KC_DLR,       KC_PERC,  KC_CIRC, KC_AMPR,      KC_ASTR,      KC_LPRN,      KC_RPRN,      KC_PIPE,
        _______, LALT_T(KC_1), LGUI_T(KC_2), LSFT_T(KC_3), LCTL_T(KC_4), KC_5,     KC_6,    RCTL_T(KC_7), RSFT_T(KC_8), RGUI_T(KC_9), RALT_T(KC_0), KC_EQL,
        KC_TILD, KC_MINS,      KC_UNDS, KC_PLUS, LT(_NAVIGATION,KC_EQL), KC_LBRC, KC_RBRC,  BRACES,       _______,      _______,      _______,      _______,
	                                                   _______,                         _______),

  [_NAVIGATION] = LAYOUT_split_2_3x6_1(
        _______, _______,                                                                                                                  _______, _______,
	_______, KC_AGIN, LCTL(KC_W),LALT(KC_W),KC_INS,  XXXXXXX,  KC_HOME,       KC_PGDN,       KC_PGUP,            KC_PGDN,            XXXXXXX, XXXXXXX,
        _______, KC_LALT,  KC_LGUI,  KC_LSFT,  KC_LCTL,  XXXXXXX,  KC_END,        KC_LEFT,       KC_RGHT,            KC_DOWN,            KC_UP,   _______,
        XXXXXXX, KC_UNDO,  KC_CUT,   KC_COPY,  KC_PSTE,  XXXXXXX,  XXXXXXX,       LCTL(KC_LEFT), LCTL(KC_RGHT),      LCTL(KC_DOWN),      LCTL(KC_UP),XXXXXXX,
	                                                 _______,                                _______),

  [_FUNCTION] = LAYOUT_split_2_3x6_1(
        TG(_COLEMAKDH), XXXXXXX,                                                                                                            QK_MAKE,        QK_BOOT,
        XXXXXXX, KC_MUTE,       KC_VOLD,       KC_VOLU,       KC_F20,        XXXXXXX, XXXXXXX, KC_MPLY,       KC_MPRV,       KC_MNXT,       XXXXXXX,        QK_MAKE,
        XXXXXXX, LALT_T(KC_F1), LGUI_T(KC_F2), LSFT_T(KC_F3), LCTL_T(KC_F4), KC_F5,   KC_F6,   RCTL_T(KC_F7), RSFT_T(KC_F8), RGUI_T(KC_F9), RALT_T(KC_F10), XXXXXXX,
        _______, XXXXXXX,       KC_BRID,       KC_BRIU,       KC_F11,        XXXXXXX, XXXXXXX, KC_F12,        XXXXXXX,       XXXXXXX,       XXXXXXX,        _______,
                                                              _______,                         _______),

  [_MOUSE] = LAYOUT_split_2_3x6_1(
        __nope_,      __nope_,                                                                                                             __nope_,      __nope_,
        __nope_,      MS_BTN1,      MS_BTN2,      MS_BTN3,      MS_BTN1,      __nope_,  __nope_, __nope_,      MS_BTN1,      MS_BTN3,      MS_BTN2,      __nope_,
        __nope_,      ALTnope,      GUInope,      SFTnope,      CTLnope,      __nope_,  __nope_, RCTLnop,      RSFTnop,      RGUInop,      RALTnop,      __nope_,
        __nope_,      __nope_,      __nope_,      __nope_,      __nope_,      __nope_,  __nope_, __nope_,      __nope_,      __nope_,      __nope_,      __nope_,
	                                                        __nope_,                         __nope_),
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

void matrix_scan_user(void) {
#if defined MH_AUTO_BUTTONS && defined PS2_MOUSE_ENABLE && defined MOUSEKEY_ENABLE
  if (mh_auto_buttons_timer && (timer_elapsed(mh_auto_buttons_timer) > MH_AUTO_BUTTONS_TIMEOUT)) {
    if (!tp_buttons) {
      mouse_mode(false);
  #if defined CONSOLE_ENABLE
      print("mh_auto_buttons: off\n");
  #endif
    }
  }
#endif

#ifdef ACHORDION
  achordion_task();
#endif
}
