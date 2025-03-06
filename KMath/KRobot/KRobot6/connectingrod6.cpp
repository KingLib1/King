#include "connectingrod6.h"

ConnectingRod6::ConnectingRod6() : l1x_(50), l1y_(0), l1z_(380), l2_(420),
    l3_(25), l4_(440), l5_(98)
{

}

ConnectingRod6::ConnectingRod6(double l1x, double l1y, double l1z, double l2,
                             double l3, double l4, double l5) :
    l1x_(l1x), l1y_(l1y), l1z_(l1z), l2_(l2), l3_(l3), l4_(l4), l5_(l5)
{

}

ConnectingRod6::ConnectingRod6(const ConnectingRod6 &other) :
    l1x_(other.l1x_), l1y_(other.l1y_), l1z_(other.l1z_), l2_(other.l2_),
    l3_(other.l3_), l4_(other.l4_), l5_(other.l5_)
{

}

ConnectingRod6::~ConnectingRod6()
{

}
