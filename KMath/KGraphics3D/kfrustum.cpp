#include "kfrustum.h"

#include <QDebug>

KFrustum::KFrustum() : bottom_radius_(0), top_radius_(0), length_(0)
{

}

KFrustum::KFrustum(double bottom_radius, double top_radius, double length,
                   const KRectCoordSystem3D &sys) :
    bottom_radius_(bottom_radius), top_radius_(top_radius), length_(length),
    sys_(sys)
{

}

KFrustum::KFrustum(const KFrustum &other) : bottom_radius_(other.bottom_radius_),
    top_radius_(other.top_radius_), length_(other.length_), sys_(other.sys_)
{

}

KFrustum::~KFrustum()
{

}

KCircle3D KFrustum::circleAt(double height) const
{
    double radius = radiusAt(height);
    KVector3D center = sys_.origin() + zAxis() * height;
    return KCircle3D(center, radius, zAxis());
}

bool KFrustum::contains(const KVector3D &p) const
{
    double t = KVector3D::dotProduct(p - bottomCenter(), zAxis());
    if (t < 0 || t > length_) {
        return false;
    }

    KVector3D pedal = bottomCenter() + zAxis() * t;
    double r2 = kSquare(radiusAt(t));
    double dis2 = p.distanceSquaredToPoint(pedal);
    if (dis2 > r2) {
        return false;
    }
    return true;




//    KVector3D d = zAxis() * length_;
//    double t = KVector3D::dotProduct(p - bottomCenter(), d) / d.lengthSquared();
//    if (t < 0 || t > 1)
//        return false;

//    KVector3D pedal = bottomCenter() + d * t;
//    double r2 = kSquare(radiusAt(length_ * t));
//    double dis = p.distanceSquaredToPoint(pedal);
//    if (dis > r2)
//        return false;
//    return true;
}
