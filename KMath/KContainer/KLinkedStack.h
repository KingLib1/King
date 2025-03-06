#ifndef KLINKEDSTACK_H
#define KLINKEDSTACK_H

#include "klinkedlist.h"

template<typename T>
class KING_EXPORT KLinkedStack
{
public:
    KLinkedStack();
    KLinkedStack(const KLinkedStack<T> &other);
    ~KLinkedStack();
    inline T pop();
    inline void push(const T &value);
    inline void swap(KLinkedStack<T> &other);
    inline T &top() const;
    inline bool isEmpty() const {return stack_.isEmpty();}
    inline int size() const {return stack_.size();}
    inline void clear() {stack_.clear();}
    inline KLinkedStack<T> &operator=(const KLinkedStack<T> &other);

private:
    KLinkedList<T> stack_;
};

template<typename T>
KLinkedStack<T>::KLinkedStack()
{

}

template<typename T>
KLinkedStack<T>::KLinkedStack(const KLinkedStack<T> &other)
{
    stack_ = other.stack_;
}

template<typename T>
KLinkedStack<T>::~KLinkedStack()
{

}

template<typename T>
inline T KLinkedStack<T>::pop()
{
    return stack_.takeFirst();
}

template<typename T>
inline void KLinkedStack<T>::push(const T &value)
{
    stack_.prepend(value);
}

template<typename T>
inline void KLinkedStack<T>::swap(KLinkedStack<T> &other)
{
    stack_.swap(other.stack_);
}

template<typename T>
inline T &KLinkedStack<T>::top() const
{
    return stack_.first();
}

template<typename T>
inline KLinkedStack<T> &KLinkedStack<T>::operator=(const KLinkedStack<T> &other)
{
    stack_ = other.stack_;
    return *this;
}

#endif // KLINKEDSTACK_H
