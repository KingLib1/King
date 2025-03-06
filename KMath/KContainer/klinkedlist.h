#ifndef KLINKEDLIST_H
#define KLINKEDLIST_H

#include "King_global.h"

template <typename T>
struct KING_EXPORT KLinkedListNode
{
    KLinkedListNode() : pre_(0), next_(0x0) {}
    KLinkedListNode(const T &data) : data_(data), next_(0x0) {}
    KLinkedListNode(const T &data, KLinkedListNode *pre) :
        data_(data), pre_(pre), next_(0) {}
    KLinkedListNode(const T &data, KLinkedListNode *pre, KLinkedListNode *next)
        : data_(data), pre_(pre), next_(next) {}


    T data_;
    KLinkedListNode *pre_;
    KLinkedListNode *next_;
};

template <typename T>
class KING_EXPORT KLinkedList
{
    typedef KLinkedListNode<T> Node;

public:
    class iterator
    {
    public:
        inline iterator() : i(0) {}
        inline iterator(Node *n) : i(n) {}
        inline iterator(const iterator &other) : i(other.i) {}
        inline iterator &operator=(const iterator &other);
        inline T &operator*() const;
        inline T *operator->() const;
        inline bool operator==(const iterator &o) const;
        inline bool operator!=(const iterator &o) const;
        inline iterator &operator++();
        inline iterator operator++(int);
        inline iterator &operator--();
        inline iterator operator--(int);
        iterator operator+(int j) const;
        inline iterator operator-(int j) const;
        iterator &operator+=(int j);
        inline iterator &operator-=(int j);

//    private:
        Node *i;
    };
    //    friend class iterator;

    KLinkedList();
    KLinkedList(const KLinkedList<T> &other);
    ~KLinkedList();
    inline void append(const T &value);
    inline T &last() const;
    void clear();
    bool contains(const T &value) const;
    int count(const T &value) const;
    inline iterator begin() const {return head_->next_;}
    inline iterator end() const {return tail_->next_;}
    inline T &first() const;
    inline bool isEmpty() const;
    void prepend(const T &value);
    int removeAll(const T &value);
    void removeFirst();
    void removeLast();
    bool removeOne(const T &value);
    iterator erase(iterator &pos);
    inline int size() const;
    void swap(KLinkedList<T> &other);
    T takeFirst();
    T takeLast();
    bool operator==(const KLinkedList<T> &other) const;
    inline bool operator!=(const KLinkedList<T> &other) const;
    KLinkedList<T> operator+(const KLinkedList<T> &other) const;
    KLinkedList<T> &operator+=(const KLinkedList<T> &other);
    inline KLinkedList<T> &operator+=(const T &value);
    inline KLinkedList<T> &operator<<(const T &value);
    inline KLinkedList<T> &operator<<(const KLinkedList<T> &other);
    KLinkedList<T> &operator=(const KLinkedList<T> &other);

private:
    int size_ = 0;
    KLinkedListNode<T> *head_ = 0;
    KLinkedListNode<T> *tail_ = 0;
};

template<typename T>
KLinkedList<T>::KLinkedList()
{
    head_ = new KLinkedListNode<T>;
    tail_ = head_;
}

template<typename T>
KLinkedList<T>::KLinkedList(const KLinkedList<T> &other)
{
    head_ = new KLinkedListNode<T>;
    tail_ = head_;
    size_ = other.size_;
    Node *p = other.head_->next_;
    while (p) {
        Node *node = new Node(p->data_, tail_);
        tail_->next_ = node;
        tail_ = node;
        p = p->next_;
    }
}

template<typename T>
KLinkedList<T>::~KLinkedList()
{
    clear();
    delete head_;
}

template<typename T>
inline void KLinkedList<T>::append(const T &value)
{
    Node *node = new Node(value, tail_);
    tail_->next_ = node;
    tail_ = node;
    ++size_;
}

template<typename T>
inline T &KLinkedList<T>::last() const
{
//    assert(size_ != 0);
    return tail_->data_;
}

template<typename T>
void KLinkedList<T>::clear()
{
    tail_ = head_;
    size_ = 0;
    KLinkedListNode<T> *node = head_->next_;
    head_->next_ = 0;
    KLinkedListNode<T> *next;
    while (node) {
        next = node->next_;
        delete node;
        node = next;
    }
}

