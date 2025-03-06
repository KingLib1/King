#ifndef KARC2D_H
#define KARC2D_H

#include "KGraphics2D/krect.h"
#include "kmath.h"
#include "klinesegment2d.h"
#include "kvector2d.h"
#include "King.h"

class KING_EXPORT KArc2D
{
public:
    KArc2D();
    KArc2D(const KArc2D &arc);
    KArc2D(double cx, double cy, double radius, double start_angle,
           double span_angle);
    KArc2D(const KPointF &center, double radius, double start_angle,
           double span_angle);
    KArc2D(const KVector2D &v1, const KVector2D &v2, const KVector2D &v3,
           King::ArcCreateMode mode);
    void setArc(const KVector2D &v1, const KVector2D &v2, const KVector2D &v3,
                King::ArcCreateMode mode);
    KArc2D(const KPointF &start, const KPointF &end, double span_radian);

    inline KPointF startPos() const;
    inline KPointF endPos() const;
    inline KPointF midPos() const;
    inline KPointF pos(double angle) const;
    /**
     * @brief 图形上距离point最近的点
     */
    KPointF nearestPoint(const KPointF &point) const;
    /**
     * @brief 图形上距离point最近的点与point的距离
     */
    double nearestDistance(const KPointF &point) const;
    inline const KPointF &center() const {return center_;}
    inline double cx() const {return center_.x();}
    inline double cy() const {return center_.y();}
    inline double radius() const {return radius_;}
    inline double startAngle() const {return start_angle_;}
    inline double spanAngle() const;
    inline KLineSegment2D startLine() const;
    inline KLineSegment2D endLine() const;
    inline KVector2D startVector() const;
    inline KVector2D endVector() const;
    inline double spanRadian() const;
    KRect boundingRect() const;
    inline bool isClockwise() const;
    KVector2D startTangent() const;
    KVector2D endTangent() const;

    inline void setStartAngle(double angle);
    inline void setRadius(double radius);
    inline void setCenter(const KPointF &center);
    inline void setSpanAngle(double angle);

    KArc2D &operator=(const KArc2D &rhs);

private:
    bool containAngle(double angle) const;
    double normalizeAngle(double angle) const; // 0-360

    KPointF center_;
    double radius_;
    double start_angle_;
    double span_angle_;
};

inline KPointF KArc2D::startPos() const
{
    double radian = kDegreesToRadians(start_angle_);
    return KPointF(center_.x() + radius_ * kCos(radian),
                   center_.y() + radius_ * kSin(radian));
}

inline KPointF KArc2D::endPos() const
{
    double radian = kDegreesToRadians(start_angle_ + span_angle_);
    return KPointF(center_.x() + radius_ * kCos(radian),
                   center_.y() + radius_ * kSin(radian));
}

inline KPointF KArc2D::midPos() const
{
    double radian = kDegreesToRadians(start_angle_ + span_angle_ * 0.5);
    return KPointF(center_.x() + radius_ * kCos(radian),
                   center_.y() + radius_ * kSin(radian));
}

KPointF KArc2D::pos(double angle) const
{
    double radian = kDegreesToRadians(angle);
    return KPointF(center_.x() + radius_ * kCos(radian),
                   center_.y() + radius_ * kSin(radian));
}

inline double KArc2D::spanAngle() const
{
    return span_angle_;
}

inline KLineSegment2D KArc2D::startLine() const
{
    return KLineSegment2D(center_, startPos());
}

inline KLineSegment2D KArc2D::endLine() const
{
    return KLineSegment2D(center_, endPos());
}

inline KVector2D KArc2D::startVector() const
{
    return KVector2D(center_, startPos());
}

inline KVector2D KArc2D::endVector() const
{
    return KVector2D(center_, endPos());
}

inline double KArc2D::spanRadian() const
{
    return kDegreesToRadians(spanAngle());
}

inline bool KArc2D::isClockwise() const
{
    return span_angle_ < 0;
}

inline void KArc2D::setStartAngle(double angle)
{
    start_angle_ = normalizeAngle(angle);
}

inline void KArc2D::setRadius(double radius)
{
    radius_ = radius;
}

inline void KArc2D::setCenter(const KPointF &center)
{
    center_ = center; 
}

inline void KArc2D::setSpanAngle(double angle)
{
    span_angle_ = angle;
}

#endif // KARC2D_H
