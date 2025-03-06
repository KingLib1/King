#ifndef POSTURE_H
#define POSTURE_H

#include "kmatrix4x4.h"
#include "keulerangles.h"
#include "krectcoordsystem3d.h"

class Posture
{
public:
    Posture();
    Posture(const KVector3D &pos, const KVector3D &euler_angles);
    Posture(const KVector3D &pos, const KEulerAngles &euler_angles);
    Posture(double x, double y, double z, double rx, double ry, double rz);
    Posture(const KMatrix4x4 &matrix);
    Posture(const KRectCoordSystem3D &sys);
    Posture(const Posture &other);
    ~Posture();

    inline void setPos(double x, double y, double z);
    inline void setPos(const KVector3D &pos);
    inline void setEulerAngles(double rx, double ry, double rz);
    inline void setEulerAngles(const KVector3D &euler_angles);
    inline void setEulerAngles(const KEulerAngles &euler_angles);

    inline const KVector3D &pos() const;
    inline const KEulerAngles &eulerAngles() const;
    inline double x() const {return pos_.x();}
    inline double y() const {return pos_.y();}
    inline double z() const {return pos_.z();}
    inline double rx() const {return euler_.rx();}
    inline double ry() const {return euler_.ry();}
    inline double rz() const {return euler_.rz();}
    inline KMatrix4x4 toMatrix() const;
    inline KRectCoordSystem3D toRectCoordinateSystem() const;

    inline static Posture createUserCoordinateSystem(
            const KVector3D &p1, const KVector3D &p2, const KVector3D &p3);

    inline Posture &operator=(const Posture &other);

private:
    KVector3D pos_;
    KEulerAngles euler_;
};

inline const KVector3D &Posture::pos() const
{
    return pos_;
}

inline const KEulerAngles &Posture::eulerAngles() const
{
    return euler_;
}

inline KMatrix4x4 Posture::toMatrix() const
{
    return KMatrix4x4(euler_.toMatrix(), pos_);
}

inline KRectCoordSystem3D Posture::toRectCoordinateSystem() const
{
    return KRectCoordSystem3D(toMatrix());
}

inline Posture Posture::createUserCoordinateSystem(
        const KVector3D &p1, const KVector3D &p2, const KVector3D &p3)
{
    return Posture(KRectCoordSystem3D::fromThreePoints(p1, p2, p3));
}

inline Posture &Posture::operator=(const Posture &other)
{
    pos_ = other.pos_;
    euler_ = other.euler_;
    return *this;
}

#endif // POSTURE_H
