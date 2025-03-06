#include "kcircle2d.h"

#include "kquadratic.h"
#include "kellipse.h"
#include "ktriangle.h"

#include <QDebug>

KCircle2D::KCircle2D() : radius_(0)
{

}

KCircle2D::KCircle2D(const KCircle2D &circle) :
    center_(circle.center_), radius_(circle.radius_)
{

}

KCircle2D::KCircle2D(double center_x, double center_y, double radius) :
    radius_(radius)
{
    center_.setXY(center_x, center_y);
}

KCircle2D::KCircle2D(const KPointF &center, double radius) :
    center_(center), radius_(radius)
{

}

KCircle2D::KCircle2D(double radius) : radius_(radius)
{

}

KPair<double, double> KCircle2D::x(double y) const
{
    y -= center_.y();
    if (y < -radius_ || y > radius_)
        return KPair<double, double>(0, 0);

    double x = pythagoreanTheorem_Right(kFabs(y), radius_);
    return KPair<double, double>(-x + center_.x(), x + center_.x());
}

KPair<double, double> KCircle2D::y(double x) const
{
     x -= center_.x();
    if (x < -radius_ || x > radius_)
        return KPair<double, double>(0, 0);

    double y = pythagoreanTheorem_Right(kFabs(x), radius_);
    return KPair<double, double>(-y + center_.y(), y + center_.y());
}

KPair<double, double> KCircle2D::xRadian(double x) const
{
    x -= center_.x();
    if (x < -radius_ || x > radius_)
        return KPair<double, double>(0, 0);

    double a = kAcos(x / radius_);
    return KPair<double, double>(-a, a);
}

KPair<double, double> KCircle2D::yRadian(double y) const
{
    y -= center_.y();
    if (y < -radius_ || y > radius_) {
        return KPair<double, double>(0, 0);
    }

    double a = kAsin(y / radius_);
    return a >= 0 ? KPair<double, double>(a, K_PI - a) :
        KPair<double, double>(-K_PI - a, a);
}

KPair<KPointF, KPointF> KCircle2D::intersected(const KCircle2D &other,
                                               int &count) const
{
    double dis_sqr = center_.distanceSquaredToPoint(other.center_);
    double sum_sqr = kSumSquare(radius_, other.radius_);
    double dif_sqr = kDifferenceSquare(radius_, other.radius_);

    KPair<KPointF, KPointF> pair;
    if (dis_sqr > sum_sqr) {
        count = 0;
        return pair;
    }
    \
    if (dis_sqr < sum_sqr) {
        if (dis_sqr > dif_sqr) {
            count = 2;
            KVector2D cv(center_, other.center_);
            cv.normalize();
            KVector2D p1p2 = cv.rotated90();
            KTriangle t(radius_, other.radius_, kSqrt(dis_sqr));
            double cosb = t.cosB();
            double sinb = kSqrt(1 - cosb * cosb);
            double len = t.a() * cosb;
            KPointF m = center_ + cv * len;
            len = t.a() * sinb;
            p1p2 *= len;
            pair.first = m + p1p2;
            pair.second = m - p1p2;
            return pair;
        }

        if (dis_sqr < dif_sqr) {
            count = 0;
            return pair;
        }

        if (center_ == other.center_) {
            count = K_INT_MAX;
            return pair;
        }
    }

    count = 1;
    if (radius_ >= other.radius_) {
        KVector2D cv(center_, other.center_);
        double t = kSqrt(radiusSquared() / cv.lengthSquared());
        pair.first = center_ + cv * t;
        pair.second = pair.first;
    } else {
        KVector2D cv(other.center_, center_);
        double t = kSqrt(other.radiusSquared() / cv.lengthSquared());
        pair.first = other.center_ + cv * t;
        pair.second = pair.first;
    }
    return pair;
}

bool KCircle2D::intersects(const KLineSegment2D &line) const
{
    if (contains(line.p1()) || contains(line.p2()))
        return true;
    KPointF rp = line.p1() - center_;
    KPointF l(line.dx(), line.dy());
    KQuadratic q(l.originDistanceSquared(), 2 * KPointF::dotProduct(rp, l),
                 rp.originDistanceSquared() - radiusSquared());
    int num;
    KPair<double, double> root = q.root(&num);
    if (num == 0 || root.second < 0 || root.first > 1)
        return false;
    return true;
}

bool KCircle2D::intersects(const KEllipse &ell) const
{
    if (ell.contains(center_))
        return true;
    return ell.nearestDistanceSquare(center_) <= radiusSquared();
}

KPair<KArc2D, KArc2D> KCircle2D::intersectedArc(const KCircle2D &circle,
                                                bool &success) const
{
    int count;
    KPair<KPointF, KPointF> ps = intersected(circle, count);
    if (count == 0 || count == 1) {
        success = false;
        return KPair<KArc2D, KArc2D>();
    }

    success = true;
    KLineSegment2D line1(center_, ps.first);
    double start_angle = line1.angle();
    KLineSegment2D line2(center_, ps.second);
    double end_angle = line2.angle();
    double span_angle = end_angle - start_angle;
    if (span_angle < 0)
        span_angle += 360;
    KArc2D arc1(center_, radius_, start_angle, span_angle);
    KPointF mid = arc1.midPos();
    if (!circle.contains(mid))
        arc1.setSpanAngle(span_angle - 360);

    line1.setP1(circle.center_);
    line1.setP2(ps.first);
    start_angle = line1.angle();
    line2.setP1(circle.center_);
    line2.setP2(ps.second);
    end_angle = line2.angle();
    span_angle = end_angle - start_angle;
    if (span_angle < 0)
        span_angle += 360;
    KArc2D arc2(circle.center_, circle.radius_, start_angle, span_angle);
    mid = arc2.midPos();
    if (!contains(mid))
        arc2.setSpanAngle(span_angle - 360);

    return KPair<KArc2D, KArc2D>(arc1, arc2);
}

KPair<KPointF, KPointF> KCircle2D::tangentPointFrom(const KPointF &p) const
{
    double c2 = p.distanceSquaredToPoint(center_);
    double r2 = kSquare(radius_);
    double l2 = c2 - r2;
    double c = kSqrt(c2);
    double l = kSqrt(l2);
    double rad = kAcos(l / c);
    KVector2D pc = center_ - p;
    pc.setLength(l);

    KPair<KPointF, KPointF> pair;
    pair.first = p + pc.rotatedRadian(-rad);
    pair.second = p + pc.rotatedRadian(rad);

    return pair;
}
