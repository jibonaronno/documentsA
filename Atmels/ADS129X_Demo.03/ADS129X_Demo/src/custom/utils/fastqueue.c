#include "fastqueue.h"
#include <interrupt.h>

void FQInit(FastQueue *_queue, uint8_t *buffer, uint32_t _buffsize) {
    _queue->capacity = _buffsize;
    _queue->buffer = buffer;
    FQclear(_queue);
}

inline int FQsize(FastQueue *_queue) {
    return _queue->count;
}

bool FQisEmpty(FastQueue *_queue) {
    return _queue->count == 0;
}

bool FQisFull(FastQueue *_queue) {
    return _queue->count == _queue->capacity;
}

void FQclear(FastQueue *_queue) {
    _queue->bufferpos = _queue->count = 0u;
}

uint32_t FQavailable(FastQueue *_queue) {
    return (_queue->capacity - _queue->count);
}

uint32_t FQpop(FastQueue *_queue, char * t, uint32_t count) {
    return FQgetdata(_queue, 0, t, count, true);
}

inline uint32_t FQpopAll(FastQueue *_queue, char * t) {
    return FQgetdata(_queue, 0, t, _queue->count, true);
}

inline char FQatrealpos(FastQueue *_queue, uint32_t realindex) {
    return _queue->buffer[realindex];
}

inline bool FQisSequential(FastQueue *_queue) {
    return (_queue->bufferpos + _queue->count) <= _queue->capacity;
}

uint32_t FQpush(FastQueue *_queue, char * t, uint32_t count) {
    cpu_irq_enter_critical();
    uint32_t lavailable = FQavailable(_queue);
    if ((lavailable) && (count > 0)) {
        if (count > lavailable) count = lavailable;
        uint32_t endindex = _queue->bufferpos + _queue->count;
        if (endindex > (_queue->capacity - 1)) endindex -= _queue->capacity;

        if ((endindex + count) <= _queue->capacity) {
            memcpy((void*)&(_queue->buffer[endindex]), (void*)t, count * sizeof(char));
        } else {
            int partialcount = _queue->capacity - (endindex);
            memcpy((void*)&(_queue->buffer[endindex]), (void*)t, partialcount * sizeof(char));
            memcpy((void*)_queue->buffer, (void*)&t[partialcount], (count - partialcount) * sizeof(char));
        }
        _queue->count += count;
        cpu_irq_leave_critical();
        return count;
    } else {
        cpu_irq_leave_critical();
        //        qDebug() << "FULL" << this->capacity;
        return 0;
    }
}

inline uint32_t FQgetdata(FastQueue *_queue, uint32_t index, char *t, uint32_t count, bool pop) {
    cpu_irq_enter_critical();
    if ((index >= 0) && (index < _queue->count) && (count > 0)) {
        if ((index + count) > _queue->count) count = _queue->count - index;
        if ((index += _queue->bufferpos) > (_queue->capacity - 1)) index -= _queue->capacity;

        if (index + count <= _queue->capacity) {
            memcpy((void*)t, (void*)&(_queue->buffer[index]), count * sizeof(char));
        } else {
            int partialcount = _queue->capacity - index;
            memcpy((void*)t, (void*)&(_queue->buffer[index]), partialcount * sizeof(char));
            memcpy((void*)&t[partialcount], (void*)_queue->buffer, (count - partialcount) * sizeof(char));
        }

        if (pop) {
            if ((_queue->bufferpos += count) > (_queue->capacity - 1)) _queue->bufferpos -= _queue->capacity;
            _queue->count -= count;
        }
        cpu_irq_leave_critical();
        return count;
    }
    cpu_irq_leave_critical();
    return 0;
}

inline uint32_t FQremove(FastQueue *_queue, uint32_t count) {
    cpu_irq_enter_critical();
    if (count > _queue->count) count = _queue->count;
    if ((_queue->bufferpos += count) >= _queue->capacity) _queue->bufferpos -= _queue->capacity;
    _queue->count -= count;
    cpu_irq_leave_critical();
    return count;
}

inline char FQpop1(FastQueue *_queue) {
    char result = FQatpos(_queue, 0);
    FQremove(_queue, 1);
    return result;
    // bad implementation, it should be raised some exception if getdata result is -1
}

inline uint32_t FQgetrealindex(FastQueue *_queue, uint32_t index) {
    if ((index += _queue->bufferpos) >= _queue->capacity) index -= _queue->capacity;
    return index;
}

inline char FQatpos(FastQueue *_queue, uint32_t index) {
    // assert this precondition
    // if ((index >= 0) && (index < count))

    return _queue->buffer[FQgetrealindex(_queue, index)];
}

/*char* getSlice(uint32_t index, uint32_t count) {
    index = getrealindex(index);
    if (!isEmpty()) {
        if ((count <= 0) || (count > this->count))
            count = this->count;
        T * result = new T[count];
        if (isSequential())
            memcpy(result, &buffer[index], count * sizeof(T));
        else {
            qint32 slicecount = capacity - index;
            if (slicecount >= count)
                memcpy(result, &buffer[index], count * sizeof(T));
            else
            {
                memcpy(result, &buffer[index], slicecount * sizeof(T));
                memcpy(&result[slicecount], buffer, (count - slicecount) * sizeof(T));
            }
            //            qint32 slicestartpos = index + count;
            //            if (slicestartpos <= bufferpos)
            //                memcpy(result, &buffer[index], count * sizeof(T));
            //            else {
            //                memcpy(result, &buffer[index], qAbs(capacity - index) * sizeof(T));
            //                memcpy(&result[qAbs(capacity - index)], buffer, (count-(capacity - index)) * sizeof(T));
            //            }
        }
        return result;
    }
    else
        return NULL;
}*/
