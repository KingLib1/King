#include "kpointf.h"

KPointF::KPointF() : x_(0), y_(0)
{

}

KPointF::KPointF(double x, double y) : x_(x), y_(y)
{

}

KPointF::KPointF(const KPointF &p) : x_(p.x_), y_(p.y_)
{

}

KPointF::KPointF(const KPoint &p) : x_(p.x()), y_(p.y())
{

}
