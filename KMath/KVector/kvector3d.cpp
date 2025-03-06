#include "kvector3d.h"

KVector3D::KVector3D() : x_(0), y_(0), z_(0)
{

}

KVector3D::KVector3D(double x, double y) : x_(x), y_(y), z_(0)
{

}

KVector3D::KVector3D(double x, double y, double z) : x_(x), y_(y), z_(z)
{

}

KVector3D::KVector3D(const KPointF &point) : x_(point.x()), y_(point.y()), z_(0)
{

}

KVector3D::KVector3D(const KPointF &point, double z) :
    x_(point.x()), y_(point.y()), z_(z)
{

}

KVector3D::KVector3D(const KVector3D &v) : x_(v.x()), y_(v.y()), z_(v.z())
{

}

void KVector3D::setLength(double length)
{
    double temp = this->length();
    if (temp < EPS6)
        return;
    temp = length / temp;
    *this *= temp;
}

void KVector3D::rotate(double angle, const KVector3D &axis)
{
    KVector3D n(axis);
    n.normalize();
    KVector3D z = KVector3D::dotProduct(n, *this) * n;
    KVector3D x = *this - z;
    KVector3D y = KVector3D::crossProduct(n, x);
    double radian = kDegreesToRadians(angle);
    *this = kCos(radian) * x + kSin(radian) * y + z;
}

void KVector3D::normalize()
{
    double len = length();
    if (len < EPS6)
        return;
    x_ /= len;
    y_ /= len;
    z_ /= len;
}

KVector3D KVector3D::normalized() const
{
    double len = length();
    if (len < EPS6)
        return KVector3D();
    return KVector3D(x_ / len, y_ / len, z_ / len);
}

void KVector3D::rotateX_Radian(double radian)
{
    double temp = y_;
    double sina = kSin(radian);
    double cosa = kCos(radian);
    y_ = temp * cosa - z_ * sina;
    z_ = temp * sina + z_ * cosa;
}

void KVector3D::rotateY_Radian(double radian)
{
    double temp = x_;
    double sina = kSin(radian);
    double cosa = kCos(radian);
    x_ = temp * cosa + z_ * sina;
    z_ = z_ * cosa - temp * sina;
}

void KVector3D::rotateZ_Radian(double radian)
{
    double temp = x_;
    double sina = kSin(radian);
    double cosa = kCos(radian);
    x_ = temp * cosa - y_ * sina;
    y_ = temp * sina + y_ * cosa;
}

double KVector3D::radian(const KVector3D &v1, const KVector3D &v2)
{
    double ac = angleCosine(v1, v2);
    if (ac > 1)
        ac = 1;
    return kAcos(ac);
}
