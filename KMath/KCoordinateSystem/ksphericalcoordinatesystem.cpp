#include "ksphericalcoordinatesystem.h"

KSphericalCoordinateSystem::KSphericalCoordinateSystem()
{

}

KSphericalCoordinateSystem::KSphericalCoordinateSystem(
        double radius, double azimuth, double zenith) :
    radius_(radius), azimuth_(azimuth), zenith_(zenith)
{

}

KSphericalCoordinateSystem::KSphericalCoordinateSystem(
        const KSphericalCoordinateSystem &sys) :
    radius_(sys.radius_), azimuth_(sys.azimuth_), zenith_(sys.zenith_)
{

}

KSphericalCoordinateSystem::~KSphericalCoordinateSystem()
{

}
