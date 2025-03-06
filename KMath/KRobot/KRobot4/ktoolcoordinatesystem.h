#ifndef KTOOLCOORDINATESYSTEM_H
#define KTOOLCOORDINATESYSTEM_H

#include "kpointf.h"

class KToolCoordinateSystem
{
public:
    KToolCoordinateSystem();
    KToolCoordinateSystem(double dx, double dy);
    KToolCoordinateSystem(const KPointF &offset_pos);
    KToolCoordinateSystem(const KToolCoordinateSystem &other);
    ~KToolCoordinateSystem();

    inline void setOffsetPos(const KPointF &offset);
    inline void setOffsetPos(double dx, double dy);

    inline const KPointF &offsetPos() const;
    inline double offsetLength() const;
    inline double offsetRadian() const;
    inline double offsetAngle() const;

    inline KToolCoordinateSystem &operator=(const KToolCoordinateSystem &other);

private:
    KPointF offset_;
    double len_;
    double radian_;
};

inline void KToolCoordinateSystem::setOffsetPos(const KPointF &offset)
{
    offset_ = offset;
    len_ = offset.originDistance();
    radian_ = kAtan2(offset.y(), offset.x());
}

inline void KToolCoordinateSystem::setOffsetPos(double dx, double dy)
{
    offset_.setXY(dx, dy);
    len_ = kSqrt(kSquareSum(dx, dy));
    radian_ = kAtan2(dy, dx);
}

inline const KPointF &KToolCoordinateSystem::offsetPos() const
{
    return offset_;
}

inline double KToolCoordinateSystem::offsetLength() const
{
    return len_;
}

inline double KToolCoordinateSystem::offsetRadian() const
{
    return radian_;
}

inline double KToolCoordinateSystem::offsetAngle() const
{
    return kRadiansToDegrees(radian_);
}

inline KToolCoordinateSystem &KToolCoordinateSystem::operator=(
        const KToolCoordinateSystem &other)
{
    offset_ = other.offset_;
    len_ = other.len_;
    radian_ = other.radian_;
    return *this;
}

#endif // KTOOLCOORDINATESYSTEM_H
