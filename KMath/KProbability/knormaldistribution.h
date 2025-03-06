#ifndef KNORMALDISTRIBUTION_H
#define KNORMALDISTRIBUTION_H

#include <math.h>

#include "kmath.h"

#define SQRT_2PI 2.5066282746310005024

class KNormalDistribution
{
public:
    KNormalDistribution();
    KNormalDistribution(double mu, double sigma);
    KNormalDistribution(const KNormalDistribution &nor);
    ~KNormalDistribution();

    inline void setMu(double mu);
    inline void setSigma(double sigma);

    inline double mu() const;
    inline double sigma() const;
    /**
     * @brief 概率密度
     */
    inline double density(double x) const;
    /**
     * @brief 期望
     */
    inline double E() const;
    /**
     * @brief 方差
     */
    inline double D() const;

private:
    double mu_;
    double sigma_;
};

inline void KNormalDistribution::setMu(double mu)
{
    mu_ = mu;
}

inline void KNormalDistribution::setSigma(double sigma)
{
    sigma_ = sigma;
}

inline double KNormalDistribution::mu() const
{
    return mu_;
}

inline double KNormalDistribution::sigma() const
{
    return sigma_;
}

inline double KNormalDistribution::density(double x) const
{
    return 1 / (SQRT_2PI * sigma_) * pow(K_E, -kSquare((x - mu_) / sigma_) / 2);
}

inline double KNormalDistribution::E() const
{
    return mu_;
}

inline double KNormalDistribution::D() const
{
    return kSquare(sigma_);
}

#endif // KNORMALDISTRIBUTION_H
