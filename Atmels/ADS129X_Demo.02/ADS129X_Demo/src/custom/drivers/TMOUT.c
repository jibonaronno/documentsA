/*!
** @file TMOUT.c
** @version 01.00
** @brief
**
The module implements timeout functionality. With this implementation,
it is possible to wait for a given time, and the time is counted by
a periodic interrupt.
*/
/*!
**  @addtogroup TMOUT_module TMOUT module documentation
**  @{
*/

/* MODULE TMOUT. */

#include "TMOUT.h"

#define TMOUT_NOF_COUNTERS  10         /* number of timeout counters available */

static TMOUT_CounterType TMOUT_Counters[TMOUT_NOF_COUNTERS]; /* array of timeout counters */
static bool TMOUT_FreeCounters[TMOUT_NOF_COUNTERS]; /* array to indicate which counters are free */


#define TMOUT_FUNC_COUNT    3
struct timeoutItem {
    TimeoutFunction_t func;
    uint16_t baseCount;
    uint16_t currentCount;
};

static struct timeoutItem tmoutItems[TMOUT_FUNC_COUNT];

bool RegisterTimeoutFunction(TimeoutFunction_t func, uint16_t period_ticks) {
    cpu_irq_enter_critical();
    for(int i=0; i<TMOUT_FUNC_COUNT; i++) {
        if(tmoutItems[i].func == func)
            break;
        if(tmoutItems[i].func == NULL) {
            tmoutItems[i].func = func;
            tmoutItems[i].baseCount = period_ticks;
            tmoutItems[i].currentCount = period_ticks;
            break;
        }
    }
    cpu_irq_leave_critical();
    return true;
}

void UnregisterTimeoutFunction(TimeoutFunction_t func) {
    cpu_irq_enter_critical();
    for(int i=0; i<TMOUT_FUNC_COUNT; i++) {
        if(tmoutItems[i].func == func) {
            tmoutItems[i].func = NULL;
        }
    }
    cpu_irq_leave_critical();
}

static inline void TimeoutFunctionsInit(void) {
    cpu_irq_enter_critical();
    for(int i=0; i<TMOUT_FUNC_COUNT; i++) {
        tmoutItems[i].func = NULL;
        tmoutItems[i].baseCount = 0;
        tmoutItems[i].currentCount = 0;
    }
    cpu_irq_leave_critical();
}

static inline void TimeoutFunctionsUpdate(void) {
    for(int i=0; i<TMOUT_FUNC_COUNT; i++) {
        if(tmoutItems[i].func != NULL) {
            if(--tmoutItems[i].currentCount == 0) {
                tmoutItems[i].currentCount = tmoutItems[i].baseCount;
                tmoutItems[i].func();
            }
        }
    }
}

/*
** ===================================================================
**     Method      :  TMOUT_GetCounter (component Timeout)
**     Description :
**         Initializes a new timeout counter and returns the handle to
**         it. At the end, use LeaveCounter() to free up the resource.
**     Parameters  :
**         NAME            - DESCRIPTION
**         nofTicks        - Number of ticks for the counter
**                           until it expires.
**     Returns     :
**         ---             - Handle to the counter, to be used for
**                           further API calls.
** ===================================================================
*/
TMOUT_CounterHandle TMOUT_GetCounter(TMOUT_CounterType nofTicks) {
    TMOUT_CounterHandle handle;

    handle = 0;
    if (nofTicks==0) {
        nofTicks = 1; /* wait at least for one tick, otherwise will timeout immediately */
    }
    cpu_irq_enter_critical();
    while (handle<TMOUT_NOF_COUNTERS && !TMOUT_FreeCounters[handle]) {
        handle++;
    }
    if (handle<TMOUT_NOF_COUNTERS) {
        TMOUT_FreeCounters[handle]=false;
        TMOUT_Counters[handle] = nofTicks;
    }
    cpu_irq_leave_critical();
    if (handle==TMOUT_NOF_COUNTERS) {
        return TMOUT_OUT_OF_HANDLE;
    }
    return handle;
}

/*
** ===================================================================
**     Method      :  TMOUT_LeaveCounter (component Timeout)
**     Description :
**         To be called to return the counter. Note that a counter
**         always should be returned so it can be reused.
**     Parameters  :
**         NAME            - DESCRIPTION
**         handle          - Counter handle
**     Returns     : Nothing
** ===================================================================
*/
void TMOUT_LeaveCounter(TMOUT_CounterHandle* handle) {
    if (*handle==TMOUT_OUT_OF_HANDLE) {
        return;
    }
    cpu_irq_enter_critical();
    TMOUT_Counters[*handle] = 0;
    TMOUT_FreeCounters[*handle]=true;
    cpu_irq_leave_critical();
    *handle = TMOUT_OUT_OF_HANDLE;
}

