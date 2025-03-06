#include "kcomplex.h"

KComplex::KComplex() : a_(0), b_(0)
{
    
}

KComplex::KComplex(double a, double b) : a_(a), b_(b)
{
    
}

KComplex::KComplex(const KComplex &complex) : a_(complex.a_), b_(complex.b_)
{
    
}

KComplex::~KComplex()
{
    
}
