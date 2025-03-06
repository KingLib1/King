#include "kboundingvolume.h"

#include "ktriangle3d.h"

KBoundingVolume::KBoundingVolume() : min(0, 0, 0), max(0, 0, 0)
{

}

KBoundingVolume::KBoundingVolume(double minx, double miny, double minz,
                                 double maxx, double maxy, double maxz) :
    min(minx, miny, minz), max(maxx, maxy, maxz)
{

}

KBoundingVolume::KBoundingVolume(const KVector3D &min, const KVector3D &max) :
    min(min), max(max)
{

}

KBoundingVolume::KBoundingVolume(const QVector<KVector3D> &points)
{
    if (points.isEmpty())
        return;

    min = points.at(0);
    max = min;
    for (int i = 1; i < points.size(); ++i) {
        const KVector3D &p = points.at(i);
        if (p.x() < min.x()) min.setX(p.x());
        else if (p.x() > max.x()) max.setX(p.x());
        if (p.y() < min.y()) min.setY(p.y());
        else if (p.y() > max.y()) max.setY(p.y());
        if (p.z() < min.z()) min.setZ(p.z());
        else if (p.z() > max.z()) max.setZ(p.z());
    }
}

bool KBoundingVolume::collision(const KBoundingVolume &other) const
{
    if (max.x() < other.min.x())
        return false;
    if (min.x() > other.max.x())
        return false;
    if (max.y() < other.min.y())
        return false;
    if (min.y() > other.max.y())
        return false;
    if (max.z() < other.min.z())
        return false;
    if (min.z() > other.max.z())
        return false;

    return true;
}

bool KBoundingVolume::intersects(const KRay3D &ray) const
{
    bool inside = true;
    double xt, yt, zt;
    if (ray.length() <= 0) {
        if (ray.origin().x() < min.x()) {
            if (ray.direction().x() <= EPS6)
                return false;
            xt = (min.x() - ray.origin().x()) / ray.direction().x();
            inside = false;
        } else if (ray.origin().x() > max.x()) {
            if (ray.direction().x() >= -EPS6)
                return false;
            xt = (max.x() - ray.origin().x()) / ray.direction().x();
            inside = false;
        } else {
            xt = 0;
        }

        if (ray.origin().y() < min.y()) {
            if (ray.direction().y() <= EPS6)
                return false;
            yt = (min.y() - ray.origin().y()) / ray.direction().y();
            inside = false;
        } else if (ray.origin().y() > max.y()) {
            if (ray.direction().y() >= -EPS6)
                return false;
            yt = (max.y() - ray.origin().y()) / ray.direction().y();
            inside = false;
        } else {
            yt = 0;
        }

        if (ray.origin().z() < min.z()) {
            if (ray.direction().z() <= EPS6)
                return false;
            zt = (min.z() - ray.origin().z()) / ray.direction().z();
            inside = false;
        } else if (ray.origin().z() > max.z()) {
            if (ray.direction().z() >= -EPS6)
                return false;
            zt = (max.z() - ray.origin().z()) / ray.direction().z();
            inside = false;
        } else {
            zt = 0;
        }

        if (inside)
            return true;

        int which = 0;
        double t = xt;
        if (yt > t) {
            which = 1;
            t = yt;
        }
        if (zt > t) {
            which = 2;
            t = zt;
        }

        switch (which) {
        case 0: {
            double y = ray.origin().y() + ray.direction().y() * t;
            if (y < min.y() || y > max.y())
                return false;
            double z = ray.origin().z() + ray.direction().z() * t;
            if (z < min.z() || z > max.z())
                return false;
            break;
        }
        case 1: {
            double x = ray.origin().x() + ray.direction().x() * t;
            if (x < min.x() || x > max.x())
                return false;
            double z = ray.origin().z() + ray.direction().z() * t;
            if (z < min.z() || z > max.z())
                return false;
            break;
        }
        case 2: {
            double x = ray.origin().x() + ray.direction().x() * t;
            if (x < min.x() || x > max.x())
                return false;
            double y = ray.origin().y() + ray.direction().y() * t;
            if (y < min.y() || y > max.y())
                return false;
            break;
        }
        }

        return true;
    }


    if (ray.origin().x() < min.x()) {
        xt = min.x() - ray.origin().x();
        if (ray.direction().x() * ray.length() < xt)
            return false;
        if (isZero(ray.direction().x()))
            return false;
        xt /= ray.direction().x();
        inside = false;
    } else if (ray.origin().x() > max.x()) {
        xt = max.x() - ray.origin().x();
        if (ray.direction().x() * ray.length() > xt)
            return false;
        if (isZero(ray.direction().x()))
            return false;
        xt /= ray.direction().x();
        inside = false;
    } else {
        xt = 0;
    }

    if (ray.origin().y() < min.y()) {
        yt = min.y() - ray.origin().y();
        if (ray.direction().y() * ray.length() < yt)
            return false;
        if (isZero(ray.direction().y()))
            return false;
        yt /= ray.direction().y();
        inside = false;
    } else if (ray.origin().y() > max.y()) {
        yt = max.y() - ray.origin().y();
        if (ray.direction().y() * ray.length() > yt)
            return false;
        if (isZero(ray.direction().y()))
            return false;
        yt /= ray.direction().y();
        inside = false;
    } else {
        yt = 0;
    }

    if (ray.origin().z() < min.z()) {
        zt = min.z() - ray.origin().z();
        if (ray.direction().z() * ray.length() < zt)
            return false;
        if (isZero(ray.direction().z()))
            return false;
        zt /= ray.direction().z();
        inside = false;
    } else if (ray.origin().z() > max.z()) {
        zt = max.z() - ray.origin().z();
        if (ray.direction().z() * ray.length() > zt)
            return false;
        if (isZero(ray.direction().z()))
            return false;
        zt /= ray.direction().z();
        inside = false;
    } else {
        zt = 0;
    }

    if (inside)
        return true;

    int which = 0;
    double t = xt;
    if (yt > t) {
        which = 1;
        t = yt;
    }
    if (zt > t) {
        which = 2;
        t = zt;
    }

    switch (which) {
    case 0: {
        double y = ray.origin().y() + ray.direction().y() * t;
        if (y < min.y() || y > max.y())
            return false;
        double z = ray.origin().z() + ray.direction().z() * t;
        if (z < min.z() || z > max.z())
            return false;
        break;
    }
    case 1: {
        double x = ray.origin().x() + ray.direction().x() * t;
        if (x < min.x() || x > max.x())
            return false;
        double z = ray.origin().z() + ray.direction().z() * t;
        if (z < min.z() || z > max.z())
            return false;
        break;
    }
    case 2: {
        double x = ray.origin().x() + ray.direction().x() * t;
        if (x < min.x() || x > max.x())
            return false;
        double y = ray.origin().y() + ray.direction().y() * t;
        if (y < min.y() || y > max.y())
            return false;
        break;
    }
    }

    return true;
}

