#ifndef KARC3D_H
#define KARC3D_H

#include <QVector>

#include "karc2d.h"
#include "krectcoordsystem3d.h"

/**
 * @brief The KArc3D class
 * 圆弧自身拥有坐标系，圆心为原点，第一个点位于x轴上，在自己的xoy平面上为逆时针圆弧
 */

class KING_EXPORT KArc3D
{
public:
    KArc3D();
    KArc3D(double radius, double span_angle, const KRectCoordSystem3D &sys = KRectCoordSystem3D());
    KArc3D(const KArc2D &arc);
    KArc3D(const KArc3D &arc);
    KArc3D(const KVector3D &v1, const KVector3D &v2, const KVector3D &v3,
           King::ArcCreateMode mode = King::TangentPointPoint);

    inline void setCenter(const KVector3D &center);
    inline void setRadius(double radius);
    inline void setSpanRadian(double radian);
    inline void setSpanAngle(double angle);
    inline void setCoordSys(const KRectCoordSystem3D &sys);
    inline void transpose();
    inline void translate(const KVector3D &dv);
    QVector<KVector3D> splitToKVector3D(int slices) const;

    inline const KVector3D &center() const;
    inline double radius() const {return radius_;}
    inline double spanRadian() const {return span_;}
    inline double spanAngle() const;
    inline KVector3D startPos() const;
    inline KVector3D endPos() const;
    inline KVector3D startCenterVector() const;
    inline KVector3D endCenterVector() const;
    inline KVector3D midPos() const;
    KVector3D pos(double radian, bool &success);
    inline const KVector3D &normal() const;
    inline KVector3D startTangent() const;
    inline KVector3D endTangent() const;
    inline double arcLength() const;

    inline KArc3D &operator=(const KArc3D &arc);

private:
    inline const KVector3D &xAxis() const;
    inline const KVector3D &yAxis() const;

    double radius_;
    double span_;  // 跨越弧度
    KRectCoordSystem3D sys_;
};

inline void KArc3D::setCenter(const KVector3D &center)
{
    sys_.setOrigin(center);
}

inline void KArc3D::setRadius(double radius)
{
    radius_ = radius;
}

inline void KArc3D::setSpanRadian(double radian)
{
    span_ = radian;
}

inline void KArc3D::setSpanAngle(double angle)
{
    span_ = kDegreesToRadians(angle);
}

inline void KArc3D::setCoordSys(const KRectCoordSystem3D &sys)
{
    sys_ = sys;
}

inline void KArc3D::transpose()
{
    sys_.setZXAxis(-normal(), endCenterVector());
}

inline void KArc3D::translate(const KVector3D &dv)
{
    sys_.translateByBase(dv);
}

inline const KVector3D &KArc3D::center() const
{
    return sys_.origin();
}

inline double KArc3D::spanAngle() const
{
    return kRadiansToDegrees(span_);
}

inline KVector3D KArc3D::startPos() const
{
    return radius_ * xAxis() + center();
}

inline KVector3D KArc3D::endPos() const
{
    double x = radius_ * kCos(span_);
    double y = radius_ * kSin(span_);
    return x * xAxis() + y * yAxis() + center();
}

inline KVector3D KArc3D::startCenterVector() const
{
    return startPos() - center();
}

inline KVector3D KArc3D::endCenterVector() const
{
    return endPos() - center();
}

inline KVector3D KArc3D::midPos() const
{
    double radian = 0.5 * span_;
    double x = radius_ * kCos(radian);
    double y = radius_ * kSin(radian);
    return x * xAxis() + y * yAxis() + center();
}

inline const KVector3D &KArc3D::normal() const
{
    return sys_.zAxis();
}

inline KVector3D KArc3D::startTangent() const
{
    return yAxis();
}

inline KVector3D KArc3D::endTangent() const
{
    KVector2D tan(0, 1);
    tan.rotateRadian(span_);
    return tan.x() * xAxis() + tan.y() * yAxis();
}

inline double KArc3D::arcLength() const
{
    return span_ * radius_;
}

inline KArc3D &KArc3D::operator=(const KArc3D &arc)
{
    radius_ = arc.radius_;
    span_ = arc.span_;
    sys_ = arc.sys_;
    return *this;
}

inline const KVector3D &KArc3D::xAxis() const
{
    return sys_.xAxis();
}

inline const KVector3D &KArc3D::yAxis() const
{
    return sys_.yAxis();
}

#endif // KARC3D_H
