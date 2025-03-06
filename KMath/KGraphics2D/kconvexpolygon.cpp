#include "kconvexpolygon.h"

#include "KVector/kvector2d.h"

KConvexPolygon::KConvexPolygon()
{

}

KConvexPolygon::KConvexPolygon(const QVector<KPointF> &points) : points_(points)
{

}

KRect KConvexPolygon::boundingRect() const
{
    if (points_.isEmpty())
        return KRect();
    return boundingRectWithValid();
}

bool KConvexPolygon::isClockwise() const
{
    if (points_.size() < 3)
        return false;
    return isClockwiseWithValid();
}

bool KConvexPolygon::containsPoint(const KPointF &point) const
{
    if (points_.size() < 3)
        return false;
    return isClockwiseWithValid() ? containsPointWithClockwise(point) :
                                    containsPointWithAntiClockwise(point);
}

KRect KConvexPolygon::boundingRectWithValid() const
{
    double left = points_.at(0).x();
    double right = left;
    double top = points_.at(0).y();
    double bottom = top;
    for (int i = 1; i < points_.size(); ++i) {
        if (points_.at(i).x() < left)
            left = points_.at(i).x();
        if (points_.at(i).x() > right)
            right = points_.at(i).x();
        if (points_.at(i).y() > top)
            top = points_.at(i).y();
        if (points_.at(i).y() < bottom)
            bottom = points_.at(i).y();
    }
    return KRect(left, bottom, right - left, top - bottom);
}

bool KConvexPolygon::isClockwiseWithValid() const
{
    KVector2D v1(points_.at(0), points_.at(1));
    KVector2D v2(points_.at(0), points_.at(2));
    return KVector2D::crossProduct(v1, v2) > 0 ? false : true;
}

bool KConvexPolygon::containsPointWithClockwise(const KPointF &point) const
{
    int last = points_.size() - 1;
    for (int i = 0; i < last; ++i) {
        KVector2D v1(points_.at(i), points_.at(i + 1));
        KVector2D v2(points_.at(i), point);
        if (KVector2D::crossProduct(v1, v2) > 0)
            return false;
    }
    KVector2D v1(points_.last(), points_.at(0));
    KVector2D v2(points_.last(), point);
    return KVector2D::crossProduct(v1, v2) > 0 ? false : true;
}

bool KConvexPolygon::containsPointWithAntiClockwise(const KPointF &point) const
{
    int last = points_.size() - 1;
    for (int i = 0; i < last; ++i) {
        KVector2D v1(points_.at(i), points_.at(i + 1));
        KVector2D v2(points_.at(i), point);
        if (KVector2D::crossProduct(v1, v2) < 0)
            return false;
    }
    KVector2D v1(points_.last(), points_.at(0));
    KVector2D v2(points_.last(), point);
    return KVector2D::crossProduct(v1, v2) < 0 ? false : true;
}
