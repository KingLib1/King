#ifndef KSTACK_H
#define KSTACK_H

#include "KVector.h"

template<typename T>
class KING_EXPORT KStack
{
public:
    KStack();

    inline void push(const T &value);
    inline T pop();
    inline const T &top() const;
    inline T &top();
    inline void swap(KStack<T> &other);
    inline bool isEmpty() const;

private:
    KVector<T> stack_;
};

template<typename T>
KStack<T>::KStack()
{

}

template<typename T>
inline void KStack<T>::push(const T &value)
{
    stack_.append(value);
}

template<typename T>
inline T KStack<T>::pop()
{
    return stack_.takeLast();
}

template<typename T>
inline const T &KStack<T>::top() const
{
    return stack_.last();
}

template<typename T>
inline T &KStack<T>::top()
{
    return stack_.last();
}

template<typename T>
inline void KStack<T>::swap(KStack<T> &other)
{
    stack_.swap(other.stack_);
}

template<typename T>
inline bool KStack<T>::isEmpty() const
{
    return stack_.isEmpty();
}

#endif // KSTACK_H
