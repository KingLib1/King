#ifndef KCUBOID_H
#define KCUBOID_H

#include "krectcoordsystem3d.h"
#include "kray3d.h"

class KING_EXPORT KCuboid
{
public:
    KCuboid();
    KCuboid(const KCuboid &cuboid);
    KCuboid(double length, double width, double height);
    KCuboid(double length, double width, double height,
            const KRectCoordSystem3D &sys);

    inline void setLength(double length);
    inline void setWidth(double width);
    inline void setHeight(double height);
    inline void setCenter(const KVector3D &center);
    inline void setMatrix(const KMatrix4x4 &matrix);
    inline void translateByBase(const KVector3D &offset);
    inline void translateByBase(double dx, double dy, double dz);
    inline void translateBySelf(const KVector3D &offset);
    inline void translateBySelf(double dx, double dy, double dz);
    inline void rotateXBySelf(double angle);
    inline void rotateXByBase(double angle);
    inline void rotateYBySelf(double angle);
    inline void rotateYByBase(double angle);
    inline void rotateZBySelf(double angle);
    inline void rotateZByBase(double angle);

    inline double length() const;
    inline double width() const;
    inline double height() const;
    inline KVector3D firstOctantVertex() const;
    inline KVector3D secondOctantVertex() const;
    inline KVector3D thirdOctantVertex() const;
    inline KVector3D fourthOctantVertex() const;
    inline KVector3D fifthOctantVertex() const;
    inline KVector3D sixthOctantVertex() const;
    inline KVector3D seventhOctantVertex() const;
    inline KVector3D eighthOctantVertex() const;
    inline const KVector3D &center() const;
    inline const KVector3D &xAxis() const;
    inline const KVector3D &yAxis() const;
    inline const KVector3D &zAxis() const;
    inline KMatrix4x4 matrix() const;
    /**
     * @brief 暂未实现
     */
//    bool intersects(const KRay3D &ray) const;
    bool containsPoint(const KVector3D &point) const;

    inline KCuboid &operator=(const KCuboid &cuboid);

private:
    KVector3D size_; // 长x 宽y 高z
    KRectCoordSystem3D sys_;
};

inline void KCuboid::setLength(double length)
{
    size_.setX(length);
}

inline void KCuboid::setWidth(double width)
{
    size_.setY(width);
}

inline void KCuboid::setHeight(double height)
{
    size_.setZ(height);
}

inline void KCuboid::setCenter(const KVector3D &center)
{
    sys_.setOrigin(center);
}

inline void KCuboid::setMatrix(const KMatrix4x4 &matrix)
{
    sys_.setOrigin(matrix.translation());
    sys_.setXYAxis(matrix.xAxis(), matrix.yAxis());
}

inline void KCuboid::translateByBase(const KVector3D &offset)
{
    sys_.translateByBase(offset);
}

inline void KCuboid::translateByBase(double dx, double dy, double dz)
{
    sys_.translateByBase(dx, dy, dz);
}

inline void KCuboid::translateBySelf(const KVector3D &offset)
{
    sys_.translateBySelf(offset);
}

inline void KCuboid::translateBySelf(double dx, double dy, double dz)
{
    sys_.translateBySelf(dx, dy, dz);
}

inline void KCuboid::rotateXBySelf(double angle)
{
    sys_.rotateXBySelf(angle);
}

inline void KCuboid::rotateXByBase(double angle)
{
    sys_.rotateXByBase(angle);
}

inline void KCuboid::rotateYBySelf(double angle)
{
    sys_.rotateYBySelf(angle);
}

inline void KCuboid::rotateYByBase(double angle)
{
    sys_.rotateYByBase(angle);
}

inline void KCuboid::rotateZBySelf(double angle)
{
    sys_.rotateZBySelf(angle);
}

inline void KCuboid::rotateZByBase(double angle)
{
    sys_.rotateZByBase(angle);
}

inline double KCuboid::length() const
{
    return size_.x();
}

inline double KCuboid::width() const
{
    return size_.y();
}

inline double KCuboid::height() const
{
    return size_.z();
}

inline KVector3D KCuboid::firstOctantVertex() const
{
    double x = length() / 2;
    double y = width() / 2;
    double z = height() / 2;
    return x * xAxis() + y * yAxis() + z * zAxis() + sys_.origin();
}

inline KVector3D KCuboid::secondOctantVertex() const
{
    double x = -length() / 2;
    double y = width() / 2;
    double z = height() / 2;
    return x * xAxis() + y * yAxis() + z * zAxis() + sys_.origin();
}

inline KVector3D KCuboid::thirdOctantVertex() const
{
    double x = -length() / 2;
    double y = -width() / 2;
    double z = height() / 2;
    return x * xAxis() + y * yAxis() + z * zAxis() + sys_.origin();
}

inline KVector3D KCuboid::fourthOctantVertex() const
{
    double x = length() / 2;
    double y = -width() / 2;
    double z = height() / 2;
    return x * xAxis() + y * yAxis() + z * zAxis() + sys_.origin();
}

inline KVector3D KCuboid::fifthOctantVertex() const
{
    double x = length() / 2;
    double y = width() / 2;
    double z = -height() / 2;
    return x * xAxis() + y * yAxis() + z * zAxis() + sys_.origin();
}

inline KVector3D KCuboid::sixthOctantVertex() const
{
    double x = -length() / 2;
    double y = width() / 2;
    double z = -height() / 2;
    return x * xAxis() + y * yAxis() + z * zAxis() + sys_.origin();
}

inline KVector3D KCuboid::seventhOctantVertex() const
{
    double x = -length() / 2;
    double y = -width() / 2;
    double z = -height() / 2;
    return x * xAxis() + y * yAxis() + z * zAxis() + sys_.origin();
}

inline KVector3D KCuboid::eighthOctantVertex() const
{
    double x = length() / 2;
    double y = -width() / 2;
    double z = -height() / 2;
    return x * xAxis() + y * yAxis() + z * zAxis() + sys_.origin();
}

inline const KVector3D &KCuboid::center() const
{
    return sys_.origin();
}

inline const KVector3D &KCuboid::xAxis() const
{
    return sys_.xAxis();
}

inline const KVector3D &KCuboid::yAxis() const
{
    return sys_.yAxis();
}

inline const KVector3D &KCuboid::zAxis() const
{
    return sys_.zAxis();
}

inline KMatrix4x4 KCuboid::matrix() const
{
    return sys_.toMatrix4x4();
}

inline KCuboid &KCuboid::operator=(const KCuboid &cuboid)
{
    size_ = cuboid.size_;
    sys_ = cuboid.sys_;
    return *this;
}

#endif // KCUBOID_H
