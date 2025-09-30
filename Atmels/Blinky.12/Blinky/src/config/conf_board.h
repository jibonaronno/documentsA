/**
 * \file
 *
 * \brief User board configuration template
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef CONF_BOARD_H
#define CONF_BOARD_H

/** Board oscillator settings */
#define BOARD_FREQ_SLCK_XTAL        (32768U)
#define BOARD_FREQ_SLCK_BYPASS      (32768U)
//#define BOARD_FREQ_MAINCK_XTAL      (12000000U)
//#define BOARD_FREQ_MAINCK_BYPASS    (12000000U)

#define BOARD_FREQ_MAINCK_XTAL      (48000000U)/*(12000000U)*/
#define BOARD_FREQ_MAINCK_BYPASS    (48000000U)/*(12000000U)*/
#define BOARD_MCK                   (48000000U)/*CHIP_FREQ_CPU_MAX*/
//#define BOARD_OSC_STARTUP_US        15625
//! [board clock configuration]

/** Master clock frequency */
//#define BOARD_MCK                   CHIP_FREQ_CPU_MAX

/** board main clock xtal startup time */
#define BOARD_OSC_STARTUP_US   15625

#endif // CONF_BOARD_H