bool KBoundingVolume::contains(const KVector3D &p) const
{
    if (p.x() < min.x())
        return false;
    if (p.x() > max.x())
        return false;
    if (p.y() < min.y())
        return false;
    if (p.y() > max.y())
        return false;
    if (p.z() < min.z())
        return false;
    if (p.z() > max.z())
        return false;
    return true;
}

QVector<KBoundingVolume> KBoundingVolume::divideIntoEight() const
{
    QVector<KBoundingVolume> volumes;
    KVector3D mid = KVector3D::midpoint(min, max);

    KBoundingVolume volume(mid, max);
    volumes << volume; // 第一卦限

    volume.min.setX(min.x());
    volume.max.setX(mid.x());
    volumes << volume; // 第二卦限

    volume.min.setY(min.y());
    volume.max.setY(mid.y());
    volumes << volume; // 第三卦限

    volume.min.setX(mid.x());
    volume.max.setX(max.x());
    volumes << volume; // 第四卦限

    volume.min.setY(mid.y());
    volume.max.setY(max.y());
    volume.min.setZ(min.z());
    volume.max.setZ(mid.z());
    volumes << volume; // 第五卦限

    volume.min.setX(min.x());
    volume.max.setX(mid.x());
    volumes << volume; // 第六卦限

    volume.min.setY(min.y());
    volume.max.setY(mid.y());
    volumes << volume; // 第七卦限

    volume.min.setX(mid.x());
    volume.max.setX(max.x());
    volumes << volume; // 第八卦限

    return volumes;
}

QVector<KTriangleMesh> KBoundingVolume::triangleMesh() const
{
    double dx = this->dx();
    double dy = this->dy();
    double dz = this->dz();

    KVector3D p2 = max.translatedX(-dx);
    KVector3D p3 = p2.translatedY(-dy);
    KVector3D p4 = p3.translatedX(dx);
    KVector3D p5 = max.translatedZ(-dz);
    KVector3D p6 = p5.translatedX(-dx);
    KVector3D p8 = min.translatedX(dx);

    QVector<KTriangleMesh> tris;
    KTriangleMesh tri;
    KVector3D nor(0, -1, 0);
    tri.setP1(min);
    tri.setP2(p8);
    tri.setP3(p3);
    tri.setNormal1(nor);
    tri.setNormal2(nor);
    tri.setNormal3(nor);
    tris << tri;

    tri.setP1(p3);
    tri.setP3(p4);
    tris << tri;

    nor.setY(1);
    tri.setP1(max);
    tri.setP2(p5);
    tri.setP3(p6);
    tri.setNormal1(nor);
    tri.setNormal2(nor);
    tri.setNormal3(nor);
    tris << tri;

    tri.setP2(p6);
    tri.setP3(p2);
    tris << tri;

    nor.setY(0);
    nor.setZ(1);
    tri.setP1(p3);
    tri.setP2(p4);
    tri.setNormal1(nor);
    tri.setNormal2(nor);
    tri.setNormal3(nor);
    tris << tri;

    tri.setP1(p2);
    tri.setP3(max);
    tris << tri;

    nor.setZ(-1);
    tri.setP1(min);
    tri.setP2(p6);
    tri.setP3(p8);
    tri.setNormal1(nor);
    tri.setNormal2(nor);
    tri.setNormal3(nor);
    tris << tri;

    tri.setP1(p8);
    tri.setP3(p5);
    tris << tri;

    nor.setX(-1);
    nor.setZ(0);
    tri.setP1(p2);
    tri.setP3(p3);
    tri.setNormal1(nor);
    tri.setNormal2(nor);
    tri.setNormal3(nor);
    tris << tri;

    tri.setP1(p3);
    tri.setP3(min);
    tris << tri;

    nor.setX(1);
    tri.setP1(p4);
    tri.setP2(p8);
    tri.setP3(max);
    tri.setNormal1(nor);
    tri.setNormal2(nor);
    tri.setNormal3(nor);
    tris << tri;

    tri.setP1(max);
    tri.setP3(p5);
    tris << tri;

    return tris;
}
