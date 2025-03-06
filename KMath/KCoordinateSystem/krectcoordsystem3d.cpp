#include "krectcoordsystem3d.h"

#include <QDebug>

KRectCoordSystem3D::KRectCoordSystem3D()
{
    initAxis();
}

KRectCoordSystem3D::KRectCoordSystem3D(const KVector3D &xaxis,
                                       const KVector3D &yaxis)
{
    if (kFabs(KVector3D::dotProduct(xaxis, yaxis)) > EPS9) {
        initAxis();
        return;
    }
    xaxis_ = xaxis;
    yaxis_ = yaxis;
    xaxis_.normalize();
    yaxis_.normalize();
    zaxis_ = KVector3D::crossProduct(xaxis_, yaxis_);
}

KRectCoordSystem3D::KRectCoordSystem3D(
        const KRectCoordSystem3D &sys) : origin_(sys.origin_),
    xaxis_(sys.xaxis_), yaxis_(sys.yaxis_), zaxis_(sys.zaxis_)
{

}

KRectCoordSystem3D::KRectCoordSystem3D(
        const KVector3D &origin, const KVector3D &axis1, const KVector3D &axis2,
        King::CoordinateSystemAxisCreatMode mode) : origin_(origin)
{
    if (mode == King::XY_Axis) {
        if (setXYAxis(axis1, axis2))
            return;
    } else if (mode == King::YZ_Axis) {
        if (setYZAxis(axis1, axis2))
            return;
    } else if (mode == King::ZX_Axis) {
        if (setZXAxis(axis1, axis2))
            return;
    }
    initAxis();
}

KRectCoordSystem3D::KRectCoordSystem3D(const KMatrix3x3 &matrix)
{
    xaxis_ = matrix.xAxis();
    yaxis_ = matrix.yAxis();
    zaxis_ = matrix.zAxis();
}

KRectCoordSystem3D::KRectCoordSystem3D(const KMatrix4x4 &matrix)
{
    xaxis_ = matrix.xAxis();
    yaxis_ = matrix.yAxis();
    zaxis_ = matrix.zAxis();
    origin_ = matrix.translation();
}

KRectCoordSystem3D::KRectCoordSystem3D(const KVector3D &axis,
                                       King::CoordinateAxisType type)
{
    if (!RandomCreateCoordinateSystem(axis, type))
        initAxis();
}

KRectCoordSystem3D::~KRectCoordSystem3D()
{

}

bool KRectCoordSystem3D::setXYAxis(const KVector3D &xaxis,
                                        const KVector3D &yaxis)
{
    if (kFabs(KVector3D::dotProduct(xaxis, yaxis)) > EPS3)
        return false;

    xaxis_ = xaxis;
    yaxis_ = yaxis;
    xaxis_.normalize();
    yaxis_.normalize();
    zaxis_ = KVector3D::crossProduct(xaxis_, yaxis_);
    return true;
}

bool KRectCoordSystem3D::setYZAxis(const KVector3D &yaxis,
                                   const KVector3D &zaxis)
{
    if (kFabs(KVector3D::dotProduct(yaxis, zaxis)) > EPS3)
        return false;

    yaxis_ = yaxis;
    zaxis_ = zaxis;
    yaxis_.normalize();
    zaxis_.normalize();
    xaxis_ = KVector3D::crossProduct(yaxis_, zaxis_);
    return true;
}

bool KRectCoordSystem3D::setZXAxis(const KVector3D &zaxis,
                                   const KVector3D &xaxis)
{
    if (kFabs(KVector3D::dotProduct(zaxis, xaxis)) > EPS3)
        return false;

    zaxis_ = zaxis;
    xaxis_ = xaxis;
    zaxis_.normalize();
    xaxis_.normalize();
    yaxis_ = KVector3D::crossProduct(zaxis_, xaxis_);
    return true;
}

void KRectCoordSystem3D::rotateXByBase(double angle)
{
    double radian = kDegreesToRadians(angle);
    double sina = kSin(radian);
    double cosa = kCos(radian);
    double temp = xaxis_.y();
    xaxis_.setY(temp * cosa - xaxis_.z() * sina);
    xaxis_.setZ(temp * sina + xaxis_.z() * cosa);
    temp = yaxis_.y();
    yaxis_.setY(temp * cosa - yaxis_.z() * sina);
    yaxis_.setZ(temp * sina + yaxis_.z() * cosa);
    temp = zaxis_.y();
    zaxis_.setY(temp * cosa - zaxis_.z() * sina);
    zaxis_.setZ(temp * sina + zaxis_.z() * cosa);
    temp = origin_.y();
    origin_.setY(temp * cosa - origin_.z() * sina);
    origin_.setZ(temp * sina + origin_.z() * cosa);
}

void KRectCoordSystem3D::rotateYBySelf(double angle)
{
    double r = kDegreesToRadians(angle);
    double cosr = kCos(r);
    double sinr = kSin(r);
    KVector3D zaxis(zaxis_);
    zaxis_ = zaxis * cosr + xaxis_ * sinr;
    xaxis_ = xaxis_ * cosr - zaxis * sinr;
}

