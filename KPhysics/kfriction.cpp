#include "kfriction.h"

KFriction::KFriction() : us_(0), uk_(0), n_(0)
{

}

KFriction::KFriction(double us, double uk, double n) : us_(us), uk_(uk), n_(n)
{

}

KFriction::KFriction(const KFriction &fri) :
    us_(fri.us_), uk_(fri.uk_), n_(fri.n_)
{

}

KFriction::~KFriction()
{

}
