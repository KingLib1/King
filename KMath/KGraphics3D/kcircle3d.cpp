#include "kcircle3d.h"

#include <math.h>

#include "KEquation.h"
#include "KGraphics2D/ktriangle.h"
#include "KGraphics2D/kquadratic.h"
#include "krange.h"

KCircle3D::KCircle3D(double radius) : radius_(radius)
{

}

KCircle3D::KCircle3D(const KCircle3D &circle) : sys_(circle.sys_),
    radius_(circle.radius_)
{

}

KCircle3D::KCircle3D(const KVector3D &center, double radius,
                     const KVector3D &normal) : radius_(radius)
{
    sys_.setOrigin(center);
    sys_.setZAxis(normal);
}

KCircle3D::KCircle3D(double radius, const KRectCoordSystem3D &sys) :
    sys_(sys), radius_(radius)
{

}

KVector3D KCircle3D::pos(double radian) const
{
    return (xAxis() * kCos(radian) + yAxis() * kSin(radian)) * radius_ + center();
}

bool KCircle3D::intersects(const KRay3D &ray) const
{
    double t = KVector3D::dotProduct(center() - ray.origin(), normal()) /
            KVector3D::dotProduct(ray.direction(), normal());
    if (t < 0 || (ray.length() > 0 && t > ray.length()))
        return false;
    KVector3D intersection = ray.origin() + ray.direction() * t;
    return intersection.distanceSquaredToPoint(center()) <= kSquare(radius_);
}

bool KCircle3D::intersects(const KCircle3D &c) const
{
    KVector3D l = KVector3D::crossProduct(normal(), c.normal());
    KVector3D p1;

    if (!isZero(l.x())) {
        double d1 = KVector3D::dotProduct(center(), normal());
        double d2 = KVector3D::dotProduct(c.center(), c.normal());
        KVector2D v1(normal().y(), c.normal().y());
        KVector2D v2(normal().z(), c.normal().z());
        KVector2D v3(d1, d2);
        KVector2D yz = solveHomogeneousLinearEquations2x2(v1, v2, v3);
        p1.setY(yz.x());
        p1.setZ(yz.y());
    } else if (!isZero(l.y())) {
        double d1 = KVector3D::dotProduct(center(), normal());
        double d2 = KVector3D::dotProduct(c.center(), c.normal());
        KVector2D v1(normal().x(), c.normal().x());
        KVector2D v2(normal().z(), c.normal().z());
        KVector2D v3(d1, d2);
        KVector2D xz = solveHomogeneousLinearEquations2x2(v1, v2, v3);
        p1.setX(xz.x());
        p1.setZ(xz.y());
    } else if (!isZero(l.z())) {
        double d1 = KVector3D::dotProduct(center(), normal());
        double d2 = KVector3D::dotProduct(c.center(), c.normal());
        KVector2D v1(normal().x(), c.normal().x());
        KVector2D v2(normal().y(), c.normal().y());
        KVector2D v3(d1, d2);
        KVector2D xy = solveHomogeneousLinearEquations2x2(v1, v2, v3);
        p1.setX(xy.x());
        p1.setY(xy.y());
    } else {
        KPlane3D plane1(center(), normal());
        if (plane1.contains(c.center())) {
            double dissq = center().distanceSquaredToPoint(c.center());
            double rsq = kSquare(radius() + c.radius());
            if (dissq > rsq)
                return false;
            return true;
        }
        return false;
    }

    KLineSegment3D line(p1, p1 + l);
    if (line.distanceSquaredFromPoint(center()) > kSquare(radius_) ||
            line.distanceSquaredFromPoint(c.center()) > kSquare(c.radius_))
        return false;

    KVector3D rp = p1 - center();
    KQuadratic q(l.lengthSquared(), 2 * KVector3D::dotProduct(l, rp),
                 rp.lengthSquared() - kSquare(radius_));
    KPair<double, double> root1 = q.root();

    rp = p1 - c.center();
    q.setB(2 * KVector3D::dotProduct(l, rp));
    q.setC(rp.lengthSquared() - kSquare(c.radius_));
    KPair<double, double> root2 = q.root();

    if (root1.second < root2.first || root1.first > root2.second)
        return false;
    return true;
}

