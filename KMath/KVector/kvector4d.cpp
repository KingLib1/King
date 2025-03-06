#include "kvector4d.h"

KVector4D::KVector4D() : x_(0), y_(0), z_(0), w_(0)
{

}

KVector4D::KVector4D(double x, double y, double z) : x_(x), y_(y), z_(z), w_(0)
{

}

KVector4D::KVector4D(const KVector3D &v) : x_(v.x()), y_(v.y()), z_(v.z()), w_(0)
{

}

KVector4D::KVector4D(double x, double y, double z, double w) :
    x_(x), y_(y), z_(z), w_(w)
{

}

KVector4D::KVector4D(const KVector3D &v, double w) :
    x_(v.x()), y_(v.y()), z_(v.z()), w_(w)
{

}

void KVector4D::normalize()
{
    double len = length();
    x_ /= len;
    y_ /= len;
    z_ /= len;
    w_ /= len;
}
