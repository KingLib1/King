#ifndef RECTCOORDSYSTEM_H
#define RECTCOORDSYSTEM_H

#include "King.h"
#include "kmatrix4x4.h"

class KING_EXPORT KRectCoordSystem3D
{
public:
    KRectCoordSystem3D();
    KRectCoordSystem3D(const KVector3D &xaxis, const KVector3D &yaxis);
    KRectCoordSystem3D(const KRectCoordSystem3D &sys);
    /**
     * @brief axis1和axis2必须正交，否则返回一个单位坐标系
     */
    KRectCoordSystem3D(const KVector3D &origin,
            const KVector3D &axis1, const KVector3D &axis2,
            King::CoordinateSystemAxisCreatMode mode);
    KRectCoordSystem3D(const KMatrix3x3 &matrix);
    KRectCoordSystem3D(const KMatrix4x4 &matrix);
    /**
     * @brief 以一个轴快速建立坐标系，另外两个轴的方向随机生成
     */
    KRectCoordSystem3D(const KVector3D &axis, King::CoordinateAxisType type);
    ~KRectCoordSystem3D();

    inline void setOrigin(const KVector3D &origin);
    inline void setOrigin(double x, double y, double z);
    /**
     * @brief 指定的x和y轴必须正交，否则不作任何处理。下同
     * @return
     */
    bool setXYAxis(const KVector3D &xaxis, const KVector3D &yaxis);
    bool setYZAxis(const KVector3D &yaxis, const KVector3D &zaxis);
    bool setZXAxis(const KVector3D &zaxis, const KVector3D &xaxis);
    /**
     * @brief 按基坐标系平移
     */
    inline void translateByBase(const KVector3D &translate);
    inline void translateByBase(double dx, double dy, double dz);
    inline void translateZByBase(double dz);
    /**
     * @brief 按自身坐标系平移
     */
    inline void translateBySelf(const KVector3D &translate);
    inline void translateBySelf(double dx, double dy, double dz);

    inline void rotateXBySelf(double angle);
    void rotateXByBase(double angle);
    void rotateYBySelf(double angle);
    void rotateYByBase(double angle);
    void rotateZBySelf(double angle);
    inline void rotateZByBase(double angle);
    void rotateZRadianByBase(double radian);
    /**
     * @brief 指定z轴后，x轴和y轴的方向任意生成。下同
     */
    inline void setZAxis(const KVector3D &axis);
    inline void setXAxis(const KVector3D &axis);
    inline void setYAxis(const KVector3D &axis);

    inline const KVector3D &xAxis() const;
    inline const KVector3D &yAxis() const;
    inline const KVector3D &zAxis() const;
    inline const KVector3D &origin() const;
    inline KVector3D mapToBase(const KVector3D &point) const;
    KVector3D mapFromBase(const KVector3D &point) const;
    inline KMatrix3x3 toMatrix3x3() const;
    inline KMatrix4x4 toMatrix4x4() const;
    inline KRectCoordSystem3D translatedByBase(const KVector3D &dv) const;
    inline KRectCoordSystem3D translatedBySelf(const KVector3D &dv) const;

    static KRectCoordSystem3D fromThreePoints(
            const KVector3D &p1, const KVector3D &p2, const KVector3D &p3);

    inline KRectCoordSystem3D &operator=(const KRectCoordSystem3D &sys);

private:
    inline void initAxis();
    bool RandomCreateCoordinateSystem(const KVector3D &axis,
                                      King::CoordinateAxisType type);

    KVector3D origin_;
    KVector3D xaxis_;
    KVector3D yaxis_;
    KVector3D zaxis_;
};

inline void KRectCoordSystem3D::setOrigin(const KVector3D &origin)
{
    origin_ = origin;
}

inline void KRectCoordSystem3D::setOrigin(double x, double y, double z)
{
    origin_.setXYZ(x, y, z);
}

inline void KRectCoordSystem3D::translateByBase(const KVector3D &translate)
{
    origin_ += translate;
}

inline void KRectCoordSystem3D::translateByBase(
        double dx, double dy, double dz)
{
    origin_.translate(dx, dy, dz);
}

inline void KRectCoordSystem3D::translateZByBase(double dz)
{
    origin_.translateZ(dz);
}

inline void KRectCoordSystem3D::translateBySelf(const KVector3D &translate)
{
    origin_ += translate.x() * xaxis_ + translate.y() * yaxis_ +
            translate.z() * zaxis_;
}

inline void KRectCoordSystem3D::translateBySelf(
        double dx, double dy, double dz)
{
    origin_ += dx * xaxis_ + dy * yaxis_ + dz * zaxis_;
}

inline void KRectCoordSystem3D::rotateXBySelf(double angle)
{
    double r = kDegreesToRadians(angle);
    double cosr = kCos(r);
    double sinr = kSin(r);
    KVector3D yaxis(yaxis_);
    yaxis_ = yaxis * cosr + zaxis_ * sinr;
    zaxis_ = zaxis_ * cosr - yaxis * sinr;
}

inline void KRectCoordSystem3D::rotateZByBase(double angle)
{
    rotateZRadianByBase(kDegreesToRadians(angle));
}

inline void KRectCoordSystem3D::setZAxis(const KVector3D &axis)
{
    RandomCreateCoordinateSystem(axis, King::ZAxis);
}

inline void KRectCoordSystem3D::setXAxis(const KVector3D &axis)
{
    RandomCreateCoordinateSystem(axis, King::XAxis);
}

inline void KRectCoordSystem3D::setYAxis(const KVector3D &axis)
{
    RandomCreateCoordinateSystem(axis, King::YAxis);
}

inline const KVector3D &KRectCoordSystem3D::xAxis() const
{
    return xaxis_;
}

inline const KVector3D &KRectCoordSystem3D::yAxis() const
{
    return yaxis_;
}

inline const KVector3D &KRectCoordSystem3D::zAxis() const
{
    return zaxis_;
}

inline const KVector3D &KRectCoordSystem3D::origin() const
{
    return origin_;
}

inline KVector3D KRectCoordSystem3D::mapToBase(const KVector3D &point) const
{
    return xaxis_ * point.x() + yaxis_ * point.y() + zaxis_ * point.z() + origin_;
}

inline KMatrix3x3 KRectCoordSystem3D::toMatrix3x3() const
{
    return KMatrix3x3(xaxis_, yaxis_, zaxis_);
}

inline KMatrix4x4 KRectCoordSystem3D::toMatrix4x4() const
{
    return KMatrix4x4(xaxis_, yaxis_, zaxis_, origin_);
}

inline KRectCoordSystem3D KRectCoordSystem3D::translatedByBase(
        const KVector3D &dv) const
{
    KRectCoordSystem3D sys(*this);
    sys.translateByBase(dv);
    return sys;
}

inline KRectCoordSystem3D KRectCoordSystem3D::translatedBySelf(
        const KVector3D &dv) const
{
    KRectCoordSystem3D sys(*this);
    sys.translateBySelf(dv);
    return sys;
}

inline KRectCoordSystem3D &KRectCoordSystem3D::operator=(
        const KRectCoordSystem3D &sys)
{
    origin_ = sys.origin_;
    xaxis_ = sys.xaxis_;
    yaxis_ = sys.yaxis_;
    zaxis_ = sys.zaxis_;
    return *this;
}

inline void KRectCoordSystem3D::initAxis()
{
    xaxis_.setX(1);
    yaxis_.setY(1);
    zaxis_.setZ(1);
}

#endif // RECTCOORDSYSTEM_H
