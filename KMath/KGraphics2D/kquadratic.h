#ifndef KQUADRATIC_H
#define KQUADRATIC_H

#include "kmath.h"
#include "klinear.h"
#include "KPair.h"

// y = ax^2 + bx + c
class KING_EXPORT KQuadratic
{
public:
    KQuadratic();
    KQuadratic(double a, double b, double c);
    KQuadratic(const KQuadratic &q);
    ~KQuadratic();

    inline void setA(double a);
    inline void setB(double b);
    inline void setC(double c);

    inline double a() const;
    inline double b() const;
    inline double c() const;
    inline double y(double x) const;
    inline KPair<double, double> x(double y, int *count) const;
    inline double slope(double x) const;
    inline KLinear tangent(double x) const;
    inline double delta() const;
    int rootCount() const;
    KPair<double, double> root(int *count = nullptr) const;
    inline double symmetryAxis() const;
    inline double extremum() const; // 极值
    inline KPointF vertex() const; // 顶点坐标
    inline bool intersects(const KLinear &l) const;
    KPair<KPointF, KPointF> intersection(const KLinear &l,
                                         int *count = nullptr) const;

    inline KQuadratic &operator=(const KQuadratic &other);

private:
    double a_;
    double b_;
    double c_;
};

inline void KQuadratic::setA(double a)
{
    a_ = a;
}

inline void KQuadratic::setB(double b)
{
    b_ = b;
}

inline void KQuadratic::setC(double c)
{
    c_ = c;
}

inline double KQuadratic::a() const
{
    return a_;
}

inline double KQuadratic::b() const
{
    return b_;
}

inline double KQuadratic::c() const
{
    return c_;
}

inline double KQuadratic::y(double x) const
{
    return a_ * x * x + b_ * x + c_;
}

inline KPair<double, double> KQuadratic::x(double y, int *count) const
{
    return KQuadratic(a_, b_, c_ - y).root(count);
}

inline double KQuadratic::slope(double x) const
{
    return 2 * a_ * x + b_;
}

inline KLinear KQuadratic::tangent(double x) const
{
    double k = slope(x);
    return KLinear(k, y(x) - k * x);
}

inline double KQuadratic::delta() const
{
    return b_*b_ - 4*a_*c_;
}

inline double KQuadratic::symmetryAxis() const
{
    return -b_ / (2 * a_);
}

inline double KQuadratic::extremum() const
{
    return c_ - b_ * b_ / (4 * a_);
}

inline KPointF KQuadratic::vertex() const
{
    double t1 = b_ / 2;
    double t2 = t1 / a_;
    return KPointF(-t2, c_ - t1 * t2);
}

inline bool KQuadratic::intersects(const KLinear &l) const
{
    KQuadratic q(a_, b_ - l.k(), c_ - l.b());
    return q.delta() >= -EPS6;
}

inline KQuadratic &KQuadratic::operator=(const KQuadratic &other)
{
    a_ = other.a_;
    b_ = other.b_;
    c_ = other.c_;
    return *this;
}

#endif // KQUADRATIC_H
