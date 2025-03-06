#ifndef KSPHERE_H
#define KSPHERE_H

#include <QVector>

#include "kvector3d.h"
#include "KPair.h"

class KING_EXPORT KSphere
{
public:
    KSphere();
    KSphere(const KVector3D &center, double radius);
    KSphere(double radius);
    KSphere(const KSphere &sphere);
    ~KSphere();

    inline void setCenter(const KVector3D &center);
    inline void setRadius(double radius);
    inline void translate(const KVector3D &dv);

    inline const KVector3D &center() const;
    inline double radius() const;
    /**
     * @brief 从球的底部沿着z轴往上height高度所在xoy平面的圆的半径
     */
    inline double radiusAt(double height) const;
    /**
     * @brief 从球的底部沿着z轴往上半径为radius处的的高度(first下，second上）
     */
    KPair<double, double> heightAt(double radius) const;
    inline double diameter() const;
    inline double area() const;
    inline double volume() const;
    inline double distanceToSphere(const KSphere &sphere) const;
    inline bool collision(const KSphere &sphere) const;
    inline KSphere translated(const KVector3D &dv) const;
    /**
     * @brief 刃线
     * @param lead导程，dt拆分弧度
     */
    QVector<KVector3D> blade(double lead, double dt) const;
    /**
     * @brief lowerHalfBlade
     * @param lead 导程
     * @param dlen 拆分的弧长不超过dlen
     * @param ts 返回每个点的弧度
     * @return 每个点的坐标
     */
    QVector<KVector3D> lowerHalfBlade(double lead, double dlen, QVector<double> &ts) const;
    QVector<KVector3D> bladeInRange(double lead, double dlen, double t0,
                                    double t1, QVector<double> &ts) const;
    /**
     * @brief 刃线上任意点的位置
     * @param lead 导程
     * @param t 任意点弧度
     */
    KVector3D posOnBlade(double lead, double t) const;
    /**
     * @brief 刃线上任意点的切线
     * @param lead 导程
     * @param t 任意点弧度
     */
    KVector3D tangentOnBlade(double lead, double t) const;
    /**
     * @brief 刃线上任意点的位置和切线
     * @param lead导程
     * @param t 任意点弧度
     */
    KPair<KVector3D, KVector3D> posAndTanOnBlade(double lead, double t) const;

    inline KSphere &operator=(const KSphere &sphere);

private:
    KVector3D center_;
    double radius_;
};

inline void KSphere::setCenter(const KVector3D &center)
{
    center_ = center;
}

inline void KSphere::setRadius(double radius)
{
    radius_ = radius;
}

inline void KSphere::translate(const KVector3D &dv)
{
    center_ += dv;
}

inline const KVector3D &KSphere::center() const
{
    return center_;
}

inline double KSphere::radius() const
{
    return radius_;
}

inline double KSphere::radiusAt(double height) const
{
    return pythagoreanTheorem_Right(radius_ - height, radius_);
}

inline double KSphere::diameter() const
{
    return 2 * radius_;
}

inline double KSphere::area() const
{
    return 12.566370614359172954 * radius_ * radius_;
}

inline double KSphere::volume() const
{
    return 4.1887902047863909846 * radius_ * radius_ * radius_;
}

inline double KSphere::distanceToSphere(const KSphere &sphere) const
{
    return center_.distanceToPoint(sphere.center_);
}

inline bool KSphere::collision(const KSphere &sphere) const
{
    return (center_.distanceSquaredToPoint(sphere.center_) <=
            kSquare(radius_ + sphere.radius_));
}

inline KSphere KSphere::translated(const KVector3D &dv) const
{
    KSphere sphere(*this);
    sphere.center_ += dv;
    return sphere;
}

inline KSphere &KSphere::operator=(const KSphere &sphere)
{
    center_ = sphere.center_;
    radius_ = sphere.radius_;
    return *this;
}

#endif // KSPHERE_H
