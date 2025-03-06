#include "kcylinder.h"

#include "kspliter.h"

KCylinder::KCylinder() : radius_(0), height_(0)
{

}

KCylinder::KCylinder(const KCylinder &cylinder) : radius_(cylinder.radius_),
    height_(cylinder.height_), sys_(cylinder.sys_)
{

}

KCylinder::KCylinder(double radius, double height) : radius_(radius),
    height_(height)
{

}

KCylinder::KCylinder(double radius, double height,
                     const KRectCoordSystem3D &sys) : radius_(radius),
    height_(height), sys_(sys)
{

}

KCylinder::~KCylinder()
{

}

bool KCylinder::intersects(const KRay3D &ray) const
{
    double l1l2 = KVector3D::dotProduct(zAxis(), ray.direction());
    double half_height = height_ / 2;
    double r2 = kSquare(radius_);
    // 如果z轴和ray平行
    if (kFabs(kFabs(l1l2) - 1) < EPS9) {
        KVector3D pp1 = center() - ray.origin();
        KVector3D pp2 = pp1 + zAxis();
        double diss = KVector3D::crossProduct(pp1, pp2).lengthSquared();
        if (diss > r2)
            return false;
        KVector3D d = zAxis() * half_height;
        KVector3D center1 = center() + d;
        // 射线不是无限延伸
        if (ray.length() > 0) {
            KVector3D end = ray.end();
            if (KVector3D::dotProduct(ray.origin() - center1, zAxis()) > 0 &&
                    KVector3D::dotProduct(end - center1, zAxis()) > 0)
                return false;
            center1 = center() - d;
            if (KVector3D::dotProduct(center1 - ray.origin(), zAxis()) > 0 &&
                    KVector3D::dotProduct(center1 - end, zAxis()) > 0)
                return false;
            return true;
        }

        // 射线无限延伸
        double t = KVector3D::dotProduct(center1 - ray.origin(), zAxis()) / l1l2;
        if (t >= 0)
            return true;
        center1 = center() - d;
        t = KVector3D::dotProduct(center1 - ray.origin(), zAxis()) / l1l2;
        if (t >= 0)
            return true;
        return false;
    }

    // z轴与ray不平行
    KVector3D oc = center() - ray.origin();
    double ocl1 = KVector3D::dotProduct(oc, zAxis());
    double ocl2 = KVector3D::dotProduct(oc, ray.direction());
    double D = l1l2 * l1l2 - 1;
    double D1 = ocl1 - ocl2 * l1l2;
    double D2 = ocl1 * l1l2 - ocl2;
    double t1 = D1 / D;
    double t2 = D2 / D;
    KVector3D p1 = center() + zAxis() * t1;
    KVector3D p2 = ray.origin() + ray.direction() * t2;
    if (p1.distanceSquaredToPoint(p2) > r2)
        return false;

    if (t1 > half_height) {
        KVector3D center1 = center() + zAxis() * half_height;
        double t = KVector3D::dotProduct(center1 - ray.origin(), zAxis()) /
                l1l2;
        if (t < 0 || (ray.length() > 0 && t > ray.length()))
            return false;
        KVector3D intersection = ray.origin() + ray.direction() * t;
        return intersection.distanceSquaredToPoint(center1) <= r2;
    }

    if (t1 < -half_height) {
        KVector3D center1 = center() - zAxis() * half_height;
        double t = KVector3D::dotProduct(center1 - ray.origin(), zAxis()) /
                l1l2;
        if (t < 0 || (ray.length() > 0 && t > ray.length()))
            return false;
        KVector3D intersection = ray.origin() + ray.direction() * t;
        return intersection.distanceSquaredToPoint(center1) <= r2;
    }

    if (t2 < 0) {
        KVector3D pp1 = center() - ray.origin();
        KVector3D pp2 = pp1 + zAxis();
        if (KVector3D::crossProduct(pp1, pp2).lengthSquared() <= r2)
            return true;
        return false;
    }

    if (ray.length() > 0) {
        if (t2 <= ray.length())
            return true;
        KVector3D end = ray.end();
        KVector3D pp1 = center() - end;
        KVector3D pp2 = pp1 + zAxis();
        if (KVector3D::crossProduct(pp1, pp2).lengthSquared() <= r2)
            return true;
        return false;
    }

    if (t2 >= 0)
        return true;
    return false;
}

KCircle3D KCylinder::bottomCircle() const
{
    KRectCoordSystem3D sys = sys_;
    sys.setOrigin(bottomCenter());
    return KCircle3D(radius_, sys);
}

KCircle3D KCylinder::topCircle() const
{
    KRectCoordSystem3D sys = sys_;
    sys.setOrigin(topCenter());
    return KCircle3D(radius_, sys);
}

KPair<QVector<KVector3D>, QVector<KVector3D>> KCylinder::triangleStrip(int slices) const
{
    KPair<QVector<KVector3D>, QVector<KVector3D>> pair;
    KCircle3D circle1 = bottomCircle();
    KSpliter spliter;
    QVector<KVector3D> points1 = spliter.split(circle1, slices);
    KVector3D dv = sys_.zAxis() * height_;
    QVector<KVector3D> points2;
    for (int i = 0; i < points1.size(); ++i) {
        points2 << points1.at(i) + dv;
    }

    KVector3D normal;
    for (int i = 0; i < points1.size(); ++i) {
        pair.first << points1.at(i) << points2.at(i);
        pair.second << points1.at(i) - circle1.center();
        pair.second << pair.second.last();
    }
    pair.first << points1.at(0) << points2.at(0);
    pair.second << pair.second.first() << pair.second.first();

    return pair;
}
