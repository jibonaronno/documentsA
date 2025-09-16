#ifndef FASTQUEUE_H
#define FASTQUEUE_H

#include <QtCore/QObject>
#include <QtCore/QMutex>
#include <QtCore/QFile>
#include <QtCore/QDebug>
#include "circularqueue.h"

class QUSB_S3C2440;

template <typename T>
class FastQueue
{
    friend class QUSB_S3C2440;
protected:
    T * buffer;
    qint32 bufferpos;
    qint32 capacity;
    qint32 count;
    QMutex * mutex;

    qint32 getdata(qint32 index, T * t, qint32 count, bool pop);
public:
    explicit FastQueue(qint32 capacity);
    explicit FastQueue(const QString & filename, qint32 defaultcapacity);
    explicit FastQueue(FastQueue *_fastqueue);
    ~FastQueue();

    qint32 size() const { return count; }
    bool isEmpty() const { return count == 0; }
    bool isFull() const { return count == capacity; }
    void clear() { bufferpos = count = 0; }
    qint32 available() const { return capacity - count; }

    qint32 push(T * t, qint32 count);
    qint32 pop(T * t, qint32 count) { return getdata(0, t, count, true); }
    qint32 popAll(T * t) { return getdata(0, t, count, true); }
    T pop();
    T atpos(qint32 index);
    qint32 remove(qint32 count);
    T atrealpos(qint32 realindex) const { return buffer[realindex]; }
    qint32 getrealindex(qint32 index) const;

    void lock() {mutex->lock();}
    void unlock() {mutex->unlock();}

    bool isSequential() const { return (bufferpos + count) <= capacity; }

    bool loadfromfile(const QString & name);
    bool savetofile(const QString & name) const;

    int copytoqueue(FastQueue* _destination);
    int copytoqueue(CircularQueue <T>* _destination);
    int copyToBuff(qint32 index, T * t, qint32 count) {
        return getdata(index, t, count, false);
    }

    T * getSlice(qint32 index, qint32 count);
    qint32 getCapacity() const { return capacity; }
};

template <typename T>
FastQueue<T>::FastQueue(qint32 capacity) {
    mutex = new QMutex();
    this->capacity = capacity;
    buffer = new T[this->capacity];
    memset(buffer, 0, this->capacity * sizeof(T));
    clear();
}

template <typename T>
FastQueue<T>::FastQueue(const QString & filename, qint32 defaultcapacity) {
    mutex = new QMutex();
    if (!loadfromfile(filename))
    {
        this->capacity = defaultcapacity;
        buffer = new T[this->capacity];
        memset(buffer, 0, this->capacity * sizeof(T));
        clear();
    }
}

template <typename T>
FastQueue<T>::FastQueue(FastQueue *_fastqueue) {
    mutex = new QMutex();
    capacity = _fastqueue->capacity;
    bufferpos = _fastqueue->bufferpos;
    count = _fastqueue->count;
    buffer = new T[capacity];
    memcpy(buffer, _fastqueue->buffer, capacity * sizeof(T));
}

template <typename T>
FastQueue<T>::~FastQueue() {
    qDebug() << Q_FUNC_INFO;
    delete [] buffer;
    delete mutex;
}

template <typename T>
qint32 FastQueue<T>::push(T * t, qint32 count)
{
//    qint32 available = this->available();
//    if ((available) && (count > 0))
//    {
//        if (count > available) count = available;
//        qint32 endindex = bufferpos + this->count - 1;
//        if (endindex > (capacity - 1)) endindex -= capacity;

//        if ((endindex + count) < capacity) {
//            memcpy(&buffer[endindex + 1], t, count * sizeof(T));
//        }
//        else {
//            qint32 partialcount = capacity - (endindex + 1);
//            memcpy(&buffer[endindex + 1], t, partialcount * sizeof(T));
//            memcpy(buffer, &t[partialcount], (count - partialcount) * sizeof(T));
//        }

//        this->count += count;
//        return count;
//    }
//    else {
//        qDebug() << "FULL" << this->count;
//        return 0;
//    }

    qint32 available = this->available();
    if ((available) && (count > 0))
    {
        if (count > available) count = available;
        qint32 endindex = bufferpos + this->count;
        if (endindex > (capacity - 1)) endindex -= capacity;

        if ((endindex + count) <= capacity) {
            memcpy(&buffer[endindex], t, count * sizeof(T));
        }
        else {
            qint32 partialcount = capacity - (endindex);
            memcpy(&buffer[endindex], t, partialcount * sizeof(T));
            memcpy(buffer, &t[partialcount], (count - partialcount) * sizeof(T));
        }
        this->count += count;
        return count;
    }
    else {
//        qDebug() << "FULL" << this->capacity;
        return 0;
    }
}


