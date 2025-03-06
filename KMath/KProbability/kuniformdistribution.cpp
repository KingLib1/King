#include "kuniformdistribution.h"

KUniformDistribution::KUniformDistribution()
{

}

KUniformDistribution::KUniformDistribution(double a, double b) :
    range_(a, b)
{

}

KUniformDistribution::KUniformDistribution(const KRange &range) : range_(range)
{

}

KUniformDistribution::KUniformDistribution(const KUniformDistribution &uni) :
    range_(uni.range_)
{

}

KUniformDistribution::~KUniformDistribution()
{

}

double KUniformDistribution::p(double x1, double x2) const
{
    if (x2 <= range_.lower() || x1 >= range_.upper())
        return 0;
    if (x1 <= range_.lower()) {
        if (x2 >= range_.upper())
            return 1;
        return (x2 - range_.lower()) / range_.range();
    }
    if (x2 >= range_.upper())
        return (range_.upper() - x1) / range_.range();
    return (x2 - x1) / range_.range();
}

double KUniformDistribution::f(double x) const
{
    if (x <= range_.lower())
        return 0;
    if (x >= range_.upper())
        return 1;
    return (x - range_.lower()) / range_.range();
}
