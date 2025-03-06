#include "kstandarddh.h"

KStandardDH::KStandardDH()
{

}

KStandardDH::KStandardDH(double a, double alpha, double d, double theta) :
    a_(a), alpha_(alpha), d_(d), theta_(theta)
{

}

KStandardDH::KStandardDH(const KStandardDH &dh) :
    a_(dh.a_), alpha_(dh.alpha_), d_(dh.d_), theta_(dh.theta_)
{

}

KStandardDH::~KStandardDH()
{

}
