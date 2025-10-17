#ifndef __TSM_FASTQUEUE_H
#define __TSM_FASTQUEUE_H

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    volatile uint32_t count;
    uint32_t capacity;
    uint32_t bufferpos;
    uint8_t *buffer;
} FastQueue;

extern void FQInit(FastQueue *_queue, uint8_t *buffer, uint32_t _buffsize);
extern bool FQisEmpty(FastQueue *_queue);
extern uint32_t FQgetdata(FastQueue *_queue, uint32_t index, char *t, uint32_t count, bool pop);
extern char FQatpos(FastQueue *_queue, uint32_t index);
extern uint32_t FQremove(FastQueue *_queue, uint32_t count);
extern uint32_t FQpop(FastQueue *_queue, char * t, uint32_t count);
extern char FQpop1(FastQueue *_queue);
extern void FQclear(FastQueue *_queue);
extern uint32_t FQgetrealindex(FastQueue *_queue, uint32_t index);
extern bool FQisFull(FastQueue *_queue);
extern uint32_t FQavailable(FastQueue *_queue);
extern uint32_t FQpush(FastQueue *_queue, char * t, uint32_t count);

#endif /* __TSM_FASTQUEUE_H */