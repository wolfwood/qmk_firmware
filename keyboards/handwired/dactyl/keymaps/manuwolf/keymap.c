#include QMK_KEYBOARD_H
#include "version.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MOUS 2 // media keys
#define LOL  3
#define ESO  4

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // ensure these codes start after the highest keycode defined in Quantum
  VRSN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   =  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Del  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | BkSp |   A  |   S  |   D  |   F  |   G  |                    |   H  |   J  |   K  |   L  |; / L2|'/Cmd |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|Z/Ctrl|   X  |   C  |   V  |   B  |                    |   N  |   M  |   ,  |   .  |//Ctrl|RShift|
 * |------+------+------+------+------+------'                    `------+------+------+------+------+------|
)/ * |Grv/L1|  '"  |AltShf| Left | Right|                                  |  Up  | Down |   [  |   ]  | ~L1  |
 * `----------------------------------'                                  `----------------------------------'
 *                                      ,-------------.  ,-------------.
 *                                      | App  | LGui |  | Alt  | ^/Esc|
 *                               ,------|------|------|  |------+------+------.
 *                               |      |      | Home |  | PgUp |      |      |
 *                               | Space|Backsp|------|  |------|  Tab |Enter |
 *                               |      |ace   | End  |  | PgDn |      |      |
 *                               `--------------------'  `--------------------'
 */
[BASE] = LAYOUT_dactyl_5way (  // layer 0 : default
        // left hand
          KC_MINS,         KC_1,           KC_2,     KC_3,     KC_4,  KC_5,
          KC_DEL,          KC_Q,           KC_W,     KC_E,     KC_R,  KC_T,
          LCTL_T(KC_BSPC), LT(MOUS,KC_A),  KC_S,     KC_D,     KC_F,  KC_G,
          KC_LSPO,         CTL_T(KC_Z),    KC_X,     KC_C,     KC_V,  KC_B,
	  LT(SYMB,KC_QUOT),KC_GRAVE,       KC_DQT,  KC_UNDS,  KC_TILDE,
	  KC_BSPC,         TG(ESO),

	                                                                    LT(SYMB, KC_BSPC),
	                                   LGUI_T(KC_SPC), LGUI_T(KC_SPC),  SCMD_T(KC_END),
	  KC_UP,
	  LSFT_T(KC_LEFT),KC_SPC,LALT_T(KC_RGHT),
	  LGUI_T(KC_DOWN),
	  // right hand
                             KC_6,   KC_7,     KC_8,     KC_9,               KC_0,         KC_EQL,
                             KC_Y,   KC_U,     KC_I,     KC_O,               KC_P,         KC_BSLS,
                             KC_H,   KC_J,     KC_K,     KC_L,  LT(MOUS, KC_SCLN),  LGUI_T(KC_QUOT),
                             KC_N,   KC_M,  KC_COMM,   KC_DOT,     CTL_T(KC_SLSH),         KC_RSPC,
	                             KC_LBRC,  KC_LBRC,  KC_RBRC,            KC_RBRC,          TT(SYMB),
          KC_ESC, KC_TAB,
          KC_PGUP,
          LT(SYMB,KC_TAB),  LCTL_T(KC_ENT), LALT_T(KC_ENT),
	  LALT_T(KC_PGUP),
	  LGUI_T(KC_HOME),KC_TAB,LSFT_T(KC_END),
	  LCTL_T(KC_PGDN)
    ),
