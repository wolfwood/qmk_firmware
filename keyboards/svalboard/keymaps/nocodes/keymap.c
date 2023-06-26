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

void keyboard_post_init_user(void) {
  // Customise these values if you need to debug the matrix
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}

enum layer {
    NORMAL,
    NUM_LAYERS
};

const uint16_t PROGMEM keymaps[NUM_LAYERS][MATRIX_ROWS][MATRIX_COLS] = {
 [NORMAL] = LAYOUT(
             /*Center           North           East            South           West*/
        /*R1*/ KC_NO,            KC_NO,           KC_NO,           KC_NO,           KC_NO,
        /*R2*/ KC_NO,            KC_NO,           KC_NO,           KC_NO,           KC_NO,
        /*R3*/ KC_NO,            KC_NO,           KC_NO,           KC_NO,           KC_NO,
        /*R4*/ KC_NO,            KC_NO,           KC_NO,           KC_NO,           KC_NO,
        /*L1*/ KC_NO,            KC_NO,           KC_NO,           KC_NO,           KC_NO,
        /*L2*/ KC_NO,            KC_NO,           KC_NO,           KC_NO,           KC_NO,
        /*L3*/ KC_NO,            KC_NO,           KC_NO,           KC_NO,           KC_NO,
        /*L4*/ KC_NO,            KC_NO,           KC_NO,           KC_NO,           KC_NO,
        /*RT*/ KC_NO,            KC_NO,           KC_NO,           KC_NO,           KC_NO,   KC_NO,
        /*LT*/ KC_NO,            KC_NO,           KC_NO,           KC_NO,           KC_NO,   KC_NO
        )
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
      // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif 
    return true;
};

