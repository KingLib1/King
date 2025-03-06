#include "kcylindricalcoordinatesystem.h"

KCylindricalCoordinateSystem::KCylindricalCoordinateSystem() : z_(0)
{

}

KCylindricalCoordinateSystem::KCylindricalCoordinateSystem(
        double radius, double radian, double z) : z_(z)
{
    polar_.setRadius(radius);
    polar_.setRadian(radian);
}

KCylindricalCoordinateSystem::KCylindricalCoordinateSystem(
        const KPolarCoordSystem2D &polar, double z) :
    polar_(polar), z_(z)
{

}

KCylindricalCoordinateSystem::KCylindricalCoordinateSystem(
        const KCylindricalCoordinateSystem &sys) :
    polar_(sys.polar_), z_(sys.z_)
{

}

KCylindricalCoordinateSystem::~KCylindricalCoordinateSystem()
{

}
