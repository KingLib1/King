#ifndef KFRUSTUM_H
#define KFRUSTUM_H

#include "kcircle3d.h"

// 坐标系设在底面圆心
class KING_EXPORT KFrustum
{
public:
    KFrustum();
    KFrustum(double bottom_radius, double top_radius, double length,
             const KRectCoordSystem3D &sys = KRectCoordSystem3D());
    KFrustum(const KFrustum &other);
    ~KFrustum();

    inline void setBottomRadius(double bottom_radius);
    inline void setTopRadius(double top_radius);
    inline void setLength(double length);
    inline void setBottomCenter(const KVector3D &center);
    inline void setTopCenter(const KVector3D &center);
    inline void setZAxis(const KVector3D &zaxis);
    inline void setCoordSystem(const KRectCoordSystem3D &sys);

    inline double bottomRadius() const;
    inline double topRadius() const;
    inline double radiusAt(double height) const;
    /**
     * @brief 在半径为radius处的高度
     */
    double heightAt(double radius) const;
    inline double length() const;
    inline const KVector3D &bottomCenter() const;
    inline const KRectCoordSystem3D &coordSystem() const;
    inline const KVector3D &zAxis() const;
    inline KCircle3D bottomCircle() const;
    inline KCircle3D topCircle() const;
    KCircle3D circleAt(double height) const;
    bool contains(const KVector3D &p) const;


    inline KFrustum &operator=(const KFrustum &other);

private:
    double bottom_radius_;
    double top_radius_;
    double length_;
    KRectCoordSystem3D sys_;
};

inline void KFrustum::setBottomRadius(double bottom_radius)
{
    bottom_radius_ = bottom_radius;
}

inline void KFrustum::setTopRadius(double top_radius)
{
    top_radius_ = top_radius;
}

inline void KFrustum::setLength(double length)
{
    length_ = length;
}

inline void KFrustum::setBottomCenter(const KVector3D &center)
{
    sys_.setOrigin(center);
}

inline void KFrustum::setTopCenter(const KVector3D &center)
{
    KVector3D bottom_center = center - zAxis() * length_;
    setBottomCenter(bottom_center);
}

inline void KFrustum::setZAxis(const KVector3D &zaxis)
{
    sys_.setZAxis(zaxis);
}

inline void KFrustum::setCoordSystem(const KRectCoordSystem3D &sys)
{
    sys_ = sys;
}

inline double KFrustum::bottomRadius() const
{
    return bottom_radius_;
}

inline double KFrustum::topRadius() const
{
    return top_radius_;
}

inline double KFrustum::radiusAt(double height) const
{
    return bottom_radius_ + (top_radius_ - bottom_radius_) / length_ * height;
}

inline double KFrustum::heightAt(double radius) const
{
    return (radius - bottom_radius_) * length_ / (top_radius_ - bottom_radius_);
}

inline double KFrustum::length() const
{
    return length_;
}

inline const KVector3D &KFrustum::bottomCenter() const
{
    return sys_.origin();
}

inline const KRectCoordSystem3D &KFrustum::coordSystem() const
{
    return sys_;
}

inline const KVector3D &KFrustum::zAxis() const
{
    return sys_.zAxis();
}

inline KCircle3D KFrustum::bottomCircle() const
{
    return KCircle3D(sys_.origin(), bottom_radius_, -sys_.zAxis());
}

inline KCircle3D KFrustum::topCircle() const
{
    return KCircle3D(sys_.origin() + sys_.zAxis() * length_, top_radius_,
                     sys_.zAxis());
}

inline KFrustum &KFrustum::operator=(const KFrustum &other)
{
    bottom_radius_ = other.bottom_radius_;
    top_radius_ = other.top_radius_;
    length_ = other.length_;
    sys_ = other.sys_;
    return *this;
}

#endif // KFRUSTUM_H
