#include "kexponentialdistribution.h"

KExponentialDistribution::KExponentialDistribution() : rate_(1)
{

}

KExponentialDistribution::KExponentialDistribution(double rate) : rate_(rate)
{

}

KExponentialDistribution::KExponentialDistribution(
        const KExponentialDistribution &exp) : rate_(exp.rate_)
{

}

KExponentialDistribution::~KExponentialDistribution()
{

}
