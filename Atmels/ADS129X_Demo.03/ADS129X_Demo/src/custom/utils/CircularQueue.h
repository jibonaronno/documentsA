#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H
#include <stddef.h>
#include <stdbool.h>

struct circular_buffer
{
    void *buffer;       /* data buffer */
    void *buffer_end;   /* end of data buffer */
    size_t capacity;    /* maximum number of items in the buffer */
    size_t count;       /* number of items in the buffer */
    size_t sz;          /* size of each item in the buffer */
    void *head;         /* pointer to head */
    void *tail;         /* pointer to tail */
};
typedef struct circular_buffer * circular_buffer_t;

/**
* @brief Creates a statically allocated circular buffer
*
* This function initializes the circular buffer.
* A pointer to the buffer space and a pointer
* to the control structure are required, both of them shoud be allocated
* statically by the programmer.
*
* @param cb The pointer to the structure holding circular buffer data
* @param buf Pointer to the memory used to store actual items
* @param count The number of items to store on the circular buffer
* @param size The size in bytes of each item on the buffer
*
* @return This function performs some basic validation on the parameters passed,
* if something is wrong with them,it will return NULL.
*/
circular_buffer_t cb_create_static(circular_buffer_t cb, void * buf, size_t count, size_t size);

/**
* @brief Adds one item to the circular buffer
*
* This function writes an item to the circular buffer back. This function affects
* the write pointer and the stored items counter.
*
* The number of bytes to be copied to the circular buffer was defined when the
* circular buffer was created with the function cb_create_static() (size parameter).
*
* @param fifo Pointer to a circular_buffer structure.
* @param item Pointer to a location that holds data to be written to the circular
* buffer.
*
* @return  Nothing.
*/
void cb_push_back(circular_buffer_t cb, void *item);

/**
* @brief Obtains one item from the circular buffer.
*
* This function reads an item from the circular buffer front. This function affects
* the read pointer and the stored items counter.
*
* The number of bytes to be copied to the provided buffer was defined when the
* fifo buffer was created with the function cb_create_static() (size parameter).
*
* @param cb Pointer to a circular_buffer structure.
* @param item Pointer to a location to hold the data read from the circular buffer,
* this buffer should be sized appropiately to accomodate the data.
*
* @return  Nothing.
*/
void cb_pop_front(circular_buffer_t cb, void *item);

/**
* @brief Obtains a pointer item from the circular buffer.
*
* This function return a pointer to the element in the circular buffer at the
* specified index.
* This function does not performs any changes on the buffer descriptor.
*
* @param cb Pointer to a circular_buffer structure.
*
* @return  Returns the pointer to the location that holds the item in
* circular buffer at the specified index, if the buffer hasn't enought items
* this returns NULL.
*/
void* cb_at(const circular_buffer_t cb, size_t index);

/**
* @brief Checks if the circular buffer is full.
*
* Check if it can accept one item at least.
*
* @param cb Pointer to a circular_buffer structure.
*
* @return This function returns true if the buffer is full, false otherwise.
*/
bool cb_full(const circular_buffer_t cb);

/**
* @brief Runs the functionallity tests for this module.
*
* The test result will be shown on the stdout.
*
* @return Nothing.
*/
void CB_TEST(void);

#endif  /* CIRCULAR_QUEUE_H */