#if defined MH_AUTO_BUTTONS
  //#define MH_AUTO_BUTTONS_LAYER _MBO
  #define MH_AUTO_BUTTONS_TIMEOUT 2000
  #define PS2_MOUSE_SCROLL_BTN_MASK (1<<PS2_MOUSE_BTN_MIDDLE) /* Default */
#endif

//#include QMK_KEYBOARD_H

// Defines the keycodes used by our macros in process_record_user
/*enum custom_keycodes {
  M_BRACES  = 99,  //SAFE_RANGE modifier controlled bracket pair
  M_BRPM, // bracket
  M_CBPM, // curly brace
  M_ABPM, // angle crace
  M_PRPM, // parens
  M_SQPM, // single quote
  M_DQPM, // dopple quote
  M_BSDEL, // shifted BS is delete
  M_CCCV, // copy paste
};
*/
