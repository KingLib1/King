#ifndef KQUATERNION_H
#define KQUATERNION_H

#include <QQuaternion>

#include "kvector4d.h"

class KING_EXPORT KQuaternion
{
public:
    KQuaternion();
    KQuaternion(double scalar, double x, double y, double z);
    KQuaternion(double scalar, const KVector3D &v);
    KQuaternion(const KVector4D &v);
    KQuaternion(const KQuaternion &q);
    ~KQuaternion();

    inline void setScalar(double scalar) {s_ = scalar;}
    inline void setX(double x) {v_.setX(x);}
    inline void setY(double y) {v_.setY(y);}
    inline void setZ(double z) {v_.setZ(z);}
    inline void setVector(double x, double y, double z) {v_.setXYZ(x, y, z);}
    inline void setVector(const KVector3D &vector) {v_ = vector;}
    inline void normalize();

    inline double scalar() const {return s_;}
    inline double x() const {return v_.x();}
    inline double y() const {return v_.y();}
    inline double z() const {return v_.z();}
    inline const KVector3D &vector() const {return v_;}
    inline KVector4D toVector4D() const {return KVector4D(v_, s_);}
    inline KQuaternion conjugated() const {return KQuaternion(s_, -v_);}
    inline double length() const;
    inline double lengthSquared() const;
    inline KQuaternion normalized() const;
    inline KQuaternion inverted() const;
    inline bool isIdentity() const;
    inline bool isNull() const;
    static double dotProduct(const KQuaternion &q1, const KQuaternion &q2);
    static double angleCosine(const KQuaternion &q1, const KQuaternion &q2);
    
    inline KQuaternion &operator+=(const KQuaternion &q);
    inline KQuaternion &operator-=(const KQuaternion &q);
    inline KQuaternion &operator*=(const KQuaternion &q);
    inline KQuaternion &operator*=(double factor);
    inline KQuaternion &operator/=(double divisor);
    inline KQuaternion &operator=(const KQuaternion &q);
    
    inline KQuaternion operator+(const KQuaternion &q) const;
    inline KQuaternion operator-(const KQuaternion &q) const;
    inline KQuaternion operator*(const KQuaternion &q) const;
    inline KQuaternion operator*(double factor) const;
    inline KQuaternion operator/(double divisor) const;
    
private:
    double s_; // scalar
    KVector3D v_;
};

inline void KQuaternion::normalize()
{
    double len = length();
    if (isZero(len))
        return;
    *this /= len;
}

inline double KQuaternion::length() const
{
    return kSqrt(lengthSquared());
}

inline double KQuaternion::lengthSquared() const
{
    return s_ * s_ + v_.lengthSquared();
}

inline KQuaternion KQuaternion::normalized() const
{
    double len = length();
    if (isZero(len))
        return KQuaternion(0, 0, 0, 0);
    return *this / len;
}

inline KQuaternion KQuaternion::inverted() const
{
    double lens = lengthSquared();
    return KQuaternion(s_ / lens, -v_ / lens);
}

inline bool KQuaternion::isIdentity() const
{
    return isZero(s_ - 1) && v_.isNull();
}

inline bool KQuaternion::isNull() const
{
    return isZero(s_) && v_.isNull();
}

inline double KQuaternion::dotProduct(const KQuaternion &q1,
                                      const KQuaternion &q2)
{
    return q1.s_ * q2.s_ + KVector3D::dotProduct(q1.v_, q2.v_);
}

inline double KQuaternion::angleCosine(const KQuaternion &q1,
                                       const KQuaternion &q2)
{
    return dotProduct(q1, q2) / kSqrt(q1.lengthSquared() * q2.lengthSquared());
}

inline KQuaternion &KQuaternion::operator+=(const KQuaternion &q)
{
    s_ += q.s_;
    v_ += q.v_;
    return *this;
}

inline KQuaternion &KQuaternion::operator-=(const KQuaternion &q)
{
    s_ -= q.s_;
    v_ -= q.v_;
    return *this;
}

inline KQuaternion &KQuaternion::operator*=(const KQuaternion &q)
{
    double ts = s_ * q.s_ - KVector3D::dotProduct(v_, q.v_);
    v_ = q.v_ * s_ + v_ * q.s_ + KVector3D::crossProduct(v_, q.v_);
    s_ = ts;
    return *this;
}

inline KQuaternion &KQuaternion::operator*=(double factor)
{
    s_ *= factor;
    v_ *= factor;
    return *this;
}

inline KQuaternion &KQuaternion::operator/=(double divisor)
{
    s_ /= divisor;
    v_ /= divisor;
    return *this;
}

inline KQuaternion &KQuaternion::operator=(const KQuaternion &q)
{
    s_ = q.s_;
    v_ = q.v_;
    return *this;
}

inline KQuaternion KQuaternion::operator+(const KQuaternion &q) const
{
    return KQuaternion(s_ + q.s_, v_ + q.v_);
}

inline KQuaternion KQuaternion::operator-(const KQuaternion &q) const
{
    return KQuaternion(s_ - q.s_, v_ - q.v_);
}

inline KQuaternion KQuaternion::operator*(const KQuaternion &q) const
{
    return KQuaternion(s_ * q.s_ - KVector3D::dotProduct(v_, q.v_),
                       q.v_ * s_ + v_ * q.s_ + 
                       KVector3D::crossProduct(v_, q.v_));
}

inline KQuaternion KQuaternion::operator*(double factor) const
{
    return KQuaternion(s_ * factor, v_ * factor);
}

inline KQuaternion KQuaternion::operator/(double divisor) const
{
    return KQuaternion(s_ / divisor, v_ / divisor);
}

inline KQuaternion operator*(double factor, const KQuaternion &q)
{
    return KQuaternion(q.scalar() * factor, q.vector() * factor);
}

inline KQuaternion operator-(const KQuaternion &q)
{
    return KQuaternion(-q.scalar(), -q.vector());
}

#endif // KQUATERNION_H