template<typename T>
bool KLinkedList<T>::contains(const T &value) const
{
    Node *p = head_->next_;
    while (p) {
        if (p->data_ == value)
            return true;
        p = p->next_;
    }
    return false;
}

template<typename T>
int KLinkedList<T>::count(const T &value) const
{
    KLinkedListNode<T> *p = head_->next_;
    int count = 0;
    while (p) {
        if (p->data_ == value)
            ++count;
        p = p->next_;
    }
    return count;
}

template<typename T>
inline T &KLinkedList<T>::first() const
{
//    assert(size_ != 0);
    return head_->next_->data_;
}

template<typename T>
inline bool KLinkedList<T>::isEmpty() const
{
    return size_ == 0;
}

template<typename T>
void KLinkedList<T>::prepend(const T &value)
{
    Node *node = new Node(value, head_, head_->next_);
    if (size_ > 0)
        head_->next_->pre_ = node;
    else
        tail_ = node;
    head_->next_ = node;
    ++size_;
}

template<typename T>
int KLinkedList<T>::removeAll(const T &value)
{
    Node *p = head_->next_;
    Node *q;
    int count = 0;
    while (p) {
        if (p->data_ == value) {
            p->pre_->next_ = p->next_;
            if (p == tail_)
                tail_ = p->pre_;
            else
                p->next_->pre_ = p->pre_;
            q = p;
            p = p->next_;
            delete q;
            --size_;
            ++count;
        } else {
            p = p->next_;
        }
    }
    return count;
}

template<typename T>
void KLinkedList<T>::removeFirst()
{
    if (size_ == 0)
        return;
    Node *p = head_->next_;
    head_->next_ = p->next_;
    if (p->next_)
        p->next_->pre_ = head_;
    else
        tail_ = head_;
    delete p;
    --size_;
}

template<typename T>
void KLinkedList<T>::removeLast()
{
    if (size_ == 0)
        return;
    Node *pre = tail_->pre_;
    pre->next_ = 0;
    delete tail_;
    tail_ = pre;
    --size_;
}

template<typename T>
bool KLinkedList<T>::removeOne(const T &value)
{
    KLinkedListNode<T> *p = head_->next_;
    while (p) {
        if (p->data_ == value) {
            p->pre_->next_ = p->next_;
            if (p == tail_)
                tail_ = p->pre_;
            else
                p->next_->pre_ = p->pre_;
            delete p;
            --size_;
            return true;
        } else {
            p = p->next_;
        }
    }
    return false;
}

template<typename T>
typename KLinkedList<T>::iterator KLinkedList<T>::erase(iterator &pos)
{
    Node *p = pos.i;
    Node *q;
    if (p) {
        p->pre_->next_ = p->next_;
        if (p->next_)
            p->next_->pre_ = p->pre_;
        else
            tail_ = p->pre_;
        q = p->next_;
        delete p;
        --size_;
        return q;
    } else {
        return pos;
    }
}

template<typename T>
inline int KLinkedList<T>::size() const
{
    return size_;
}

template<typename T>
void KLinkedList<T>::swap(KLinkedList<T> &other)
{
    int temp_size = size_;
    KLinkedListNode<T> *temp_head = head_;
    KLinkedListNode<T> *temp_tail = tail_;
    size_ = other.size_;
    head_ = other.head_;
    tail_ = other.tail_;
    other.size_ = temp_size;
    other.head_ = temp_head;
    other.tail_ = temp_tail;
}

template<typename T>
T KLinkedList<T>::takeFirst()
{
//    assert(size_ != 0);
    T t = head_->next_->data_;
    removeFirst();
    return t;
}

template<typename T>
T KLinkedList<T>::takeLast()
{
//    assert(size_ != 0);
    T t = tail_->data_;
    removeLast();
}

template<typename T>
bool KLinkedList<T>::operator==(const KLinkedList<T> &other) const
{
    if (size_ != other.size_)
        return false;
    if (head_ == other.head_)
        return true;
    KLinkedListNode<T> *p1 = head_->next_;
    KLinkedListNode<T> *p2 = other.head_->next_;
    while (p1) {
        if (p1->data_ != p2->data_)
            return false;
        p1 = p1->next_;
        p2 = p2->next_;
    }
    return true;
}

