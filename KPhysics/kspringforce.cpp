#include "kspringforce.h"

KSpringForce::KSpringForce()
{

}

KSpringForce::KSpringForce(double k, double rest, double current) :
    k_(k), rest_(rest), current_(current)
{

}

KSpringForce::KSpringForce(const KSpringForce &spr) :
    k_(spr.k_), rest_(spr.rest_), current_(spr.current_)
{

}

KSpringForce::~KSpringForce()
{

}
