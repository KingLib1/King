#ifndef KMODIFIEDDH_H
#define KMODIFIEDDH_H

#include "kmatrix4x4.h"

class KING_EXPORT KModifiedDH
{
public:
    KModifiedDH();
    KModifiedDH(double a, double alpha, double d, double theta);
    KModifiedDH(const KModifiedDH &dh);
    ~KModifiedDH();

    inline void setA(double a) {a_ = a;}
    inline void setAlpha(double alpha) {alpha_ = alpha;}
    inline void setD(double d) {d_ = d;}
    inline void setTheta(double theta) {theta_ = theta;}

    inline double a() const {return a_;}
    inline double alpha() const {return alpha_;}
    inline double d() const {return d_;}
    inline double theta() const {return theta_;}
    inline KMatrix4x4 toMatrix() const;

    inline KModifiedDH &operator=(const KModifiedDH &other);

private:
    double a_; // 两个z轴的公垂线长度（连杆固有参数）
    double alpha_; // 两个z轴的夹角弧度（连杆固有参数）

    double d_; // 两个x轴公垂线长度
    double theta_; // 两个x轴的夹角弧度
};

KMatrix4x4 KModifiedDH::toMatrix() const
{
    double cost = kCos(theta_);
    double sint = kSin(theta_);
    double cosa = kCos(alpha_);
    double sina = kSin(alpha_);
    return KMatrix4x4(cost, -sint, 0, a_,
                      cosa * sint, cosa * cost, -sina, -d_ * sina,
                      sina * sint, sina * cost, cosa, d_ * cosa,
                      0, 0, 0, 1);
}

KModifiedDH &KModifiedDH::operator=(const KModifiedDH &other)
{
    a_ = other.a_;
    alpha_ = other.alpha_;
    d_ = other.d_;
    theta_ = other.theta_;
    return *this;
}

#endif // KMODIFIEDDH_H
