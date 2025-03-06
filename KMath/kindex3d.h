#ifndef KINDEX3D_H
#define KINDEX3D_H

#include "King_global.h"

class KING_EXPORT KIndex3D
{
public:
    KIndex3D();
    KIndex3D(int i, int j, int k);
    KIndex3D(const KIndex3D &index);
    ~KIndex3D();

    inline void setI(int i);
    inline void setJ(int j);
    inline void setK(int k);
    inline void setIJK(int i, int j, int k);

    inline int i() const;
    inline int j() const;
    inline int k() const;
    inline int lengthSquared() const;

    inline KIndex3D &operator=(const KIndex3D &index);
    inline KIndex3D &operator+=(const KIndex3D &index);
    inline KIndex3D &operator+=(int n);
    inline KIndex3D &operator-=(const KIndex3D &index);
    inline KIndex3D &operator-=(int n);
    inline KIndex3D &operator*=(const KIndex3D &index);
    inline KIndex3D &operator*=(int n);
    inline KIndex3D &operator/=(int divisor);
    inline KIndex3D operator+(const KIndex3D &index) const;
    inline KIndex3D operator+(int n) const;
    inline KIndex3D operator-(const KIndex3D &index) const;
    inline KIndex3D operator-(int n) const;
    inline KIndex3D operator*(const KIndex3D &index) const;
    inline KIndex3D operator*(int n) const;
    inline bool operator==(const KIndex3D &index) const;
    inline bool operator!=(const KIndex3D &index) const;

private:
    int i_;
    int j_;
    int k_;
};

inline void KIndex3D::setI(int i)
{
    i_ = i;
}

inline void KIndex3D::setJ(int j)
{
    j_ = j;
}

inline void KIndex3D::setK(int k)
{
    k_ = k;
}

inline void KIndex3D::setIJK(int i, int j, int k)
{
    i_ = i;
    j_ = j;
    k_ = k;
}

inline int KIndex3D::i() const
{
    return i_;
}

inline int KIndex3D::j() const
{
    return j_;
}

inline int KIndex3D::k() const
{
    return k_;
}

inline int KIndex3D::lengthSquared() const
{
    return i_ * i_ + j_ * j_ + k_ * k_;
}

inline KIndex3D &KIndex3D::operator=(const KIndex3D &index)
{
    i_ = index.i_;
    j_ = index.j_;
    k_ = index.k_;
    return *this;
}

inline KIndex3D &KIndex3D::operator+=(const KIndex3D &index)
{
    i_ += index.i_;
    j_ += index.j_;
    k_ += index.k_;
    return *this;
}

inline KIndex3D &KIndex3D::operator+=(int n)
{
    i_ += n;
    j_ += n;
    k_ += n;
    return *this;
}

inline KIndex3D &KIndex3D::operator-=(const KIndex3D &index)
{
    i_ -= index.i_;
    j_ -= index.j_;
    k_ -= index.k_;
    return *this;
}

inline KIndex3D &KIndex3D::operator-=(int n)
{
    i_ -= n;
    j_ -= n;
    k_ -= n;
    return *this;
}

inline KIndex3D &KIndex3D::operator*=(const KIndex3D &index)
{
    i_ *= index.i_;
    j_ *= index.j_;
    k_ *= index.k_;
    return *this;
}

inline KIndex3D &KIndex3D::operator*=(int n)
{
    i_ *= n;
    j_ *= n;
    k_ *= n;
    return *this;
}

inline KIndex3D &KIndex3D::operator/=(int divisor)
{
    i_ /= divisor;
    j_ /= divisor;
    k_ /= divisor;
    return *this;
}

inline KIndex3D KIndex3D::operator+(const KIndex3D &index) const
{
    return KIndex3D(i_ + index.i_, j_ + index.j_, k_ + index.k_);
}

inline KIndex3D KIndex3D::operator+(int n) const
{
    return KIndex3D(i_ + n, j_ + n, k_ + n);
}

inline KIndex3D KIndex3D::operator-(const KIndex3D &index) const
{
    return KIndex3D(i_ - index.i_, j_ - index.j_, k_ - index.k_);
}

inline KIndex3D KIndex3D::operator-(int n) const
{
    return KIndex3D(i_ - n, j_ - n, k_ - n);
}

inline KIndex3D KIndex3D::operator*(const KIndex3D &index) const
{
    return KIndex3D(i_ * index.i_, j_ * index.j_, k_ * index.k_);
}

inline KIndex3D KIndex3D::operator*(int n) const
{
    return KIndex3D(i_ * n, j_ * n, k_ * n);
}

inline bool KIndex3D::operator==(const KIndex3D &index) const
{
    return i_ == index.i_ && j_ == index.j_ && k_ == index.k_;
}

inline bool KIndex3D::operator!=(const KIndex3D &index) const
{
    return i_ != index.i_ || j_ != index.j_ || k_ != index.k_;
}

#endif // KINDEX3D_H
