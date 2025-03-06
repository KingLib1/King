#include "kvector2d.h"

KVector2D::KVector2D() : x_(0), y_(0)
{

}

KVector2D::KVector2D(const KPointF &point) :
    x_(point.x()), y_(point.y())
{

}

KVector2D::KVector2D(const KPointF &p1, const KPointF &p2) :
    x_(p2.x() - p1.x()), y_(p2.y() - p1.y())
{

}

KVector2D::KVector2D(const KVector2D &vector) :
    x_(vector.x_), y_(vector.y_)
{

}

KVector2D::KVector2D(const KVector3D &vector) :
    x_(vector.x()), y_(vector.y())
{

}

KVector2D::KVector2D(const KVector4D &vector) :
    x_(vector.x()), y_(vector.y())
{

}

KVector2D::KVector2D(double x, double y) :
    x_(x), y_(y)
{

}

void KVector2D::setLength(double length)
{
    double len = this->length();
    *this *= length / len;
}

void KVector2D::rotate(double angle)
{
    double radian = kDegreesToRadians(angle);
    double sinr = kSin(radian);
    double cosr = kCos(radian);
    double tempx = x_;
    x_ = x_ * cosr - y_ * sinr;
    y_ = tempx * sinr + y_ * cosr;
}

void KVector2D::rotateRadian(double radian)
{
    double sinr = kSin(radian);
    double cosr = kCos(radian);
    double tempx = x_;
    x_ = x_ * cosr - y_ * sinr;
    y_ = tempx * sinr + y_ * cosr;
}

KVector2D KVector2D::rotatedRadian(double radian) const
{
    KVector2D temp(*this);
    temp.rotateRadian(radian);
    return temp;
}

void KVector2D::rotate(const KVector2D &point, double angle)
{
    *this -= point;
    rotate(angle);
    *this += point;
}

void KVector2D::rotateRadian(const KVector2D &point, double angle)
{
    *this -= point;
    rotateRadian(angle);
    *this += point;
}

KVector2D KVector2D::rotatedRadian(const KVector2D &point, double angle) const
{
    KVector2D temp(*this);
    temp.rotateRadian(point, angle);
    return temp;
}

double KVector2D::angle(const KVector2D &v1, const KVector2D &v2)
{
    return kRadiansToDegrees(radian(v1, v2));
}

double KVector2D::radian(const KVector2D &v1, const KVector2D &v2)
{
    return kAcos(angleCosine(v1, v2));
}
