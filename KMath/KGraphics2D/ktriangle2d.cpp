#include "ktriangle2d.h"

KTriangle2D::KTriangle2D()
{

}

KTriangle2D::KTriangle2D(const KPointF &p1, const KPointF &p2,
                         const KPointF &p3) : p1_(p1), p2_(p2), p3_(p3)
{

}

KTriangle2D::KTriangle2D(const KTriangle2D &triangle) :
    p1_(triangle.p1_), p2_(triangle.p2_), p3_(triangle.p3_)
{

}

KTriangle2D::~KTriangle2D()
{

}
