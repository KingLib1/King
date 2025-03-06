#ifndef KGEOMETRICDISTRIBUTION_H
#define KGEOMETRICDISTRIBUTION_H

#include "kmath.h"

class KGeometricDistribution
{
public:
    KGeometricDistribution();
    KGeometricDistribution(double p);
    KGeometricDistribution(const KGeometricDistribution &geo);
    ~KGeometricDistribution();

    inline void setP(double p);

    inline double p() const;
    /**
     * @brief 第first次才成功的概率
     */
    inline double p(int first);
    /**
     * @brief 期望
     */
    inline double E() const;
    /**
     * @brief 方差
     */
    inline double D() const;

    inline KGeometricDistribution &operator=(const KGeometricDistribution &geo);

private:
    double p_;
};

inline void KGeometricDistribution::setP(double p)
{
    p_ = p;
}

inline double KGeometricDistribution::p() const
{
    return p_;
}

inline double KGeometricDistribution::p(int first)
{
    return kPow(1 - p_, first - 1) * p_;
}

inline double KGeometricDistribution::E() const
{
    return 1 / p_;
}

inline double KGeometricDistribution::D() const
{
    return (1 - p_) / kSquare(p_);
}

inline KGeometricDistribution &KGeometricDistribution::operator=(
        const KGeometricDistribution &geo)
{
    p_ = geo.p_;
    return *this;
}

#endif // KGEOMETRICDISTRIBUTION_H
