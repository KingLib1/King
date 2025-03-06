#ifndef KCIRCLE3D_H
#define KCIRCLE3D_H

#include "krectcoordsystem3d.h"
#include "kray3d.h"
#include "KPair.h"
#include "kplane3d.h"

class KING_EXPORT KCircle3D
{
public:
    KCircle3D(double radius = 0);
    KCircle3D(const KCircle3D &circle);
    KCircle3D(const KVector3D &center, double radius, const KVector3D &normal);
    KCircle3D(double radius, const KRectCoordSystem3D &sys);

    inline void setCenter(const KVector3D &center);
    inline void setRadius(double radius);
    inline void setDiameter(double diameter);
    inline void setNormal(const KVector3D &normal);
    inline void setCoordinateSystem(const KRectCoordSystem3D &sys);
    inline bool setXYAxis(const KVector3D &xaxis, const KVector3D &yaxis);
    inline bool setZXAxis(const KVector3D &zaxis, const KVector3D &xaxis);
    inline void translate(const KVector3D &dv);
    inline void translateZ(double dz);
    inline void rotateZ(double angle);
    inline void rotateZ_Radian(double radian);
    inline void offset(double off);

    inline const KVector3D &center() const;
    KVector3D pos(double radian) const;
    inline double radius() const {return radius_;}
    inline double diameter() const;
    inline KVector3D left() const;
    inline KVector3D right() const;
    inline KVector3D top() const;
    inline KVector3D down() const;
    inline const KVector3D &xAxis() const;
    inline const KVector3D &yAxis() const;
    inline const KVector3D &normal() const;
    inline double perimeter() const;
    inline double area() const;
    inline static bool isParallel(const KCircle3D &c1, const KCircle3D &c2);
    inline KPlane3D toPlane() const;
    bool intersects(const KRay3D &ray) const;
    bool intersects(const KCircle3D &c) const;
    KVector3D intersected(const KRay3D &ray, bool &intersects) const;
    KLineSegment3D intersected(const KCircle3D &c, bool *success = nullptr) const;
    KLineSegment3D intersected(const KPlane3D &plane, bool *success = nullptr) const;
    inline KCircle3D translated(const KVector3D &dv) const;
    inline const KRectCoordSystem3D &coordSystem() const;
    inline KMatrix4x4 matrix() const;
    /**
     * @brief 根据法向量，半径和圆上两点确定圆，返回两个解
     */
    static KPair<KCircle3D, KCircle3D> circleFrom(
            const KVector3D &normal, const KVector3D &p1, const KVector3D &p2,
            double radius);

    inline KCircle3D &operator=(const KCircle3D &circle);

private:
    KRectCoordSystem3D sys_;
    double radius_;
};

inline void KCircle3D::setCenter(const KVector3D &center)
{
    sys_.setOrigin(center);
}

inline void KCircle3D::setRadius(double radius)
{
    radius_ = radius;
}

inline void KCircle3D::setDiameter(double diameter)
{
    radius_ = 0.5 * diameter;
}

inline void KCircle3D::setNormal(const KVector3D &normal)
{
    sys_.setZAxis(normal);
}

inline void KCircle3D::setCoordinateSystem(const KRectCoordSystem3D &sys)
{
    sys_ = sys;
}

inline bool KCircle3D::setXYAxis(const KVector3D &xaxis, const KVector3D &yaxis)
{
    return sys_.setXYAxis(xaxis, yaxis);
}

inline bool KCircle3D::setZXAxis(const KVector3D &zaxis, const KVector3D &xaxis)
{
    return sys_.setZXAxis(zaxis, xaxis);
}

inline void KCircle3D::translate(const KVector3D &dv)
{
    sys_.translateByBase(dv);
}

inline void KCircle3D::translateZ(double dz)
{
    sys_.translateZByBase(dz);
}

inline void KCircle3D::rotateZ(double angle)
{
    sys_.rotateZByBase(angle);
}

inline void KCircle3D::rotateZ_Radian(double radian)
{
    sys_.rotateZRadianByBase(radian);
}

inline void KCircle3D::offset(double off)
{
    radius_ += off;
}

inline const KVector3D &KCircle3D::center() const
{
    return sys_.origin();
}

inline double KCircle3D::diameter() const
{
    return 2 * radius_;
}

inline KVector3D KCircle3D::left() const
{
    return center() - xAxis() * radius_;
}

inline KVector3D KCircle3D::right() const
{
    return center() + xAxis() * radius_;
}

inline KVector3D KCircle3D::top() const
{
    return center() + yAxis() * radius_;
}

inline KVector3D KCircle3D::down() const
{
    return center() - yAxis() * radius_;
}

inline const KVector3D &KCircle3D::xAxis() const
{
    return sys_.xAxis();
}

inline const KVector3D &KCircle3D::yAxis() const
{
    return sys_.yAxis();
}

inline const KVector3D &KCircle3D::normal() const
{
    return sys_.zAxis();
}

inline double KCircle3D::perimeter() const
{
    return K_2PI * radius_;
}

inline double KCircle3D::area() const
{
    return K_PI * radius_ * radius_;
}

inline bool KCircle3D::isParallel(const KCircle3D &c1, const KCircle3D &c2)
{
    return KVector3D::isParallel(c1.normal(), c2.normal());
}

inline KPlane3D KCircle3D::toPlane() const
{
    return KPlane3D(center(), normal());
}

inline KCircle3D KCircle3D::translated(const KVector3D &dv) const
{
    KCircle3D circle(*this);
    circle.sys_.translateByBase(dv);
    return circle;
}

inline const KRectCoordSystem3D &KCircle3D::coordSystem() const
{
    return sys_;
}

inline KMatrix4x4 KCircle3D::matrix() const
{
    return sys_.toMatrix4x4();
}

inline KCircle3D &KCircle3D::operator=(const KCircle3D &circle)
{
    sys_ = circle.sys_;
    radius_ = circle.radius_;
    return *this;
}

#endif // KCIRCLE3D_H
