#ifndef KOCTREE_H
#define KOCTREE_H

#include "King_global.h"

template<typename T>
class KING_EXPORT KOctreeNode
{
public:
    KOctreeNode();
    KOctreeNode(const T &data);
    ~KOctreeNode();

    void newAll();
    void newFirst();
    void newSecond();
    void newThird();
    void newfourth();
    void newFifth();
    void newSixth();
    void newSeventh();
    void newEighth();

    T data_;
    KOctreeNode<T> *first = nullptr;
    KOctreeNode<T> *second = nullptr;
    KOctreeNode<T> *third = nullptr;
    KOctreeNode<T> *fourth = nullptr;
    KOctreeNode<T> *fifth = nullptr;
    KOctreeNode<T> *sixth = nullptr;
    KOctreeNode<T> *seventh = nullptr;
    KOctreeNode<T> *eighth = nullptr;
};

template<typename T>
KOctreeNode<T>::KOctreeNode()
{

}

template<typename T>
KOctreeNode<T>::KOctreeNode(const T &data) : data_(data)
{

}

template<typename T>
KOctreeNode<T>::~KOctreeNode()
{
    if (first) delete first;
    if (second) delete second;
    if (third) delete third;
    if (fourth) delete fourth;
    if (fifth) delete fifth;
    if (sixth) delete sixth;
    if (seventh) delete seventh;
    if (eighth) delete eighth;
}

template<typename T>
void KOctreeNode<T>::newAll()
{
    newFirst();
    newSecond();
    newThird();
    newfourth();
    newFifth();
    newSixth();
    newSeventh();
    newEighth();
}

template<typename T>
void KOctreeNode<T>::newFirst()
{
    first = new KOctreeNode<T>;
}

template<typename T>
void KOctreeNode<T>::newSecond()
{
    second = new KOctreeNode<T>;
}

template<typename T>
void KOctreeNode<T>::newThird()
{
    third = new KOctreeNode<T>;
}

template<typename T>
void KOctreeNode<T>::newfourth()
{
    fourth = new KOctreeNode<T>;
}

template<typename T>
void KOctreeNode<T>::newFifth()
{
    fifth = new KOctreeNode<T>;
}

template<typename T>
void KOctreeNode<T>::newSixth()
{
    sixth = new KOctreeNode<T>;
}

template<typename T>
void KOctreeNode<T>::newSeventh()
{
    seventh = new KOctreeNode<T>;
}

template<typename T>
void KOctreeNode<T>::newEighth()
{
    eighth = new KOctreeNode<T>;
}

template<typename T>
class KOctree
{
public:
    KOctree();
    ~KOctree();

    void initTree(const T data);

    KOctreeNode<T> *root() { return root_; }

private:
    KOctreeNode<T> *root_ = nullptr;
};

template<typename T>
KOctree<T>::KOctree()
{

}

template<typename T>
KOctree<T>::~KOctree()
{
    if (root_)
        delete root_;
}

template<typename T>
void KOctree<T>::initTree(const T data)
{
    root_ = new KOctreeNode<T>(data);
}

#endif // KOCTREE_H
