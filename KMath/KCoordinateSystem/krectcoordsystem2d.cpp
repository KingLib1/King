#include "krectcoordsystem2d.h"

KRectCoordSystem2D::KRectCoordSystem2D() : xaxis_(1, 0), yaxis_(0, 1)
{

}

KRectCoordSystem2D::KRectCoordSystem2D(const KVector2D &axis,
                                       King::CoordinateAxisType type)
{
    if (type == King::XAxis) {
        xaxis_ = axis.normalized();
        yaxis_ = xaxis_.rotated90();
    } else {
        yaxis_ = axis.normalized();
        xaxis_ = yaxis_.rotatedNeg90();
    }
}

KRectCoordSystem2D::KRectCoordSystem2D(
        const KVector2D &origin, const KVector2D &axis,
        King::CoordinateAxisType type) : origin_(origin)
{
    if (type == King::XAxis) {
        xaxis_ = axis.normalized();
        yaxis_ = xaxis_.rotated90();
    } else {
        yaxis_ = axis.normalized();
        xaxis_ = yaxis_.rotatedNeg90();
    }
}

KVector2D KRectCoordSystem2D::mapFromBase(const KVector2D &p) const
{
    KVector2D op = p - origin_;
    return KVector2D(xaxis_.x()*op.x() + xaxis_.y()*op.y(),
                     yaxis_.x()*op.x() + yaxis_.y()*op.y());
}

KVector2D KRectCoordSystem2D::mapToBase(const KVector2D &p) const
{
    return xaxis_*p.x() + yaxis_*p.y() + origin_;
}
