#include "klinesegment3d.h"

KLineSegment3D::KLineSegment3D()
{

}

KLineSegment3D::KLineSegment3D(double x1, double y1, double z1,
                 double x2, double y2, double z2)
{
    p1_.setXYZ(x1, y1, z1);
    p2_.setXYZ(x2, y2, z2);
}

KLineSegment3D::KLineSegment3D(const KVector3D &p1, const KVector3D &p2) :
    p1_(p1), p2_(p2)
{

}

KLineSegment3D::KLineSegment3D(const KLineSegment3D &line) :
    p1_(line.p1_), p2_(line.p2_)
{

}

KLineSegment3D::~KLineSegment3D()
{

}

double KLineSegment3D::distanceToLine(const KLineSegment3D &line) const
{
    KVector3D v = toVector();
    KVector3D n = KVector3D::crossProduct(v, line.toVector());
    KVector3D pp1 = p1_ - line.p1_;
    if (n.isNull()) {
        KVector3D pp2 = p2_ - line.p1_;
        return kSqrt(KVector3D::crossProduct(pp1, pp2).lengthSquared() /
                     v.lengthSquared());
    }
    return kFabs(KVector3D::dotProduct(pp1, n)) / n.length();
}

KVector3D KLineSegment3D::nearestPoint(const KVector3D &point) const
{
    KVector3D d = p2_ - p1_;
    double t = KVector3D::dotProduct(point - p1_, d) / d.lengthSquared();
    if (t < 0)
        return p1_;
    if (t > 1)
        return p2_;
    return p1_ + d * t;
}

bool KLineSegment3D::contains(const KVector3D &point, double fuzziness) const
{
    double d1 = dx();
    if (!isZero(d1, fuzziness)) {
        double t = (point.x() - x1()) / d1;
        if (t > 1 || t < 0)
            return false;
        return isEqual(t * dy(), point.y() - y1(), fuzziness) &&
                isEqual(t * dz(), point.z() - z1(), fuzziness);
    }

    double d2 = dy();
    if (!isZero(d2, fuzziness)) {
        double t = (point.y() - y1()) / d2;
        if (t > 1 || t < 0)
            return false;
        return isZero(point.x() - x1(), fuzziness) &&
                isEqual(t * dz(), point.z() - z1(), fuzziness);
    }

    double d3 = dz();
    if (!isZero(d3, fuzziness)) {
        double t = (point.z() - z1()) / d3;
        if (t > 1 || t < 0)
            return false;
        return isZero(point.x() - x1(), fuzziness) &&
                isZero(point.y() - y1(), fuzziness);
    }

    return isZero(point.x() - x1(), fuzziness) &&
            isZero(point.y() - y1(), fuzziness) &&
            isZero(point.z() - z1(), fuzziness);
}

bool KLineSegment3D::contains_XY(const KVector3D &point, double fuzziness) const
{
    double d1 = dx();
    if (!isZero(d1, fuzziness)) {
        double t = (point.x() - x1()) / d1;
        if (t > 1 || t < 0)
            return false;
        return isEqual(t * dy(), point.y() - y1(), fuzziness);
    }

    double d2 = dy();
    if (!isZero(d2, fuzziness)) {
        double t = (point.y() - y1()) / d2;
        if (t > 1 || t < 0)
            return false;
        return isZero(point.x() - x1(), fuzziness);
    }

    return isZero(point.x() - x1(), fuzziness) &&
            isZero(point.y() - y1(), fuzziness);
}

double KLineSegment3D::radian(const KLineSegment3D &line1,
                              const KLineSegment3D &line2)
{
    KVector3D v1 = line1.toVector();
    KVector3D v2 = line2.toVector();
    return kAcos(KVector3D::dotProduct(v1, v2) /
                 kSqrt(v1.lengthSquared() * v2.lengthSquared()));
}
