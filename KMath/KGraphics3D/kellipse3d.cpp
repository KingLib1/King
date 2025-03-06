#include "kellipse3d.h"

#include <QVector>

#include "KVector/kvector2d.h"
#include "KEquation.h"

KEllipse3D::KEllipse3D() : a_(0), b_(0)
{

}

KEllipse3D::KEllipse3D(double a, double b) : a_(a), b_(b)
{

}

KEllipse3D::KEllipse3D(double a, double b, const KRectCoordSystem3D &sys) :
    sys_(sys), a_(a), b_(b)
{

}

KEllipse3D::KEllipse3D(const KEllipse3D &ell) :
    sys_(ell.sys_), a_(ell.a_), b_(ell.b_)
{

}

KEllipse3D::~KEllipse3D()
{

}

bool KEllipse3D::intersects(const KRay3D &ray) const
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
    return (kSquareSum(b_ * xy.x(), a_ * xy.y()) <=  kSquare(a_ * b_));
}

KVector3D KEllipse3D::intersection(const KRay3D &ray, bool *success) const
{
    double dot = KVector3D::dotProduct(ray.direction(), normal());
    if (kFabs(dot) < EPS9) {
        if (success)
            *success = false;
        return KVector3D();
    }
    double t = KVector3D::dotProduct(center() - ray.origin(), normal()) / dot;
    if (t < 0 || (ray.length() > 0 && t > ray.length())) {
        if (success)
            *success = false;
        return KVector3D();
    }
    KVector3D p = ray.origin() + ray.direction() * t;
    KVector2D v3(p.x() - center().x(), p.y() - center().y());
    KVector2D xy = solveHomogeneousLinearEquations2x2(xAxis(), yAxis(), v3);
    if (kSquareSum(b_ * xy.x(), a_ * xy.y()) <=  kSquare(a_ * b_)) {
        if (success)
            *success = true;
        return p;
    }
    if (success)
        *success = false;
    return KVector3D();
}
