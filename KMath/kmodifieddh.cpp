#include "kmodifieddh.h"

KModifiedDH::KModifiedDH()
{

}

KModifiedDH::KModifiedDH(double a, double alpha, double d, double theta) :
    a_(a), alpha_(alpha), d_(d), theta_(theta)
{

}

KModifiedDH::KModifiedDH(const KModifiedDH &dh) :
    a_(dh.a_), alpha_(dh.alpha_), d_(dh.d_), theta_(dh.theta_)

{

}

KModifiedDH::~KModifiedDH()
{

}
