#include "kpolyline.h"

KPolyline::KPolyline()
{

}

KPolyline::KPolyline(const QVector<KVertex> &vertexes) : vertexes_(vertexes)
{

}

bool KPolyline::isLine(int index)
{
    return isZero(vertexes_.at(index).bulge);
}

bool KPolyline::isArc(int index)
{
    return !isLine(index);
}

KLineSegment2D KPolyline::toLineSegment(int index) const
{
    return KLineSegment2D(vertexes_.at(index).pos, vertexes_.at(index + 1).pos);
}

KArc2D KPolyline::toArc(int index) const
{
    double span_rad = kAtan(vertexes_.at(index).bulge) * 4;
    return KArc2D(vertexes_.at(index).pos, vertexes_.at(index + 1).pos, span_rad);
}

KPolyline &KPolyline::operator<<(const KVertex &vertex)
{
    vertexes_ << vertex;
    return *this;
}
