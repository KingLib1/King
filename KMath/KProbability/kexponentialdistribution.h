#ifndef KEXPONENTIALDISTRIBUTION_H
#define KEXPONENTIALDISTRIBUTION_H

#include <math.h>

#include "kmath.h"

class KExponentialDistribution
{
public:
    KExponentialDistribution();
    KExponentialDistribution(double rate);
    KExponentialDistribution(const KExponentialDistribution &exp);
    ~KExponentialDistribution();

    inline void setRate(double rate); // lambda

    inline double rate() const;
    inline double density(double x) const; // 概率密度
    inline double p(double x1, double x2) const; // 落在(x1, x2)间的概率
    inline double f(double x) const; // 分布函数
    /**
     * @brief 期望
     */
    inline double E() const;
    /**
     * @brief 方差
     */
    inline double D() const;

    inline KExponentialDistribution &operator=(
            const KExponentialDistribution &exp);

private:
    double rate_;
};

inline void KExponentialDistribution::setRate(double rate)
{
    rate_ = rate;
}

inline double KExponentialDistribution::rate() const
{
    return rate_;
}

inline double KExponentialDistribution::density(double x) const
{
    if (x <= 0)
        return 0;
    return rate_ * pow(K_E, -rate_ * x);
}

inline double KExponentialDistribution::p(double x1, double x2) const
{
    return pow(K_E, -rate_ * x1) - pow(K_E, -rate_ * x2);
}

inline double KExponentialDistribution::f(double x) const
{
    if (x <= 0)
        return 0;
    return 1 - pow(K_E, -rate_ * x);
}

inline double KExponentialDistribution::E() const
{
    return 1 / rate_;
}

inline double KExponentialDistribution::D() const
{
    return 1 / kSquare(rate_);
}

inline KExponentialDistribution &KExponentialDistribution::operator=(
        const KExponentialDistribution &exp)
{
    rate_ = exp.rate_;
    return *this;
}

#endif // KEXPONENTIALDISTRIBUTION_H
