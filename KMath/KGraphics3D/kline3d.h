#ifndef KLINE3D_H
#define KLINE3D_H

#include "kvector3d.h"

class KING_EXPORT KLine3D
{
public:
    enum CreateMode {
        Point_Point,
        Point_Direction
    };

    KLine3D();
    KLine3D(const KVector3D &v1, const KVector3D &v2, CreateMode mode);
    KLine3D(const KLine3D &line);
    ~KLine3D();

    inline void setLine(const KVector3D &p1, const KVector3D &p2);

    inline const KVector3D &point() const;
    inline const KVector3D &direction() const;
    inline KVector3D unitDirection() const;
    inline double distanceToLine(const KLine3D &line) const;

    inline KLine3D &operator=(const KLine3D &line);

private:
    KVector3D point_;
    KVector3D direction_; // 非单位
};

inline void KLine3D::setLine(const KVector3D &p1, const KVector3D &p2)
{
    point_ = p1;
    direction_ = p2 - p1;
}

inline const KVector3D &KLine3D::point() const
{
    return point_;
}

inline const KVector3D &KLine3D::direction() const
{
    return direction_;
}

inline KVector3D KLine3D::unitDirection() const
{
    return direction_.normalized();
}

inline double KLine3D::distanceToLine(const KLine3D &line) const
{
    KVector3D normal = KVector3D::crossProduct(direction_, line.direction_);
    if (normal.isNull()) {
        return kSqrt(KVector3D::crossProduct(
                         point_ - line.point_, direction_).lengthSquared() /
                     direction_.lengthSquared());
    }
    return KVector3D::dotProduct(point_ - line.point_, normal) /
            normal.length();
}

inline KLine3D &KLine3D::operator=(const KLine3D &line)
{
    point_ = line.point_;
    direction_ = line.direction_;
    return *this;
}

#endif // KLINE3D_H
