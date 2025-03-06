#ifndef KRAY3D_H
#define KRAY3D_H

#include "klinesegment3d.h"

class KING_EXPORT KRay3D
{
public:
    KRay3D();
    KRay3D(const KVector3D &origin, const KVector3D &direction, double length);
    KRay3D(const KRay3D &ray);
    ~KRay3D();

    inline void setOrigin(const KVector3D &origin);
    inline void setDirection(const KVector3D &direction);
    inline void setLength(double length);

    inline const KVector3D &origin() const;
    inline KVector3D end() const;
    inline const KVector3D &direction() const;
    inline double length() const;
    inline KLineSegment3D toLineSegment() const;

    inline KRay3D &operator=(const KRay3D &ray);

private:
    KVector3D origin_;
    KVector3D direction_;
    double length_;
};

inline void KRay3D::setOrigin(const KVector3D &origin)
{
    origin_ = origin;
}

inline void KRay3D::setDirection(const KVector3D &direction)
{
    direction_ = direction;
    direction_.normalize();
}

inline void KRay3D::setLength(double length)
{
    length_ = length;
}

inline const KVector3D &KRay3D::origin() const
{
    return origin_;
}

inline KVector3D KRay3D::end() const
{
    return origin_ + direction_ * length_;
}

inline const KVector3D &KRay3D::direction() const
{
    return direction_;
}

inline double KRay3D::length() const
{
    return length_;
}

inline KLineSegment3D KRay3D::toLineSegment() const
{
    return KLineSegment3D(origin_, end());
}

inline KRay3D &KRay3D::operator=(const KRay3D &ray)
{
    origin_ = ray.origin_;
    direction_ = ray.direction_;
    length_ = ray.length_;
    return *this;
}

#endif // KRAY3D_H
