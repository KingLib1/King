#ifndef KQUEUE_H
#define KQUEUE_H

#include <QList>

#include "King_global.h"

template<typename T>
class KING_EXPORT KQueue
{
public:
    KQueue();

    inline void enqueue(const T &value);
    inline T dequeue();
    inline T &head();
    inline const T &head() const;
    inline bool isEmpty() const;
    inline void swap(KQueue<T> &other);

private:
    QList<T> queue_;
};

template<typename T>
KQueue<T>::KQueue()
{

}

template<typename T>
inline void KQueue<T>::enqueue(const T &value)
{
    queue_.append(value);
}

template<typename T>
inline T KQueue<T>::dequeue()
{
    return queue_.takeFirst();
}

template<typename T>
inline T &KQueue<T>::head()
{
    return queue_.first();
}

template<typename T>
inline const T &KQueue<T>::head() const
{
    return queue_.first();
}

template<typename T>
inline bool KQueue<T>::isEmpty() const
{
    return queue_.isEmpty();
}

template<typename T>
inline void KQueue<T>::swap(KQueue<T> &other)
{
    queue_.swap(other);
}

#endif // KQUEUE_H
