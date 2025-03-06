#include "kpoissondistribution.h"

KPoissonDistribution::KPoissonDistribution() : lambda_(0)
{

}

KPoissonDistribution::KPoissonDistribution(double lambda) : lambda_(lambda)
{

}

KPoissonDistribution::KPoissonDistribution(const KPoissonDistribution &poi) :
    lambda_(poi.lambda_)
{

}

KPoissonDistribution::~KPoissonDistribution()
{

}
