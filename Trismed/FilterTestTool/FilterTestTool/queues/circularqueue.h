#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H

#include <QtCore/QObject>
#include <QtCore/QMutex>
#include <QtCore/QFile>
#include <QtCore/QDebug>

template <typename T>
class CircularQueue
{
protected:
    T * buffer;
    qint32 bufferpos;
    qint32 capacity;
    qint32 count;
    QMutex * mutex;

    quint64 pushedcount;
private:

public:
    explicit CircularQueue(qint32 capacity);
    explicit CircularQueue(const CircularQueue<T> & other);
    explicit CircularQueue(CircularQueue<T> &other, qint32 _count);
    explicit CircularQueue(const QString & filename, qint32 defaultcapacity);
    virtual ~CircularQueue();

    virtual qint32 size() const { return count; }
    bool isEmpty() const { return count == 0; }
    bool isFull() const { return count == capacity; }
    void clear() { pushedcount = count = bufferpos = 0; }

//    QMutex * accessMutex() const { return mutex; }
    void lock() {mutex->lock();}
    void unlock() {mutex->unlock();}

    virtual quint64 pushedCount() const;
    bool isSequential() const { return !isFull() || (bufferpos == 0); }

    virtual void push(T * t, qint32 count);
    virtual T atpos(qint32 index) const { return buffer[getrealindex(index)]; }
    T atrealpos(qint32 realindex) const;
    qint32 getrealindex(qint32 index) const;

    bool savetofile(const QString & name, qint32 count = 0) const; // save last count elements, if count == 0 save all elements
    bool loadfromfile(const QString & name);

    T * getBackSlice(qint32 count);
    void getBackSliceTo(T *destinationptr, qint32 count);
    T * getSlice(qint32 index, qint32 count);

    qint32 getCapacity() const { return capacity; }
    void setCapacity(qint32 value, bool clear = false);
};

template <typename T>
CircularQueue<T>::CircularQueue(qint32 capacity) {
    mutex = new QMutex();
    this->capacity = capacity;
    buffer = new T[this->capacity];
    memset(buffer, 0, this->capacity * sizeof(T));
    clear();
}

template <typename T>
CircularQueue<T>::CircularQueue(const CircularQueue<T> & other) {
    mutex = new QMutex();
    this->capacity = other.capacity;
    this->bufferpos = other.bufferpos;
    this->count = other.count;
    this->pushedcount = other.pushedcount;

    buffer = new T[this->capacity];
    memcpy(buffer, other.buffer, this->count * sizeof(T));
}

template <typename T>
CircularQueue<T>::CircularQueue(CircularQueue<T> & other, qint32 _count) {
    mutex = new QMutex();
    capacity = _count;
    bufferpos = 0;
    count = _count;
    pushedcount = _count;
    buffer = other.getBackSlice(count);
}

template <typename T>
CircularQueue<T>::CircularQueue(const QString & filename, qint32 defaultcapacity) {
    mutex = new QMutex();
    capacity = 0;
    buffer = 0;
    if (!loadfromfile(filename)) {
        this->capacity = defaultcapacity;
        buffer = new T[this->capacity];
        memset(buffer, 0, this->capacity * sizeof(T));
        clear();
    }
}

template <typename T>
CircularQueue<T>::~CircularQueue() {
    if (buffer)
        delete [] buffer;
    delete mutex;
}

template <typename T>
void CircularQueue<T>::push(T * t, qint32 count) {
    if ((bufferpos + count) <= capacity){
        memcpy(&buffer[bufferpos], t, count * sizeof(T));
    }
    else {
        qint32 partialcount = capacity - bufferpos;
        memcpy(&buffer[bufferpos], t, partialcount * sizeof(T));
        memcpy(buffer, &t[partialcount], (count - partialcount) * sizeof(T));
    }
    if ((bufferpos += count) >= capacity) bufferpos -= capacity;
    if (this->count < capacity) this->count += qMin(count, capacity - this->count);
    pushedcount += count;
}

