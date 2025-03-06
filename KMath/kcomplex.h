#ifndef KCOMPLEX_H
#define KCOMPLEX_H

#include "kmath.h"
// 复数 z = a + bi 
class KING_EXPORT KComplex
{
public:
    KComplex();
    KComplex(double a, double b);
    KComplex(const KComplex &complex);
    ~KComplex();
    
    inline void setA(double a) {a_ = a;}
    inline void setB(double b) {b_ = b;}
    
    inline double a() const {return a_;}
    inline double b() const {return b_;}
    inline double length() const;
    inline double lengthSquared() const;
    /**
     * @brief 复数的平方
     */
    inline KComplex squared() const;
    /**
     * @brief 共轭复数
     */
    inline KComplex conjugated() const;
    
    inline KComplex &operator+=(const KComplex &other);
    inline KComplex &operator-=(const KComplex &other);
    inline KComplex &operator*=(const KComplex &other);
    inline KComplex &operator*=(double factor);
    inline KComplex &operator/=(const KComplex &other);
    inline KComplex &operator/=(double divisor);
    inline KComplex &operator=(const KComplex &other);
    
    inline KComplex operator+(const KComplex &other) const;
    inline KComplex operator-(const KComplex &other) const;
    inline KComplex operator*(const KComplex &other) const;
    inline KComplex operator*(double factor) const;
    inline KComplex operator/(const KComplex &other) const;
    inline KComplex operator/(double divisor) const;
    
private:
    double a_; // 实部
    double b_; // 虚部
};

inline double KComplex::length() const
{
    return kSqrt(a_ * a_ + b_ * b_);
}

inline double KComplex::lengthSquared() const
{
    return a_ * a_ + b_ * b_;
}

inline KComplex KComplex::squared() const
{
    return KComplex(a_ * a_ - b_ * b_, a_ * b_ * 2);
}

inline KComplex KComplex::conjugated() const
{
    return KComplex(a_, -b_);
}

inline KComplex &KComplex::operator+=(const KComplex &other)
{
    a_ += other.a_;
    b_ += other.b_;
    return *this;
}

inline KComplex &KComplex::operator-=(const KComplex &other)
{
    a_ -= other.a_;
    b_ -= other.b_;
    return *this;
}

inline KComplex &KComplex::operator*=(const KComplex &other)
{
    double ta = a_ * other.a_ - b_ * other.b_;
    b_ = a_ * other.b_ + other.a_ * b_;
    a_ = ta;
    return *this;
}

inline KComplex &KComplex::operator*=(double factor)
{
    a_ *= factor;
    b_ *= factor;
    return *this;
}

inline KComplex &KComplex::operator/=(const KComplex &other)
{
    double ol2 = other.lengthSquared();
    double ta = (a_ * other.a_ + b_ * other.b_) / ol2;
    b_ = (other.a_ * b_ - a_ * other.b_) / ol2;
    a_ = ta;
    return *this;
}

inline KComplex &KComplex::operator/=(double divisor)
{
    a_ /= divisor;
    b_ /= divisor;
    return *this;
}

inline KComplex &KComplex::operator=(const KComplex &other)
{
    a_ = other.a_;
    b_ = other.b_;
    return *this;
}

inline KComplex KComplex::operator+(const KComplex &other) const
{
    return KComplex(a_ + other.a_, b_ + other.b_);
}

inline KComplex KComplex::operator-(const KComplex &other) const
{
    return KComplex(a_ - other.a_, b_ - other.b_);
}

inline KComplex KComplex::operator*(const KComplex &other) const
{
    return KComplex(a_ * other.a_ - b_ * other.b_, 
                    a_ * other.b_ + other.a_ * b_);
}

inline KComplex KComplex::operator*(double factor) const
{
    return KComplex(factor * a_, factor * b_);
}

inline KComplex KComplex::operator/(const KComplex &other) const
{
    double ol2 = other.lengthSquared();
    return KComplex((a_ * other.a_ + b_ * other.b_) / ol2,
                    (other.a_ * b_ - a_ * other.b_) / ol2);
}

inline KComplex KComplex::operator/(double divisor) const
{
    return KComplex(a_ / divisor, b_ / divisor);
}

inline KComplex operator-(const KComplex &complex)
{
    return KComplex(-complex.a(), -complex.b());
}

inline KComplex operator*(double factor, const KComplex &complex)
{
    return KComplex(factor * complex.a(), factor * complex.b());
}

#endif // KCOMPLEX_H
