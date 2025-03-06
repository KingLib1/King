#ifndef KELLIPTICCYLINDER_H
#define KELLIPTICCYLINDER_H

#include "kellipse3d.h"
#include "kcuboid.h"

class KING_EXPORT KEllipticCylinder
{
public:
    KEllipticCylinder();
    KEllipticCylinder(double a, double b, double height);
    KEllipticCylinder(double a, double b, double height,
                      const KRectCoordSystem3D &sys);
    ~KEllipticCylinder();

    inline void setA(double a);
    inline void setB(double b);
    inline void setHeight(double height);
    inline void setCenter(const KVector3D &center);
    inline void translateByBase(const KVector3D &dv);
    inline void translateBySelf(const KVector3D &dv);

    inline double a() const;
    inline double b() const;
    inline double height() const;
    inline const KVector3D &center() const;
    inline const KVector3D &zAxis() const;
    inline double volume() const;
    inline KCuboid boundingVolume() const;
    inline KVector3D bottomCenter() const;
    inline KVector3D topCenter() const;
    inline KEllipse3D bottomEllipse() const;
    inline KEllipse3D topEllipse() const;

private:
    double a_;
    double b_;
    double height_;
    KRectCoordSystem3D sys_;
};

inline void KEllipticCylinder::setA(double a)
{
    a_ = a;
}

inline void KEllipticCylinder::setB(double b)
{
    b_ = b;
}

inline void KEllipticCylinder::setHeight(double height)
{
    height_ = height;
}

inline void KEllipticCylinder::setCenter(const KVector3D &center)
{
    sys_.setOrigin(center);
}

inline void KEllipticCylinder::translateByBase(const KVector3D &dv)
{
    sys_.translateByBase(dv);
}

inline void KEllipticCylinder::translateBySelf(const KVector3D &dv)
{
    sys_.translateBySelf(dv);
}

inline double KEllipticCylinder::a() const
{
    return a_;
}

inline double KEllipticCylinder::b() const
{
    return b_;
}

inline double KEllipticCylinder::height() const
{
    return height_;
}

inline const KVector3D &KEllipticCylinder::center() const
{
    return sys_.origin();
}

inline const KVector3D &KEllipticCylinder::zAxis() const
{
    return sys_.zAxis();
}

inline double KEllipticCylinder::volume() const
{
    return K_PI * a_ * b_;
}

inline KCuboid KEllipticCylinder::boundingVolume() const
{
    return KCuboid(2 * a_, 2 * b_, height_, sys_);
}

inline KVector3D KEllipticCylinder::bottomCenter() const
{
    return center() - zAxis() * (height_ / 2);
}

inline KVector3D KEllipticCylinder::topCenter() const
{
    return center() + zAxis() * (height_ / 2);
}

inline KEllipse3D KEllipticCylinder::bottomEllipse() const
{
    KRectCoordSystem3D sys(bottomCenter(), -zAxis(), sys_.xAxis(),
                                King::ZX_Axis);
    return KEllipse3D(a_, b_, sys);
}

inline KEllipse3D KEllipticCylinder::topEllipse() const
{
    KRectCoordSystem3D sys(topCenter(), zAxis(), sys_.xAxis(),
                                King::ZX_Axis);
    return KEllipse3D(a_, b_, sys);
}

#endif // KELLIPTICCYLINDER_H
