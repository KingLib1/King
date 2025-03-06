#ifndef KVECTOR4D_H
#define KVECTOR4D_H

#include "kvector3d.h"

class KING_EXPORT KVector4D
{
public:
    KVector4D();
    KVector4D(double x, double y, double z);
    KVector4D(const KVector3D &v);
    KVector4D(double x, double y, double z, double w);
    KVector4D(const KVector3D &v, double w);
    inline double x() const {return x_;}
    inline double y() const {return y_;}
    inline double z() const {return z_;}
    inline double w() const {return w_;}
    inline void setX(double x) {x_ = x;}
    inline void setY(double y) {y_ = y;}
    inline void setZ(double z) {z_ = z;}
    inline void setW(double w) {w_ = w;}
    inline KVector3D toVector3D() const {return KVector3D(x_, y_, z_);}

    void normalize();
    inline double length() const;
    inline double lengthSquared() const;

private:
    double x_;
    double y_;
    double z_;
    double w_;
};

inline double KVector4D::length() const
{
    return kSqrt(lengthSquared());
}

inline double KVector4D::lengthSquared() const
{
    return x_*x_ + y_*y_ + z_*z_ + w_*w_;
}

#endif // KVECTOR4D_H
