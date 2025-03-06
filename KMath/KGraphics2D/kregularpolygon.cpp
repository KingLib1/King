#include "kregularpolygon.h"

#include <math.h>

KRegularPolygon::KRegularPolygon() : radius_(1), sides_(3)
{
    xaxis_.setX(1);
}

KRegularPolygon::KRegularPolygon(const KPointF &center, double radius,
                                 int sides_count, const KVector2D &xaxis) :
    center_(center), radius_(radius), sides_(sides_count), xaxis_(xaxis)
{

}

KRegularPolygon::KRegularPolygon(const KRegularPolygon &polygon) :
    center_(polygon.center_), radius_(polygon.radius_),
    sides_(polygon.sides_), xaxis_(polygon.xaxis_)
{

}

void KRegularPolygon::vertex(QVector<KPointF> &points) const
{
    double rad = kAtan2(xaxis_.y(), xaxis_.x());
    double per_rad = K_2PI / sides_;
    for (int i = 0; i < sides_; ++i) {
        double x = radius_ * kCos(rad) + center_.x();
        double y = radius_ * kSin(rad) + center_.y();
        points << KPointF(x, y);
        rad += per_rad;
    }
}

KRegularPolygon &KRegularPolygon::operator=(const KRegularPolygon &polygon)
{
    center_ = polygon.center_;
    radius_ = polygon.radius_;
    sides_ = polygon.sides_;
    xaxis_ = polygon.xaxis_;
    return *this;
}
