#include "kplane3d_2.h"

#include "kvector2d.h"
#include "KEquation.h"

KPlane3D_2::KPlane3D_2(): d_(0)
{
    n_.setZ(1);
}

KPlane3D_2::KPlane3D_2(const KVector3D &point, const KVector3D &normal) :
    n_(normal), d_(KVector3D::dotProduct(point, normal))
{

}

KPlane3D_2::KPlane3D_2(const KVector3D &normal, double d) :
    n_(normal), d_(d)
{

}

KLine3D KPlane3D_2::intersected(const KPlane3D_2 &plane) const
{
    KVector3D l = KVector3D::crossProduct(n_, plane.n_);
    double fabx = kFabs(l.x());
    double faby = kFabs(l.y());
    double fabz = kFabs(l.z());
    if (fabx < EPS6 && faby < EPS6 && fabz < EPS6)
        return KLine3D();

    KVector3D intersection;
    if (fabx > faby && fabx > fabz) {
        KVector2D v1(n_.y(), plane.n_.y());
        KVector2D v2(n_.z(), plane.n_.z());
        KVector2D v3(d_, plane.d_);
        KVector2D yz = solveHomogeneousLinearEquations2x2(v1, v2, v3);
        intersection.setY(yz.x());
        intersection.setZ(yz.y());
    } else if (faby > fabz) {
        KVector2D v1(n_.x(), plane.n_.x());
        KVector2D v2(n_.z(), plane.n_.z());
        KVector2D v3(d_, plane.d_);
        KVector2D xz = solveHomogeneousLinearEquations2x2(v1, v2, v3);
        intersection.setX(xz.x());
        intersection.setZ(xz.y());
    } else {
        KVector2D v1(n_.x(), plane.n_.x());
        KVector2D v2(n_.y(), plane.n_.y());
        KVector2D v3(d_, plane.d_);
        KVector2D xy = solveHomogeneousLinearEquations2x2(v1, v2, v3);
        intersection.setX(xy.x());
        intersection.setY(xy.y());
    }
    return KLine3D(intersection, l, KLine3D::Point_Direction);
}
