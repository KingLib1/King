#include "kline3d.h"

KLine3D::KLine3D()
{
    direction_.setZ(1);
}

KLine3D::KLine3D(const KVector3D &v1, const KVector3D &v2, CreateMode mode) :
    point_(v1)
{
    if (mode == Point_Point)
        direction_ = v2 - v1;
    else
        direction_ = v2;
}

KLine3D::KLine3D(const KLine3D &line) : point_(line.point_),
    direction_(line.direction_)
{

}

KLine3D::~KLine3D()
{

}
