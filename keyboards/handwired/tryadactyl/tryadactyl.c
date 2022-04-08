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

#include "tryadactyl.h"

#ifdef PS2_MOUSE_ENABLE
#include "ps2_mouse.h"
#include "ps2.h"
#endif


#ifdef PS2_MOUSE_ENABLE
void ps2_mouse_init_user() {
  /*
    PS2_MOUSE_SEND(0xE2);
    PS2_MOUSE_SEND(0x81);
    PS2_MOUSE_SEND(0x4A);
    PS2_MOUSE_SEND(0x59);


  PS2_MOUSE_SEND(0xE2, "pts: 0xE2");
  PS2_MOUSE_SEND(0x47, "pts: 0x47");
  PS2_MOUSE_SEND(0x2C, "pts: 0x2C");
  PS2_MOUSE_SEND(0x01, "pts: 0x00");
  */

  /*
  PS2_MOUSE_SEND(0xE2, "tfups: 0xE2");
  PS2_MOUSE_SEND(0x80, "tfups: 0x80");
  PS2_MOUSE_SEND(0x60, "tfups: 0x60");
  PS2_MOUSE_SEND(0xf0, "tfups: 0xf0");
  */
}
#endif
