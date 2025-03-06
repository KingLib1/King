#ifndef KPOISSONDISTRIBUTION_H
#define KPOISSONDISTRIBUTION_H

#include <math.h>

#include "kmath.h"

class KPoissonDistribution
{
public:
    KPoissonDistribution();
    KPoissonDistribution(double lambda);
    KPoissonDistribution(const KPoissonDistribution &poi);
    ~KPoissonDistribution();

    inline void setLambda(double lambda);

    inline double lambda() const;
    inline double p(unsigned k) const; // 发生k次概率
    /**
     * @brief 期望
     */
    inline double E() const;
    /**
     * @brief 方差
     */
    inline double D() const;

    inline KPoissonDistribution &operator=(const KPoissonDistribution &poi);

private:
    double lambda_;
};

inline void KPoissonDistribution::setLambda(double lambda)
{
    lambda_ = lambda;
}

inline double KPoissonDistribution::lambda() const
{
    return lambda_;
}

inline double KPoissonDistribution::p(unsigned k) const
{
    return double(static_cast<long double>
                  (kPow(lambda_, int(k)) * pow(K_E, -lambda_)) /
                  kFactorial_ld(k));
}

inline double KPoissonDistribution::E() const
{
    return lambda_;
}

inline double KPoissonDistribution::D() const
{
    return lambda_;
}

inline KPoissonDistribution &KPoissonDistribution::operator=(
        const KPoissonDistribution &poi)
{
    lambda_ = poi.lambda_;
    return *this;
}

#endif // KPOISSONDISTRIBUTION_H
