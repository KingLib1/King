#ifndef KVECTOR3D_H
#define KVECTOR3D_H

#include "kpointf.h"

class KING_EXPORT KVector3D
{
public:
    KVector3D();
    KVector3D(double x, double y);
    KVector3D(double x, double y, double z);
    KVector3D(const KPointF &point);
    KVector3D(const KPointF &point, double z);
    KVector3D(const KVector3D &v);

    inline void setX(double x) {x_ = x;}
    inline void setY(double y) {y_ = y;}
    inline void setZ(double z) {z_ = z;}
    inline void setXYZ(double xyz);
    inline void setXYZ(double x, double y, double z);
    void setLength(double length);
    void rotate(double angle, const KVector3D &axis);
    inline void rotate(const KVector3D &point, double angle,
                       const KVector3D &axis);
    inline void rotateX(double angle);
    inline void rotateY(double angle);
    inline void rotateZ(double angle);
    void rotateX_Radian(double radian);
    void rotateY_Radian(double radian);
    void rotateZ_Radian(double radian);
    inline void translateX(double dx);
    inline void translateY(double dy);
    inline void translateZ(double dz);
    inline void translate(double dx, double dy, double dz);
    inline void translate(const KVector3D &dv);
    inline void scale(double factor);
    inline void scale(const KVector3D &vector);
    inline void scale(double x, double y, double z);
    inline void scale(double x, double y);
    inline void scale(double factor, const KVector3D &axis);
    void normalize();
    inline void invert();

    inline bool isNull() const;
    inline static bool isParallel(const KVector3D &v1, const KVector3D &v2);
    inline double x() const {return x_;}
    inline double y() const {return y_;}
    inline double z() const {return z_;}
    static inline KVector3D midpoint(const KVector3D &p1, const KVector3D &p2);
    /**
     * @brief 关于点mid对称的点
     */
    inline KVector3D symmetryPointAbout(const KVector3D &mid) const;
    inline KVector3D translated(double dx, double dy, double dz) const;
    inline KVector3D translated(const KVector3D &dv) const;
    inline KVector3D translatedX(double dx) const;
    inline KVector3D translatedY(double dy) const;
    inline KVector3D translatedZ(double dz) const;
    inline KVector3D rotatedX(double angle) const;
    inline KVector3D rotatedY(double angle) const;
    inline KVector3D rotatedZ(double angle) const;
    inline KVector3D rotatedX_Radian(double radian) const;
    inline KVector3D rotatedY_Radian(double radian) const;
    inline KVector3D rotatedZ_Radian(double radian) const;
    inline KVector3D ceil() const;
    inline KVector3D floor() const;
    inline KVector3D round() const;
    inline KPointF toKPointF() const;
    inline double xSquare() const {return x_ * x_;}
    inline double ySquare() const {return y_ * y_;}
    inline double zSquare() const {return z_ * z_;}
    inline double xDirectionCosine() const;
    inline double yDirectionCosine() const;
    inline double zDirectionCosine() const;
    static inline double angleCosine(const KVector3D &v1, const KVector3D &v2);
    static double radian(const KVector3D &v1, const KVector3D &v2);
    static inline double angle(const KVector3D &v1, const KVector3D &v2);
    inline double distanceToPoint(const KVector3D &point) const;
    inline double distanceSquaredToPoint(const KVector3D &point) const;
    inline double distanceSquaredToPoint_XY(const KVector3D &point) const;
    inline double distanceToZAxis() const;
    inline double distanceSquaredToZAxis() const;
    KVector3D normalized() const;

    inline double length() const;
    inline double lengthSquared() const;
    inline bool isEqualWith(const KVector3D &v, double fuzziness = EPS6) const;

    static inline double dotProduct(const KVector3D &v1, const KVector3D &v2)
    {
        return (v1.x_*v2.x_ + v1.y_*v2.y_ + v1.z_*v2.z_);
    }

    static inline KVector3D crossProduct(const KVector3D &v1, const KVector3D &v2)
    {
        return KVector3D(v1.y_*v2.z_ - v1.z_*v2.y_,
                         v1.z_*v2.x_ - v1.x_*v2.z_,
                         v1.x_*v2.y_ - v1.y_*v2.x_);
    }

    static inline KVector3D xAxis()
    {
        return KVector3D(1, 0, 0);
    }

    static inline KVector3D yAxis()
    {
        return KVector3D(0, 1, 0);
    }

    static inline KVector3D zAxis()
    {
        return KVector3D(0, 0, 1);
    }

    inline KVector3D operator-(const KVector3D &v) const;
    inline KVector3D operator+(const KVector3D &v) const;
    inline KVector3D operator/(double divisor) const;
    inline KVector3D &operator+=(const KVector3D &rhs);
    inline KVector3D &operator-=(const KVector3D &rhs);
    inline KVector3D &operator/=(double divisor);
    inline KVector3D &operator=(const KVector3D &rhs);
    inline KVector3D operator*(double factor) const;
    inline KVector3D &operator*=(double factor);
    inline bool operator==(const KVector3D &v) const;
    inline bool operator!=(const KVector3D &v) const;

private:
    double x_;
    double y_;
    double z_;
};

