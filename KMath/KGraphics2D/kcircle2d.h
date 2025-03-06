#ifndef KCIRCLE2D_H
#define KCIRCLE2D_H

#include <QVector>

#include "krect.h"
#include "kvector2d.h"
#include "KPair.h"
#include "karc2d.h"

class KEllipse;

class KING_EXPORT KCircle2D
{
public:
    KCircle2D();
    KCircle2D(const KCircle2D &circle);
    KCircle2D(double center_x, double center_y, double radius);
    KCircle2D(const KPointF &center, double radius);
    KCircle2D(double radius);

    inline void setCenter(const KPointF &center);
    inline void setRadius(double radius);
    inline void translate(const KVector2D &dv);

    // first <= second
    KPair<double, double> x(double y) const;
    // first <= second
    KPair<double, double> y(double x) const;
    // first <= second
    KPair<double, double> xRadian(double x) const;
    // first <= second
    KPair<double, double> yRadian(double y) const;
    inline KRect boundingRect() const;
    inline double cx() const {return center_.x();}
    inline double cy() const {return center_.y();}
    inline double radius() const {return radius_;}
    inline double radiusSquared() const {return kSquare(radius_);}
    inline double diameter() const;
    inline const KPointF &center() const {return center_;}
    inline KPointF point(double radian) const;
    inline KCircle2D translated(const KVector2D &dv) const;
    inline double circumference() const;
    inline double area() const;
    inline bool intersects(const KCircle2D &circle) const;
    KPair<KPointF, KPointF> intersected(const KCircle2D &other, int &count) const;
    bool intersects(const KLineSegment2D &line) const;
    inline bool contains(const KPointF &point) const;
    bool intersects(const KEllipse &ell) const;
    // 与circle相交的圆弧部分
    KPair<KArc2D, KArc2D> intersectedArc(const KCircle2D &circle, bool &success) const;
    /**
     * @brief 经过圆外一点的该圆的切线的切点
     */
    KPair<KPointF, KPointF> tangentPointFrom(const KPointF &p) const;

    inline KCircle2D &operator=(const KCircle2D &circle);

private:
    KPointF center_;
    double radius_;
};

inline void KCircle2D::setCenter(const KPointF &center)
{
    center_ = center;
}

inline void KCircle2D::setRadius(double radius)
{
    radius_ = radius;
}

inline void KCircle2D::translate(const KVector2D &dv)
{
    center_ += dv;
}

inline KRect KCircle2D::boundingRect() const
{
    return KRect(center_.x() - radius_, center_.y() - radius_,
                 2 * radius_, 2 * radius_);
}

inline double KCircle2D::diameter() const
{
    return 2 * radius_;
}

inline KPointF KCircle2D::point(double radian) const
{
    return KPointF(radius_ * kCos(radian), radius_ * kSin(radian)) + center_;
}

inline KCircle2D KCircle2D::translated(const KVector2D &dv) const
{
    return KCircle2D(center_.x() + dv.x(), center_.y() + dv.y(), radius_);
}

inline double KCircle2D::circumference() const
{
    return K_2PI * radius_;
}

inline double KCircle2D::area() const
{
    return K_PI * radius_ * radius_;
}

inline bool KCircle2D::intersects(const KCircle2D &circle) const
{
    return center_.distanceSquaredToPoint(circle.center_) <=
            kSquare(radius_ + circle.radius_);
}

inline bool KCircle2D::contains(const KPointF &point) const
{
    return point.distanceSquaredToPoint(center_) <= radiusSquared();
}

inline KCircle2D &KCircle2D::operator=(const KCircle2D &circle)
{
    center_ = circle.center_;
    radius_ = circle.radius_;
    return *this;
}

#endif // KCIRCLE_H
