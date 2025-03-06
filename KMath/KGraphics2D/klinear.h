#ifndef KLINEAR_H
#define KLINEAR_H

#include "kpointf.h"

// y = kx + b
class KING_EXPORT KLinear
{
public:
    KLinear();
    KLinear(double k, double b);
    KLinear(const KPointF &p1, const KPointF &p2);
    KLinear(const KPointF &p, double k);
    KLinear(double x, double y, double k);
    KLinear(const KLinear &other);
    ~KLinear();

    inline void setK(double k);
    inline void setB(double b);

    inline double k() const;
    inline double b() const;
    inline double y(double x) const;
    inline double x(double y) const;
    inline double distance(const KPointF &point) const;
    inline double distanceSquare(const KPointF &point) const;
    inline KPointF intersection(const KLinear &other) const;

private:
    double k_;
    double b_;
};

inline void KLinear::setK(double k)
{
    k_ = k;
}

inline void KLinear::setB(double b)
{
    b_ = b;
}

inline double KLinear::k() const
{
    return k_;
}

inline double KLinear::b() const
{
    return b_;
}

inline double KLinear::y(double x) const
{
    return k_ * x + b_;
}

inline double KLinear::x(double y) const
{
    return (y - b_) / k_;
}

inline double KLinear::distance(const KPointF &point) const
{
    return kSqrt(distanceSquare(point));
}

inline double KLinear::distanceSquare(const KPointF &point) const
{
    return kSquare(k_ * point.x() - point.y() + b_) / (k_ * k_ + 1);
}

inline KPointF KLinear::intersection(const KLinear &other) const
{
    if (isEqual(k_, other.k_))
        return KPointF();
    double x = (other.b_ - b_) / (k_ - other.k_);
    return KPointF(x, y(x));
}

#endif // KLINEAR_H
