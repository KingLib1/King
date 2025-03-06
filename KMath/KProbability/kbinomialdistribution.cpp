#include "kbinomialdistribution.h"

KBinomialDistribution::KBinomialDistribution() : n_(0), p_(0)
{

}

KBinomialDistribution::KBinomialDistribution(unsigned n, double p) :
    n_(n), p_(p)
{

}

KBinomialDistribution::KBinomialDistribution(const KBinomialDistribution &bin) :
    n_(bin.n_), p_(bin.p_)
{

}

KBinomialDistribution::~KBinomialDistribution()
{

}
