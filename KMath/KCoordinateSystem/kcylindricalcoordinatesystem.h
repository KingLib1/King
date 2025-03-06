#ifndef KCYLINDRICALCOORDINATESYSTEM_H
#define KCYLINDRICALCOORDINATESYSTEM_H

#include "kpolarcoordsystem2d.h"

class KING_EXPORT KCylindricalCoordinateSystem
{
public:
    KCylindricalCoordinateSystem();
    KCylindricalCoordinateSystem(double radius, double radian, double z);
    KCylindricalCoordinateSystem(const KPolarCoordSystem2D &polar, double z);
    KCylindricalCoordinateSystem(const KCylindricalCoordinateSystem &sys);
    ~KCylindricalCoordinateSystem();

    inline void setRadius(double radius);
    inline void setRadian(double radian);
    inline void setZ(double z);
    inline void setPoint(double x, double y, double z);
    inline void setXY(double x, double y);
    inline void normalize();

    inline double radius() const;
    inline double radian() const;
    inline double z() const;
    inline double x() const;
    inline double y() const;

    inline KCylindricalCoordinateSystem &operator=(
            const KCylindricalCoordinateSystem &sys);

private:
    KPolarCoordSystem2D polar_;
    double z_;
};

inline void KCylindricalCoordinateSystem::setRadius(double radius)
{
    polar_.setRadius(radius);
}

inline void KCylindricalCoordinateSystem::setRadian(double radian)
{
    polar_.setRadian(radian);
}

inline void KCylindricalCoordinateSystem::setZ(double z)
{
    z_ = z;
}

inline void KCylindricalCoordinateSystem::setPoint(double x, double y, double z)
{
    polar_.setPoint(x, y);
    z_ = z;
}

inline void KCylindricalCoordinateSystem::setXY(double x, double y)
{
    polar_.setPoint(x, y);
}

inline void KCylindricalCoordinateSystem::normalize()
{
    polar_.normalize();
}

inline double KCylindricalCoordinateSystem::radius() const
{
    return polar_.radius();
}

inline double KCylindricalCoordinateSystem::radian() const
{
    return polar_.radian();
}

inline double KCylindricalCoordinateSystem::z() const
{
    return z_;
}

inline double KCylindricalCoordinateSystem::x() const
{
    return polar_.x();
}

inline double KCylindricalCoordinateSystem::y() const
{
    return polar_.y();
}

inline KCylindricalCoordinateSystem &KCylindricalCoordinateSystem::operator=(
        const KCylindricalCoordinateSystem &sys)
{
    polar_ = sys.polar_;
    z_ = sys.z_;
    return *this;
}

#endif // KCYLINDRICALCOORDINATESYSTEM_H
