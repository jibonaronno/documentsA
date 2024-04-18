#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "util.h"
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <signal.h>
#include <inttypes.h>


/******************************************************************************
 * constants
 ******************************************************************************/
#define MAX_POSITION  (1000)
#define MIN_POSITION  (50)

/******************************************************************************
 * macros
 ******************************************************************************/
#define ARRAY_LEN(a)    (sizeof(a) / sizeof(*(a)))

/******************************************************************************
 * forward declarations
 ******************************************************************************/

void YOUR_ISR(void);
void your_main(void);
static void *low_priority_thread(void * arg);
static void *hi_priority_thread(void * arg);

/******************************************************************************
 * types
 ******************************************************************************/

struct thread {
    /* set by system */
    pthread_t thread_id;
    pthread_attr_t attr;
    struct sched_param sched_params;

    /* user defined */
    void *(*start_routine)(void *);
    int priority;
    size_t stack_size;
};

enum {
    LO_PRI_THREAD = 0,
    HI_PRI_THREAD = 1,
};

/******************************************************************************
 * globals
 ******************************************************************************/

static uint8_t start_position = 0;
static uint8_t end_position = 0;
static bool is_debug = false;
static uint32_t  isr_tick_hz = 0;

struct thread threads[] = {
   [LO_PRI_THREAD] = {
        .start_routine = low_priority_thread,
        .priority = 20,
        .stack_size = 4096,
    },
    [HI_PRI_THREAD] = {
        .start_routine = hi_priority_thread,
        .priority = 21,
        .stack_size = 4096,
    },
};

/* wait for these threads to return before stopping */
const pthread_t * const join_list[] = {
    // we care about the "main" function ending which is in the low priority
    // thread
    &(threads[LO_PRI_THREAD].thread_id),
};

static uint64_t app_start_time = 0;
static FILE *output_text_file = NULL;

/******************************************************************************
 * private functions
 ******************************************************************************/

static void *hi_priority_thread(void * arg)
{
    /* time between simulated ISR firings */

    while(1)
    {
        usleep(isr_tick_hz * 1000);
        YOUR_ISR();
    }

    return NULL;
}

static void *low_priority_thread(void * arg)
{

    your_main();

    // exit pthread when main returns
    pthread_exit(0);

    return NULL;
}

static void print_help_text(void)
{
    printf("Cmd Usage:\n"
                       "  -f <isr freq in ms> : YOUR_ISR will be called at this rate. nominal is 20ms. set as appropriate for this problem\n"
                       "  -o <output text file> : this text file will have the output of all of your calls to write_text_output()\n"
                       "  -s <starting position> : ramp start position\n"
                       "  -e <ending position> : ramp ending position\n"
                       "  -d (no params) : flag to set debug mode - for your own use. access this var through get_is_debug()\n");
}

static void process_cmd_line(int argc, char *argv[])
{

    int opt;
    bool err_found = false;

    while((opt = getopt(argc, argv, "s:e:do:f:h")) != -1)
    {
        switch (opt)
        {
            //debug
            case 'd':
                is_debug = true;
                break;

            // frequency of ISR
            case 'f':
                isr_tick_hz = strtoul(optarg, NULL, 0);
                break;

            // output text file
            case 'o':
                output_text_file = fopen(optarg, "wb+");
                break;

            case 's':
                start_position = strtoul(optarg, NULL, 0);
                break;

            case 'e':
                end_position = strtoul(optarg, NULL, 0);
                break;


            case 'h':
                print_help_text();
                exit(0);
                break;

            default:
                printf("unknown option\n");
                exit(-1);
                break;
        }
    }

    if (isr_tick_hz == 0)
    {
        printf("Err: isr_tick_hz must be supplied with '-f'\n");
        err_found = true;
    }

    if (output_text_file == NULL)
    {
        printf("Err: must supply a file for logging text from write_text_output() with the '-o'\n");
        err_found = true;
    }

    if ((start_position < MIN_POSITION) ||
        (start_position > MAX_POSITION))
    {
        printf("Err: invalid start position (%d). min: %d. max: %d\n",
                start_position,
                MIN_POSITION,
                MAX_POSITION);

        err_found = true;
    }

    if ((end_position < MIN_POSITION) ||
        (end_position > MAX_POSITION))
    {
        printf("Err: invalid end position (%d). min: %d. max: %d\n",
                end_position,
                MIN_POSITION,
                MAX_POSITION);

        err_found = true;
    }


    if (err_found)
    {
        printf("Exiting due to errors \n\n");
        print_help_text();
        exit(-2);
    }
}

