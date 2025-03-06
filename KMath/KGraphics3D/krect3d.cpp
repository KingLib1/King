#include "krect3d.h"

#include <QDebug>

#include "KEquation.h"

KRect3D::KRect3D()
{

}

KRect3D::KRect3D(const KRect3D &rect) : size_(rect.size_), sys_(rect.sys_)
{

}

KRect3D::KRect3D(const KVector3D &center, double width, double height)
{
    sys_.setOrigin(center);
    setSize(width, height);
}

KRect3D::KRect3D(const KVector3D &center, const KSizeF &size) :
    size_(size)
{
    sys_.setOrigin(center);
}

KRect3D::KRect3D(const KRect &rect)
{
    setSize(rect.width(), rect.height());
    sys_.setOrigin(rect.centerX(), rect.centerY(), 0);
}

KRect3D::~KRect3D()
{

}



bool KRect3D::intersects(const KRay3D &ray) const
{
    double dot = KVector3D::dotProduct(ray.direction(), normal());
    if (kFabs(dot) < EPS9)
        return false;
    double t = KVector3D::dotProduct(center() - ray.origin(), normal()) / dot;
    if (t < 0 || (ray.length() > 0 && t > ray.length()))
        return false;
    KVector3D p = ray.origin() + ray.direction() * t;
    KVector2D v1(xAxis());
    KVector2D v2(yAxis());
    KVector2D v3(p.x() - center().x(), p.y() - center().y());
    KVector2D xy = solveHomogeneousLinearEquations2x2(v1, v2, v3);
    double right = width() * 0.5;
    if (xy.x() > right)
        return false;
    double left = -right;
    if (xy.x() < left)
        return false;
    double top = height() * 0.5;
    if (xy.y() > top)
        return false;
    double bottom = -top;
    if (xy.y() < bottom)
        return false;
    return true;
}

KVector3D KRect3D::intersection(const KRay3D &ray, bool &intersects) const
{
    double dot = KVector3D::dotProduct(ray.direction(), normal());
    if (kFabs(dot) < EPS9) {
        intersects = false;
        return KVector3D();
    }
    double t = KVector3D::dotProduct(center() - ray.origin(), normal()) / dot;
    if (t < 0 || (ray.length() > 0 && t > ray.length())) {
        intersects = false;
        return KVector3D();
    }
    KVector3D p = ray.origin() + ray.direction() * t;
    KVector2D v1(xAxis());
    KVector2D v2(yAxis());
    KVector2D v3(p.x() - center().x(), p.y() - center().y());
    KVector2D xy = solveHomogeneousLinearEquations2x2(v1, v2, v3);
    double right = width() * 0.5;
    if (xy.x() > right) {
        intersects = false;
        return KVector3D();
    }
    double left = -right;
    if (xy.x() < left) {
        intersects = false;
        return KVector3D();
    }
    double top = height() * 0.5;
    if (xy.y() > top) {
        intersects = false;
        return KVector3D();
    }
    double bottom = -top;
    if (xy.y() < bottom) {
        intersects = false;
        return KVector3D();
    }
    intersects = true;
    return p;
}