inline void KVector3D::setXYZ(double xyz)
{
    x_ = xyz;
    y_ = xyz;
    z_ = xyz;
}

inline void KVector3D::setXYZ(double x, double y, double z)
{
    x_ = x;
    y_ = y;
    z_ = z;
}

inline void KVector3D::rotate(const KVector3D &point, double angle,
                              const KVector3D &axis)
{
    KVector3D p = *this - point;
    p.rotate(angle, axis);
    *this = p + point;
}

inline void KVector3D::rotateX(double angle)
{
    rotateX_Radian(kDegreesToRadians(angle));
}

inline void KVector3D::rotateY(double angle)
{
    rotateY_Radian(kDegreesToRadians(angle));
}

inline void KVector3D::rotateZ(double angle)
{
    rotateZ_Radian(kDegreesToRadians(angle));
}

inline void KVector3D::translateX(double dx)
{
    x_ += dx;
}

inline void KVector3D::translateY(double dy)
{
    y_ += dy;
}

inline void KVector3D::translateZ(double dz)
{
    z_ += dz;
}

inline void KVector3D::translate(double dx, double dy, double dz)
{
    x_ += dx;
    y_ += dy;
    z_ += dz;
}

inline void KVector3D::translate(const KVector3D &dv)
{
    x_ += dv.x_;
    y_ += dv.y_;
    z_ += dv.z_;
}

inline void KVector3D::scale(double factor)
{
    x_ *= factor;
    y_ *= factor;
    z_ *= factor;
}

inline void KVector3D::scale(const KVector3D &vector)
{
    x_ *= vector.x();
    y_ *= vector.y();
    z_ *= vector.z();
}

inline void KVector3D::scale(double x, double y, double z)
{
    x_ *= x;
    y_ *= y;
    z_ *= z;
}

inline void KVector3D::scale(double x, double y)
{
    x_ *= x;
    y_ *= y;
}

inline void KVector3D::scale(double factor, const KVector3D &axis)
{
    KVector3D n(axis.normalized());
    *this += n * ((factor - 1) * KVector3D::dotProduct(n, *this));
}

inline void KVector3D::invert()
{
    x_ = -x_;
    y_ = -y_;
    z_ = -z_;
}

inline bool KVector3D::isNull() const
{
    return kFabs(x_) < EPS6 && kFabs(y_) < EPS6 && kFabs(z_) < EPS6;
}

inline bool KVector3D::isParallel(const KVector3D &v1, const KVector3D &v2)
{
    return KVector3D::crossProduct(v1, v2).isNull();
}

inline KVector3D KVector3D::midpoint(const KVector3D &p1, const KVector3D &p2)
{
    return KVector3D((p1.x_ + p2.x_) * 0.5,
                     (p1.y_ + p2.y_) * 0.5,
                     (p1.z_ + p2.z_) * 0.5);
}

inline KVector3D KVector3D::symmetryPointAbout(const KVector3D &mid) const
{
    return KVector3D(mid.x() * 2 - x_, mid.y() * 2 - y_, mid.z() * 2 - z_);
}

inline KVector3D KVector3D::translated(double dx, double dy, double dz) const
{
    return KVector3D(x_ + dx, y_ + dy, z_ + dz);
}

inline KVector3D KVector3D::translated(const KVector3D &dv) const
{
    return KVector3D(x_ + dv.x_, y_ + dv.y_, z_ + dv.z_);
}

inline KVector3D KVector3D::translatedX(double dx) const
{
    return KVector3D(x_ + dx, y_, z_);
}

inline KVector3D KVector3D::translatedY(double dy) const
{
    return KVector3D(x_, y_ + dy, z_);
}

inline KVector3D KVector3D::translatedZ(double dz) const
{
    return KVector3D(x_, y_, z_ + dz);
}

inline KVector3D KVector3D::rotatedX(double angle) const
{
    KVector3D v(*this);
    v.rotateX(angle);
    return v;
}

inline KVector3D KVector3D::rotatedY(double angle) const
{
    KVector3D v(*this);
    v.rotateY(angle);
    return v;
}

inline KVector3D KVector3D::rotatedZ(double angle) const
{
    KVector3D v(*this);
    v.rotateZ(angle);
    return v;
}

inline KVector3D KVector3D::rotatedX_Radian(double radian) const
{
    KVector3D v(*this);
    v.rotateX_Radian(radian);
    return v;
}

inline KVector3D KVector3D::rotatedY_Radian(double radian) const
{
    KVector3D v(*this);
    v.rotateY_Radian(radian);
    return v;
}

