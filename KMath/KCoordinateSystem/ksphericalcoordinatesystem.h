#ifndef KSPHERICALCOORDINATESYSTEM_H
#define KSPHERICALCOORDINATESYSTEM_H

#include "kvector3d.h"

class KING_EXPORT KSphericalCoordinateSystem
{
public:
    KSphericalCoordinateSystem();
    KSphericalCoordinateSystem(double radius, double azimuth, double zenith);
    KSphericalCoordinateSystem(const KSphericalCoordinateSystem &sys);
    ~KSphericalCoordinateSystem();

    inline void setRadius(double radius);
    /**
     * @brief 设置水平角
     */
    inline void setAzimuth(double azimuth);
    /**
     * @brief 设置垂直角
     */
    inline void setZenith(double zenith);
    inline void setPoint(const KVector3D &point);

    inline double radius() const;
    inline double azimuth() const;
    inline double zenith() const;
    inline double x() const;
    inline double y() const;
    inline double z() const;
    inline KVector3D toPoint() const;

    inline KSphericalCoordinateSystem &operator=(
            const KSphericalCoordinateSystem &sys);

private:
    double radius_;
    double azimuth_; // 水平角
    double zenith_;  // 垂直角
};

inline void KSphericalCoordinateSystem::setRadius(double radius)
{
    radius_ = radius;
}

inline void KSphericalCoordinateSystem::setAzimuth(double azimuth)
{
    azimuth_ = azimuth;
}

inline void KSphericalCoordinateSystem::setZenith(double zenith)
{
    zenith_ = zenith;
}

inline void KSphericalCoordinateSystem::setPoint(const KVector3D &point)
{
    radius_ = point.length();
    azimuth_ = kAtan2(point.y(), point.x());
    zenith_ = kAcos(point.z() / radius_);
}

inline double KSphericalCoordinateSystem::radius() const
{
    return radius_;
}

inline double KSphericalCoordinateSystem::azimuth() const
{
    return azimuth_;
}

inline double KSphericalCoordinateSystem::zenith() const
{
    return zenith_;
}

inline double KSphericalCoordinateSystem::x() const
{
    return radius_ * kSin(zenith_) * kCos(azimuth_);
}

inline double KSphericalCoordinateSystem::y() const
{
    return radius_ * kSin(zenith_) * kSin(azimuth_);
}

inline double KSphericalCoordinateSystem::z() const
{
    return radius_ * kCos(zenith_);
}

inline KVector3D KSphericalCoordinateSystem::toPoint() const
{
    double l = radius_ * kSin(zenith_);
    return KVector3D(l * kCos(azimuth_), l * kSin(azimuth_),
                     radius_ * kCos(zenith_));
}

inline KSphericalCoordinateSystem &KSphericalCoordinateSystem::operator=(
        const KSphericalCoordinateSystem &sys)
{
    radius_ = sys.radius_;
    azimuth_ = sys.azimuth_;
    zenith_ = sys.zenith_;
    return *this;
}

#endif // KSPHERICALCOORDINATESYSTEM_H
