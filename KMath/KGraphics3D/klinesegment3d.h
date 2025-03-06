#ifndef KLINESEGMENT3D_H
#define KLINESEGMENT3D_H

#include "kline3d.h"

class KING_EXPORT KLineSegment3D
{
public:
    KLineSegment3D();
    KLineSegment3D(double x1, double y1, double z1,
                   double x2, double y2, double z2);
    KLineSegment3D(const KVector3D &p1, const KVector3D &p2);
    KLineSegment3D(const KLineSegment3D &line);
    ~KLineSegment3D();
    inline const KVector3D &p1() const;
    inline const KVector3D &p2() const;
    inline void setP1(double x, double y, double z);
    inline void setP1(const KVector3D &p);
    inline void setP2(double x, double y, double z);
    inline void setP2(const KVector3D &p);
    inline void setLine(double x1, double y1, double z1,
                        double x2, double y2, double z2);
    inline void setLine(const KVector3D &p1, const KVector3D &p2);
    /**
     * @brief 设置直线长度，p1不动
     */
    inline void setLength(double length);
    /**
     * @brief 设置缩放比例，p1不动
     */
    inline void setScale(double scale);
    inline void setX1(double x);
    inline void setY1(double y);
    inline void setZ1(double z);
    inline void setX2(double x);
    inline void setY2(double y);
    inline void setZ2(double z);
    /**
     * @brief 首尾颠倒
     */
    inline void invert();

    inline KVector3D midpoint() const;
    /**
     * @brief 按比例取点
     */
    inline KVector3D scalePoint(double scale) const;
    inline double x1() const;
    inline double y1() const;
    inline double z1() const;
    inline double x2() const;
    inline double y2() const;
    inline double z2() const;
    inline double dx() const;
    inline double dy() const;
    inline double dz() const;
    inline double length() const;
    inline double lengthSquared() const;
    inline KVector3D toVector() const;
    inline KVector3D toUnitVector() const;
    inline void translate(const KVector3D &dv);
    inline void translate(double dx, double dy, double dz);
    inline void translateX(double dx);
    inline void translateY(double dy);
    inline void translateZ(double dz);
    inline KLineSegment3D inverted() const;

    inline double distanceFromPoint(double x, double y, double z) const;
    inline double distanceFromPoint(const KVector3D &p) const;
    inline double distanceSquaredFromPoint(double x, double y, double z) const;
    inline double distanceSquaredFromPoint(const KVector3D &p) const;
    double distanceToLine(const KLineSegment3D &line) const;
    inline KVector3D symmetryPoint(const KVector3D &p) const;
    inline KLine3D toLine() const;
    inline KLineSegment3D translated(const KVector3D &dv) const;
    inline bool isParallelWith(const KLineSegment3D &line) const;
    /**
     * @brief 点到直线的垂足
     */
    inline KVector3D pedal(const KVector3D &point) const;
    /**
     * @brief 直线上离point最近的点
     */
    KVector3D nearestPoint(const KVector3D &point) const;
    bool contains(const KVector3D &point, double fuzziness = EPS6) const;
    bool contains_XY(const KVector3D &point, double fuzziness = EPS6) const;

    static double radian(const KLineSegment3D &line1,
                         const KLineSegment3D &line2);
    inline static double angle(const KLineSegment3D &line1,
                               const KLineSegment3D &line2);

    inline KLineSegment3D &operator=(const KLineSegment3D &line);
    inline bool operator==(const KLineSegment3D &line) const;
    inline bool operator!=(const KLineSegment3D &line) const;

private:
    KVector3D p1_;
    KVector3D p2_;
};

inline const KVector3D &KLineSegment3D::p1() const
{
    return p1_;
}

inline const KVector3D &KLineSegment3D::p2() const
{
    return p2_;
}

inline void KLineSegment3D::setP1(double x, double y, double z)
{
    p1_.setXYZ(x, y, z);
}

inline void KLineSegment3D::setP1(const KVector3D &p)
{
    p1_ = p;
}

inline void KLineSegment3D::setP2(double x, double y, double z)
{
    p2_.setXYZ(x, y, z);
}

inline void KLineSegment3D::setP2(const KVector3D &p)
{
    p2_ = p;
}

inline void KLineSegment3D::setLine(double x1, double y1, double z1,
                                    double x2, double y2, double z2)
{
    p1_.setXYZ(x1, y1, z1);
    p2_.setXYZ(x2, y2, z2);
}

inline void KLineSegment3D::setLine(const KVector3D &p1, const KVector3D &p2)
{
    p1_ = p1;
    p2_ = p2;
}

inline void KLineSegment3D::setLength(double length)
{
    KVector3D d = p2_ - p1_;
    d.normalize();
    p2_ = p1_ + d * length;
}

inline void KLineSegment3D::setScale(double scale)
{
    KVector3D d = p2_ - p1_;
    p2_ = p1_ + d * scale;
}

inline void KLineSegment3D::setX1(double x)
{
    p1_.setX(x);
}

inline void KLineSegment3D::setY1(double y)
{
    p1_.setY(y);
}

inline void KLineSegment3D::setZ1(double z)
{
    p1_.setZ(z);
}

inline void KLineSegment3D::setX2(double x)
{
    p2_.setX(x);
}

inline void KLineSegment3D::setY2(double y)
{
    p2_.setY(y);
}

