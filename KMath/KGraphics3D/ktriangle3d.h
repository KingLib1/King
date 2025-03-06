#ifndef KTRIANGLE3D_H
#define KTRIANGLE3D_H

#include "ktriangle2d.h"
#include "kcuboid.h"
#include "klinesegment3d.h"
#include "kray3d.h"
#include "kboundingvolume.h"
#include "KPair.h"

class KING_EXPORT KTriangle3D
{
public:
    KTriangle3D();
    /**
     * @brief 逆时针传参
     */
    KTriangle3D(const KVector3D &p1, const KVector3D &p2, const KVector3D &p3);
    KTriangle3D(const KTriangle2D &triangle);
    KTriangle3D(const KTriangle2D &triangle, double z);
    KTriangle3D(const KTriangle3D &triangle);
    ~KTriangle3D();

    inline void setP1(const KVector3D &p);
    inline void setP2(const KVector3D &p);
    inline void setP3(const KVector3D &p);
    inline void setPoints(const KVector3D &p1, const KVector3D &p2,
                          const KVector3D &p3);
    inline void translate(const KVector3D &dv);
    inline void translate(double dx, double dy, double dz);

    inline const KVector3D &p1() const;
    inline const KVector3D &p2() const;
    inline const KVector3D &p3() const;
    inline const KVector3D v12() const;
    inline const KVector3D v21() const;
    inline const KVector3D v13() const;
    inline const KVector3D v31() const;
    inline const KVector3D v23() const;
    inline const KVector3D v32() const;
    inline KLineSegment3D edge1() const;
    inline KLineSegment3D edge2() const;
    inline KLineSegment3D edge3() const;
    double radian1() const;
    double radian2() const;
    double radian3() const;
    inline double angle1() const;
    inline double angle2() const;
    inline double angle3() const;
    inline double lengthSquared1() const;
    inline double lengthSquared2() const;
    inline double lengthSquared3() const;
    inline double length1() const;
    inline double length2() const;
    inline double length3() const;
    inline double area() const;
    inline double perimeter() const;
    inline double zMax() const;
    inline double zMin() const;
    inline double xMax() const;
    inline double xMin() const;
    inline double yMax() const;
    inline double yMin() const;
    inline KRange zRange() const;
    inline KRange xRange() const;
    inline KRange yRange() const;
    KCuboid boundingCuboid() const;
    KBoundingVolume boundingVolume() const;
    inline KVector3D normal() const;
    inline KTriangle3D translated(const KVector3D &dv) const;
    inline KTriangle3D translated(double dx, double dy, double dz) const;
    bool intersects(const KLineSegment3D &line) const;
    bool intersects(const KRay3D &ray) const;
    bool intersects(const KTriangle3D &other) const;
    bool intersects_fast(const KTriangle3D &other) const;
    KVector3D intersected(const KLineSegment3D &line, bool &success) const;
    inline bool isValid() const;
    bool containsPoint(const KVector3D &point) const;
    inline KVector3D barycentre() const;
    inline KVector3D barycentricCoordinatesToPoint(
            const KVector3D &barycenter) const;
    inline KVector3D barycentricCoordinatesToPoint(
            double b1, double b2, double b3) const;
    /**
     * @brief 按最长边拆分为两个三角形
     */
    KPair<KTriangle3D, KTriangle3D> divide() const;

private:
    KVector3D p1_;
    KVector3D p2_;
    KVector3D p3_;
};

inline void KTriangle3D::setP1(const KVector3D &p)
{
    p1_ = p;
}

inline void KTriangle3D::setP2(const KVector3D &p)
{
    p2_ = p;
}

inline void KTriangle3D::setP3(const KVector3D &p)
{
    p3_ = p;
}

inline void KTriangle3D::setPoints(const KVector3D &p1, const KVector3D &p2,
                                   const KVector3D &p3)
{
    p1_ = p1;
    p2_ = p2;
    p3_ = p3;
}

inline void KTriangle3D::translate(const KVector3D &dv)
{
    p1_ += dv;
    p2_ += dv;
    p3_ += dv;
}

inline void KTriangle3D::translate(double dx, double dy, double dz)
{
    p1_.translate(dx, dy, dz);
    p2_.translate(dx, dy, dz);
    p3_.translate(dx, dy, dz);
}

inline const KVector3D &KTriangle3D::p1() const
{
    return p1_;
}

inline const KVector3D &KTriangle3D::p2() const
{
    return p2_;
}

