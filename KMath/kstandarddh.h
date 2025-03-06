#ifndef KSTANDARDDH_H
#define KSTANDARDDH_H

#include "kmatrix4x4.h"

class KING_EXPORT KStandardDH
{
public:
    KStandardDH();
    KStandardDH(double a, double alpha, double d, double theta);
    KStandardDH(const KStandardDH &dh);
    ~KStandardDH();

    inline void setA(double a) {a_ = a;}
    inline void setAlpha(double alpha) {alpha_ = alpha;}
    inline void setD(double d) {d_ = d;}
    inline void setTheta(double theta) {theta_ = theta;}

    inline double a() const {return a_;}
    inline double alpha() const {return alpha_;}
    inline double d() const {return d_;}
    inline double theta() const {return theta_;}
    inline KMatrix4x4 toMatrix() const;

    inline KStandardDH &operator=(const KStandardDH &other);

private:
    double a_; // 两个z轴的公垂线长度（连杆固有参数）
    double alpha_; // 两个z轴的夹角弧度（连杆固有参数）

    double d_; // 两个x轴公垂线长度
    double theta_; // 两个x轴的夹角弧度
};

inline KMatrix4x4 KStandardDH::toMatrix() const
{
    double cost = kCos(theta_);
    double sint = kSin(theta_);
    double cosa = kCos(alpha_);
    double sina = kSin(alpha_);
    return KMatrix4x4(cost, -sint * cosa, sint * sina, a_ * cost,
                      sint, cost * cosa, -cost * sina, a_ * sint,
                      0, sina, cosa, d_,
                      0, 0, 0, 1);
}

inline KStandardDH &KStandardDH::operator=(const KStandardDH &other)
{
    a_ = other.a_;
    alpha_ = other.alpha_;
    d_ = other.d_;
    theta_ = other.theta_;
    return *this;
}

#endif // KSTANDARDDH_H