/*
** ===================================================================
**     Method      :  TMOUT_CounterExpired (component Timeout)
**     Description :
**         Returns true if the timeout counter has been expired
**     Parameters  :
**         NAME            - DESCRIPTION
**         handle          - The timeout handle retrieved using
**                           GetCounter()
**     Returns     :
**         ---             - Returns TRUE if the counter has been
**                           expired, FALSE otherwise
** ===================================================================
*/
bool TMOUT_CounterExpired(TMOUT_CounterHandle handle) {
    bool res;

    if (handle==TMOUT_OUT_OF_HANDLE) {
        return true;
    }
    cpu_irq_enter_critical();
    res = (bool)(TMOUT_Counters[handle]==0);
    cpu_irq_leave_critical();
    return res;
}

/*
** ===================================================================
**     Method      :  TMOUT_AddTick (component Timeout)
**     Description :
**         Method to be called from a periodic timer or interrupt. It
**         will decrement all current counters by one down to zero.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void TMOUT_AddTick(void) {
    uint8_t i;

    cpu_irq_enter_critical();
    for(i=0; i<TMOUT_NOF_COUNTERS; i++) {
        if (TMOUT_Counters[i]>0) {
            TMOUT_Counters[i]--;
        }
    }
    cpu_irq_leave_critical();
}

void TC_TMOUT_Handler (void) {
    uint32_t ul_status;
    /* Read TC_TMoUT Status. */
    ul_status = tc_get_status(TC_TMOUT, TC_TMOUT_CHN);
    /* RC compare. */
    if ((ul_status & TC_SR_CPCS) == TC_SR_CPCS) {
        TMOUT_AddTick();
        TimeoutFunctionsUpdate();
    }
}

/**
 * \brief Configure Timer Counter to generate an interrupt every 10ms.
 * This interrupt will be used to flush UART input and echo back.
 */
static void _configure_TC_TMOUT(void) {
    uint32_t ul_div;
    uint32_t ul_tcclks;
    uint32_t ul_sysclk;
    uint32_t ul_frec_hz = (uint32_t)TMOUT_BASE_FREQ_HZ;

    /* Get system clock. */
    ul_sysclk = sysclk_get_cpu_hz();

    /* Configure PMC. */
    pmc_enable_periph_clk(ID_TC_TMOUT);

    /* Configure TC for a TC_FREQ frequency and trigger on RC compare. */
    tc_find_mck_divisor(ul_frec_hz, ul_sysclk, &ul_div, &ul_tcclks,
                        ul_sysclk);
    tc_init(TC_TMOUT, TC_TMOUT_CHN, ul_tcclks | TC_CMR_CPCTRG);
    tc_write_rc(TC_TMOUT, TC_TMOUT_CHN, (ul_sysclk / ul_div) / ul_frec_hz);

    /* Configure and enable interrupt on RC compare. */
    NVIC_SetPriority((IRQn_Type)ID_TC_TMOUT, 10);
    NVIC_EnableIRQ((IRQn_Type)ID_TC_TMOUT);
    tc_enable_interrupt(TC_TMOUT, TC_TMOUT_CHN, TC_IER_CPCS);
}

/*
** ===================================================================
**     Method      :  TMOUT_Init (component Timeout)
**     Description :
**         Initialization of the driver
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void TMOUT_Init(void) {
    uint8_t i;

    for(i=0; i<TMOUT_NOF_COUNTERS; i++) {
        TMOUT_Counters[i] = 0;
        TMOUT_FreeCounters[i] = true;
    }

    TimeoutFunctionsInit();

    /* Configure TC TMOUT */
    _configure_TC_TMOUT();
    tc_start(TC_TMOUT, TC_TMOUT_CHN);
    tc_set_block_mode(TC_TMOUT, 0);
}

/*
** ===================================================================
**     Method      :  TMOUT_Value (component Timeout)
**     Description :
**         Return the current value of the counter (in ticks)
**     Parameters  :
**         NAME            - DESCRIPTION
**         handle          - Handle of the timeout counter
**     Returns     :
**         ---             - Returns the value of the timeout counter.
** ===================================================================
*/
TMOUT_CounterType TMOUT_Value(TMOUT_CounterHandle handle) {
    TMOUT_CounterType val;

    if (handle==TMOUT_OUT_OF_HANDLE) {
        return 0; /* return dummy value */
    }
    cpu_irq_enter_critical();
    val = TMOUT_Counters[handle];
    cpu_irq_leave_critical();
    return val;
}

/*
** ===================================================================
**     Method      :  TMOUT_SetCounter (component Timeout)
**     Description :
**         Sets the counter to a new value and returns the value just
**         prior to the call.
**     Parameters  :
**         NAME            - DESCRIPTION
**         handle          - Counter handle which shall get a new
**                           value.
**         nofTicks        - New value (tick count) of the
**                           timeout counter. Pass zero to have it
**                           expire immediately.
**     Returns     :
**         ---             - Value of counter before reset.
** ===================================================================
*/
TMOUT_CounterType TMOUT_SetCounter(TMOUT_CounterHandle handle, TMOUT_CounterType nofTicks) {
    TMOUT_CounterType res;

    if (handle==TMOUT_OUT_OF_HANDLE) {
        return 0; /* return dummy value */
    }
    cpu_irq_enter_critical();
    res = TMOUT_Counters[handle];
    TMOUT_Counters[handle] = nofTicks;
    cpu_irq_leave_critical();
    return res;
}

/* END TMOUT. */

/*!
** @}
*/
