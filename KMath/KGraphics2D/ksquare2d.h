#ifndef KSQUARE2D_H
#define KSQUARE2D_H

#include "kvector2d.h"

class KSquare2D
{
public:
    KSquare2D(double side_length = 0);
    KSquare2D(const KPointF &center, double side_length);

    inline void setSideLength(double side_length);
    inline double sideLength() const;

    inline void setCenter(const KPointF &center);
    inline const KPointF &center() const;

    inline void translate(const KPointF &dv);
    inline void translate(const KVector2D &dv);

    inline KPointF topLeft() const;
    inline KPointF topRight() const;
    inline KPointF bottomLeft() const;
    inline KPointF bottomRight() const;
    inline double area() const;
    inline double perimeter() const;

    inline KSquare2D &operator=(const KSquare2D &other);

private:
    KPointF center_;
    double side_length_;
};

inline void KSquare2D::setSideLength(double side_length)
{
    side_length_ = side_length;
}

inline double KSquare2D::sideLength() const
{
    return side_length_;
}

inline void KSquare2D::setCenter(const KPointF &center)
{
    center_ = center;
}

inline const KPointF &KSquare2D::center() const
{
    return center_;
}

inline void KSquare2D::translate(const KPointF &dv)
{
    center_ += dv;
}

inline void KSquare2D::translate(const KVector2D &dv)
{
    center_ += dv;
}

inline KPointF KSquare2D::topLeft() const
{
    double half = side_length_ / 2;
    return KPointF(center_.x() - half, center_.y() + half);
}

inline KPointF KSquare2D::topRight() const
{
    double half = side_length_ / 2;
    return KPointF(center_.x() + half, center_.y() + half);
}

inline KPointF KSquare2D::bottomLeft() const
{
    double half = side_length_ / 2;
    return KPointF(center_.x() - half, center_.y() - half);
}

inline KPointF KSquare2D::bottomRight() const
{
    double half = side_length_ / 2;
    return KPointF(center_.x() + half, center_.y() - half);
}

inline double KSquare2D::area() const
{
    return kSquare(side_length_);
}

inline double KSquare2D::perimeter() const
{
    return side_length_ * 4;
}

inline KSquare2D &KSquare2D::operator=(const KSquare2D &other)
{
    center_ = other.center_;
    side_length_ = other.side_length_;
    return *this;
}

#endif // KSQUARE2D_H