KVector3D KCircle3D::intersected(const KRay3D &ray, bool &intersects) const
{
    double t = KVector3D::dotProduct(center() - ray.origin(), normal()) /
            KVector3D::dotProduct(ray.direction(), normal());
    if (t < 0 || (ray.length() > 0 && t > ray.length())) {
        intersects = false;
        return KVector3D();
    }
    KVector3D p = ray.origin() + ray.direction() * t;
    intersects = p.distanceSquaredToPoint(center()) <= kSquare(radius_);
    if (intersects)
        return p;
    return KVector3D();
}

KLineSegment3D KCircle3D::intersected(const KCircle3D &c, bool *success) const
{
    KVector3D l = KVector3D::crossProduct(normal(), c.normal());
    KVector3D p1;

    if (!isZero(l.x())) {
        double d1 = KVector3D::dotProduct(center(), normal());
        double d2 = KVector3D::dotProduct(c.center(), c.normal());
        KVector2D v1(normal().y(), c.normal().y());
        KVector2D v2(normal().z(), c.normal().z());
        KVector2D v3(d1, d2);
        KVector2D yz = solveHomogeneousLinearEquations2x2(v1, v2, v3);
        p1.setY(yz.x());
        p1.setZ(yz.y());
    } else if (!isZero(l.y())) {
        double d1 = KVector3D::dotProduct(center(), normal());
        double d2 = KVector3D::dotProduct(c.center(), c.normal());
        KVector2D v1(normal().x(), c.normal().x());
        KVector2D v2(normal().z(), c.normal().z());
        KVector2D v3(d1, d2);
        KVector2D xz = solveHomogeneousLinearEquations2x2(v1, v2, v3);
        p1.setX(xz.x());
        p1.setZ(xz.y());
    } else if (!isZero(l.z())) {
        double d1 = KVector3D::dotProduct(center(), normal());
        double d2 = KVector3D::dotProduct(c.center(), c.normal());
        KVector2D v1(normal().x(), c.normal().x());
        KVector2D v2(normal().y(), c.normal().y());
        KVector2D v3(d1, d2);
        KVector2D xy = solveHomogeneousLinearEquations2x2(v1, v2, v3);
        p1.setX(xy.x());
        p1.setY(xy.y());
    } else {
        KPlane3D plane1(center(), normal());
        if (plane1.contains(c.center())) {
            double dissq = center().distanceSquaredToPoint(c.center());
            double rsq = kSquare(radius() + c.radius());
            if (dissq > rsq) {
                if (success)
                    *success = false;
                return KLineSegment3D();
            }
            if (success)
                *success = true;
            if (dissq <= kSquare(radius_ - c.radius_))
                return KLineSegment3D();
            KVector3D cv = c.center() - center();
            KVector3D v1 = KVector3D::crossProduct(normal(), cv);
            v1.normalize();
            cv.normalize();
            KTriangle t(radius_, c.radius_, kSqrt(dissq));
            double cosb = t.cosB();
            double sinb = kSqrt(1 - cosb * cosb);
            double len = t.a() * cosb;
            KVector3D m = center() + len * cv;
            len = t.a() * sinb;
            v1 *= len;
            return KLineSegment3D(m + v1, m - v1);
        } else {
            if (success)
                *success = false;
            return KLineSegment3D();
        }
    }

    KLineSegment3D line(p1, p1 + l);
    if (line.distanceSquaredFromPoint(center()) > kSquare(radius_) ||
            line.distanceSquaredFromPoint(c.center()) > kSquare(c.radius_)) {
        if (success)
            *success = false;
        return KLineSegment3D();
    }

    KVector3D rp = p1 - center();
    KQuadratic q(l.lengthSquared(), 2 * KVector3D::dotProduct(l, rp),
                 rp.lengthSquared() - kSquare(radius_));
    KPair<double, double> root1 = q.root();

    rp = p1 - c.center();
    q.setB(2 * KVector3D::dotProduct(l, rp));
    q.setC(rp.lengthSquared() - kSquare(c.radius_));
    KPair<double, double> root2 = q.root();

    if (root1.second < root2.first || root1.first > root2.second) {
        if (success)
            *success = false;
        return KLineSegment3D();
    }

    if (success)
        *success = true;
    KRange range1(root1.first, root1.second);
    KRange range2(root2.first, root2.second);
    KRange range12 = range1.intersected(range2);
    return KLineSegment3D(p1 + l * range12.lower(), p1 + l * range12.upper());
}

