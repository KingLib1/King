#ifndef KHYPERGEOMETRICDISTRIBUTION_H
#define KHYPERGEOMETRICDISTRIBUTION_H

#include "kprobability.h"

class KHypergeometricDistribution
{
public:
    KHypergeometricDistribution();
    KHypergeometricDistribution(unsigned n, unsigned m);
    KHypergeometricDistribution(const KHypergeometricDistribution &hyp);
    ~KHypergeometricDistribution();

    inline void setN(unsigned n);
    inline void setM(unsigned m);

    inline unsigned n() const;
    inline unsigned m() const;
    /**
     * @brief 抽取k1次，抽取到k2个指定元素的概率
     */
    inline double p(unsigned k1, unsigned k2) const;

    inline KHypergeometricDistribution &operator=(
            const KHypergeometricDistribution &hyp);

private:
    unsigned n_;  // 一共n个元素
    unsigned m_;  // n个里包含m个指定元素
};

inline void KHypergeometricDistribution::setN(unsigned n)
{
    n_ = n;
}

inline void KHypergeometricDistribution::setM(unsigned m)
{
    m_ = m;
}

inline unsigned KHypergeometricDistribution::n() const
{
    return n_;
}

inline unsigned KHypergeometricDistribution::m() const
{
    return m_;
}

inline double KHypergeometricDistribution::p(unsigned k1, unsigned k2) const
{
    return combination(m_, k2) * combination(n_ - m_, k1 - k2) /
            combination(n_, k1);
}

inline KHypergeometricDistribution &KHypergeometricDistribution::operator=(
        const KHypergeometricDistribution &hyp)
{
    n_ = hyp.n_;
    m_ = hyp.m_;
    return *this;
}

#endif // KHYPERGEOMETRICDISTRIBUTION_H