inline KVector3D KVector3D::rotatedZ_Radian(double radian) const
{
    KVector3D v(*this);
    v.rotateZ_Radian(radian);
    return v;
}

inline KVector3D KVector3D::ceil() const
{
    return KVector3D(kCeil(x_), kCeil(y_), kCeil(z_));
}

inline KVector3D KVector3D::floor() const
{
    return KVector3D(kFloor(x_), kFloor(y_), kFloor(z_));
}

inline KVector3D KVector3D::round() const
{
    return KVector3D(kRound(x_), kRound(y_), kRound(z_));
}

inline KPointF KVector3D::toKPointF() const
{
    return KPointF(x_, y_);
}

inline double KVector3D::xDirectionCosine() const
{
    return x_ / length();
}

inline double KVector3D::yDirectionCosine() const
{
    return y_ / length();
}

inline double KVector3D::zDirectionCosine() const
{
    return z_ / length();
}

inline double KVector3D::angleCosine(const KVector3D &v1, const KVector3D &v2)
{
    return dotProduct(v1, v2) / kSqrt(v1.lengthSquared() * v2.lengthSquared());
}

inline double KVector3D::angle(const KVector3D &v1, const KVector3D &v2)
{
    return kRadiansToDegrees(radian(v1, v2));
}

inline double KVector3D::distanceToPoint(const KVector3D &point) const
{
    double dx = point.x_ - x_;
    double dy = point.y_ - y_;
    double dz = point.z_ - z_;
    return kSqrt(dx * dx + dy * dy + dz * dz);
}

inline double KVector3D::distanceSquaredToPoint(const KVector3D &point) const
{
    double dx = point.x_ - x_;
    double dy = point.y_ - y_;
    double dz = point.z_ - z_;
    return dx * dx + dy * dy + dz * dz;
}

inline double KVector3D::distanceSquaredToPoint_XY(const KVector3D &point) const
{
    double dx = point.x_ - x_;
    double dy = point.y_ - y_;
    return dx * dx + dy * dy;
}

inline double KVector3D::distanceToZAxis() const
{
    return kSqrt(kSquareSum(x_, y_));
}

inline double KVector3D::distanceSquaredToZAxis() const
{
    return kSquareSum(x_, y_);
}

inline double KVector3D::length() const
{
    return kSqrt(lengthSquared());
}

inline double KVector3D::lengthSquared() const
{
    return x_*x_ + y_*y_ + z_*z_;
}

inline bool KVector3D::isEqualWith(const KVector3D &v, double fuzziness) const
{
    return isEqual(x_, v.x_, fuzziness) && isEqual(y_, v.y_, fuzziness) &&
            isEqual(z_, v.z_, fuzziness);
}

inline KVector3D KVector3D::operator-(const KVector3D &v) const
{
    return KVector3D(x_ - v.x_, y_ - v.y_, z_ - v.z_);
}

inline KVector3D KVector3D::operator+(const KVector3D &v) const
{
    return KVector3D(x_ + v.x_, y_ + v.y_, z_ + v.z_);
}

inline KVector3D KVector3D::operator/(double divisor) const
{
    return KVector3D(x_ / divisor, y_ / divisor, z_ / divisor);
}

inline KVector3D &KVector3D::operator+=(const KVector3D &rhs)
{
    x_ += rhs.x_;
    y_ += rhs.y_;
    z_ += rhs.z_;
    return *this;
}

inline KVector3D &KVector3D::operator-=(const KVector3D &rhs)
{
    x_ -= rhs.x_;
    y_ -= rhs.y_;
    z_ -= rhs.z_;
    return *this;
}

inline KVector3D &KVector3D::operator/=(double divisor)
{
    x_ /= divisor;
    y_ /= divisor;
    z_ /= divisor;
    return *this;
}

inline KVector3D &KVector3D::operator=(const KVector3D &rhs)
{
    x_ = rhs.x();
    y_ = rhs.y();
    z_ = rhs.z();
    return *this;
}

inline KVector3D KVector3D::operator*(double factor) const
{
    return KVector3D(x_ * factor, y_ * factor, z_ * factor);
}

inline KVector3D &KVector3D::operator*=(double factor)
{
    x_ *= factor;
    y_ *= factor;
    z_ *= factor;
    return *this;
}

inline bool KVector3D::operator==(const KVector3D &v) const
{
    return isEqual(x_, v.x_) && isEqual(y_, v.y_) && isEqual(z_, v.z_);
}

inline bool KVector3D::operator!=(const KVector3D &v) const
{
    return !(*this == v);
}

inline KVector3D operator-(const KVector3D &v)
{
    return KVector3D(-v.x(), -v.y(), -v.z());
}

inline KVector3D operator*(double factor, const KVector3D &vector)
{
    return KVector3D(factor * vector.x(),
                     factor * vector.y(),
                     factor * vector.z());
}

#endif // KVECTOR3D_H