template <typename T>
qint32 FastQueue<T>::getdata(qint32 index, T * t, qint32 count, bool pop) {
    if ((index >= 0) && (index < this->count) && (count > 0)) {
        if ((index + count) > this->count) count = this->count - index;
        if ((index += bufferpos) > (capacity - 1)) index -= capacity;

        if (index + count <= capacity) {
            memcpy(t, &buffer[index], count * sizeof(T));
        }
        else {
            qint32 partialcount = capacity - index;
            memcpy(t, &buffer[index], partialcount * sizeof(T));
            memcpy(&t[partialcount], buffer, (count - partialcount) * sizeof(T));
        }

        if (pop) {
            if ((bufferpos += count) > (capacity - 1)) bufferpos -= capacity;
            this->count -= count;
        }
        return count;
    }
    else
        return 0;
}

template <typename T>
T FastQueue<T>::pop() {
    T result = atpos(0);
    remove(1);
    return result;

    // bad implementation, it should be raised some exception if getdata result is -1
}

template <typename T>
inline qint32 FastQueue<T>::getrealindex(qint32 index) const {
//    Q_ASSERT_X((index >= 0) && (index < count), "FastQueue<T>::getrealindex", "index out of range");

//    if (!isSequential())
//        index = (bufferpos + index) % capacity;

//    return index;

    if ((index += bufferpos) >= capacity) index -= capacity;

    return index;
}

template <typename T>
T FastQueue<T>::atpos(qint32 index) {
    // assert this precondition
    // if ((index >= 0) && (index < count))

    return buffer[getrealindex(index)];
}

template <typename T>
qint32 FastQueue<T>::remove(qint32 count) {
    if (count > this->count) count = this->count;
    if ((bufferpos += count) >= capacity) bufferpos -= capacity;
    this->count -= count;
    return count;
}

template <typename T>
bool FastQueue<T>::loadfromfile(const QString & name)
{
    QFile file(name);
     if (file.open(QIODevice::ReadOnly)) {
         T * tmpbuffer = new T[file.size() / sizeof(T)];
         qint64 result = file.read((char*) tmpbuffer, file.size());
         if (result != -1) {
             if (buffer) delete [] buffer;
             buffer = tmpbuffer;

             if (result > (capacity * sizeof(T)))
                 capacity = file.size() / sizeof(T);

             bufferpos = 0;
             count = result / sizeof(T);

             return true;
         }
         else {
             delete [] tmpbuffer;
             return false;
         }
     }
     else
         return false;
}

template <typename T>
bool FastQueue<T>::savetofile(const QString & name) const {
    QFile file(name);
    if (file.open(QIODevice::WriteOnly)) {
        qint64 result;
        if (isSequential())
            result = file.write((char*) buffer, count * sizeof(T));
        else {
            result = file.write((char*) &buffer[bufferpos], (count - bufferpos) * sizeof(T));
            if (result != -1)
                result = file.write((char*) buffer, bufferpos * sizeof(T));
        }
        return (result != -1);
    }
    else
        return false;
}

template <typename T>
int FastQueue<T>::copytoqueue(FastQueue* _destination) {
    qint32 localcount = this->count;
    if(_destination->available() >= localcount) {
        T *tmpdata = new T [localcount];
        this->getdata(0, tmpdata, localcount, false);
//        this->pop(tmpdata, localcount);
        _destination->push(tmpdata, localcount);
        delete tmpdata;
    }
    else {
        qDebug("full!!!!!!");
    }
    return localcount;
}

template <typename T>
int FastQueue<T>::copytoqueue(CircularQueue<T> *_destination) {
    qint32 localcount = this->count;
//    if(!_destination->isFull())
    {
        T *tmpdata = new T [localcount];
        this->getdata(0, tmpdata, localcount, false);
//        this->pop(tmpdata, localcount);
        _destination->push(tmpdata, localcount);
        delete tmpdata;
    }
/*    else {
        qDebug("full!!!!!!");
    }*/
    return localcount;
}

template <typename T>
T * FastQueue<T>::getSlice(qint32 index, qint32 count) {
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
}
#endif // FASTQUEUE_H
