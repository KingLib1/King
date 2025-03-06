#ifndef KPLANE3D_H
#define KPLANE3D_H

#include "kray3d.h"

class KING_EXPORT KPlane3D
{
public:
    KPlane3D();
    KPlane3D(const KVector3D &point, const KVector3D &normal);
    KPlane3D(const KVector3D &p1, const KVector3D &p2, const KVector3D &p3);
    KPlane3D(const KVector3D &normal, double d);
    KPlane3D(const KPlane3D &plane);
    ~KPlane3D();

    inline void translate(const KVector3D &dv);

    inline const KVector3D &normal() const;
    // 原点到平面的有向距离
    inline double directedDistanceFromOrigin() const; // d_
    inline bool contains(const KVector3D &point) const;
    // 距离绝对值
    inline double distanceFromPoint(const KVector3D &point) const;
    // 点到平面的有向距离
    inline double directedDistanceFromPoint(const KVector3D &point) const;
    /**
     * @brief 点在平面的哪一侧
     * @return 1为正侧，-1为负侧，0为在平面上
     */
    int whichSide(const KVector3D &point) const;

    /**
     * @brief 线段与平面的交点
     */
    KVector3D intersection(const KLineSegment3D &line, bool &intersect) const;
    KVector3D intersection(const KLine3D &line, bool *success = nullptr) const;
    inline bool intersects(const KLineSegment3D &line) const;
    KLine3D intersected(const KPlane3D &plane) const;
    bool intersects(const KRay3D &ray) const;
    inline KVector3D projectionPoint(const KVector3D &p) const;
    inline KVector3D projectionVector(const KVector3D &v) const;

    inline KPlane3D &operator=(const KPlane3D &other);

private:
    KVector3D n_;
    double d_;  // p.n = d;(矢量表示法，n为单位法向量, p为平面上任意点)
};

inline void KPlane3D::translate(const KVector3D &dv)
{
    d_ += KVector3D::dotProduct(n_, dv);
}

inline const KVector3D &KPlane3D::normal() const
{
    return n_;
}

inline double KPlane3D::directedDistanceFromOrigin() const
{
    return -d_;
}

inline bool KPlane3D::contains(const KVector3D &point) const
{
    return distanceFromPoint(point) < EPS6;
}

inline double KPlane3D::distanceFromPoint(const KVector3D &point) const
{
    return kFabs(directedDistanceFromPoint(point));
}

inline double KPlane3D::directedDistanceFromPoint(const KVector3D &point) const
{
    return KVector3D::dotProduct(point, n_) - d_;
}

inline bool KPlane3D::intersects(const KLineSegment3D &line) const
{
    return (KVector3D::dotProduct(line.p1(), n_) - d_) *
            (KVector3D::dotProduct(line.p2(), n_) - d_) <= 0;
}

inline KVector3D KPlane3D::projectionPoint(const KVector3D &p) const
{
    return p + n_ * (d_ - KVector3D::dotProduct(n_, p));
}

inline KVector3D KPlane3D::projectionVector(const KVector3D &v) const
{
    return v - n_ * KVector3D::dotProduct(n_, v);
}

inline KPlane3D &KPlane3D::operator=(const KPlane3D &other)
{
    d_ = other.d_;
    n_ = other.n_;
    return *this;
}

#endif // KPLANE3D_H
