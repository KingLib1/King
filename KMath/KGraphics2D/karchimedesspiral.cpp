#include "karchimedesspiral.h"

#include "kmath.h"

KArchimedesSpiral::KArchimedesSpiral()
{

}

KArchimedesSpiral::KArchimedesSpiral(double a, double b)
    : a_(a), b_(b)
{

}

KPointF KArchimedesSpiral::pos(double radian) const
{
    double r = a_ + b_ * radian;
    return KPointF(r * kCos(radian), r * kSin(radian));
}