KLineSegment3D KCircle3D::intersected(const KPlane3D &plane, bool *success) const
{
    KVector3D l = KVector3D::crossProduct(normal(), plane.normal());
    KVector3D p1;

    if (!isZero(l.x())) {
        double d1 = KVector3D::dotProduct(center(), normal());
        double d2 = plane.directedDistanceFromOrigin();
        KVector2D v1(normal().y(), plane.normal().y());
        KVector2D v2(normal().z(), plane.normal().z());
        KVector2D v3(d1, d2);
        KVector2D yz = solveHomogeneousLinearEquations2x2(v1, v2, v3);
        p1.setY(yz.x());
        p1.setZ(yz.y());
    } else if (!isZero(l.y())) {
        double d1 = KVector3D::dotProduct(center(), normal());
        double d2 = plane.directedDistanceFromOrigin();
        KVector2D v1(normal().x(), plane.normal().x());
        KVector2D v2(normal().z(), plane.normal().z());
        KVector2D v3(d1, d2);
        KVector2D xz = solveHomogeneousLinearEquations2x2(v1, v2, v3);
        p1.setX(xz.x());
        p1.setZ(xz.y());
    } else if (!isZero(l.z())) {
        double d1 = KVector3D::dotProduct(center(), normal());
        double d2 = plane.directedDistanceFromOrigin();
        KVector2D v1(normal().x(), plane.normal().x());
        KVector2D v2(normal().y(), plane.normal().y());
        KVector2D v3(d1, d2);
        KVector2D xy = solveHomogeneousLinearEquations2x2(v1, v2, v3);
        p1.setX(xy.x());
        p1.setY(xy.y());
    } else {
        if (success)
            *success = false;
        return KLineSegment3D();
    }

    KLineSegment3D line(p1, p1 + l);
    if (line.distanceSquaredFromPoint(center()) > kSquare(radius_)) {
        if (success)
            *success = false;
        return KLineSegment3D();
    }

    KVector3D rp = p1 - center();
    KQuadratic q(l.lengthSquared(), 2 * KVector3D::dotProduct(l, rp),
                 rp.lengthSquared() - kSquare(radius_));
    KPair<double, double> root = q.root();

    if (success)
        *success = true;
    return KLineSegment3D(p1 + l * root.first, p1 + l * root.second);
}

KPair<KCircle3D, KCircle3D> KCircle3D::circleFrom(
        const KVector3D &normal, const KVector3D &p1, const KVector3D &p2,
        double radius)
{
    KVector3D v12 = p2 - p1;
    KVector3D po = KVector3D::crossProduct(normal, v12);
    KVector3D p = KVector3D::midpoint(p1, p2);
    double p1p_len = p1.distanceToPoint(p);
    double po_len = pythagoreanTheorem_Right(p1p_len, radius);
    po.setLength(po_len);
    return KPair<KCircle3D, KCircle3D>(KCircle3D(p + po, radius, normal),
                                       KCircle3D(p - po, radius, normal));
}
