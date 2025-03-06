#ifndef KVECTOR2D_H
#define KVECTOR2D_H

#include "kpointf.h"
#include "kvector4d.h"

class KING_EXPORT KVector2D
{
public:
    KVector2D();
    KVector2D(const KPointF &point);
    KVector2D(const KPointF &p1, const KPointF &p2);
    KVector2D(const KVector2D &vector);
    KVector2D(const KVector3D &vector);
    KVector2D(const KVector4D &vector);
    KVector2D(double x, double y);

    inline void transpose();
    inline void invert();
    inline void rotate90();
    inline void rotateNeg90();

    inline KVector2D transposed() const;
    inline KVector2D inverted() const;
    inline KVector2D rotated90() const;
    inline KVector2D rotatedNeg90() const;

    inline double x() const {return x_;}
    inline double y() const {return y_;}
    inline void setX(double x) {x_ = x;}
    inline void setY(double y) {y_ = y;}
    inline void setXY(double x, double y) {x_ = x; y_ = y;}
    void setLength(double length);
    void rotate(double angle);
    void rotateRadian(double radian);
    KVector2D rotatedRadian(double radian) const;
    void rotate(const KVector2D &point, double angle);
    void rotateRadian(const KVector2D &point, double angle);
    KVector2D rotatedRadian(const KVector2D &point, double angle) const;

    inline double length() const;
    inline double lengthSquared() const;
    inline static double dotProduct(const KVector2D &v1, const KVector2D &v2);
    inline static double crossProduct(const KVector2D &v1, const KVector2D &v2);
    inline bool isNull() const;
    inline void normalize();
    inline KVector2D normalized() const;
    inline KPointF toPointF() const;
    inline KVector3D toVector3D() const;
    inline KVector4D toVector4D() const;
    inline static double angleCosine(const KVector2D &v1, const KVector2D &v2);
    static double angle(const KVector2D &v1, const KVector2D &v2);
    static double radian(const KVector2D &v1, const KVector2D &v2);
    inline static double vectorRadian(const KVector2D &v1, const KVector2D &v2);
    inline static double vectorAngle(const KVector2D &v1, const KVector2D &v2);


    inline KVector2D operator+(const KVector2D &v) const;
    inline KVector2D operator-(const KVector2D &v) const;
    inline KVector2D operator*(double factor) const;
    inline KVector2D operator/(double divisor) const;
    inline KVector2D &operator*=(double factor);
    inline KVector2D &operator*=(const KVector2D &vector);
    inline KVector2D &operator+=(const KVector2D &vector);
    inline KVector2D &operator-=(const KVector2D &vector);
    inline KVector2D &operator/=(double factor);
    inline KVector2D &operator/=(const KVector2D &vector);
    inline KVector2D &operator=(const KVector2D &other);
    inline KVector2D &operator=(const KPointF &other);

private:
    double x_;
    double y_;
};

inline void KVector2D::transpose()
{
    kSwap(x_, y_);
}

inline void KVector2D::invert()
{
    x_ = -x_;
    y_ = -y_;
}

inline void KVector2D::rotate90()
{
    double tempx = x_;
    x_ = -y_;
    y_ = tempx;
}

inline void KVector2D::rotateNeg90()
{
    double temp = x_;
    x_ = y_;
    y_ = -temp;
}

inline KVector2D KVector2D::transposed() const
{
    return KVector2D(y_, x_);
}

inline KVector2D KVector2D::inverted() const
{
    return KVector2D(-x_, -y_);
}

inline KVector2D KVector2D::rotated90() const
{
    return KVector2D(-y_, x_);
}

inline KVector2D KVector2D::rotatedNeg90() const
{
    return KVector2D(y_, -x_);
}

inline double KVector2D::length() const
{
    return kSqrt(x_*x_ + y_*y_);
}

inline double KVector2D::lengthSquared() const
{
    return x_*x_ + y_*y_;
}

inline double KVector2D::dotProduct(const KVector2D &v1, const KVector2D &v2)
{
    return v1.x_ * v2.x_ + v1.y_ * v2.y_;
}

