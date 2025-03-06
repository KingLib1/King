#include "ktriangle.h"

KTriangle::KTriangle() : a_(0), b_(0), c_(0)
{

}

KTriangle::KTriangle(double a, double b, double c) : a_(a), b_(b), c_(c)
{

}

KTriangle::KTriangle(const KTriangle &tri) : a_(tri.a_), b_(tri.b_), c_(tri.c_)
{

}

KTriangle::~KTriangle()
{

}
