#include "karc2d.h"

#include <QDebug>

KArc2D::KArc2D() : radius_(0), start_angle_(0), span_angle_(0)
{

}

KArc2D::KArc2D(const KArc2D &arc) : center_(arc.center_), radius_(arc.radius_),
    start_angle_(arc.start_angle_), span_angle_(arc.span_angle_)
{

}

KArc2D::KArc2D(double cx, double cy, double radius, double start_angle,
               double span_angle) : center_(cx, cy), radius_(radius),
    span_angle_(span_angle)
{
    start_angle_ = normalizeAngle(start_angle);
}

KArc2D::KArc2D(const KPointF &center, double radius, double start_angle,
               double span_angle) : center_(center), radius_(radius),
    span_angle_(span_angle)
{
    start_angle_ = normalizeAngle(start_angle);
}

KArc2D::KArc2D(const KVector2D &v1, const KVector2D &v2, const KVector2D &v3,
               King::ArcCreateMode mode)
{
    setArc(v1, v2, v3, mode);
}

void KArc2D::setArc(const KVector2D &v1, const KVector2D &v2,
                    const KVector2D &v3, King::ArcCreateMode mode)
{
    if (mode == King::TangentPointPoint) {
        KVector2D v23 = v3 - v2;
        KVector2D v2o(v1);
        v2o.rotate90();
        double dot = KVector2D::dotProduct(v23, v2o);
        if (kFabs(dot) < 1e-9) {
            radius_ = 0;
            start_angle_ = 0;
            span_angle_ = 0;
            return;
        }
        double n = 0.5 * v23.lengthSquared() / dot;
        v2o *= n;
        KVector2D c = v2 + v2o;
        center_.setXY(c.x(), c.y());
        radius_ = v2o.length();

        KLineSegment2D l1(v1);
        KLineSegment2D l23(v2, v3);
        KLineSegment2D lo2(c, v2);
        KLineSegment2D lo3(c, v3);
        start_angle_ = lo2.angle();
        if (l1.radianTo(l23) > K_PI)
            span_angle_ = -lo3.angleTo(lo2);
        else
            span_angle_ = lo2.angleTo(lo3);
    } else if (mode == King::PointPointTangent) {
        KVector2D v2o = v3.rotated90();
        KVector2D v21(v1 - v2);
        double dot = KVector2D::dotProduct(v21, v2o);
        if (kFabs(dot) < 1e-9) {
            radius_ = 0;
            start_angle_ = 0;
            span_angle_ = 0;
            return;
        }
        double n = 0.5 * v21.lengthSquared() / dot;
        v2o *= n;
        KVector2D c = v2 + v2o;
        center_.setXY(c.x(), c.y());
        radius_ = v2o.length();

        KLineSegment2D l3(v3);
        KLineSegment2D l21(v2, v1);
        KLineSegment2D lo2(c, v2);
        KLineSegment2D lo1(c, v1);
        start_angle_ = lo1.angle();
        if (l3.radianTo(l21) < K_PI)
            span_angle_ = lo1.angleTo(lo2);
        else
            span_angle_ = -lo2.angleTo(lo1);
    }
}

KArc2D::KArc2D(const KPointF &start, const KPointF &end, double span_radian)
{
    double temp_radian = kFabs(span_radian);
    if (temp_radian > K_PI)
        temp_radian = K_2PI - temp_radian;

    double chord_len_2 = start.distanceToPoint(end) / 2;
    radius_ = chord_len_2 / kSin(temp_radian / 2);

    KVector2D v(start, end);
    if (span_radian >= 0)
        temp_radian <= K_PI ? v.rotate90() : v.rotateNeg90();
    else
        temp_radian <= K_PI ? v.rotateNeg90() : v.rotate90();
    v.setLength(pythagoreanTheorem_Right(chord_len_2, radius_));
    center_ = KPointF::midPoint(start, end) + v;

    KLineSegment2D cs(center_, start);
    start_angle_ = cs.angle();
    span_angle_ = kRadiansToDegrees(span_radian);
}

KPointF KArc2D::nearestPoint(const KPointF &point) const
{
    double dx = point.x() - center_.x();
    double dy = point.y() - center_.y();
    double angle = kRadiansToDegrees(kAtan2(dy, dx));
    bool contain = containAngle(angle);
    if (contain) {
        double factor = radius_ / kSqrt(dx * dx + dy * dy);
        dx *= factor;
        dy *= factor;
        return KPointF(center_.x() + dx, center_.y() + dy);
    } else {
        KPointF start = startPos();
        KPointF end = endPos();
        if (start.distanceSquaredToPoint(point) >
                end.distanceSquaredToPoint(point))
            return end;
        else
            return start;
    }
}

double KArc2D::nearestDistance(const KPointF &point) const
{
    double dx = point.x() - center_.x();
    double dy = point.y() - center_.y();
    double angle = kRadiansToDegrees(kAtan2(dy, dx));
    bool contain = containAngle(angle);
    if (contain) {
        return kFabs(kSqrt(dx * dx + dy * dy) - radius_);
    } else {
        return kSqrt(kMin(startPos().distanceSquaredToPoint(point),
                          endPos().distanceSquaredToPoint(point)));
    }
}

KRect KArc2D::boundingRect() const
{
    KPointF p1 = startPos();
    KPointF p2 = endPos();
    double left = kMin(p1.x(), p2.x());
    double right = kMax(p1.x(), p2.x());
    double top = kMax(p1.y(), p2.y());
    double bottom = kMin(p1.y(), p2.y());

    if (containAngle(0) || containAngle(360))
        right = center_.x() + radius_;
    if (containAngle(90))
        top = center_.y() + radius_;
    if (containAngle(180))
        left = center_.x() - radius_;
    if (containAngle(270))
        bottom = center_.y() - radius_;

    return KRect(left, bottom, right - left, top - bottom);
}

KVector2D KArc2D::startTangent() const
{
    if (span_angle_ < 0) {
        KVector2D v(startPos(), center_);
        v.rotate90();
        return v;
    } else {
        KVector2D v(center_, startPos());
        v.rotate90();
        return v;
    }
}

KVector2D KArc2D::endTangent() const
{
    if (span_angle_ < 0) {
        KVector2D v(endPos(), center_);
        v.rotate90();
        return v;
    } else {
        KVector2D v(center_, endPos());
        v.rotate90();
        return v;
    }
}

KArc2D &KArc2D::operator=(const KArc2D &rhs)
{
    center_ = rhs.center_;
    radius_ = rhs.radius_;
    start_angle_ = rhs.start_angle_;
    span_angle_ = rhs.span_angle_;
    return *this;
}

double KArc2D::normalizeAngle(double angle) const
{
    if (angle >= 0) {
        if (angle < 360)
            return angle;
        int n = int(angle / 360.0);
        angle -= n * 360;
    } else {
        int n = int(-angle / 360.0);
        angle += n * 360;
        if (angle < 0)
            angle += 360;
    }
    return angle;
}

bool KArc2D::containAngle(double angle) const
{
    angle = normalizeAngle(angle);
    double angle2 = start_angle_ + span_angle_;
    if (span_angle_ < 0) {
        if (angle > start_angle_)
            angle -= 360;
        return angle >= angle2;
    } else {
        if (angle < start_angle_)
            angle += 360;
        return angle <= angle2;
    }
}
