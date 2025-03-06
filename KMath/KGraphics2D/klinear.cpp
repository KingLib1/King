#include "klinear.h"

KLinear::KLinear() : k_(1), b_(0)
{

}

KLinear::KLinear(double k, double b) : k_(k), b_(b)
{

}

KLinear::KLinear(const KPointF &p1, const KPointF &p2)
{
    k_ = (p2.y() - p1.y()) / (p2.x() - p1.x());
    b_ = p1.y() - k_ * p1.x();
}

KLinear::KLinear(const KPointF &p, double k) : k_(k)
{
    b_ = p.y() - k_ * p.x();
}

KLinear::KLinear(double x, double y, double k) : k_(k)
{
    b_ = y - k_ * x;
}

KLinear::KLinear(const KLinear &other) : k_(other.k_), b_(other.b_)
{

}

KLinear::~KLinear()
{

}