template<typename T>
inline bool KLinkedList<T>::operator!=(const KLinkedList<T> &other) const
{
    return !(*this == other);
}

template<typename T>
KLinkedList<T> KLinkedList<T>::operator+(const KLinkedList<T> &other) const
{
    KLinkedList<T> list(*this);
    list += other;
    return list;
}

template<typename T>
KLinkedList<T> &KLinkedList<T>::operator+=(const KLinkedList<T> &other)
{
    size_ += other.size_;
    KLinkedListNode<T> *p = other.head_->next_;
    while (p) {
        Node *node = new Node(p->data_, tail_);
        tail_->next_ = node;
        tail_ = node;
        p = p->next_;
    }
    return *this;
}

template<typename T>
inline KLinkedList<T> &KLinkedList<T>::operator+=(const T &value)
{
    append(value);
    return *this;
}

template<typename T>
inline KLinkedList<T> &KLinkedList<T>::operator<<(const T &value)
{
    append(value);
    return *this;
}

template<typename T>
inline KLinkedList<T> &KLinkedList<T>::operator<<(const KLinkedList<T> &other)
{
    return *this += other;
}

template<typename T>
KLinkedList<T> &KLinkedList<T>::operator=(const KLinkedList<T> &other)
{
    int min_size = size_ <= other.size_ ? size_ : other.size_;
    KLinkedListNode<T> *p1 = head_;
    KLinkedListNode<T> *p2 = other.head_;
    for (int i = 0; i < min_size; ++i) {
        p1 = p1->next_;
        p2 = p2->next_;
        p1->data_ = p2->data_;
    }

    if (size_ <= other.size_) {
        p2 = p2->next_;
        while (p2) {
            Node *node = new Node(p2->data_, tail_);
            tail_->next_ = node;
            tail_ = node;
            p2 = p2->next_;
        }
    } else {
        tail_ = p1;
        p1 = p1->next_;
        tail_->next_ = 0;
        Node *next;
        while (p1) {
            next = p1->next_;
            delete p1;
            p1 = next;
        }
    }
    size_ = other.size_;
    return *this;
}

template<typename T>
inline typename KLinkedList<T>::iterator &KLinkedList<T>::iterator::operator=(
        const KLinkedList::iterator &other)
{
    i = other.i;
    return *this;
}

template<typename T>
inline T &KLinkedList<T>::iterator::operator*() const
{
    return i->data_;
}

template<typename T>
inline T *KLinkedList<T>::iterator::operator->() const
{
    return &i->data_;
}

template<typename T>
inline bool KLinkedList<T>::iterator::operator==(const KLinkedList::iterator &o) const
{
    return i == o.i;
}

template<typename T>
inline bool KLinkedList<T>::iterator::operator!=(const KLinkedList::iterator &o) const
{
    return i != o.i;
}

template<typename T>
inline typename KLinkedList<T>::iterator &KLinkedList<T>::iterator::operator++()
{
    i = i->next_;
    return *this;
}

template<typename T>
inline typename KLinkedList<T>::iterator KLinkedList<T>::iterator::operator++(int)
{
    Node *p = i;
    i = i->next_;
    return p;
}

template<typename T>
inline typename KLinkedList<T>::iterator &KLinkedList<T>::iterator::operator--()
{
    i = i->pre_;
    return *this;
}

template<typename T>
inline typename KLinkedList<T>::iterator KLinkedList<T>::iterator::operator--(int)
{
    Node *p = i;
    i = i->pre_;
    return p;
}

template<typename T>
typename KLinkedList<T>::iterator KLinkedList<T>::iterator::operator+(int j) const
{
    Node *p = i;
    if (j > 0)
        while (j--)
            p = p->next_;
    else
        while (j++)
            p = p->pre_;
    return p;
}

template<typename T>
inline typename KLinkedList<T>::iterator KLinkedList<T>::iterator::operator-(int j) const
{
    return operator+(-j);
}

template<typename T>
typename KLinkedList<T>::iterator &KLinkedList<T>::iterator::operator+=(int j)
{
    if (j > 0)
        while (j--)
            i = i->next_;
    else
        while(j++)
            i = i->pre_;
    return i;
}

template<typename T>
inline typename KLinkedList<T>::iterator &KLinkedList<T>::iterator::operator-=(int j)
{
    return operator+=(-j);
}

#endif // KLINKEDLIST_H
