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

#pragma once

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS  10
#define MATRIX_COLS  6
#define PFET_ROWS
//#define THUMB_DOWN_ACTIVE_DARK
#define FORCE_NKRO
#undef PS2_MOUSE_ENABLE
//#define DEBUG_MATRIX_SCAN_RATE

// wiring of each half
//Layout for svalboard v0 (different from lalboard_v2)
//1 2 3 4 5 6
//S E D N W None
//Both Thumbs (these are same as lalboard_v2)
//OL OU D IL MODE DOUBLE
//Knuckle Nail Down Pad Up Double

#define MATRIX_COL_PUSHED_STATES { 0, 0, 1, 0, 0, 0 }
#ifdef THUMB_DOWN_ACTIVE_DARK
    #define MATRIX_COL_PUSHED_STATES_THUMBS { 0, 0, 1, 0, 0, 0 }
#else
    #define MATRIX_COL_PUSHED_STATES_THUMBS { 0, 0, 0, 0, 0, 0 }
#endif
#define DOUBLEDOWN_COL 5 // need a pullup on COL6
#define PREWAIT_US 90
#define POSTWAIT_US 90

#define SERIAL_DEBUG
#define SERIAL_USART_TX_PIN GP0 
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500 // Timeout window in ms in which the double tap can occur.

#ifdef PS2_MOUSE_ENABLE
  //#define SERIAL_PIO_USE_PIO1
  #define PS2_PIO_USE_PIO1
  #define PS2_RESET_PIN GP25
  #define PS2_CLOCK_PIN GP24
  #define PS2_DATA_PIN GP23
  #define PS2_MOUSE_ROTATE 270 
#endif

#if defined(POINTING_DEVICE_ENABLE)

  // Pointing device stuff
  #define SPLIT_POINTING_ENABLE
  #define POINTING_DEVICE_COMBINED

  #if defined(POINTING_DEVICE_IS_PIMORONI)

    #define I2C_DRIVER I2CD1
    #define I2C1_SDA_PIN GP18
    #define I2C1_SCL_PIN GP19
    #define PIMORONI_TRACKBALL_SCALE 5

  #endif

  #if (defined(POINTING_DEVICE_IS_PMW3360) || defined(POINTING_DEVICE_IS_PMW3389))
    // SPI stuff
    #define USE_FFC_SPI

    #ifdef USE_FFC_SPI
        #define SPI_DRIVER SPID1
        // for FFC connector
        #define SPI_SCK_PIN GP26
        // Use TX# pin from SPI set.
        #define SPI_MOSI_PIN GP27
        // Use RX# pin from SPI set.
        #define SPI_MISO_PIN GP24
        // PMW33XX stuff
        // Use CS# pin from SPI set. Might not actually have to be the CS# pin, since
        // there's supposed to be support for multiple PMW33XX sensors, with different
        // CS pins.
        #define PMW33XX_CS_PIN GP25
      #else
    //for Separate Pimoroni Connector
        #define SPI_DRIVER SPID0
        #define SPI_SCK_PIN GP18
        // Use TX# pin from SPI set.
        #define SPI_MOSI_PIN GP19
        // Use RX# pin from SPI set.
        #define SPI_MISO_PIN GP16
        // PMW33XX stuff
        // Use CS# pin from SPI set. Might not actually have to be the CS# pin, since
        // there's supposed to be support for multiple PMW33XX sensors, with different
        // CS pins.
        #define PMW33XX_CS_PIN GP17
    #endif
    #define PMW33XX_CS_DIVISOR 4
    #define PMW33XX_CPI 3200
    #define POINTING_DEVICE_INVERT_X_RIGHT
    /* #define ROTATIONAL_TRANSFORM_ANGLE_RIGHT 75 */
  #endif
#endif

#if defined MH_AUTO_BUTTONS
  #define MH_AUTO_BUTTONS_LAYER MBO
  #define MH_AUTO_BUTTONS_TIMEOUT 5000
  #define PS2_MOUSE_SCROLL_BTN_MASK 0 
  //(1<<PS2_MOUSE_BTN_MIDDLE) // this mask disables the key for non-PS2 purposes
#endif

//#define USB_POLLING_INTERVAL_MS 1




