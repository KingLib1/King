#ifndef KCYLINDER_H
#define KCYLINDER_H

#include <QVector>

#include "krectcoordsystem3d.h"
#include "kcuboid.h"
#include "kcircle3d.h"

class KING_EXPORT KCylinder
{
public:
    KCylinder();
    KCylinder(const KCylinder &cylinder);
    KCylinder(double radius, double height);
    KCylinder(double radius, double height, const KRectCoordSystem3D &sys);
    ~KCylinder();

    inline void setRadius(double radius);
    inline void setHeight(double height);
    inline void setCenter(const KVector3D &center);
    inline void setCoordinateSystem(const KRectCoordSystem3D &sys);
    inline void setMatrix(const KMatrix4x4 &matrix);
    inline void translateByBase(const KVector3D &dv);
    inline void translateBySelf(const KVector3D &dv);

    inline double radius() const;
    inline double diameter() const;
    inline double height() const;
    inline const KVector3D &center() const;
    inline const KVector3D &zAxis() const;
    inline const KRectCoordSystem3D &coordinateSystem() const;
    inline double volume() const;
    inline double surfaceArea() const;
    inline KCuboid boundingVolume() const;
    inline KVector3D bottomCenter() const;
    inline KVector3D topCenter() const;
    KCircle3D bottomCircle() const;
    KCircle3D topCircle() const;
    inline bool containsPoint(const KVector3D &point) const;
    bool intersects(const KRay3D &ray) const;

    /**
     * @brief triangleStrip
     * @param slices
     * @return 顶点和法向量
     */
    KPair<QVector<KVector3D>, QVector<KVector3D>> triangleStrip(int slices) const;

    inline KCylinder &operator=(const KCylinder &cylinder);

private:
    double radius_;
    double height_;
    KRectCoordSystem3D sys_;
};

inline void KCylinder::setRadius(double radius)
{
    radius_ = radius;
}

inline void KCylinder::setHeight(double height)
{
    height_ = height;
}

inline void KCylinder::setCenter(const KVector3D &center)
{
    sys_.setOrigin(center);
}

inline void KCylinder::setCoordinateSystem(
        const KRectCoordSystem3D &sys)
{
    sys_ = sys;
}

inline void KCylinder::setMatrix(const KMatrix4x4 &matrix)
{
    sys_.setOrigin(matrix.translation());
    sys_.setXYAxis(matrix.xAxis(), matrix.yAxis());
}

inline void KCylinder::translateByBase(const KVector3D &dv)
{
    sys_.translateByBase(dv);
}

inline void KCylinder::translateBySelf(const KVector3D &dv)
{
    sys_.translateBySelf(dv);
}

inline double KCylinder::radius() const
{
    return radius_;
}

inline double KCylinder::diameter() const
{
    return 2 * radius_;
}

inline double KCylinder::height() const
{
    return height_;
}

inline const KVector3D &KCylinder::center() const
{
    return sys_.origin();
}

inline const KVector3D &KCylinder::zAxis() const
{
    return sys_.zAxis();
}

inline const KRectCoordSystem3D &KCylinder::coordinateSystem() const
{
    return sys_;
}

inline double KCylinder::volume() const
{
    return K_PI * radius_ * radius_ * height_;
}

inline double KCylinder::surfaceArea() const
{
    return K_2PI * radius_ * (radius_ + height_);
}

inline KCuboid KCylinder::boundingVolume() const
{
    double d = diameter();
    return KCuboid(d, d, height_, sys_);
}

inline KVector3D KCylinder::bottomCenter() const
{
    return center() - zAxis() * (height_ / 2);
}

inline KVector3D KCylinder::topCenter() const
{
    return center() + zAxis() * (height_ / 2);
}

inline bool KCylinder::containsPoint(const KVector3D &point) const
{
    KVector3D cp = point - center();
    double t = KVector3D::dotProduct(cp, zAxis()) / zAxis().lengthSquared();
    double half_height = height_ / 2;
    if (t > half_height || t < -half_height)
        return false;
    return (cp - zAxis() * t).lengthSquared() <= kSquare(radius_);
}

inline KCylinder &KCylinder::operator=(const KCylinder &cylinder)
{
    radius_ = cylinder.radius_;
    height_ = cylinder.height_;
    sys_ = cylinder.sys_;
    return *this;
}

#endif // KCYLINDER_H
