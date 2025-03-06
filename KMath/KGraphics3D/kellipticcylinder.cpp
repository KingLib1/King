#include "kellipticcylinder.h"

KEllipticCylinder::KEllipticCylinder() : a_(0), b_(0), height_(0)
{

}

KEllipticCylinder::KEllipticCylinder(double a, double b, double height) :
    a_(a), b_(b), height_(height)
{

}

KEllipticCylinder::KEllipticCylinder(double a, double b, double height,
                                     const KRectCoordSystem3D &sys) :
    a_(a), b_(b), height_(height), sys_(sys)
{

}

KEllipticCylinder::~KEllipticCylinder()
{

}
