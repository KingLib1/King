#include "kgeometricdistribution.h"

KGeometricDistribution::KGeometricDistribution() : p_(0)
{

}

KGeometricDistribution::KGeometricDistribution(double p) : p_(p)
{

}

KGeometricDistribution::KGeometricDistribution(
        const KGeometricDistribution &geo) : p_(geo.p_)
{

}

KGeometricDistribution::~KGeometricDistribution()
{

}
