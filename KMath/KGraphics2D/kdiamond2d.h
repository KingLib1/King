#ifndef KDIAMOND2D_H
#define KDIAMOND2D_H

#include "kpointf.h"

// 菱形。默认中心点为原点，四个顶点在x和y轴上
class KING_EXPORT KDiamond2D
{
public:
    /**
     * @param 当mode = 0时, a为x轴半对角线长，b为y轴半对角线长
     * @param 当mode = 1时, a为边长，b为最小内角的角度
     */
    KDiamond2D(double a = 0, double b = 0, int mode = 0);

    inline KPointF right() const;
    inline KPointF top() const;
    inline KPointF left() const;
    inline KPointF bottom() const;
    inline double sideLength() const;
    inline double area() const;
    inline double perimeter() const;
    inline double height() const; // 高

private:
    double a_; // x轴半对角线长
    double b_; // y轴半对角线长
};

inline KPointF KDiamond2D::right() const
{
    return KPointF(a_, 0);
}

inline KPointF KDiamond2D::top() const
{
    return KPointF(0, b_);
}

inline KPointF KDiamond2D::left() const
{
    return KPointF(-a_, 0);
}

inline KPointF KDiamond2D::bottom() const
{
    return KPointF(0, -b_);
}

inline double KDiamond2D::sideLength() const
{
    return pythagoreanTheorem_Bevel(a_, b_);
}

inline double KDiamond2D::area() const
{
    return a_ * b_ * 2;
}

inline double KDiamond2D::perimeter() const
{
    return sideLength() * 4;
}

inline double KDiamond2D::height() const
{
    return area() / sideLength();
}

#endif // KDIAMOND2D_H
