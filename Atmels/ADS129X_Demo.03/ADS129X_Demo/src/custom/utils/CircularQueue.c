#include "CircularQueue.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#ifdef WITH_TEST
#include <stdio.h>
#endif

circular_buffer_t cb_create_static(circular_buffer_t cb, void * buf, size_t count, size_t size)
{
    if ((buf != NULL) && (cb != NULL) && (count != 0u)) {
        cb->buffer = buf;
        cb->buffer_end = (uint8_t *)cb->buffer + count * size;
        cb->capacity = count;
        cb->count = 0u;
        cb->sz = size;
        cb->head = cb->buffer;
        cb->tail = cb->buffer;
    }
    else {
        cb = NULL;
    }
    return cb;
}

void cb_push_back(circular_buffer_t cb, void *item)
{
    memcpy(cb->head, item, cb->sz);
    cb->head = (uint8_t*)cb->head + cb->sz;
    if(cb->head == cb->buffer_end) {
        cb->head = cb->buffer;
    }
    if(cb->count < cb->capacity) {
        cb->count++;
    }
    else {
        cb->tail = (uint8_t*)cb->tail + cb->sz;
        if(cb->tail == cb->buffer_end) {
            cb->tail = cb->buffer;
        }
    }
}

void cb_pop_front(circular_buffer_t cb, void *item)
{
    if(cb->count != 0u) {
        memcpy(item, cb->tail, cb->sz);
        cb->tail = (uint8_t*)cb->tail + cb->sz;
        if(cb->tail == cb->buffer_end) {
            cb->tail = cb->buffer;
        }
        cb->count--;
    }
    else {
        memset(item, 0, cb->sz);
    }
}

bool cb_full(const circular_buffer_t cb)
{
    bool result = false;
    if(cb->count == cb->capacity) {
        result = true;
    }
    return result;
}

void * cb_at(const circular_buffer_t cb, size_t index)
{
    void *result;
    size_t startPos = index * cb->sz;
    size_t bytesToEnd = (size_t) ((uint8_t*)cb->buffer_end - (uint8_t*)cb->tail);
    if(startPos < bytesToEnd) {
        result = (uint8_t*)cb->tail + startPos;
    }
    else {
        result = (uint8_t*)cb->buffer + (startPos - bytesToEnd);
    }
    return result;
}

/**
* Functionallity Test
*/

#ifdef WITH_TEST
#define TEST_ITEMS 5u
#pragma diag_suppress=Pm064
static void printCQ(circular_buffer_t cb);
static void printCQ(circular_buffer_t cb)
{
    int32_t value = 0;
    printf("[ ");
    for(int i = 0; i < (int)cb->count; i++) {
        value =* ((int32_t*)cb_at(cb, (unsigned int)i));
        if((unsigned int)i < cb->count-1u) {
            printf("%d, ", value);
        }
    }
    printf("%d ]\n", value);
}
#pragma diag_default=Pm064

void CB_TEST(void)
{
    int32_t cbTestBuffer[TEST_ITEMS];
    struct circular_buffer cb;
    cb_create_static(&cb, (void*) &cbTestBuffer, TEST_ITEMS, sizeof(int32_t));

    for(int32_t i=0; i<35; i++) {
        cb_push_back(&cb, &i);
        printCQ(&cb);
    }

}
#endif