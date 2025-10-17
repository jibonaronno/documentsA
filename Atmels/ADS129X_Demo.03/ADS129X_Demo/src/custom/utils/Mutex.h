#ifndef MUTEX_H
#define MUTEX_H

#include <stdbool.h>
#include <stdatomic.h>

typedef volatile atomic_flag Mutex;

#define MUTEX_UNLOCKED  ATOMIC_FLAG_INIT
#define MUTEX_LOCKED  { 1 }

#define MutexLock(mutex) while(atomic_flag_test_and_set(mutex)){}

#define MutexTryLock(mutex) !atomic_flag_test_and_set(mutex)
#define MutexUnlock(mutex) atomic_flag_clear(mutex)

#endif /*MUTEX_H*/