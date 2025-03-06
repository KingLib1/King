#include "kray3d.h"

KRay3D::KRay3D() : length_(1)
{
    direction_.setZ(1);
}

KRay3D::KRay3D(const KVector3D &origin, const KVector3D &direction, double length) :
    origin_(origin), direction_(direction), length_(length)
{
    direction_.normalize();
}

KRay3D::KRay3D(const KRay3D &ray) : origin_(ray.origin_), direction_(ray.direction_),
    length_(ray.length_)
{

}

KRay3D::~KRay3D()
{

}
