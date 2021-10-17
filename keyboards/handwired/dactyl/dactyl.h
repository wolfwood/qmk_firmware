#ifndef DACTYL_H
#define DACTYL_H

#include "quantum.h"
#include <stdint.h>
#include <stdbool.h>
#include "i2c_master.h"
#include <util/delay.h>

#define I2C_ADDR        (0b0100000 << 1)
#define I2C_TIMEOUT     100
#define IODIRA          0x00            // i/o direction register
#define IODIRB          0x01
#define GPPUA           0x0C            // GPIO pull-up resistor register
#define GPPUB           0x0D
#define GPIOA           0x12            // general purpose i/o port register (write modifies OLAT)
#define GPIOB           0x13
#define OLATA           0x14            // output latch register
#define OLATB           0x15

extern uint8_t expander_status;
extern uint8_t expander_input_pin_mask;
extern bool i2c_initialized;

void init_dactyl(void);
void init_expander(void);

/*
 *   LEFT HAND: LINES 38-45
 *  RIGHT HAND: LINES 47-54
 */
#define LAYOUT_dactyl(                                                  \
                                                                        \
    k00,k01,k02,k03,k04,k05,                                            \
    k10,k11,k12,k13,k14,k15,                                            \
    k20,k21,k22,k23,k24,k25,                                            \
    k30,k31,k32,k33,k34,k35,                                            \
    k40,k41,k42,k43,k44,                                                \
                            k55,k56,                                    \
                                k54,                                    \
                        k53,k52,k51,                                    \
                                                                        \
            k08,k09,k0A,k0B,k0C,k0D,                                    \
            k18,k19,k1A,k1B,k1C,k1D,                                    \
            k28,k29,k2A,k2B,k2C,k2D,                                    \
            k38,k39,k3A,k3B,k3C,k3D,                                    \
                k49,k4A,k4B,k4C,k4D,                                    \
    k57,k58,                                                            \
    k59,                                                                \
    k5C,k5B,k5A )                                                       \
                                                                        \
   /* matrix positions */                                               \
   {                                                                    \
     { k00, k01, k02, k03, k04, k05, KC_NO, KC_NO,     KC_NO, k08, k09, k0A, k0B, k0C, k0D }, \
    { k10, k11, k12, k13, k14, k15, KC_NO, KC_NO,     KC_NO, k18, k19, k1A, k1B, k1C, k1D }, \
    { k20, k21, k22, k23, k24, k25, KC_NO, KC_NO,     KC_NO, k28, k29, k2A, k2B, k2C, k2D }, \
    { k30, k31, k32, k33, k34, k35, KC_NO, KC_NO,     KC_NO, k38, k39, k3A, k3B, k3C, k3D }, \
    { k40, k41, k42, k43, k44, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k49, k4A, k4B, k4C, k4D }, \
    {KC_NO,k51, k52, k53, k54, k55, k56, KC_NO,         k57, k58, k59, k5A, k5B, k5C,KC_NO}, \
   }

#define LAYOUT_dactyl_5way(							\
                                                                        \
    k00,k01,k02,k03,k04,k05,                                            \
    k10,k11,k12,k13,k14,k15,                                            \
    k20,k21,k22,k23,k24,k25,                                            \
    k30,k31,k32,k33,k34,k35,                                            \
    k40,k41,k42,k43,k44,                                                \
                            k55,k56,                                    \
                                k54,                                    \
                        k53,k52,k51,                                    \
            k06,                                                        \
        k16,k46,k36,							\
            k26,                                                        \
                                                                        \
            k08,k09,k0A,k0B,k0C,k0D,                                    \
            k18,k19,k1A,k1B,k1C,k1D,                                    \
            k28,k29,k2A,k2B,k2C,k2D,                                    \
            k38,k39,k3A,k3B,k3C,k3D,                                    \
                k49,k4A,k4B,k4C,k4D,                                    \
    k57,k58,                                                            \
    k59,                                                                \
    k5C,k5B,k5A,                                                        \
                        k07,						\
                    k17,k47,k37,					\
                        k27 )						\
                                                                        \
   /* matrix positions */                                               \
   {                                                                    \
    { KC_NO, k00, k01, k02, k03, k04, k05, k16,     k07, k08, k09, k0A, k0B, k0C, k0D }, \
    { KC_NO, k10, k11, k12, k13, k14, k15, k06,     k17, k18, k19, k1A, k1B, k1C, k1D }, \
    { KC_NO, k20, k21, k22, k23, k24, k25, k26,     k27, k28, k29, k2A, k2B, k2C, k2D }, \
    { KC_NO, k30, k31, k32, k33, k34, k35, k36,     k37, k38, k39, k3A, k3B, k3C, k3D }, \
    { KC_NO, k40, k41, k42, k43, k44, KC_NO, k46, k47, KC_NO, k49, k4A, k4B, k4C, k4D }, \
    { KC_NO, KC_NO,k51,k52, k53, k54, k55, k56,     k57, k58, k59, k5A, k5B, k5C,KC_NO}, \
   }

#endif
