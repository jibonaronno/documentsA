

#pragma once

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <stdbool.h>

/******************************************************************************
 * here are some convenience function to aid you in your development. you
 * do not need to utilize the functions if they are not helpful for you
 ******************************************************************************/

/* convenience function. if the debug flag is set, this will become a call to
 * printf. if the debug flag is not set, this call will be ignored */
int print_debug_log(const char *format, ...);

/* set the position the motor is currently generating. this position will be applied
 * instantaneously. it is up to you to make subsequent calls to this function
 * to get a position ramp that follows the bounds of the question - instead of
 * applying the position, this emulation hardware just logs this to the output
 * file provided in order to generate a plot */
void apply_position(float position_mm);

/* get the starting position or current position as set by the command line option */
uint8_t get_start_position(void);

/* get the ending or desired position as set by the command line option */
uint8_t get_end_position(void);

/* this option is false unless the -d flag is set on the cmd line
 * (i.e. "./solution -d") */
bool get_is_debug(void);

/* get the current system time in us */
uint64_t current_timestamp_us(void);