inline const KVector3D &KTriangle3D::p3() const
{
    return p3_;
}

const KVector3D KTriangle3D::v12() const
{
    return p2_ - p1_;
}

inline const KVector3D KTriangle3D::v21() const
{
    return p1_ - p2_;
}

inline const KVector3D KTriangle3D::v13() const
{
    return p3_ - p1_;
}

inline const KVector3D KTriangle3D::v31() const
{
    return p1_ - p3_;
}

inline const KVector3D KTriangle3D::v23() const
{
    return p3_ - p2_;
}

inline const KVector3D KTriangle3D::v32() const
{
    return p2_ - p3_;
}

inline KLineSegment3D KTriangle3D::edge1() const
{
    return KLineSegment3D(p2_, p3_);
}

inline KLineSegment3D KTriangle3D::edge2() const
{
    return KLineSegment3D(p3_, p1_);
}

inline KLineSegment3D KTriangle3D::edge3() const
{
    return KLineSegment3D(p1_, p2_);
}

inline double KTriangle3D::angle1() const
{
    return kRadiansToDegrees(radian1());
}

inline double KTriangle3D::angle2() const
{
    return kRadiansToDegrees(radian2());
}

inline double KTriangle3D::angle3() const
{
    return kRadiansToDegrees(radian3());
}

inline double KTriangle3D::lengthSquared1() const
{
    return (p2_ - p3_).lengthSquared();
}

inline double KTriangle3D::lengthSquared2() const
{
    return (p1_ - p3_).lengthSquared();
}

inline double KTriangle3D::lengthSquared3() const
{
    return (p1_ - p2_).lengthSquared();
}

inline double KTriangle3D::length1() const
{
    return (p2_ - p3_).length();
}

inline double KTriangle3D::length2() const
{
    return (p1_ - p3_).length();
}

inline double KTriangle3D::length3() const
{
    return (p1_ - p2_).length();
}

inline double KTriangle3D::area() const
{
    return KVector3D::crossProduct(p2_ - p1_, p3_ - p1_).length() * 0.5;
}

inline double KTriangle3D::perimeter() const
{
    return v12().length() + v13().length() + v23().length();
}

inline double KTriangle3D::zMax() const
{
    return kMax(p1_.z(), p2_.z(), p3_.z());
}

inline double KTriangle3D::zMin() const
{
    return kMin(p1_.z(), p2_.z(), p3_.z());
}

inline double KTriangle3D::xMax() const
{
    return kMax(p1_.x(), p2_.x(), p3_.x());
}

inline double KTriangle3D::xMin() const
{
    return kMin(p1_.x(), p2_.x(), p3_.x());
}

inline double KTriangle3D::yMax() const
{
    return kMax(p1_.y(), p2_.y(), p3_.y());
}

inline double KTriangle3D::yMin() const
{
    return kMin(p1_.y(), p2_.y(), p3_.y());
}

inline KRange KTriangle3D::zRange() const
{
    return KRange(zMin(), zMax());
}

inline KRange KTriangle3D::xRange() const
{
    return KRange(xMin(), xMax());
}

inline KRange KTriangle3D::yRange() const
{
    return KRange(yMin(), yMax());
}

inline KVector3D KTriangle3D::normal() const
{
    return KVector3D::crossProduct(v12(), v13());
}

inline KTriangle3D KTriangle3D::translated(const KVector3D &dv) const
{
    return KTriangle3D(p1_ + dv, p2_ + dv, p3_ + dv);
}

inline KTriangle3D KTriangle3D::translated(double dx, double dy, double dz) const
{
    return translated(KVector3D(dx, dy, dz));
}

inline bool KTriangle3D::isValid() const
{
    return kFabs(KVector3D::crossProduct(v12(), v13()).lengthSquared()) > EPS9;
}

inline KVector3D KTriangle3D::barycentre() const
{
    return (p1_ + p2_ + p3_) / 3;
}

inline KVector3D KTriangle3D::barycentricCoordinatesToPoint(
        const KVector3D &barycenter) const
{
    return p1_ * barycenter.x() + p2_ * barycenter.y() + p3_ * barycenter.z();
}

inline KVector3D KTriangle3D::barycentricCoordinatesToPoint(
        double b1, double b2, double b3) const
{
    return p1_ * b1 + p2_ * b2 + p3_ * b3;
}

#endif // KTRIANGLE3D_H
