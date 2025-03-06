#ifndef KTRIANGLE_H
#define KTRIANGLE_H

#include "kmath.h"

class KING_EXPORT KTriangle
{
public:
    KTriangle();
    KTriangle(double a, double b, double c);
    KTriangle(const KTriangle &tri);
    ~KTriangle();

    inline void setA(double a);
    inline void setB(double b);
    inline void setC(double c);
    inline void setABC(double a, double b, double c);

    inline double cosA() const;
    inline double cosB() const;
    inline double cosC() const;
    inline double sinA() const;
    inline double sinB() const;
    inline double sinC() const;
    inline double angleA() const;
    inline double angleB() const;
    inline double angleC() const;
    inline double radianA() const;
    inline double radianB() const;
    inline double radianC() const;
    inline double a() const {return a_;}
    inline double b() const {return b_;}
    inline double c() const {return c_;}
    inline bool isValid() const;
    inline double area() const;
    inline double perimeter() const;
    /**
     * @brief 以a为底边所对应的高
     */
    inline double aHeight() const;
    /**
     * @brief 以b为底边所对应的高
     */
    inline double bHeight() const;
    /**
     * @brief 以c为底边所对应的高
     */
    inline double cHeight() const;

    inline KTriangle &operator=(const KTriangle &t);

private:
    double a_;
    double b_;
    double c_;
};

inline void KTriangle::setA(double a)
{
    a_ = a;
}

inline void KTriangle::setB(double b)
{
    b_ = b;
}

inline void KTriangle::setC(double c)
{
    c_ = c;
}

inline void KTriangle::setABC(double a, double b, double c)
{
    a_ = a;
    b_ = b;
    c_ = c;
}

inline double KTriangle::cosA() const
{
    return (b_*b_ + c_*c_ - a_*a_) / (2*b_*c_);
}

inline double KTriangle::cosB() const
{
    return (a_*a_ + c_*c_ - b_*b_) / (2*a_*c_);
}

inline double KTriangle::cosC() const
{
    return (a_*a_ + b_*b_ - c_*c_) / (2*a_*b_);
}

inline double KTriangle::sinA() const
{
    return kSqrt(1 - kSquare(cosA()));
}

inline double KTriangle::sinB() const
{
    return kSqrt(1 - kSquare(cosB()));
}

inline double KTriangle::sinC() const
{
    return kSqrt(1 - kSquare(cosC()));
}

inline double KTriangle::angleA() const
{
    return kRadiansToDegrees(radianA());
}

inline double KTriangle::angleB() const
{
    return kRadiansToDegrees(radianB());
}

inline double KTriangle::angleC() const
{
    return kRadiansToDegrees(radianC());
}

inline double KTriangle::radianA() const
{
    return kAcos(cosA());
}

inline double KTriangle::radianB() const
{
    return kAcos(cosB());
}

inline double KTriangle::radianC() const
{
    return kAcos(cosC());
}

inline bool KTriangle::isValid() const
{
    return a_ + b_ > c_ && a_ + c_ > b_ && b_ + c_ > a_;
}

inline double KTriangle::area() const
{
    double p = (a_ + b_ + c_) / 2;
    return kSqrt(p * (p - a_) * (p - b_) * (p - c_));
}

inline double KTriangle::perimeter() const
{
    return a_ + b_ + c_;
}

inline double KTriangle::aHeight() const
{
    return area() / a_;
}

inline double KTriangle::bHeight() const
{
    return area() / b_;
}

inline double KTriangle::cHeight() const
{
    return area() / c_;
}

inline KTriangle &KTriangle::operator=(const KTriangle &t)
{
    a_ = t.a_;
    b_ = t.b_;
    c_ = t.c_;
    return *this;
}

#endif // TRIANGLE_H
