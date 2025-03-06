#ifndef KPOLARCOORDSYSTEM2D_H
#define KPOLARCOORDSYSTEM2D_H

#include "kpointf.h"

class KING_EXPORT KPolarCoordSystem2D
{
public:
    KPolarCoordSystem2D();
    KPolarCoordSystem2D(double radius, double radian);
    KPolarCoordSystem2D(const KPointF &point);
    KPolarCoordSystem2D(const KPolarCoordSystem2D &sys);
    ~KPolarCoordSystem2D();

    inline void setRadius(double radius);
    inline void setRadian(double radian);
    inline void setPoint(const KPointF &point);
    inline void setPoint(double x, double y);
    inline void normalize();

    inline double radius() const;
    inline double radian() const;
    inline double x() const;
    inline double y() const;

    inline KPolarCoordSystem2D &operator=(
            const KPolarCoordSystem2D &sys);

private:
    double radius_;
    double radian_;
};

inline void KPolarCoordSystem2D::setRadius(double radius)
{
    radius_ = radius;
}

inline void KPolarCoordSystem2D::setRadian(double radian)
{
    radian_ = radian;
}

inline void KPolarCoordSystem2D::setPoint(const KPointF &point)
{
    setPoint(point.x(), point.y());
}

inline void KPolarCoordSystem2D::setPoint(double x, double y)
{
    radius_ = kSqrt(x * x + y * y);
    radian_ = kAtan2(y, x);
}

inline void KPolarCoordSystem2D::normalize()
{
    if (radius_ < 0) {
        radius_ = -radius_;
        radian_ += K_PI;
    }
    radian_ = radianNormalized(radian_);
}

inline double KPolarCoordSystem2D::radius() const
{
    return radius_;
}

inline double KPolarCoordSystem2D::radian() const
{
    return radian_;
}

inline double KPolarCoordSystem2D::x() const
{
    return radius_ * kCos(radian_);
}

inline double KPolarCoordSystem2D::y() const
{
    return radius_ * kSin(radian_);
}

inline KPolarCoordSystem2D &KPolarCoordSystem2D::operator=(
        const KPolarCoordSystem2D &sys)
{
    radius_ = sys.radius_;
    radian_ = sys.radian_;
    return *this;
}

#endif // KPOLARCOORDSYSTEM2D_H
