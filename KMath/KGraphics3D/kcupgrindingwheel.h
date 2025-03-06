#ifndef KCUPGRINDINGWHEEL_H
#define KCUPGRINDINGWHEEL_H

#include "kcircle3d.h"
#include "kflatgrindingwheel.h"

class KING_EXPORT KCupGrindingWheel
{
public:
    KCupGrindingWheel();

    inline void setRadius(double radius);
    inline void setFillet(double fillet);
    inline void setExternalDepth(double depth);
    inline void setInternalDepth(double depth);
    inline void setAbrasiveWidth(double width);
    inline void setExternalAngle(double angle);
    inline void setInternalAngle(double angle);
    inline void setBottomCenter(const KVector3D &center);
    inline void setNormal(const KVector3D &normal);

    inline double radius() const;
    inline double fillet() const;
    inline double externalDepth() const;
    inline double internalDepth() const;
    inline double abrasiveWidth() const;
    inline double externalAngle() const;
    inline double internalAngle() const;
    inline const KVector3D &bottomCenter() const;
    inline const KVector3D &normal() const;
    double externalRadiusAt(double height) const;
    KFrustum boundingFrustum() const;
    KFlatGrindingWheel toFlatGrindingWheel() const;

    bool contains(const KVector3D &p) const;

    QVector<KCircle3D> split() const;

private:
    double radius_ = 0; // 半径
    double fillet_ = 0; // 圆角
    double external_depth_ = 0; // 外部深度
    double internal_depth_ = 0; // 内部深度
    double abrasive_width_ = 0; // 磨料宽度
    double external_angle_ = 0; // 外角
    double internal_angle_ = 0; // 内角
    KVector3D normal_ = KVector3D(0, 0, 1);
    KVector3D bottom_center_;
};

inline void KCupGrindingWheel::setRadius(double radius)
{
    radius_ = radius;
}

inline void KCupGrindingWheel::setFillet(double fillet)
{
    fillet_ = fillet;
}

inline void KCupGrindingWheel::setExternalDepth(double depth)
{
    external_depth_ = depth;
}

inline void KCupGrindingWheel::setInternalDepth(double depth)
{
    internal_depth_ = depth;
}

inline void KCupGrindingWheel::setAbrasiveWidth(double width)
{
    abrasive_width_ = width;
}

inline void KCupGrindingWheel::setExternalAngle(double angle)
{
    external_angle_ = angle;
}

inline void KCupGrindingWheel::setInternalAngle(double angle)
{
    internal_angle_ = angle;
}

inline void KCupGrindingWheel::setBottomCenter(const KVector3D &center)
{
    bottom_center_ = center;
}

inline void KCupGrindingWheel::setNormal(const KVector3D &normal)
{
    normal_ = normal;
}

inline double KCupGrindingWheel::radius() const
{
    return radius_;
}

inline double KCupGrindingWheel::fillet() const
{
    return fillet_;
}

inline double KCupGrindingWheel::externalDepth() const
{
    return external_depth_;
}

inline double KCupGrindingWheel::internalDepth() const
{
    return internal_depth_;
}

inline double KCupGrindingWheel::abrasiveWidth() const
{
    return abrasive_width_;
}

inline double KCupGrindingWheel::externalAngle() const
{
    return external_angle_;
}

inline double KCupGrindingWheel::internalAngle() const
{
    return internal_angle_;
}

inline const KVector3D &KCupGrindingWheel::bottomCenter() const
{
    return bottom_center_;
}

inline const KVector3D &KCupGrindingWheel::normal() const
{
    return normal_;
}

#endif // KCUPGRINDINGWHEEL_H
