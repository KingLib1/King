#include "kpolygon3d.h"

KPolygon3D::KPolygon3D()
{

}

KPolygon3D::KPolygon3D(const QVector<KVector3D> &points) : points_(points)
{

}

KPolygon3D::KPolygon3D(const KPolygon3D &polygon) : points_(polygon.points_)
{

}

KPolygon3D::~KPolygon3D()
{

}

QVector<KLineSegment3D> KPolygon3D::toLineSegment() const
{
    if (points_.isEmpty())
        return QVector<KLineSegment3D>();
    QVector<KLineSegment3D> lines(points_.size());
    int last = points_.size() - 1;
    for (int i = 0; i < last; ++i)
        lines.replace(i, KLineSegment3D(points_.at(i), points_.at(i + 1)));
    lines.replace(last, KLineSegment3D(points_.at(last), points_.at(0)));
    return lines;
}
