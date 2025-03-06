#include "kquadratic.h"

KQuadratic::KQuadratic() : a_(1), b_(0), c_(0)
{

}

KQuadratic::KQuadratic(double a, double b, double c) : a_(a), b_(b), c_(c)
{

}

KQuadratic::KQuadratic(const KQuadratic &q) : a_(q.a_), b_(q.b_), c_(q.c_)
{

}

KQuadratic::~KQuadratic()
{

}

int KQuadratic::rootCount() const
{
    double d = delta();
    if (d > EPS6)
        return 2;
    if (d < -EPS6)
        return 0;
    return 1;
}

KPair<double, double> KQuadratic::root(int *count) const
{
    double d = delta();
    if (d > EPS6) {
        if (count)
            *count = 2;
        double sq_del = kSqrt(d);
        double a2 = a_ * 2;
        return KPair<double, double>((-b_ - sq_del) / a2, (-b_ + sq_del) / a2);
    }

    if (d < -EPS6) {
        if (count)
            *count = 0;
        return KPair<double, double>(0, 0);
    }

    if (count)
        *count = 1;
    double x = -b_ / (2 * a_);
    return KPair<double, double>(x, x);
}

KPair<KPointF, KPointF> KQuadratic::intersection(const KLinear &l,
                                                 int *count) const
{
    KQuadratic q(a_, b_ - l.k(), c_ - l.b());
    int num;
    KPair<double, double> r = q.root(&num);
    if (count)
        *count = num;
    if (num == 0)
        return KPair<KPointF, KPointF>();
    return KPair<KPointF, KPointF>(KPointF(r.first, l.y(r.first)),
                                   KPointF(r.second, l.y(r.second)));
}
