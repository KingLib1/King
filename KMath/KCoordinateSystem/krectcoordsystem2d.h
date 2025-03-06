#ifndef KRECTCOORDSYSTEM2D_H
#define KRECTCOORDSYSTEM2D_H

#include "kvector2d.h"
#include "King.h"

class KING_EXPORT KRectCoordSystem2D
{
public:
    KRectCoordSystem2D();
    KRectCoordSystem2D(const KVector2D &xaxis,
                       King::CoordinateAxisType type  = King::XAxis);
    KRectCoordSystem2D(const KVector2D &origin, const KVector2D &xaxis,
                       King::CoordinateAxisType type  = King::XAxis);

    inline void setOrigin(const KVector2D &origin);
    inline void setXAxis(const KVector2D &xaxis);
    inline void setYAxis(const KVector2D &yaxis);
    inline void translate(const KVector2D &dv);
    KVector2D mapFromBase(const KVector2D &p) const;
    KVector2D mapToBase(const KVector2D &p) const;

    inline const KVector2D &origin() const;
    inline const KVector2D &xAxis() const;
    inline const KVector2D &yAxis() const;

    inline KRectCoordSystem2D &operator=(const KRectCoordSystem2D &other);

private:
    KVector2D origin_;
    KVector2D xaxis_;
    KVector2D yaxis_;
};

inline void KRectCoordSystem2D::setOrigin(const KVector2D &origin)
{
    origin_ = origin;
}

inline void KRectCoordSystem2D::setXAxis(const KVector2D &xaxis)
{
    xaxis_ = xaxis.normalized();
    yaxis_ = xaxis_.rotated90();
}

inline void KRectCoordSystem2D::setYAxis(const KVector2D &yaxis)
{
    yaxis_ = yaxis.normalized();
    xaxis_ = yaxis_.rotatedNeg90();
}

inline void KRectCoordSystem2D::translate(const KVector2D &dv)
{
    origin_ += dv;
}

inline const KVector2D &KRectCoordSystem2D::origin() const
{
    return origin_;
}

inline const KVector2D &KRectCoordSystem2D::xAxis() const
{
    return xaxis_;
}

inline const KVector2D &KRectCoordSystem2D::yAxis() const
{
    return yaxis_;
}

inline KRectCoordSystem2D &KRectCoordSystem2D::operator=(
        const KRectCoordSystem2D &other)
{
    origin_ = other.origin_;
    xaxis_ = other.xaxis_;
    yaxis_ = other.yaxis_;
    return *this;
}

#endif // KRECTCOORDSYSTEM2D_H
