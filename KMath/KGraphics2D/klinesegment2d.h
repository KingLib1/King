#ifndef KLINESEGMENT2D_H
#define KLINESEGMENT2D_H

#include <QVector>

#include "kvector2d.h"
#include "krange.h"

class KRect;

class KING_EXPORT KLineSegment2D
{
public:
    enum IntersectType {
        NoIntersection,   // 平行
        BoundedIntersection,  // 有交点且交点都不在直线两端
        UnboundedIntersection  // 不平行没交点或不平行但交点在某直线两端
    };

    KLineSegment2D();
    KLineSegment2D(double x1, double y1, double x2, double y2);
    KLineSegment2D(const KPointF &p1, const KPointF &p2);
    KLineSegment2D(const KLineSegment2D &line);
    /**
     * @brief 起点为（0， 0），终点为v
     * @param v
     */
    KLineSegment2D(const KVector2D &v);
    /**
     * @brief 起点为v1, 终点为v2
     * @param v1
     * @param v2
     */
    KLineSegment2D(const KVector2D &v1, const KVector2D &v2);
    ~KLineSegment2D();

    KRect boundingRect() const;

    inline void setP1(const KPointF &p1);
    inline void setP1(double x, double y);
    inline const KPointF &p1() const {return p1_;}
    inline void setP2(const KPointF &p2);
    inline void setP2(double x, double y);
    inline const KPointF &p2() const {return p2_;}
    inline double x1() const {return p1_.x();}
    inline double y1() const {return p1_.y();}
    inline double x2() const {return p2_.x();}
    inline double y2() const {return p2_.y();}
    inline double dx() const {return p2_.x() - p1_.x();}
    inline double dy() const {return p2_.y() - p1_.y();}
    inline KPointF center() const;
    inline double lengthSquared() const;
    inline double length() const;
    /**
     * @brief DDA数值微分法生成像素点
     */
    QVector<KPointF> DDA() const;

    inline void setLine(double x1, double y1, double x2, double y2);
    inline void setPoints(const KPointF &p1, const KPointF &p2);
    /**
     * @brief x轴正方向与直线逆时针方向夹角，0-360，不包括360
     */
    inline double angle() const;
    /**
     * @brief 返回直线到给定直线逆时针旋转角度
     */
    double angleTo(const KLineSegment2D &line) const;
    inline double radian() const;
    double radianTo(const KLineSegment2D &line) const;
    void setAngle(double angle);
    void invert();
    /**
     * @brief 线段上离该点最近的点到该点的距离
     */
    inline double nearestDistanceFromPoint(const KPointF &p) const;
    double nearestDistanceFromPoint(double x, double y) const;
    inline double nearestDistanceSquareFromPoint(const KPointF &p) const;
    double nearestDistanceSquareFromPoint(double x, double y) const;
    /**
     * @brief 点到直线的距离，直线由线段两点无限延伸
     */
    inline double distanceFromPointToLine(const KPointF &p) const;
    inline double distanceSquareFromPointToLine(const KPointF &p) const;

    void setLength(double length);
    inline void translate(double dx, double dy);
    inline void translate(const KPointF &offset);
    inline KLineSegment2D translated(double dx, double dy) const;
    inline KLineSegment2D translated(const KPointF &offset) const;
    inline KLineSegment2D unitVector() const;
    inline KVector2D toVector() const;
    inline KLineSegment2D normalLine() const;
    inline KRange xRange() const;
    inline KRange yRange() const;
    inline char maxChangeDirection() const;
    bool intersects(const KLineSegment2D &line) const; // 快速排斥 & 跨立试验
    KLineSegment2D::IntersectType intersect(const KLineSegment2D &line,
                                            KPointF *intersection) const;
    KPointF nearestPoint(const KPointF &point) const;
    /**
     * @brief 最近点离起点的比例值
     */
    double nearestPointScale(const KPointF &p) const;

private:
    KPointF p1_;
    KPointF p2_;
};

inline KPointF KLineSegment2D::center() const
{
    return KPointF((p1_.x() + p2_.x()) / 2, (p1_.y() + p2_.y()) / 2);
}