/* Keymap 1: Symbol Layer
 *
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |Versn |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   !  |   @  |   {  |   }  |   |  |                    |  Up  |   7  |   8  |   9  |   *  |  F12 |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   #  |   $  |   [  |   ]  |   `  |                    | Down |   4  |   5  |   6  |   +  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   %  |   ^  |   (  |   )  |   ~  |                    |   &  |   1  |   2  |   3  |   \  |      |
 * |------+------+------+------+------+------'                    `------+------+------+------+------+------|
 * |RESET |      |      |      |      |                                  |      |   .  |   0  |   =  |      |
 * `----------------------------------'                                  `----------------------------------'
 *                                      ,-------------.  ,-------------.
 *                                      |      |      |  |      |      |
 *                               ,------|------|------|  |------+------+------.
 *                               |      |      |      |  |      |      |      |
 *                               |      |      |------|  |------|      |      |
 *                               |      |      |      |  |      |      |      |
 *                               `--------------------'  `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_dactyl_5way(
       // left hand
          VRSN,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,
       KC_TRNS,  KC_EXLM,    KC_AT,  KC_LCBR,  KC_RCBR,  KC_PIPE,
       KC_TRNS,  KC_HASH,   KC_DLR,  KC_LBRC,  KC_RBRC,   KC_GRV,
	 RESET,  KC_PERC,  KC_CIRC,  KC_LPRN,  KC_RPRN,  KC_TILD,
       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
		                                                                KC_TRNS,  KC_TRNS,
                                                                   KC_TRNS,
                                               KC_TRNS,  KC_TRNS,  KC_TRNS,
	  KC_TRNS,
	  KC_TRNS,KC_TRNS,KC_TRNS,
	  KC_TRNS,
	  // right hand
                KC_F6,      KC_F7,   KC_F8, KC_F9,  KC_F10,   KC_F11,
                KC_UP,       KC_7,    KC_8,  KC_9, KC_ASTR,   KC_F12,
                KC_DOWN,     KC_4,    KC_5,  KC_6, KC_PLUS,  KC_TRNS,
                KC_AMPR,     KC_1,    KC_2,  KC_3, KC_BSLS,  KC_TRNS,
                          KC_TRNS,  KC_DOT,  KC_0,  KC_EQL,  KC_TRNS,
      KC_TRNS,  KC_TRNS,
      KC_TRNS,
	  KC_TRNS,  KC_TRNS,  KC_TRNS,


	  KC_TRNS,
	  KC_TRNS,KC_TRNS,KC_TRNS,
	  KC_TRNS
),
/* Keymap 2: Media and mouse keys
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      | MsUp |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |MsLeft|MsDown|MsRght|      |                    |      |      |      |      |      | Play |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      | Prev | Next |      |      |
 * |------+------+------+------+------+------'                    `------+------+------+------+------+------|
 * |      |      |      | Lclk | Rclk |                                  | VolUp| VolDn| Mute |      |      |
 * `----------------------------------'                                  `----------------------------------'
 *                                      ,-------------.  ,-------------.
 *                                      |      |      |  |      |      |
 *                               ,------|------|------|  |------+------+------.
 *                               |      |      |      |  |      |      |Brwser|
 *                               |      |      |------|  |------|      |Back  |
 *                               |      |      |      |  |      |      |      |
 *                               `--------------------'  `--------------------'
 *
 */
// MOUSE
[MOUS] = LAYOUT_dactyl_5way(
       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_MS_U,  KC_TRNS,  KC_TRNS,
       KC_TRNS,  KC_TRNS,  KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_TRNS,
       KC_TRNS,  KC_TRNS,  KC_MS_WH_LEFT,  KC_MS_WH_UP,  KC_MS_WH_DOWN,  KC_MS_WH_RIGHT,
       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                                                         KC_BTN3,  KC_WBAK,
                                                                   KC_BTN2,
                                               KC_BTN1,  KC_BTN1,  KC_WWW_FORWARD,
       	  KC_MS_U,
	  KC_MS_L,KC_BTN3,KC_MS_R,
	  KC_MS_D,
    // right hand
                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                KC_TRNS,  KC_TRNS,  KC_MS_U,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                KC_TRNS,  KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_TRNS,  KC_TRNS,
                KC_MS_WH_LEFT,  KC_MS_WH_DOWN,  KC_MS_WH_UP,    KC_MS_WH_RIGHT, KC_TRNS,  KC_TRNS,
                          KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
      KC_TRNS, KC_WBAK,
      KC_WWW_FORWARD,
       KC_BTN3,  KC_BTN1,  KC_BTN1,
       	  KC_MS_U,
	  KC_MS_L,KC_BTN3,KC_MS_R,
	  KC_MS_D
),

[LOL] = LAYOUT_dactyl_5way(
       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
       KC_TAB,   KC_A,     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                                                         KC_TRNS,  KC_TRNS,
                                                                   KC_P,
                                        KC_LSFT,  LCTL_T(KC_SPC),  KC_LGUI,
	  KC_TRNS,
	  KC_TRNS,KC_TRNS,KC_TRNS,
	  KC_TRNS,
     // right hand
                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                          KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
      KC_TRNS,  KC_TRNS,
      KC_TRNS,
       KC_TRNS,  KC_TRNS,  KC_TRNS,
	  KC_TRNS,
	  KC_TRNS,KC_TRNS,KC_TRNS,
	  KC_TRNS
),

[ESO] = LAYOUT_dactyl_5way(
       KC_K,     KC_J,     KC_I,     KC_M,     KC_P,     KC_N,
       KC_TAB,   KC_LALT,  KC_V,     KC_E,  KC_A,  KC_G,
       KC_Q,     KC_X,     KC_LSFT,  KC_R,  KC_W,  KC_T,
       KC_LCTRL, KC_SPC,   KC_BSPC,  KC_G,  KC_LALT,  KC_TRNS,
       LGUI(KC_F), KC_T,   KC_Z,     KC_H,     KC_LALT,
                                                         KC_GRV,  KC_TRNS,
                                                                   KC_P,
                                         KC_SPC,  LSFT_T(KC_SPC),  KC_LGUI,
	  KC_D,
	  KC_S,KC_TRNS,KC_F,
       KC_C,

    // right hand
                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                 KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                KC_TRNS,  KC_BTN1,  KC_BTN2,  KC_BTN3,  KC_GRV,  KC_TRNS,
                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                          KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
       KC_TRNS,  KC_TRNS,
       KC_TRNS,
       KC_TRNS,  KC_TRNS,  KC_TRNS,
	  KC_MS_U,
	  KC_MS_L,KC_TRNS,KC_MS_R,
       KC_MS_D
),

};
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {};
