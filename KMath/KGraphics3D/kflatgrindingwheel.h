#ifndef KFLATGRINDINGWHEEL_H
#define KFLATGRINDINGWHEEL_H

#include <QVector>

#include "kcircle3d.h"
#include "kfrustum.h"

class KING_EXPORT KFlatGrindingWheel
{
public:
    enum Type {
        Big, // 大端在下
        Small // 小端在下
    };
    KFlatGrindingWheel();

    inline void setBigRadius(double radius);
    inline void setBottomFillet(double fillet);
    inline void setTopFillet(double fillet);
    inline void setAngle(double angle);
    inline void setWidth(double width);
    inline void setType(Type type);
    inline void setFilletRings(double slices);
    inline void setConeRings(double slices);
    inline void setBottomCenter(const KVector3D &center);
    inline void setNormal(const KVector3D &normal);

    inline double bigRadius() const;
    inline double bottomFillet() const;
    inline double topFillet() const;
    inline double angle() const;
    inline double width() const;
    inline Type type() const;
    inline const KVector3D &bottomCenter() const;
    inline KVector3D topCenter() const;
    inline const KVector3D &normal() const;
    double radiusAt(double height) const;
    bool contains(const KVector3D &p) const;
    KFrustum boundingFrustum() const;
    double topRadius() const;
    double bottomRadius() const;
    KCircle3D topCircle() const;
    KCircle3D bottomCircle() const;

    QVector<KCircle3D> split(int *num1 = nullptr,
                             int *num2 = nullptr,
                             int *num3 = nullptr) const;

private:
    double big_radius_ = 0;
    double bottom_fillet_ = 0;
    double top_fillet_ = 0;
    double angle_ = 0;
    double width_ = 0;
    Type type_ = Type::Big;
    int fillet_rings_ = 64;
    int cone_rings_ = 2;
    KVector3D bottom_center_;
    KVector3D normal_ = KVector3D(0, 0, 1);
};

inline void KFlatGrindingWheel::setBigRadius(double radius)
{
    big_radius_ = radius;
}

inline void KFlatGrindingWheel::setBottomFillet(double fillet)
{
    bottom_fillet_ = fillet;
}

inline void KFlatGrindingWheel::setTopFillet(double fillet)
{
    top_fillet_ = fillet;
}

inline void KFlatGrindingWheel::setAngle(double angle)
{
    angle_ = angle;
}

inline void KFlatGrindingWheel::setWidth(double width)
{
    width_ = width;
}

inline void KFlatGrindingWheel::setType(Type type)
{
    type_ = type;
}

inline void KFlatGrindingWheel::setFilletRings(double slices)
{
    fillet_rings_ = slices;
}

inline void KFlatGrindingWheel::setConeRings(double slices)
{
    cone_rings_ = slices;
}

inline void KFlatGrindingWheel::setBottomCenter(const KVector3D &center)
{
    bottom_center_ = center;
}

inline void KFlatGrindingWheel::setNormal(const KVector3D &normal)
{
    normal_ = normal;
    normal_.normalize();
}

inline double KFlatGrindingWheel::bigRadius() const
{
    return big_radius_;
}

inline double KFlatGrindingWheel::bottomFillet() const
{
    return bottom_fillet_;
}

inline double KFlatGrindingWheel::topFillet() const
{
    return top_fillet_;
}

inline double KFlatGrindingWheel::angle() const
{
    return angle_;
}

inline double KFlatGrindingWheel::width() const
{
    return width_;
}

inline const KVector3D &KFlatGrindingWheel::bottomCenter() const
{
    return bottom_center_;
}

inline KVector3D KFlatGrindingWheel::topCenter() const
{
    return bottom_center_ + normal_ * width_;
}

inline const KVector3D &KFlatGrindingWheel::normal() const
{
    return normal_;
}

inline KFlatGrindingWheel::Type KFlatGrindingWheel::type() const
{
    return type_;
}

#endif // KFLATGRINDINGWHEEL_H
