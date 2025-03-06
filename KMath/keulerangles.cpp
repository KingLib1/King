#include "keulerangles.h"

KEulerAngles::KEulerAngles()
{

}

KEulerAngles::KEulerAngles(double rx, double ry, double rz)
{
    euler_.setXYZ(rx, ry, rz);
}

KEulerAngles::KEulerAngles(const KVector3D &euler) : euler_(euler)
{

}

KEulerAngles::KEulerAngles(const KMatrix3x3 &matrix)
{
    euler_.setXYZ(kRadiansToDegrees(kAtan2(matrix.m32(), matrix.m33())),
                  kRadiansToDegrees(kAsin(-matrix.m31())),
                  kRadiansToDegrees(kAtan2(matrix.m21(), matrix.m11())));
}

KEulerAngles::KEulerAngles(const KVector3D &xaxis, const KVector3D &yaxis,
                           const KVector3D &zaxis)
{
    euler_.setXYZ(kRadiansToDegrees(kAtan2(yaxis.z(), zaxis.z())),
                  kRadiansToDegrees(kAsin(-xaxis.z())),
                  kRadiansToDegrees(kAtan2(xaxis.y(), xaxis.x())));
}

KEulerAngles::KEulerAngles(const KMatrix4x4 &matrix)
{
    euler_.setXYZ(kRadiansToDegrees(kAtan2(matrix.m32(), matrix.m33())),
                  kRadiansToDegrees(kAsin(-matrix.m31())),
                  kRadiansToDegrees(kAtan2(matrix.m21(), matrix.m11())));
}

KEulerAngles::KEulerAngles(const KRectCoordSystem3D &rect)
{
    euler_.setXYZ(kRadiansToDegrees(kAtan2(rect.yAxis().z(), rect.zAxis().z())),
                  kRadiansToDegrees(kAsin(-rect.xAxis().z())),
                  kRadiansToDegrees(kAtan2(rect.xAxis().y(), rect.xAxis().x())));
}

KEulerAngles::KEulerAngles(const KEulerAngles &other) : euler_(other.euler_)
{

}

KEulerAngles::~KEulerAngles()
{

}

KMatrix3x3 KEulerAngles::toMatrix() const
{
    double a = kDegreesToRadians(euler_.x());
    double b = kDegreesToRadians(euler_.y());
    double c = kDegreesToRadians(euler_.z());
    double sina = kSin(a);
    double cosa = kCos(a);
    double sinb = kSin(b);
    double cosb = kCos(b);
    double sinc = kSin(c);
    double cosc = kCos(c);
    double sinasinb = sina * sinb;
    double cosasinc = cosa * sinc;
    double cosacosc = cosa * cosc;
    return KMatrix3x3(cosb*cosc, sinasinb*cosc - cosasinc, sina*sinc + cosacosc*sinb,
                      cosb*sinc, cosacosc + sinasinb*sinc, cosasinc*sinb - sina*cosc,
                      -sinb, sina*cosb, cosa*cosb);
}
