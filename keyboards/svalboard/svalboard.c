#include "svalboard.h"

#ifdef PS2_MOUSE_ENABLE
#include "ps2_mouse.h"
#include "ps2.h"
#endif

#ifdef PS2_MOUSE_ENABLE
void ps2_mouse_init_user() {
  //sensitivity command in fourth byte 00 = 0 multiplier, FF = 2.0 multiplier
  /*
    PS2_MOUSE_SEND(0xE2);
    PS2_MOUSE_SEND(0x81);
    PS2_MOUSE_SEND(0x4A);
    PS2_MOUSE_SEND(0x59);
    */

//Z tap -- doesn't seem to work.  0x01 is on.

  PS2_MOUSE_SEND(0xE2, "pts: 0xE2");
  PS2_MOUSE_SEND(0x47, "pts: 0x47");
  PS2_MOUSE_SEND(0x2C, "pts: 0x2C");
  PS2_MOUSE_SEND(0x01, "pts: 0x01");  // 01 turns on Z tap, 00 turns off


  // transfer function plateau speed -- default is 0x61
/*
  PS2_MOUSE_SEND(0xE2, "tfups: 0xE2");
  PS2_MOUSE_SEND(0x80, "tfups: 0x80");
  PS2_MOUSE_SEND(0x60, "tfups: 0x60");
  PS2_MOUSE_SEND(0xf0, "tfups: 0xf0");
  */
}
#endif