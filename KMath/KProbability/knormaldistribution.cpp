#include "knormaldistribution.h"

KNormalDistribution::KNormalDistribution() : mu_(0), sigma_(1)
{

}

KNormalDistribution::KNormalDistribution(double mu, double sigma) :
    mu_(mu), sigma_(sigma)
{

}

KNormalDistribution::KNormalDistribution(const KNormalDistribution &nor) :
    mu_(nor.mu_), sigma_(nor.sigma_)
{

}

KNormalDistribution::~KNormalDistribution()
{

}