template <typename T>
inline qint32 CircularQueue<T>::getrealindex(qint32 index) const {
    Q_ASSERT_X((index >= 0) && (index < count), "CircularQueue<T>::getrealindex", "index out of range");
    if (!isSequential())
        index = (bufferpos + index) % capacity;
    return index;
}

template <typename T>
inline T CircularQueue<T>::atrealpos(qint32 realindex) const {
    Q_ASSERT_X((realindex >= 0) && (realindex < count), "CircularQueue<T>::atrealpos", "index out of range");
    return buffer[realindex];
}

template <typename T>
bool CircularQueue<T>::savetofile(const QString & name, qint32 count) const {
    QFile file(name);
    if (!isEmpty() && file.open(QIODevice::WriteOnly)) {
        if ((count <= 0) || (count > this->count))
            count = this->count;
        qint64 result;
        if (isSequential())
            result = file.write((char*) &buffer[this->count - count], count * sizeof(T));
        else {
            qint32 savestartpos = bufferpos - count;
            if (savestartpos >= 0)
                result = file.write((char*) &buffer[savestartpos], count * sizeof(T));
            else {
                result = file.write((char*) &buffer[this->count + savestartpos], qAbs(savestartpos) * sizeof(T));
                if (result != -1)
                    result = file.write((char*) buffer, bufferpos * sizeof(T));
            }
        }
        return (result != -1);
    }
    else
        return false;
}

template <typename T>
bool CircularQueue<T>::loadfromfile(const QString & name) {
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
            pushedcount = count;
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
T * CircularQueue<T>::getBackSlice(qint32 count) {
    if (!isEmpty()) {
        if ((count <= 0) || (count > this->count))
            count = this->count;
        T * result = new T[count];
        if (isSequential())
            memcpy(result, &buffer[this->count - count], count * sizeof(T));
        else {
            qint32 slicestartpos = bufferpos - count;
            if (slicestartpos >= 0)
                memcpy(result, &buffer[slicestartpos], count * sizeof(T));
            else {
                memcpy(result, &buffer[this->count + slicestartpos], qAbs(slicestartpos) * sizeof(T));
                memcpy(&result[qAbs(slicestartpos)], buffer, bufferpos * sizeof(T));
            }
        }
        return result;
    }
    else
        return NULL;
}

template <typename T>
void CircularQueue<T>::getBackSliceTo(T *destinationptr, qint32 count) {
    if (count!=0 && !isEmpty()) {
        if (count > this->count)
            count = this->count;
        if (isSequential())
            memcpy(destinationptr, &buffer[this->count - count], count * sizeof(T));
        else {
            qint32 slicestartpos = bufferpos - count;
            if (slicestartpos >= 0)
                memcpy(destinationptr, &buffer[slicestartpos], count * sizeof(T));
            else {
                memcpy(destinationptr, &buffer[this->count + slicestartpos], qAbs(slicestartpos) * sizeof(T));
                memcpy(&destinationptr[qAbs(slicestartpos)], buffer, bufferpos * sizeof(T));
            }
        }
    }
}

template <typename T>
T * CircularQueue<T>::getSlice(qint32 index, qint32 count) {
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

template <typename T>
quint64 CircularQueue<T>::pushedCount() const {
    return pushedcount;
}

template <typename T>
void CircularQueue<T>::setCapacity(qint32 value, bool clear) {
    if ((value > 0) && (capacity != value)) {
        T * tmpbuffer = new T[value];
        if (clear)
            this->clear();
        else {
            if (value < capacity) {
                count = value;
                if (bufferpos >= count)
                    bufferpos = 0;
            }
            memcpy(tmpbuffer, buffer, count * sizeof(T));
        }
        if (buffer) delete [] buffer;
        buffer = tmpbuffer;
        capacity = value;
    }
}

#endif // CIRCULARQUEUE_H
