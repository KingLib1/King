#include "kplane3d.h"

#include "KEquation.h"

KPlane3D::KPlane3D(): d_(0)
{
    n_.setZ(1);
}

KPlane3D::KPlane3D(const KVector3D &point, const KVector3D &normal) : n_(normal)
{
    n_.normalize();
    d_ = KVector3D::dotProduct(point, n_);
}

KPlane3D::KPlane3D(const KVector3D &p1, const KVector3D &p2, const KVector3D &p3)
    : n_(KVector3D::crossProduct(p2 - p1, p3 - p1))
{
    n_.normalize();
    d_ = KVector3D::dotProduct(p1, n_);
}

KPlane3D::KPlane3D(const KVector3D &normal, double d) :
    n_(normal.normalized()), d_(d)
{

}

KPlane3D::KPlane3D(const KPlane3D &plane) : n_(plane.n_), d_(plane.d_)
{

}

KPlane3D::~KPlane3D()
{

}

int KPlane3D::whichSide(const KVector3D &point) const
{
    double dis = directedDistanceFromPoint(point);
    if (dis > EPS6)
        return 1;
    if (dis < -EPS6)
        return -1;
    return 0;
}

KVector3D KPlane3D::intersection(const KLineSegment3D &line, bool &intersect)
const
{
    KVector3D l = line.toVector();
    double l_n = KVector3D::dotProduct(l, n_);
    if (kFabs(l_n) < EPS9) {
        if (contains(line.p1())) {
            intersect = true;
            return line.p1();
        } else {
            intersect = false;
            return KVector3D();
        }
    }
    double t = (d_ - KVector3D::dotProduct(line.p1(), n_)) / l_n;
    if (t >= 0 && t <= 1) {
        intersect = true;
        return line.p1() + l * t;
    }
    intersect = false;
    return KVector3D();
}

KVector3D KPlane3D::intersection(const KLine3D &line, bool *success) const
{
    auto &l = line.direction();
    double l_n = KVector3D::dotProduct(l, n_);
    if (kFabs(l_n) < EPS9) {
        if (contains(line.point())) {
            if (success)
                *success = true;
            return line.point();
        } else {
            if (success)
                *success = false;
            return KVector3D();
        }
    }

    double t = (d_ - KVector3D::dotProduct(line.point(), n_)) / l_n;
    if (success)
        *success = true;
    return line.point() + l * t;
}

KLine3D KPlane3D::intersected(const KPlane3D &plane) const
{
    KVector3D l = KVector3D::crossProduct(n_, plane.n_);
    double fabx = kFabs(l.x());
    double faby = kFabs(l.y());
    double fabz = kFabs(l.z());
    if (fabx < EPS9 && faby < EPS9 && fabz < EPS9)
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

bool KPlane3D::intersects(const KRay3D &ray) const
{
    double dot = KVector3D::dotProduct(ray.direction(), n_);
    if (kFabs(dot) < EPS9)
        return contains(ray.origin());

    double t = (d_ - KVector3D::dotProduct(n_, ray.origin())) / dot;
    if (t < 0 || (ray.length() > 0 && t > ray.length()))
        return false;
    return true;
}
