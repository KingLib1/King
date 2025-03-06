#include "ktoolcoordinatesystem.h"

KToolCoordinateSystem::KToolCoordinateSystem() : len_(0), radian_(0)
{

}

KToolCoordinateSystem::KToolCoordinateSystem(double dx, double dy) :
    len_(kSqrt(kSquareSum(dx, dy))), radian_(kAtan2(dy, dx))
{
    offset_.setXY(dx, dy);
}

KToolCoordinateSystem::KToolCoordinateSystem(const KPointF &offset_pos) :
    offset_(offset_pos), len_(offset_pos.originDistance()),
    radian_(kAtan2(offset_pos.y(), offset_pos.x()))
{

}

KToolCoordinateSystem::KToolCoordinateSystem(const KToolCoordinateSystem &other)
    : offset_(other.offset_), len_(other.len_), radian_(other.radian_)
{

}

KToolCoordinateSystem::~KToolCoordinateSystem()
{


}
