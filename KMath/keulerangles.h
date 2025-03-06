#ifndef KEULERANGLES_H
#define KEULERANGLES_H

#include "krectcoordsystem3d.h"

// 绕原来的x-y-z
class KING_EXPORT KEulerAngles
{
public:
    KEulerAngles();
    KEulerAngles(double rx, double ry, double rz);
    KEulerAngles(const KVector3D &euler);
    KEulerAngles(const KMatrix3x3 &matrix);
    KEulerAngles(const KVector3D &xaxis, const KVector3D &yaxis,
                 const KVector3D &zaxis);
    KEulerAngles(const KMatrix4x4 &matrix);
    KEulerAngles(const KRectCoordSystem3D &rect);
    KEulerAngles(const KEulerAngles &other);
    ~KEulerAngles();

    inline void setRx(double rx);
    inline void setRy(double ry);
    inline void setRz(double rz);
    inline void setRxyz(double rx, double ry, double rz);
    inline void setRxyz(const KVector3D &euler);

    inline double rx() const;
    inline double ry() const;
    inline double rz() const;
    inline const KVector3D &vector3D() const;
    KMatrix3x3 toMatrix() const;

    inline KEulerAngles &operator=(const KEulerAngles &other);

private:
    // rx,ry,rz均以角度值表示
    KVector3D euler_;
};

inline void KEulerAngles::setRx(double rx)
{
    euler_.setX(rx);
}

inline void KEulerAngles::setRy(double ry)
{
    euler_.setY(ry);
}

inline void KEulerAngles::setRz(double rz)
{
    euler_.setZ(rz);
}

inline void KEulerAngles::setRxyz(double rx, double ry, double rz)
{
    euler_.setXYZ(rx, ry, rz);
}

inline void KEulerAngles::setRxyz(const KVector3D &euler)
{
    euler_ = euler;
}

inline double KEulerAngles::rx() const
{
    return euler_.x();
}

inline double KEulerAngles::ry() const
{
    return euler_.y();
}

inline double KEulerAngles::rz() const
{
    return euler_.z();
}

inline const KVector3D &KEulerAngles::vector3D() const
{
    return euler_;
}

inline KEulerAngles &KEulerAngles::operator=(const KEulerAngles &other)
{
    euler_ = other.euler_;
    return *this;
}

#endif // KEULERANGLES_H
