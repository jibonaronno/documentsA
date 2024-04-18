
#include <stdint.h>
#include <stdio.h>

#include "util.h"

/* This file should be the start of your solution. the function names "YOUR_ISR"
 * and "your_main" should not be changed but otherwise, all code in this file
 * can be edited as needed to meet the desired result. all code here is just
 * to give an example input and output */

/*
 * This function simulates an on-target ISR. it is called at a regular interval
 * and is at a higher priority than the your_main() function.
 *
 * the rate at which this function is called by the test harness can be set
 * with the '-f' option. the '-f' option takes the time between calls in
 * milliseconds as the parameter
 */
void YOUR_ISR(void)
{
    /* Any code in this function is yours to change. anything already in this
     * function is here purely to show use of utility functions. feel free
     * to use/ignore/remove */

    /* as an example, printing this out will give you an idea for the time
     * jitter with respect to how often this gets called. these logs print out
     * when the -d option is supplied */

    static uint64_t last_time = 0;
    uint64_t now = current_timestamp_us();
    uint64_t delta = now - last_time;
    last_time = now;

    print_debug_log("time: %llu. delta = %llu\n", now, delta);
}

/* write the equivalant of the main() function here.
 * this thread will run at a lower priority than YOUR_ISR().
 * when this function returns, the program will end execution */
void your_main(void)
{

    print_debug_log("starting application\n");
    /* this is will generate some data that you can plot to make sure your
     * tools work. replace this function with one of your own creation that
     * will meet the criteria */

    sleep(1);
    apply_position(35.0);
    sleep(1);
    apply_position(95.0);

    print_debug_log("ending application\n");
    /* when this function returns the application execution is completed */
}

