#ifndef KBINOMIALDISTRIBUTION_H
#define KBINOMIALDISTRIBUTION_H

#include "kprobability.h"
#include "kmath.h"

class KBinomialDistribution
{
public:
    KBinomialDistribution();
    KBinomialDistribution(unsigned n, double p);
    KBinomialDistribution(const KBinomialDistribution &bin);
    ~KBinomialDistribution();

    inline void setN(unsigned n);
    inline void setP(double p);

    /**
     * @brief 试验次数
     */
    inline unsigned n() const;
    /**
     * @brief 单次发生的概率
     */
    inline double p() const;
    /**
     * @brief 发生k次的概率
     */
    inline double p(unsigned k) const;
    /**
     * @brief 期望
     */
    inline double E() const;
    /**
     * @brief 方差
     */
    inline double D() const;

    inline KBinomialDistribution &operator=(const KBinomialDistribution &bin);

private:
    unsigned n_; // n重贝努利试验
    double p_; // 每次试验发生的概率
};

inline void KBinomialDistribution::setN(unsigned n)
{
    n_ = n;
}

inline void KBinomialDistribution::setP(double p)
{
    p_ = p;
}

inline unsigned KBinomialDistribution::n() const
{
    return n_;
}

inline double KBinomialDistribution::p() const
{
    return p_;
}

inline double KBinomialDistribution::p(unsigned k) const
{
    return combination(n_, k) * kPow(p_, int(k)) * kPow(1 - p_, int(n_ - k));
}

inline double KBinomialDistribution::E() const
{
    return n_ * p_;
}

inline double KBinomialDistribution::D() const
{
    return n_ * p_ * (1 - p_);
}

inline KBinomialDistribution &KBinomialDistribution::operator=(
        const KBinomialDistribution &bin)
{
    n_ = bin.n_;
    p_ = bin.p_;
    return *this;
}

#endif // KBINOMIALDISTRIBUTION_H