void KRectCoordSystem3D::rotateYByBase(double angle)
{
    double radian = kDegreesToRadians(angle);
    double sina = kSin(radian);
    double cosa = kCos(radian);
    double temp = xaxis_.x();
    xaxis_.setX(temp * cosa + xaxis_.z() * sina);
    xaxis_.setZ(xaxis_.z() * cosa - temp * sina);
    temp = yaxis_.x();
    yaxis_.setX(temp * cosa + yaxis_.z() * sina);
    yaxis_.setZ(yaxis_.z() * cosa - temp * sina);
    temp = zaxis_.x();
    zaxis_.setX(temp * cosa + zaxis_.z() * sina);
    zaxis_.setZ(zaxis_.z() * cosa - temp * sina);
    temp = origin_.x();
    origin_.setX(temp * cosa + origin_.z() * sina);
    origin_.setZ(origin_.z() * cosa - temp * sina);
}

void KRectCoordSystem3D::rotateZBySelf(double angle)
{
    double r = kDegreesToRadians(angle);
    double cosr = kCos(r);
    double sinr = kSin(r);
    KVector3D xaxis(xaxis_);
    xaxis_ = xaxis * cosr + yaxis_ * sinr;
    yaxis_ = yaxis_ * cosr - xaxis * sinr;
}

void KRectCoordSystem3D::rotateZRadianByBase(double radian)
{
    double sina = kSin(radian);
    double cosa = kCos(radian);
    double temp = xaxis_.x();
    xaxis_.setX(temp * cosa - xaxis_.y() * sina);
    xaxis_.setY(temp * sina + xaxis_.y() * cosa);
    temp = yaxis_.x();
    yaxis_.setX(temp * cosa - yaxis_.y() * sina);
    yaxis_.setY(temp * sina + yaxis_.y() * cosa);
    temp = zaxis_.x();
    zaxis_.setX(temp * cosa - zaxis_.y() * sina);
    zaxis_.setY(temp * sina + zaxis_.y() * cosa);
    temp = origin_.x();
    origin_.setX(temp * cosa - origin_.y() * sina);
    origin_.setY(temp * sina + origin_.y() * cosa);
}

KVector3D KRectCoordSystem3D::mapFromBase(const KVector3D &point) const
{
    KVector3D xt(xaxis_.x(), yaxis_.x(), zaxis_.x());
    KVector3D yt(xaxis_.y(), yaxis_.y(), zaxis_.y());
    KVector3D zt(xaxis_.z(), yaxis_.z(), zaxis_.z());
    KVector3D tp = point - origin_;
    return xt * tp.x() + yt * tp.y() + zt * tp.z();
}

KRectCoordSystem3D KRectCoordSystem3D::fromThreePoints(
        const KVector3D &p1, const KVector3D &p2, const KVector3D &p3)
{
    KRectCoordSystem3D sys;
    sys.origin_ = p1;
    sys.xaxis_ = p2 - p1;
    sys.yaxis_ = p3 - p1;
    sys.zaxis_ = KVector3D::crossProduct(sys.xaxis_, sys.yaxis_);
    sys.xaxis_.normalize();
    sys.zaxis_.normalize();
    sys.yaxis_ = KVector3D::crossProduct(sys.zaxis_, sys.xaxis_);
    return sys;
}

bool KRectCoordSystem3D::RandomCreateCoordinateSystem(
        const KVector3D &axis, King::CoordinateAxisType type)
{
    double x1, y1;
    if (kFabs(axis.x()) < EPS6) {
        if (kFabs(axis.y()) < EPS6) {
            if (kFabs(axis.z()) < EPS6)
                return false;
        }
        x1 = 1;
        y1 = 0;
    } else {
        if (kFabs(axis.y()) < EPS9) {
            x1 = 0;
            y1 = 1;
        } else {
            x1 = 1;
            y1 = -axis.x() * x1 / axis.y();
        }
    }
    double z1 = 0;
    if (type == King::ZAxis) {
        zaxis_ = axis;
        zaxis_.normalize();
        xaxis_.setXYZ(x1, y1, z1);
        xaxis_.normalize();
        yaxis_ = KVector3D::crossProduct(zaxis_, xaxis_);
    } else if (type == King::XAxis) {
        xaxis_ = axis;
        xaxis_.normalize();
        yaxis_.setXYZ(x1, y1, z1);
        yaxis_.normalize();
        zaxis_ = KVector3D::crossProduct(xaxis_, yaxis_);
    } else if (type == King::YAxis) {
        yaxis_ = axis;
        yaxis_.normalize();
        zaxis_.setXYZ(x1, y1, z1);
        zaxis_.normalize();
        xaxis_ = KVector3D::crossProduct(yaxis_, zaxis_);
    }
    return true;
}
