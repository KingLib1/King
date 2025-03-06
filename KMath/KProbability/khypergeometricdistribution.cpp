#include "khypergeometricdistribution.h"

KHypergeometricDistribution::KHypergeometricDistribution() : n_(0), m_(0)
{

}

KHypergeometricDistribution::KHypergeometricDistribution(unsigned n, unsigned m)
    : n_(n), m_(m)
{

}

KHypergeometricDistribution::KHypergeometricDistribution(
        const KHypergeometricDistribution &hyp) : n_(hyp.n_), m_(hyp.m_)
{

}

KHypergeometricDistribution::~KHypergeometricDistribution()
{

}
