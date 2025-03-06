#ifndef KUNIFORMDISTRIBUTION_H
#define KUNIFORMDISTRIBUTION_H

#include "krange.h"

class KUniformDistribution
{
public:
    KUniformDistribution();
    KUniformDistribution(double a, double b);
    KUniformDistribution(const KRange &range);
    KUniformDistribution(const KUniformDistribution &uni);
    ~KUniformDistribution();

    inline void setA(double a);
    inline void setB(double b);
    inline void setRange(const KRange &range);
    inline void setRange(double a, double b);

    inline const KRange &range() const;
    inline double a() const;
    inline double b() const;
    inline double density(double x) const;
    double p(double x1, double x2) const; // 落在(x1, x2)间的概率
    double f(double x) const; // 分布函数
    /**
     * @brief 期望
     */
    inline double E() const;
    /**
     * @brief 方差
     */
    inline double D() const;

private:
    KRange range_;
};

inline void KUniformDistribution::setA(double a)
{
    range_.setLower(a);
}

inline void KUniformDistribution::setB(double b)
{
    range_.setUpper(b);
}

inline void KUniformDistribution::setRange(const KRange &range)
{
    range_ = range;
}

inline void KUniformDistribution::setRange(double a, double b)
{
    range_.setRange(a, b);
}

inline const KRange &KUniformDistribution::range() const
{
    return range_;
}

inline double KUniformDistribution::a() const
{
    return range_.lower();
}

inline double KUniformDistribution::b() const
{
    return range_.upper();
}

inline double KUniformDistribution::density(double x) const
{
    if (range_.contains(x))
        return 1 / range_.range();
    return 0;
}

inline double KUniformDistribution::E() const
{
    return range_.middle();
}

inline double KUniformDistribution::D() const
{
    return range_.range() / 12;
}

#endif // KUNIFORMDISTRIBUTION_H
