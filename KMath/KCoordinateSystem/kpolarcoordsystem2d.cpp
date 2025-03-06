#include "kpolarcoordsystem2d.h"

KPolarCoordSystem2D::KPolarCoordSystem2D() : radius_(0), radian_(0)
{

}

KPolarCoordSystem2D::KPolarCoordSystem2D(double radius, double radian)
    : radius_(radius), radian_(radian)
{

}

KPolarCoordSystem2D::KPolarCoordSystem2D(const KPointF &point)
{
    setPoint(point);
}

KPolarCoordSystem2D::KPolarCoordSystem2D(
        const KPolarCoordSystem2D &sys) :
    radius_(sys.radius_), radian_(sys.radian_)
{

}

KPolarCoordSystem2D::~KPolarCoordSystem2D()
{

}
