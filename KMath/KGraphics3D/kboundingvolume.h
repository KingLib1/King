#ifndef KBOUNDINGVOLUME_H
#define KBOUNDINGVOLUME_H

#include <QVector>

#include "kvector3d.h"
#include "krange.h"
#include "kray3d.h"
#include "ktrianglemesh.h"

class KING_EXPORT KBoundingVolume
{
public:
    KBoundingVolume();
    KBoundingVolume(double minx, double miny, double minz,
                    double maxx, double maxy, double maxz);
    KBoundingVolume(const KVector3D &min, const KVector3D &max);
    KBoundingVolume(const QVector<KVector3D> &points);
    bool collision(const KBoundingVolume &other) const;
    bool intersects(const KRay3D &ray) const;
    bool contains(const KVector3D &p) const;
    QVector<KBoundingVolume> divideIntoEight() const;
    QVector<KTriangleMesh> triangleMesh() const;

    inline KVector3D mid() const;
    inline double dx() const;
    inline double dy() const;
    inline double dz() const;
    inline KRange xRange() const;
    inline KRange yRange() const;
    inline KRange zRange() const;

    KVector3D min;
    KVector3D max;
};

inline KVector3D KBoundingVolume::mid() const
{
    return KVector3D::midpoint(min, max);
}

inline double KBoundingVolume::dx() const
{
    return max.x() - min.x();
}

inline double KBoundingVolume::dy() const
{
    return max.y() - min.y();
}

inline double KBoundingVolume::dz() const
{
    return max.z() - min.z();
}

inline KRange KBoundingVolume::xRange() const
{
    return KRange(min.x(), max.x());
}

inline KRange KBoundingVolume::yRange() const
{
    return KRange(min.y(), max.y());
}

inline KRange KBoundingVolume::zRange() const
{
    return KRange(min.z(), max.z());
}

#endif // KBOUNDINGVOLUME_H
