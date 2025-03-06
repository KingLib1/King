#include "ksquare2d.h"

KSquare2D::KSquare2D(double side_length) : side_length_(side_length)
{

}

KSquare2D::KSquare2D(const KPointF &center, double side_length) :
    center_(center), side_length_(side_length)
{

}
