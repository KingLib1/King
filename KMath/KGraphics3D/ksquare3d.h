#ifndef KSQUARE3D_H
#define KSQUARE3D_H

#include "krectcoordsystem3d.h"
#include "KPair.h"
#include "ktriangle3d.h"

class KING_EXPORT KSquare3D
{
public:
    KSquare3D();
    KSquare3D(double side_length);
    KSquare3D(const KRectCoordSystem3D &sys, double side_length);

    inline void setCoordSys(const KRectCoordSystem3D &sys);
    inline void setCenter(const KVector3D &center);
    inline void setSideLength(double len);

    inline const KRectCoordSystem3D &coordSys() const;
    inline double sideLength() const;
    inline const KVector3D &center() const;
    KPair<KTriangle3D, KTriangle3D> triangles() const;

private:
    KRectCoordSystem3D sys_;
    double side_len_;
};

inline void KSquare3D::setCoordSys(const KRectCoordSystem3D &sys)
{
    sys_ = sys;
}

inline void KSquare3D::setCenter(const KVector3D &center)
{
    sys_.setOrigin(center);
}

inline void KSquare3D::setSideLength(double len)
{
    side_len_ = len;
}

inline const KRectCoordSystem3D &KSquare3D::coordSys() const
{
    return sys_;
}

inline double KSquare3D::sideLength() const
{
    return side_len_;
}

inline const KVector3D &KSquare3D::center() const
{
    return sys_.origin();
}

#endif // KSQUARE3D_H
