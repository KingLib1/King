#include "ksphere.h"

#include "kspliter.h"

KSphere::KSphere()
{

}

KSphere::KSphere(const KVector3D &center, double radius) :
    center_(center), radius_(radius)
{

}

KSphere::KSphere(double radius) : radius_(radius)
{

}

KSphere::KSphere(const KSphere &sphere) :
    center_(sphere.center_), radius_(sphere.radius_)
{

}

KSphere::~KSphere()
{

}

KPair<double, double> KSphere::heightAt(double radius) const
{
    KPair<double, double> pair;
    double right = pythagoreanTheorem_Right(radius, radius_);
    pair.first = radius_ - right;
    pair.second = radius_ + right;
    return pair;
}

QVector<KVector3D> KSphere::blade(double lead, double dt) const
{
    double dz = lead / K_2PI;
    double t1 = radius_ * 2 / dz;

    KSpliter spliter;
    QVector<double> ts = spliter.split(0, t1, dt);

    QVector<KVector3D> poses;
    KVector3D dv = center_ - KVector3D(0, 0, radius_);
    for (int i = 0; i < ts.size(); ++i) {
        double z = ts.at(i) * dz;
        double radius = radiusAt(z);
        double x = radius * kCos(ts.at(i));
        double y = radius * kSin(ts.at(i));
        poses << KVector3D(x, y, z) + dv;
    }

    return poses;
}

QVector<KVector3D> KSphere::lowerHalfBlade(double lead, double dlen, QVector<double> &ts)
const
{
    ts.clear();

    double dz = lead / K_2PI;
    double t1 = radius_ / dz;
    double dt = 0.02;
    double t0 = 0;
    ts << t0;
    QVector<KVector3D> poses;
    KVector3D dv = center_ - KVector3D(0, 0, radius_);

    KVector3D pos;
    poses << pos + dv;
    while (t0 < t1) {
        double t = t0 + dt;
        if (t > t1) {
            t = t1;
            dt = t1 - t0;
        }
        double z = t * dz;
        double radius = radiusAt(z);
        KVector3D next(radius * kCos(t), radius * kSin(t), z);
        if (next.distanceToPoint(pos) > dlen) {
            dt /= 2;
            continue;
        }
        dt = 0.02;
        t0 = t;
        pos = next;
        ts << t;
        poses << next + dv;
    }

    return poses;
}

QVector<KVector3D> KSphere::bladeInRange(double lead, double dlen, double t0,
                                         double t1, QVector<double> &ts) const
{
    ts.clear();

    double dz = lead / K_2PI;
    double dt = 0.02;

    ts << t0;
    QVector<KVector3D> poses;
    KVector3D dv = center_ - KVector3D(0, 0, radius_);

    double z = t0 * dz;
    double radius = radiusAt(z);
    KVector3D pos(radius * kCos(t0), radius * kSin(t0), z);
    poses << pos + dv;
    while (t0 < t1) {
        double t = t0 + dt;
        if (t > t1) {
            t = t1;
            dt = t1 - t0;
        }
        z = t * dz;
        radius = radiusAt(z);
        KVector3D next(radius * kCos(t), radius * kSin(t), z);
        if (next.distanceToPoint(pos) > dlen) {
            dt /= 2;
            continue;
        }
        dt = 0.02;
        t0 = t;
        pos = next;
        ts << t;
        poses << next + dv;
    }

    return poses;
}

KVector3D KSphere::posOnBlade(double lead, double t) const
{
    double dz = lead / K_2PI;
    double z = t * dz;
    double radius = radiusAt(z);
    double x = radius * kCos(t);
    double y = radius * kSin(t);
    KVector3D pos(x, y, z);
    KVector3D dv = center_ - KVector3D(0, 0, radius_);
    return pos + dv;
}

KVector3D KSphere::tangentOnBlade(double lead, double t) const
{
    if (isZero(t)) {
        return KVector3D(1, 0, 0);
    }

    double dz = lead / K_2PI;
    double z = t * dz;
    double r_z = radius_ - z;
    double r = pythagoreanTheorem_Right(r_z, radius_);
    double a1 = r_z * dz / r;
    double cost = kCos(t);
    double sint = kSin(t);
    double dx = a1 * cost - r * sint;
    double dy = a1 * sint + r * cost;
    return KVector3D(dx, dy, dz);
}

KPair<KVector3D, KVector3D> KSphere::posAndTanOnBlade(double lead, double t) const
{
    KPair<KVector3D, KVector3D> pair;

    double dz = lead / K_2PI;
    double z = t * dz;
    double r_z = radius_ - z;
    double r = pythagoreanTheorem_Right(r_z, radius_);
    double cost = kCos(t);
    double sint = kSin(t);
    double x = r * cost;
    double y = r * sint;
    KVector3D pos(x, y, z);
    KVector3D dv = center_ - KVector3D(0, 0, radius_);
    pair.first = pos + dv;

    if (isZero(t)) {
        pair.second.setX(1);
        return pair;
    }
    double a1 = r_z * dz / r;
    double dx = a1 * cost - y;
    double dy = a1 * sint + x;
    pair.second.setXYZ(dx, dy, dz);

    return pair;
}
