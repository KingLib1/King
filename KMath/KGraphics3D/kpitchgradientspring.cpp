#include "kpitchgradientspring.h"

#include "KIntegral.h"

KPitchGradientSpring::KPitchGradientSpring() :
    r1_(0), r2_(0), p1_(0), p2_(0), turns_(0), z0_(0), t0_(0)/*,
    dir_(SpiralDirection::Right)*/
{

}

KPitchGradientSpring::KPitchGradientSpring(double r1, double r2, double pitch1,
    double pitch2, double turns, double z0, double t0/*,
    SpiralDirection direction*/): r1_(r1), r2_(r2), p1_(pitch1),
    p2_(pitch2), turns_(turns), z0_(z0), t0_(t0)/*, dir_(direction)*/
{

}

double KPitchGradientSpring::zAt(double dt) const
{
    double kp = (p2_ - p1_) / totalRadian();
    return (kp * dt / 2 + p1_) * dt * K_1_2PI + z0_;
}

KVector3D KPitchGradientSpring::pos(double dt) const
{
    double total_rad = totalRadian();
    double r = r1_ + (r2_ - r1_) * dt / total_rad;
    double t = t0_ + dt;
    double kp = (p2_ - p1_) / total_rad;
    return KVector3D(r*kCos(t), r*kSin(t), (p1_ + kp*dt/2)*dt*K_1_2PI + z0_);
}

KVector3D KPitchGradientSpring::tangentVector(double dt) const
{
    double T = totalRadian();
    double kr = (r2_ - r1_) / T;
    double r = r1_ + kr * dt;
    double t = t0_ + dt;
    double cost = kCos(t);
    double sint = kSin(t);

    return KVector3D(kr*cost - r*sint, kr*sint + r*cost,
                     (p1_+ (p2_ - p1_) / T * dt) * K_1_2PI);
}

KPair<KVector3D, KVector3D> KPitchGradientSpring::posAndTan(double dt) const
{
    KPair<KVector3D, KVector3D> pair;

    double T = totalRadian();
    double kr = (r2_ - r1_) / T;
    double r = r1_ + kr * dt;
    double t = t0_ + dt;
    double kp = (p2_ - p1_) / T;
    double cost = kCos(t);
    double sint = kSin(t);
    double x = r*cost;
    double y = r*sint;
    pair.first.setXYZ(x, y, (p1_ + kp*dt/2) * dt * K_1_2PI + z0_);
    pair.second.setXYZ(kr*cost - y, kr*sint + x,
                       (p1_+ kp * dt) * K_1_2PI);

    return pair;
}

double KPitchGradientSpring::length() const
{
    double T = turns_ * K_2PI;
    double kr = (r2_ - r1_) / T;
    double kp = (p2_ - p1_) / T;
    double kz1 = p1_ / K_2PI;
    double kkz = kp / K_2PI;
    double kr2 = kr * kr;
    double a = kr2 + kkz * kkz;
    double b = (r1_ * kr + kz1 * kkz) * 2;
    double c = kr2 + r1_ * r1_ + kz1 * kz1;
    if (isZero(a))
        return kIntegral5_1(c, b, 0, T);
    double b_2a = b / (2 * a);
    return kSqrt(a)*kIntegral8_9(c/a - b_2a*b_2a, b_2a, T + b_2a);
}

QVector<KPair<KVector3D, KVector3D>> KPitchGradientSpring::split2(int slices)
{
    QVector<KPair<KVector3D, KVector3D>> pairs;

    double T = totalRadian();
    double kr = (r2_ - r1_) / T;
    double kp = (p2_ - p1_) / T;
    double per_t = T / slices;
    double per_r = (r2_ - r1_) / slices;
    double r = r1_;
    double dt = 0;
    KPair<KVector3D, KVector3D> pair;
    for (int i = 0; i <= slices; ++i) {
        double t = t0_ + dt;
        double cost = kCos(t);
        double sint = kSin(t);
        double x = r*cost;
        double y = r*sint;
        pair.first.setXYZ(x, y, (p1_ + kp*dt/2) * dt * K_1_2PI + z0_);
        pair.second.setXYZ(kr*cost - y, kr*sint + x,(p1_+ kp*dt) * K_1_2PI);
        pairs << pair;
        r += per_r;
        dt += per_t;
    }

    return pairs;
}

KBoundingVolume KPitchGradientSpring::boundingVolume() const
{
    double zmin;
    double zmax;
    double endz = z0_ + height();

    if ((p1_ >= 0 && p2_ >= 0) || (p1_ <= 0 && p2_ <= 0)) {
        kMinAndMax(z0_, endz, zmin, zmax);
    } else {
        double z = p1_ * p1_ * turns_ / (2 * (p1_ - p2_)) + z0_;
        kMinAndMax(z0_, endz, z, zmin, zmax);
    }

    double rmax = kMax(r1_, r2_);
    return KBoundingVolume(-rmax, -rmax, zmin, rmax, rmax, zmax);
}

KRange KPitchGradientSpring::zRange() const
{
    double zmin;
    double zmax;
    double endz = z0_ + height();

    if ((p1_ >= 0 && p2_ >= 0) || (p1_ <= 0 && p2_ <= 0)) {
        kMinAndMax(z0_, endz, zmin, zmax);
    } else {
        double z = p1_ * p1_ * turns_ / (2 * (p1_ - p2_)) + z0_;
        kMinAndMax(z0_, endz, z, zmin, zmax);
    }

    return KRange(zmin, zmax);
}
