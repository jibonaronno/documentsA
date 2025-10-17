/*	Generic FIFO buffer Implementation
	Copyright (C) 2014 Jesus Ruben Santa Anna Zamudio.

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

	Author website: http://geekfactory.mx
	Author e-mail: ruben at geekfactory dot mx
 */

#include "FIFO.h"

/*-------------------------------------------------------------*
 *		Private function prototypes			*
 *-------------------------------------------------------------*/
static void fifo_copy_from(fifo_t fifo, void *item);
static void fifo_copy_to(fifo_t fifo, const void *item);

/*-------------------------------------------------------------*
 *		Public API implementation			*
 *-------------------------------------------------------------*/
fifo_t fifo_create_static(fifo_t fifo, void * buf, uint32_t count, size_t size)
{
    /* Sanity check for memory and element sizes */
    if ((buf != NULL) && (fifo != NULL) && (count != 0u)) {
        fifo->itemspace = buf;
        fifo->itemsize = size;
        fifo->allocatedbytes = count * size;
        fifo->readoffset = 0u;
        fifo->writeoffset = 0u;
        fifo->storedbytes = 0u;
        fifo->storeditems = 0u;
    }
    else {
        fifo = NULL;
    }
    return fifo;
}

bool fifo_add(fifo_t fifo, const void * item)
{
    bool result;
    if (!fifo_is_full(fifo)) {
        fifo_copy_to(fifo, item);
        fifo->storedbytes += fifo->itemsize;
        fifo->storeditems++;
        result = true;
    }
    else {
        result = false;
    }
    return result;
}

bool fifo_get(fifo_t fifo, void * item)
{
    bool result;
    if (!fifo_is_empty(fifo)) {
        fifo_copy_from(fifo, item);
        fifo->storedbytes -= fifo->itemsize;
        fifo->storeditems--;
        result = true;
    }
    else {
        result = false;
    }
    return  result;
}

void * fifo_get_ptr(fifo_t fifo)
{
    void *ptr;
    if (!fifo_is_empty(fifo)) {
        ptr = (((uint8_t*)fifo->itemspace) + fifo->readoffset);
        fifo->readoffset += fifo->itemsize;
        if (fifo->readoffset >= fifo->allocatedbytes) {
            fifo->readoffset = 0u;
        }
        fifo->storedbytes -= fifo->itemsize;
        fifo->storeditems--;
    }
    else {
        ptr = NULL;
    }
    return ptr;
}

void * fifo_peek_ptr(const fifo_t fifo, size_t index)
{
    uint8_t *ptr;
    uint8_t *endptr;
    if (fifo->storeditems > index) {
        size_t offset = index * fifo->itemsize;
        ptr = (((uint8_t*)fifo->itemspace) + fifo->readoffset) + offset;
        endptr = (((uint8_t*)fifo->itemspace) + fifo->allocatedbytes);
        if(ptr  >= endptr) {
            ptr = (uint8_t*)fifo->itemspace+(ptr - endptr);
        }
    }
    else {
        ptr = NULL;
    }
    return (void*)ptr;
}

bool fifo_is_full(const fifo_t fifo)
{
    bool result;
    if (fifo->storedbytes >= fifo->allocatedbytes) {
        result = true;
    }
    else {
        result = false;
    }
    return result;
}

bool fifo_is_empty(const fifo_t fifo)
{
    bool result;
    if (fifo->storedbytes == 0u) {
        result = true;
    }
    else {
        result = false;
    }
    return result;
}

bool fifo_discard(fifo_t fifo, uint32_t count, enum fifo_side side)
{
    uint32_t t;
    bool result = false;
    t = fifo->itemsize * count; /* Compute byte size of elements to be deleted */
    if (t <= fifo->storedbytes) { /* Check if we can remove the requested ammount of data */
        if (side == E_FIFO_FRONT) {
            fifo->readoffset = (fifo->readoffset + t) % fifo->allocatedbytes; /* Increase read pointer n elements */
            fifo->storedbytes -= t; /* Decrease stored bytes number */
        }
        else {
            fifo->writeoffset = (fifo->writeoffset - t) % fifo->allocatedbytes; /* Decrease write pointer n elements */
            fifo->storedbytes -= t; /* Decrease stored bytes number */
        }
        fifo->storeditems--;
        result = true;
    }
    return result;
}

size_t fifo_item_count(const fifo_t fifo)
{
    return fifo->storeditems;
}

static void fifo_copy_from(fifo_t fifo, void * item)
{
    memcpy(item, (((uint8_t*)fifo->itemspace) + fifo->readoffset), fifo->itemsize);
    fifo->readoffset += fifo->itemsize;
    if (fifo->readoffset >= fifo->allocatedbytes) {
        fifo->readoffset = 0u;
    }
}

static void fifo_copy_to(fifo_t fifo, const void *item)
{
    memcpy(((uint8_t*)fifo->itemspace) + fifo->writeoffset, item, fifo->itemsize);
    fifo->writeoffset += fifo->itemsize;
    if (fifo->writeoffset >= fifo->allocatedbytes) {
        fifo->writeoffset = 0u;
    }
}