static void cleanup(void)
{
    /* cancel any threads */

    for (int i = 0; i < ARRAY_LEN(threads); i++)
    {
        /* should we cancel this thread ?*/

        bool cancel = true;

#if 0
        /* check if we have already joined on this thread. if so, dont cancel
         * the pthread */

        for(int join_idx = 0; join_idx < ARRAY_LEN(join_list); join_idx++)
        {
            if (threads[i].thread_id == *(join_list[join_idx]))
            {
                /* this one is already joined. dont cancel */

                cancel = false;
                break;
            }
        }
#endif

        if (cancel)
        {
            //printf("cancelling thread %d", (uint32_t)threads[i].thread_id);
            /* this thread is likely still running, cancel it */

            pthread_cancel(threads[i].thread_id);
        }
    }

    if (output_text_file)
    {
        fclose(output_text_file);
        output_text_file = NULL;
    }

    exit(-1);
}

static void sigaction_handler(int s)
{
    cleanup();
}

/******************************************************************************
 * public  functions
 ******************************************************************************/

uint8_t get_start_position(void)
{
    return start_position;
}

uint8_t get_end_position(void)
{
    return end_position;
}

bool get_is_debug(void)
{
    return is_debug;
}

int print_debug_log(const char *format, ...)
{
    int bytes_printed = 0;
    if(is_debug)
    {
	    va_list args;
        va_start(args, format);

        bytes_printed = vprintf(format, args);

        va_end(args);
    }

    return bytes_printed;
}

uint64_t current_timestamp_us(void) {
    struct timeval t;
    gettimeofday(&t, NULL);
    uint64_t time_us = t.tv_sec * 1000000ULL + t.tv_usec;

    return time_us;
}

void write_text_output(char *str)
{
    if (output_text_file == NULL)
    {
        return;
    }

    fwrite(str, 1, strlen(str), output_text_file);
}

/* emulate applying position by writing the position and the current timestamp to
 * out to the file */
void apply_position(float position_mm)
{
    uint64_t now = current_timestamp_us();

    double time_since_start_s = (now - app_start_time) / 1000.0;

    char temp[128];

    snprintf(temp, sizeof(temp), "%0.6f, %0.2f\n", time_since_start_s, position_mm);

    write_text_output(temp);
}

int main(int argc, char * argv[])
{

    /* catch ctrl-c */

    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = sigaction_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);

    /* handle cmd line arguments */

    process_cmd_line(argc, argv);

    /* make note of the current time */

    app_start_time = current_timestamp_us();

    /* we will always start with the starting position */

    apply_position(start_position);

    for (int i = 0; i < ARRAY_LEN(threads); i++)
    {
        /* initialize the threads attribute structure */

        int status = pthread_attr_init(&(threads[i].attr));

        if (status != 0)
        {
            printf("Error: could not initialize pthread attributes");
            return -1;
        }

        /* set the stack size */

        pthread_attr_setstacksize(&(threads[i].attr), threads[i].stack_size);

        if (status != 0)
        {
            printf("Error: could not pthread stack size. errcode: %d", status);
            return -2;
        }

        /* set the thread scheduling policy */

        int ret_code = pthread_attr_setschedpolicy(&(threads[i].attr), SCHED_RR);
        if (ret_code)
        {
            printf("Error: could not set sched policy. errcode: %d\n", ret_code);
            return -2;
        }

        /* set the thread priority */

        pthread_attr_getschedparam(&(threads[i].attr), &(threads[i].sched_params));
        threads[i].sched_params.sched_priority = threads[i].priority;
        status = pthread_attr_setschedparam(&(threads[i].attr), &(threads[i].sched_params));

        if (status != 0)
        {
            printf("Error: could not set pthread priority. errcode: %d", status);
            return -3;
        }

        /* create the thread */

        status = pthread_create(&(threads[i].thread_id),
                                &(threads[i].attr),
                                threads[i].start_routine,
                                NULL);

        if (status != 0)
        {
            printf("Error: could not inititlaize pthread. errcode: %d", status);
            return -4;
        }

        //printf("thread id %d created\n", (uint32_t)threads[i].thread_id);
    }

    /* wait for the threads to close */

    for (int i = 0; i < ARRAY_LEN(join_list); i++)
    {
        void *res = NULL;
        //printf("waiting for thread %d to join", (uint32_t)threads[i].thread_id);
        pthread_join(*(join_list[i]), &res);
    }

    cleanup();

    return 0;
}