inline double KLineSegment2D::lengthSquared() const
{
    return kSquareSum(dx(), dy());
}

inline double KLineSegment2D::length() const
{
    return kSqrt(lengthSquared());
}

inline void KLineSegment2D::setP1(const KPointF &p1)
{
    p1_ = p1;
}

inline void KLineSegment2D::setP1(double x, double y)
{
    p1_.setXY(x, y);
}

inline void KLineSegment2D::setP2(const KPointF &p2)
{
    p2_ = p2;
}

inline void KLineSegment2D::setP2(double x, double y)
{
    p2_.setXY(x, y);
}

inline void KLineSegment2D::setLine(double x1, double y1, double x2, double y2)
{
    p1_.setXY(x1, y1);
    p2_.setXY(x2, y2);
}

inline void KLineSegment2D::setPoints(const KPointF &p1, const KPointF &p2)
{
    p1_ = p1;
    p2_ = p2;
}

inline double KLineSegment2D::angle() const
{
    return kRadiansToDegrees(radian());
}

inline double KLineSegment2D::radian() const
{
    double radian = kAtan2(dy(), dx());
    if (radian < 0)
        radian += K_2PI;
    return radian;
}

inline double KLineSegment2D::nearestDistanceFromPoint(const KPointF &p) const
{
    return nearestDistanceFromPoint(p.x(), p.y());
}

inline double KLineSegment2D::nearestDistanceSquareFromPoint(const KPointF &p) const
{
    return nearestDistanceSquareFromPoint(p.x(), p.y());
}

inline double KLineSegment2D::distanceFromPointToLine(const KPointF &p) const
{
    KVector2D p12(dx(), dy());
    KVector2D p13(p1_, p);
    return kFabs(KVector2D::crossProduct(p12, p13)) / p12.length();
}

inline double KLineSegment2D::distanceSquareFromPointToLine(const KPointF &p) const
{
    KVector2D p12(dx(), dy());
    KVector2D p13(p1_, p);
    return kSquare(KVector2D::crossProduct(p12, p13)) / p12.lengthSquared();
}

inline void KLineSegment2D::translate(double dx, double dy)
{
    p1_.translate(dx, dy);
    p2_.translate(dx, dy);
}

inline void KLineSegment2D::translate(const KPointF &offset)
{
    p1_ += offset;
    p2_ += offset;
}

inline KLineSegment2D KLineSegment2D::translated(double dx, double dy) const
{
    return KLineSegment2D(p1_.x() + dx, p1_.y() + dy, p2_.x() + dx, p2_.y() + dy);
}

inline KLineSegment2D KLineSegment2D::translated(const KPointF &offset) const
{
    return KLineSegment2D(p1_.x() + offset.x(), p1_.y() + offset.y(),
                   p2_.x() + offset.x(), p2_.y() + offset.y());
}

inline KLineSegment2D KLineSegment2D::unitVector() const
{
    KLineSegment2D unit(*this);
    unit.setLength(1);
    return unit;
}

inline KVector2D KLineSegment2D::toVector() const
{
    return KVector2D(p1_, p2_);
}

inline KLineSegment2D KLineSegment2D::normalLine() const
{
    return KLineSegment2D(p1_.x(), p1_.y(),
                          p1_.x() + p1_.y() - p2_.y(), p1_.y() + p2_.x() - p1_.x());
}

inline KRange KLineSegment2D::xRange() const
{
    if (p1_.x() < p2_.x())
        return KRange(p1_.x(), p2_.x());
    return KRange(p2_.x(), p1_.x());
}

inline KRange KLineSegment2D::yRange() const
{
    if (p1_.y() < p2_.y())
        return KRange(p1_.y(), p2_.y());
    return KRange(p2_.y(), p1_.y());
}

inline char KLineSegment2D::maxChangeDirection() const
{
    return kFabs(dx()) >= kFabs(dy()) ? 'x' : 'y';
}

#endif // KLINESEGMENT2D_H
