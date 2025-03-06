#ifndef KLINKEDQUEUE_H
#define KLINKEDQUEUE_H

#include "klinkedlist.h"

template<typename T>
class KING_EXPORT KLinkedQueue
{
public:
    KLinkedQueue();
    KLinkedQueue(const KLinkedQueue<T> &other);
    ~KLinkedQueue();
    inline T dequeue();
    inline void enqueue(const T &value);
    inline T &head() const;
    inline T &last() const;
    inline void swap(KLinkedQueue<T> &other);
    inline bool isEmpty() const {return queue_.isEmpty();}
    inline int size() const {return queue_.size();}
    inline void clear() {queue_.clear();}

    inline KLinkedQueue<T> &operator=(const KLinkedQueue<T> &other);

private:
    KLinkedList<T> queue_;
};

template<typename T>
KLinkedQueue<T>::KLinkedQueue()
{

}

template<typename T>
KLinkedQueue<T>::KLinkedQueue(const KLinkedQueue<T> &other)
{
    queue_ = other.queue_;
}

template<typename T>
KLinkedQueue<T>::~KLinkedQueue()
{

}

template<typename T>
inline T KLinkedQueue<T>::dequeue()
{
    return queue_.takeFirst();
}

template<typename T>
inline void KLinkedQueue<T>::enqueue(const T &value)
{
    queue_.append(value);
}

template<typename T>
inline T &KLinkedQueue<T>::head() const
{
    return queue_.first();
}

template<typename T>
T &KLinkedQueue<T>::last() const
{
    return queue_.last();
}

template<typename T>
inline void KLinkedQueue<T>::swap(KLinkedQueue<T> &other)
{
    queue_.swap(other.queue_);
}

template<typename T>
inline KLinkedQueue<T> &KLinkedQueue<T>::operator=(const KLinkedQueue<T> &other)
{
    queue_ = other.queue_;
    return *this;
}

#endif // KLINKEDQUEUE_H
