#ifndef KINDEX2D_H
#define KINDEX2D_H

#include "King_global.h"

class KING_EXPORT KIndex2D
{
public:
    KIndex2D();
    KIndex2D(int i, int j);
    KIndex2D(const KIndex2D &index);
    ~KIndex2D();

    inline void setI(int i);
    inline void setJ(int j);
    inline void transpose();

    inline int i() const;
    inline int j() const;

    inline KIndex2D &operator=(const KIndex2D &index);

private:
    int i_;
    int j_;
};

inline void KIndex2D::setI(int i)
{
    i_ = i;
}

inline void KIndex2D::setJ(int j)
{
    j_ = j;
}

inline void KIndex2D::transpose()
{
    int temp = i_;
    i_ = j_;
    j_ = temp;
}

inline int KIndex2D::i() const
{
    return i_;
}

inline int KIndex2D::j() const
{
    return j_;
}

inline KIndex2D &KIndex2D::operator=(const KIndex2D &index)
{
    i_ = index.i_;
    j_ = index.j_;
    return *this;
}

#endif // KINDEX2D_H
