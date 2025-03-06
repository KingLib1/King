#ifndef KELLIPSEX_H
#define KELLIPSEX_H

#include "krectcoordsystem2d.h"

// c1 x^2 + c2 y^2 + c3 xy = 1,  x^2 / a^2 + y^2 / b^2 = 1
class KING_EXPORT KEllipseX
{
public:
    KEllipseX();
    KEllipseX(double a, double b, const KRectCoordSystem2D &sys = KRectCoordSystem2D());
    /**
     * @brief 通过二次项系数构建椭圆
     */
    KEllipseX(const KVector3D &coefficient);

    inline void setCenter(const KPointF &center);
    inline KPointF center() const;

    inline void setA(double a) {a_ = a;}
    inline double a() const {return a_;}

    inline void setB(double b) {b_ = b;}
    inline double b() const {return b_;}

    /**
     * @brief 计算二次型的系数 c1 c2 c3
     */
    KVector3D toEquationCoefficient() const;
    inline const KRectCoordSystem2D &coordSys() const;

private:
    double a_;
    double b_;
    KRectCoordSystem2D sys_;
};

inline void KEllipseX::setCenter(const KPointF &center)
{
    sys_.setOrigin(center);
}

inline KPointF KEllipseX::center() const
{
    return sys_.origin().toPointF();
}

inline const KRectCoordSystem2D &KEllipseX::coordSys() const
{
    return sys_;
}

#endif // KELLIPSEX_H
