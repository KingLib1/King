#include "k01distribution.h"

K01Distribution::K01Distribution() : p_(0)
{

}

K01Distribution::K01Distribution(double p) : p_(p)
{

}

K01Distribution::K01Distribution(const K01Distribution &dis) : p_(dis.p_)
{

}

K01Distribution::~K01Distribution()
{

}
