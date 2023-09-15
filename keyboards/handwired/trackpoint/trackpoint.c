#include "trackpoint.h"

#include "ps2_mouse.h"
#include "ps2.h"

void ps2_mouse_init_user() {
  //sensitivity
  PS2_MOUSE_SEND(0xE2, "");
  PS2_MOUSE_SEND(0x81, "");
  PS2_MOUSE_SEND(0x4A, "");
  PS2_MOUSE_SEND(0xF0, "");

  //neg inertia
  PS2_MOUSE_SEND(0xE2, "");
  PS2_MOUSE_SEND(0x81, "");
  PS2_MOUSE_SEND(0x4D, "");
  PS2_MOUSE_SEND(0x07, "");

  // upper plateau speed
  PS2_MOUSE_SEND(0xE2, "tfups: 0xE2");
  PS2_MOUSE_SEND(0x81, "tfups: 0x80");
  PS2_MOUSE_SEND(0x60, "tfups: 0x60");
  PS2_MOUSE_SEND(0xF0, "tfups: 0xf0");
}