inline void KLineSegment3D::setZ2(double z)
{
    p2_.setZ(z);
}

inline void KLineSegment3D::invert()
{
    KVector3D temp = p1_;
    p1_ = p2_;
    p2_ = temp;
}

inline KVector3D KLineSegment3D::midpoint() const
{
    return KVector3D::midpoint(p1_, p2_);
}

inline KVector3D KLineSegment3D::scalePoint(double scale) const
{
    return p1_ + (p2_ - p1_) * scale;
}

inline double KLineSegment3D::x1() const
{
    return p1_.x();
}

inline double KLineSegment3D::y1() const
{
    return p1_.y();
}

inline double KLineSegment3D::z1() const
{
    return p1_.z();
}

inline double KLineSegment3D::x2() const
{
    return p2_.x();
}

inline double KLineSegment3D::y2() const
{
    return p2_.y();
}

inline double KLineSegment3D::z2() const
{
    return p2_.z();
}

inline double KLineSegment3D::dx() const
{
    return p2_.x() - p1_.x();
}

inline double KLineSegment3D::dy() const
{
    return p2_.y() - p1_.y();
}

inline double KLineSegment3D::dz() const
{
    return p2_.z() - p1_.z();
}

inline double KLineSegment3D::length() const
{
    double x = dx();
    double y = dy();
    double z = dz();
    return kSqrt(x*x + y*y + z*z);
}

inline double KLineSegment3D::lengthSquared() const
{
    double x = dx();
    double y = dy();
    double z = dz();
    return x * x + y * y + z * z;
}

inline KVector3D KLineSegment3D::toVector() const
{
    return p2_ - p1_;
}

inline KVector3D KLineSegment3D::toUnitVector() const
{
    KVector3D v(p2_ - p1_);
    v.normalize();
    return v;
}

inline void KLineSegment3D::translate(const KVector3D &dv)
{
    p1_.translate(dv);
    p2_.translate(dv);
}

inline void KLineSegment3D::translate(double dx, double dy, double dz)
{
    p1_.translate(dx, dy, dz);
    p2_.translate(dx, dy, dz);
}

inline void KLineSegment3D::translateX(double dx)
{
    p1_.translateX(dx);
    p2_.translateX(dx);
}

inline void KLineSegment3D::translateY(double dy)
{
    p1_.translateY(dy);
    p2_.translateY(dy);
}

inline void KLineSegment3D::translateZ(double dz)
{
    p1_.translateZ(dz);
    p2_.translateZ(dz);
}

inline KLineSegment3D KLineSegment3D::inverted() const
{
    return KLineSegment3D(p2_, p1_);
}

inline double KLineSegment3D::distanceFromPoint(double x, double y, double z)
const
{
    return distanceFromPoint(KVector3D(x, y, z));
}

inline double KLineSegment3D::distanceFromPoint(const KVector3D &p) const
{
    return kSqrt(distanceSquaredFromPoint(p));
}

inline double KLineSegment3D::distanceSquaredFromPoint(
        double x, double y, double z) const
{
    return distanceSquaredFromPoint(KVector3D(x, y, z));
}

inline double KLineSegment3D::distanceSquaredFromPoint(const KVector3D &p) const
{
    KVector3D pp1 = p1_ - p;
    KVector3D pp2 = p2_ - p;
    return KVector3D::crossProduct(pp1, pp2).lengthSquared() / lengthSquared();
}

inline KVector3D KLineSegment3D::symmetryPoint(const KVector3D &p) const
{
    KVector3D p12(p2_ - p1_);
    KVector3D p31(p1_ - p);
    double n = -KVector3D::dotProduct(p12, p31) / p12.lengthSquared();
    return KVector3D(2 * (p1_.x() + n * p12.x()) - p.x(),
                     2 * (p1_.y() + n * p12.y()) - p.y(),
                     2 * (p1_.z() + n * p12.z()) - p.z());
}

inline KLine3D KLineSegment3D::toLine() const
{
    return KLine3D(p1_, p2_, KLine3D::Point_Point);
}

inline KLineSegment3D KLineSegment3D::translated(const KVector3D &dv) const
{
    return KLineSegment3D(p1_ + dv, p2_ + dv);
}

inline bool KLineSegment3D::isParallelWith(const KLineSegment3D &line) const
{
    return KVector3D::crossProduct(toVector(), line.toVector()).isNull();
}

inline KVector3D KLineSegment3D::pedal(const KVector3D &point) const
{
    KVector3D d = p2_ - p1_;
    double t = KVector3D::dotProduct(point - p1_, d) / d.lengthSquared();
    return p1_ + d * t;
}

inline double KLineSegment3D::angle(const KLineSegment3D &line1,
                                    const KLineSegment3D &line2)
{
    return kRadiansToDegrees(radian(line1, line2));
}

inline KLineSegment3D &KLineSegment3D::operator=(const KLineSegment3D &line)
{
    p1_ = line.p1_;
    p2_ = line.p2_;
    return *this;
}

inline bool KLineSegment3D::operator==(const KLineSegment3D &line) const
{
    return p1_ == line.p1_ && p2_ == line.p2_;
}

inline bool KLineSegment3D::operator!=(const KLineSegment3D &line) const
{
    return !(*this == line);
}

#endif // KLINESEGMENT3D_H
