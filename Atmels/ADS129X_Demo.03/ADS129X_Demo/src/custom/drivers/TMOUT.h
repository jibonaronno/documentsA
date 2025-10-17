/**
 * @file TMOUT.h
 * @version 1.0
 * @brief Timeout module using periodic ticks, without RTOS.
 *
 * This module implements timeout functionality using a periodic interrupt tick.
 * It allows allocation and handling of multiple counters that expire after a
 * defined number of ticks.
 *
 * Settings:
 * - Maximum counters: 5
 * - Tick period: 1 ms
 * - RTOS: Disabled
 */

#ifndef __TMOUT_H
#define __TMOUT_H

#include <asf.h>
#include <user_board.h>
#include <stdbool.h>

/**
 * @addtogroup TMOUT_module
 * @brief Timeout module using periodic ticks, without RTOS.
 * @ingroup Drivers
 * @{
*/

/* ----------------------------- Type Definitions ----------------------------- */

/**
 * @typedef TMOUT_CounterType
 * @brief Base type for timeout counter values (tick-based).
 */
#ifndef __BWUserType_TMOUT_CounterType
#define __BWUserType_TMOUT_CounterType
typedef uint32_t TMOUT_CounterType;
#endif

/**
 * @typedef TMOUT_CounterHandle
 * @brief Type for identifying an active timeout counter.
 */
#ifndef __BWUserType_TMOUT_CounterHandle
#define __BWUserType_TMOUT_CounterHandle
typedef uint8_t TMOUT_CounterHandle;
#endif

/* ----------------------------- Constants ----------------------------- */

#define TMOUT_OUT_OF_HANDLE     0xFF  /**< Special value indicating no available handles. */

#define TMOUT_TICK_PERIOD_MS    (1000 / TMOUT_BASE_FREQ_HZ) /**< Tick period in ms based on base frequency. */

#define MS_TO_TICKS(ms)         ((ms) / TMOUT_TICK_PERIOD_MS)
#define SEC_TO_TICKS(s)         ((s) * 1000 / TMOUT_TICK_PERIOD_MS)

/* ----------------------------- Timeout Function Registration ----------------------------- */

/**
 * @brief Timeout callback function type.
 */
typedef void (*TimeoutFunction_t)(void);

/**
 * @brief Register a function to be called periodically.
 * 
 * @param func Pointer to the function.
 * @param period_ticks Number of ticks between executions.
 * @return true if successfully registered, false otherwise.
 */
bool RegisterTimeoutFunction(TimeoutFunction_t func, uint16_t period_ticks);

/**
 * @brief Unregister a previously registered periodic timeout function.
 *
 * @param func Pointer to the function.
 */
void UnregisterTimeoutFunction(TimeoutFunction_t func);

/* ----------------------------- Timeout Counter API ----------------------------- */

/**
 * @brief Initializes a new timeout counter and returns a handle to it.
 *
 * @param nofTicks Number of ticks before the counter expires.
 * @return TMOUT_CounterHandle Handle to the timeout counter.
 */
TMOUT_CounterHandle TMOUT_GetCounter(TMOUT_CounterType nofTicks);

/**
 * @brief Releases a previously used timeout counter.
 *
 * @param handle Pointer to the counter handle.
 */
void TMOUT_LeaveCounter(TMOUT_CounterHandle* handle);

/**
 * @brief Checks if a timeout counter has expired.
 *
 * @param handle Timeout counter handle.
 * @return true if expired, false otherwise.
 */
bool TMOUT_CounterExpired(TMOUT_CounterHandle handle);

/**
 * @brief Adds a system tick. Should be called from the periodic interrupt handler.
 */
void TMOUT_AddTick(void);

/**
 * @brief Initializes the timeout module.
 */
void TMOUT_Init(void);

/**
 * @brief Gets the current value of a timeout counter.
 *
 * @param handle Timeout counter handle.
 * @return Current tick value.
 */
TMOUT_CounterType TMOUT_Value(TMOUT_CounterHandle handle);

/**
 * @brief Sets the counter to a new value.
 *
 * @param handle Timeout counter handle.
 * @param nofTicks New tick value.
 * @return Previous tick value before setting.
 */
TMOUT_CounterType TMOUT_SetCounter(TMOUT_CounterHandle handle, TMOUT_CounterType nofTicks);

/* ----------------------------- Utility Macros ----------------------------- */

/**
 * @brief Declares a local timeout counter handle.
 */
#define INIT_LOCAL_TIMEOUT() TMOUT_CounterHandle localtimeouthandle

/**
 * @brief Waits (sleeps) for the specified milliseconds using WFI mode.
 */
#define WAIT_MS(ms) do { \
    localtimeouthandle = TMOUT_GetCounter(MS_TO_TICKS(ms)); \
    while (!TMOUT_CounterExpired(localtimeouthandle)) { \
        pmc_sleep(SAM_PM_SMODE_SLEEP_WFI); \
    } \
    TMOUT_LeaveCounter(&localtimeouthandle); \
} while (0)

/*! @} */  // End of TMOUT_module

#endif /* __TMOUT_H */
