#include "kcuboid.h"

KCuboid::KCuboid()
{

}

KCuboid::KCuboid(const KCuboid &cuboid) : size_(cuboid.size_), sys_(cuboid.sys_)
{

}

KCuboid::KCuboid(double length, double width, double height)
{
    size_.setXYZ(length, width, height);
}

KCuboid::KCuboid(double length, double width, double height,
                 const KRectCoordSystem3D &sys) : sys_(sys)
{
    size_.setXYZ(length, width, height);
}

bool KCuboid::containsPoint(const KVector3D &point) const
{
    KVector3D p = point - center();
    KVector3D p1(KVector3D::dotProduct(xAxis(), p),
                 KVector3D::dotProduct(yAxis(), p),
                 KVector3D::dotProduct(zAxis(), p));
    double hl = length() / 2;
    double hw = width() / 2;
    double hh = height() / 2;
    if (p1.x() < -hl || p1.x() > hl ||
            p1.y() < -hw || p1.y() > hw ||
            p1.z() < -hh || p1.z() > hh)
        return false;
    return true;
}
