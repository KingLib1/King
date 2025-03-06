#include "kline2d.h"

KLine2D::KLine2D()
{

}

KLine2D::KLine2D(const KPointF &p1, const KPointF &p2) : p_(p1)
{
    direction_ = p2 - p1;
    direction_.normalize();
}

KLine2D::~KLine2D()
{

}
