#include "krange.h"

KRange::KRange() : lower_(0), upper_(0)
{

}

KRange::KRange(double lower, double upper) : lower_(lower), upper_(upper)
{

}

KRange::KRange(const KRange &range) : lower_(range.lower_), upper_(range.upper_)
{

}

KRange::~KRange()
{

}
