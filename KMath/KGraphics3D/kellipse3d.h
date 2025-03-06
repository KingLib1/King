#ifndef KELLIPSE3D_H
#define KELLIPSE3D_H

#include "krectcoordsystem3d.h"
#include "kray3d.h"

class KING_EXPORT KEllipse3D
{
public:
    KEllipse3D();
    KEllipse3D(double a, double b);
    KEllipse3D(double a, double b, const KRectCoordSystem3D &sys);
    KEllipse3D(const KEllipse3D &ell);
    ~KEllipse3D();

    inline void setAB(double a, double b);
    inline void setA(double a);
    inline void setB(double b);
    inline void setCenter(const KVector3D &center);
    inline void setXYAxis(const KVector3D &xaxis, const KVector3D &yaxis);
    inline void setZXAxis(const KVector3D &zaxis, const KVector3D &xaxis);
    inline void translate(const KVector3D &dv);
    inline void translate(double dx, double dy, double dz);

    inline KVector3D right() const;
    inline KVector3D top() const;
    inline KVector3D left() const;
    inline KVector3D bottom() const;
    inline KVector3D leftFocus() const;
    inline KVector3D rightFocus() const;
    inline double area() const;
    inline const KVector3D &center() const;
    inline const KVector3D &xAxis() const;
    inline const KVector3D &yAxis() const;
    inline const KVector3D &normal() const;
    inline double a() const {return a_;}
    inline double b() const {return b_;}
    inline double c() const;
    inline double focalLength() const;
    inline KEllipse3D translated(const KVector3D &dv) const;
    inline KEllipse3D translated(double dx, double dy, double dz) const;
    bool intersects(const KRay3D &ray) const;
    KVector3D intersection(const KRay3D &ray, bool *success = nullptr) const;

    inline KEllipse3D &operator=(const KEllipse3D &ellipse);

private:
    KRectCoordSystem3D sys_;
    double a_;
    double b_;
};

inline void KEllipse3D::setAB(double a, double b)
{
    a_ = a;
    b_ = b;
}

inline void KEllipse3D::setA(double a)
{
    a_ = a;
}

inline void KEllipse3D::setB(double b)
{
    b_ = b;
}

inline void KEllipse3D::setCenter(const KVector3D &center)
{
    sys_.setOrigin(center);
}

inline void KEllipse3D::setXYAxis(const KVector3D &xaxis,
                                  const KVector3D &yaxis)
{
    sys_.setXYAxis(xaxis, yaxis);
}

inline void KEllipse3D::setZXAxis(const KVector3D &zaxis,
                                  const KVector3D &xaxis)
{
    sys_.setZXAxis(zaxis, xaxis);
}

inline void KEllipse3D::translate(const KVector3D &dv)
{
    sys_.translateByBase(dv);
}

inline void KEllipse3D::translate(double dx, double dy, double dz)
{
    sys_.translateByBase(dx, dy, dz);
}

inline KVector3D KEllipse3D::right() const
{
    return xAxis() * a_ + center();
}

inline KVector3D KEllipse3D::top() const
{
    return yAxis() * b_ + center();
}

inline KVector3D KEllipse3D::left() const
{
    return center() - a_ * xAxis();
}

inline KVector3D KEllipse3D::bottom() const
{
    return center() - b_ * yAxis();
}

inline KVector3D KEllipse3D::leftFocus() const
{
    double c = kSqrt(a_ * a_ - b_ * b_);
    return center() - xAxis() * c;
}

inline KVector3D KEllipse3D::rightFocus() const
{
    double c = kSqrt(a_ * a_ - b_ * b_);
    return center() + xAxis() * c;
}

inline double KEllipse3D::area() const
{
    return K_PI * a_ * b_;
}

inline const KVector3D &KEllipse3D::center() const
{
    return sys_.origin();
}

inline const KVector3D &KEllipse3D::xAxis() const
{
    return sys_.xAxis();
}

inline const KVector3D &KEllipse3D::yAxis() const
{
    return sys_.yAxis();
}

inline const KVector3D &KEllipse3D::normal() const
{
    return sys_.zAxis();
}

inline double KEllipse3D::c() const
{
    return kSqrt(kFabs(a_ * a_ - b_ * b_));
}

inline double KEllipse3D::focalLength() const
{
    return 2 * c();
}

inline KEllipse3D KEllipse3D::translated(const KVector3D &dv) const
{
    KEllipse3D ell(*this);
    ell.sys_.translateByBase(dv);
    return ell;
}

inline KEllipse3D KEllipse3D::translated(double dx, double dy, double dz) const
{
    KEllipse3D ell(*this);
    ell.sys_.translateByBase(dx, dy, dz);
    return ell;
}

inline KEllipse3D &KEllipse3D::operator=(const KEllipse3D &ellipse)
{
    sys_ = ellipse.sys_;
    a_ = ellipse.a_;
    b_ = ellipse.b_;
    return *this;
}

#endif // KELLIPSE3D_H