inline double KVector2D::crossProduct(const KVector2D &v1, const KVector2D &v2)
{
    return v1.x_ * v2.y_ - v2.x_ * v1.y_;
}

inline bool KVector2D::isNull() const
{
    return kFabs(x_) < 1e-9 && kFabs(y_) < 1e-9;
}

inline void KVector2D::normalize()
{
    double len = length();
    if (len < 1e-9)
        return;
    x_ /= len;
    y_ /= len;
}

inline KVector2D KVector2D::normalized() const
{
    KVector2D vector(*this);
    vector.normalize();
    return vector;
}

inline KPointF KVector2D::toPointF() const
{
    return KPointF(x_, y_);
}

inline KVector3D KVector2D::toVector3D() const
{
    return KVector3D(x_, y_, 0);
}

inline KVector4D KVector2D::toVector4D() const
{
    return KVector4D(x_, y_, 0, 0);
}

inline double KVector2D::angleCosine(const KVector2D &v1, const KVector2D &v2)
{
    return dotProduct(v1, v2) / kSqrt(v1.lengthSquared() * v2.lengthSquared());
}

inline double KVector2D::vectorRadian(const KVector2D &v1, const KVector2D &v2)
{
    return kAcos(angleCosine(v1, v2));
}

inline double KVector2D::vectorAngle(const KVector2D &v1, const KVector2D &v2)
{
    return kRadiansToDegrees(vectorRadian(v1, v2));
}

inline KVector2D KVector2D::operator+(const KVector2D &v) const
{
    return KVector2D(x_ + v.x_, y_ + v.y_);
}

inline KVector2D KVector2D::operator-(const KVector2D &v) const
{
    return KVector2D(x_ - v.x_, y_ - v.y());
}

inline KVector2D KVector2D::operator*(double factor) const
{
    return KVector2D(x_ * factor, y_ * factor);
}

inline KVector2D KVector2D::operator/(double divisor) const
{
    return KVector2D(x_ / divisor, y_ / divisor);
}

inline KVector2D &KVector2D::operator*=(double factor)
{
    x_ *= factor;
    y_ *= factor;
    return *this;
}

inline KVector2D &KVector2D::operator*=(const KVector2D &vector)
{
    x_ *= vector.x_;
    y_ *= vector.y_;
    return *this;
}

inline KVector2D &KVector2D::operator+=(const KVector2D &vector)
{
    x_ += vector.x_;
    y_ += vector.y_;
    return *this;
}

inline KVector2D &KVector2D::operator-=(const KVector2D &vector)
{
    x_ -= vector.x_;
    y_ -= vector.y_;
    return *this;
}

inline KVector2D &KVector2D::operator/=(double factor)
{
    x_ /= factor;
    y_ /= factor;
    return *this;
}

inline KVector2D &KVector2D::operator/=(const KVector2D &vector)
{
    x_ /= vector.x_;
    y_ /= vector.y_;
    return *this;
}

inline KVector2D &KVector2D::operator=(const KVector2D &other)
{
    x_ = other.x_;
    y_ = other.y_;
    return *this;
}

inline KVector2D &KVector2D::operator=(const KPointF &other)
{
    x_ = other.x();
    y_ = other.y();
    return *this;
}

inline KVector2D operator-(const KVector2D &vector)
{
    return KVector2D(-vector.x(), -vector.y());
}

inline KPointF operator-(const KPointF &point, const KVector2D &vector)
{
    return KPointF(point.x() - vector.x(), point.y() - vector.y());
}

inline KPointF &operator-=(KPointF &point, const KVector2D &vector)
{
    point.translate(-vector.x(), -vector.y());
    return point;
}

inline KPointF operator+(const KPointF &point, const KVector2D &vector)
{
    return KPointF(point.x() + vector.x(), point.y() + vector.y());
}

inline KPointF &operator+=(KPointF &point, const KVector2D &vector)
{
    point.translate(vector.x(), vector.y());
    return point;
}

#endif // KVECTOR2D_H
