#include "karchimedesspiral3d.h"

#include "KIntegral.h"

KArchimedesSpiral3D::KArchimedesSpiral3D() :
    r0_(0), t0_(0), z0_(0), dr_(0), dz_(0)
{

}

KArchimedesSpiral3D::KArchimedesSpiral3D(double r0, double t0, double z0,
                                         double dr, double dz) :
    r0_(r0), t0_(t0), z0_(z0), dr_(dr), dz_(dz)
{

}

KArchimedesSpiral3D::KArchimedesSpiral3D(double helix_angle, double radius) :
    r0_(radius), t0_(0), z0_(0), dr_(0)
{
    dz_ = isEqual(helix_angle, 90) ? 0 : radius / kTan2(helix_angle);
}

KArchimedesSpiral3D::KArchimedesSpiral3D(
        double helix_angle, double taper, double radius) :
    r0_(radius), t0_(0), z0_(0)
{
    dz_ = isEqual(helix_angle, 90) ? 0 : radius / kTan2(helix_angle);
    dr_ = dz_ * kTan2(taper);
}

KArchimedesSpiral3D::KArchimedesSpiral3D(const KVector3D &start, double helix_angle)
{
    z0_ = start.z();
    r0_ = start.distanceToZAxis();
    t0_ = kAtan2(start.y(), start.x());
    dr_ = 0;
    dz_ = isEqual(helix_angle, 90) ? 0 : r0_ / kTan2(helix_angle);
}

KArchimedesSpiral3D::KArchimedesSpiral3D(const KVector3D &p0, const KVector3D &p1)
{
    z0_ = p0.z();
    r0_ = p0.distanceToZAxis();
    t0_ = kAtan2(p0.y(), p0.x());

    double z1 = p1.z();
    double r1_ = p1.distanceToZAxis();
    double t1 = kAtan2(p1.y(), p1.x());
    double dt = t1 - t0_;
    dr_ = (r1_ - r0_) / dt;
    dz_ = (z1 - z0_) / dt;
}

void KArchimedesSpiral3D::setHelixAngle(double angle)
{
    dz_ = r0_ / kTan2(angle);
}

double KArchimedesSpiral3D::helixAngle() const
{
    return kRadiansToDegrees(kAtan(r0_ / dz_));
}

double KArchimedesSpiral3D::length(double lower, double upper) const
{
    if (isZero(dr_))
        return (upper - lower) * pythagoreanTheorem_Bevel(r0_, dz_);

    lower = r0_ + lower * dr_;
    upper = r0_ + upper * dr_;
    double a = pythagoreanTheorem_Bevel(dr_, dz_);
    return kIntegral8_1(a, lower, upper) / dr_;
}

KVector3D KArchimedesSpiral3D::pos(double dt) const
{
    double r = r0_ + dr_ * dt;
    double t = t0_ + dt;
    return KVector3D(r * kCos(t), r * kSin(t), dz_ * dt + z0_);
}

KVector3D KArchimedesSpiral3D::tangentVector(double dt) const
{
    double r = r0_ + dr_ * dt;
    double t = t0_ + dt;
    double cost = kCos(t);
    double sint = kSin(t);
    return KVector3D(dr_ * cost - r * sint, dr_ * sint + r * cost, dz_);
}

KArchimedesSpiral3D KArchimedesSpiral3D::rotated(double angle) const
{
    double radian = kDegreesToRadians(angle);
    return rotatedRadian(radian);
}

KArchimedesSpiral3D KArchimedesSpiral3D::rotatedRadian(double radian) const
{
    return KArchimedesSpiral3D(r0_, t0_ + radian, z0_, dr_, dz_);
}

double KArchimedesSpiral3D::helixAngleOfEqualLeadByRadius(double radius) const
{
    if (isZero(dz_))
        return 0;
    return kRadiansToDegrees(kAtan(radius / dz_));
}
