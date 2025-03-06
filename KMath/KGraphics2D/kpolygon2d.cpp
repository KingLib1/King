#include "kpolygon2d.h"

#include <QDebug>

#include "KGraphics2D/klinesegment2d.h"
#include "KAlgorithm.h"

inline bool operator<(const KPointF &p1, const KPointF &p2)
{
    if (kFabs(p1.x() - p2.x()) > 1e-9) {
        return p1.x() < p2.x();
    } else {
        return p1.y() < p2.y();
    }
}

// 寻找多边形最左边的点
int xMinIndex(const QVector<KPointF> &points)
{
    int min_index = 0;
    for (int i = 1; i < points.size(); ++i) {
        if (points.at(i) < points.at(min_index))
            min_index = i;
    }
    return min_index;
}

KPolygon2D::KPolygon2D()
{

}

KPolygon2D::KPolygon2D(const QVector<KPointF> &points) : points_(points)
{

}

KPolygon2D::KPolygon2D(const KPolygon2D &polygon) : points_(polygon.points_)
{

}

void KPolygon2D::translate(const KPointF &dv)
{
    for (int i = 0; i < points_.size(); ++i)
        points_[i] += dv;
}

void KPolygon2D::translate(double dx, double dy)
{
    for (int i = 0; i < points_.size(); ++i)
        points_[i].translate(dx, dy);
}

void KPolygon2D::invert()
{
    if (points_.isEmpty())
        return;
    QVector<KPointF> temp;
    temp << points_.at(0);
    for (int i = points_.size() - 1; i > 0; --i)
        temp << points_.at(i);
    points_ = temp;
}

bool KPolygon2D::clockwise() const
{
    if (points_.size() < 3)
        return false;

    double minx = points_.at(0).x();
    QVector<int> minx_index;
    minx_index << 0;
    for (int i = 1; i < points_.size(); ++i) {
        if (kFabs(points_.at(i).x() - minx) < EPS6) {
            minx_index << i;
        } else if (points_.at(i).x() < minx) {
            minx_index.clear();
            minx_index << i;
            minx = points_.at(i).x();
        }
    }

    int xminy_index = minx_index.at(0);
    double miny = points_.at(xminy_index).y();
    for (int i = 1; i < minx_index.size(); ++i) {
        if (points_.at(minx_index.at(i)).y() < miny) {
            miny = points_.at(minx_index.at(i)).y();
            xminy_index = minx_index.at(i);
        }
    }

    KVector2D v1(points_.at(xminy_index),
                 points_.at((xminy_index + 1) % points_.size()));
    KVector2D v2(points_.at(xminy_index),
                 points_.at((xminy_index - 1 + points_.size()) % points_.size()));

    return KVector2D::crossProduct(v1, v2) > 0 ? false : true;
}

void KPolygon2D::triangulation(QVector<KTriangle2D> &triangles) const
{
    if (points_.size() < 3)
        return;
    triangulation(points_, triangles);
}

KPointF KPolygon2D::left() const
{
    if (isEmpty())
        return KPointF();
    int left_index = 0;
    for (int i = 1; i < points_.size(); ++i) {
        if (points_.at(i).x() < points_.at(left_index).x())
            left_index = i;
    }
    return points_.at(left_index);
}

KPointF KPolygon2D::right() const
{
    if (isEmpty())
        return KPointF();
    int right_index = 0;
    for (int i = 1; i < points_.size(); ++i) {
        if (points_.at(i).x() > points_.at(right_index).x())
            right_index = i;
    }
    return points_.at(right_index);
}

KPointF KPolygon2D::top() const
{
    if (isEmpty())
        return KPointF();
    int top_index = 0;
    for (int i = 1; i < points_.size(); ++i) {
        if (points_.at(i).y() > points_.at(top_index).y())
            top_index = i;
    }
    return points_.at(top_index);
}

KPointF KPolygon2D::bottom() const
{
    if (isEmpty())
        return KPointF();
    int bottom_index = 0;
    for (int i = 1; i < points_.size(); ++i) {
        if (points_.at(i).y() < points_.at(bottom_index).y())
            bottom_index = i;
    }
    return points_.at(bottom_index);
}

KRect KPolygon2D::boungdingRect() const
{
    if (isEmpty())
        return KRect();
    int left_index = 0;
    int right_index = 0;
    int top_index = 0;
    int bottom_index = 0;
    for (int i = 1; i < points_.size(); ++i) {
        if (points_.at(i).x() < points_.at(left_index).x())
            left_index = i;
        else if (points_.at(i).x() > points_.at(right_index).x())
            right_index = i;
        if (points_.at(i).y() > points_.at(top_index).y())
            top_index = i;
        else if (points_.at(i).y() < points_.at(bottom_index).y())
            bottom_index = i;
    }
    return KRect(points_.at(left_index).x(), points_.at(bottom_index).y(),
                 points_.at(right_index).x() - points_.at(left_index).x(),
                 points_.at(top_index).y() - points_.at(bottom_index).y());
}

KRange KPolygon2D::xRange() const
{
    if (isEmpty())
        return xRange();
    int left_index = 0;
    int right_index = 0;
    for (int i = 1; i < points_.size(); ++i) {
        if (points_.at(i).x() < points_.at(left_index).x())
            left_index = i;
        else if (points_.at(i).x() > points_.at(right_index).x())
            right_index = i;
    }
    return KRange(points_.at(left_index).x(), points_.at(right_index).x());
}

KRange KPolygon2D::yRange() const
{
    if (isEmpty())
        return xRange();
    int top_index = 0;
    int bottom_index = 0;
    for (int i = 1; i < points_.size(); ++i) {
        if (points_.at(i).y() < points_.at(bottom_index).y())
            bottom_index = i;
        else if (points_.at(i).y() > points_.at(top_index).y())
            top_index = i;
    }
    return KRange(points_.at(bottom_index).y(), points_.at(top_index).y());
}

double KPolygon2D::xMin() const
{
    if (points_.isEmpty())
        return 0;

    double min = points_.at(0).x();
    for (int i = 1; i < points_.size(); ++i)
        if (points_.at(i).x() < min)
            min = points_.at(i).x();
    return min;
}

double KPolygon2D::xMax() const
{
    if (points_.isEmpty())
        return 0;

    double max = points_.at(0).x();
    for (int i = 0; i < points_.size(); ++i)
        if (points_.at(i).x() > max)
            max = points_.at(i).x();
    return max;
}

double KPolygon2D::yMin() const
{
    if (points_.isEmpty())
        return 0;

    double min = points_.at(0).y();
    for (int i = 1; i < points_.size(); ++i)
        if (points_.at(i).y() < min)
            min = points_.at(i).y();
    return min;
}

double KPolygon2D::yMax() const
{
    if (points_.isEmpty())
        return 0;

    double max = points_.at(0).y();
    for (int i = 0; i < points_.size(); ++i)
        if (points_.at(i).y() > max)
            max = points_.at(i).y();
    return max;
}

double KPolygon2D::area() const
{
    if (points_.size() < 3)
        return 0;

    double sum = 0;
    for (int i = 2; i < points_.size(); ++i)
        sum += points_.at(i-1).x() * (points_.at(i).y() - points_.at(i-2).y());
    sum += points_.at(0).x() * (points_.at(1).y() - points_.last().y()) +
            points_.last().x() * (points_.at(0).y() - points_.at(points_.size() - 2).y());
    return sum / 2;
}

KPolygon2D KPolygon2D::translated(const KPointF &dv) const
{
    KPolygon2D polygon;
    for (int i = 0; i < points_.size(); ++i)
        polygon.points_ << points_.at(i) + dv;
    return polygon;
}

KPolygon2D KPolygon2D::translated(double dx, double dy) const
{
    KPolygon2D polygon;
    for (int i = 0; i < points_.size(); ++i)
        polygon.points_ << points_.at(i).translated(dx, dy);
    return polygon;
}

bool KPolygon2D::containsPoint(const KPointF &point) const
{
    if (points_.size() < 3)
        return false;

    KLineSegment2D line1(point, KPointF(xMax() + 10, point.y()));
    int intersect_num = 0;
    int bound_num = 0;
    int last = points_.size() - 1;
    for (int i = 0; i < last; ++i) {
        KLineSegment2D line2(points_.at(i), points_.at(i + 1));
        if (line1.intersects(line2)) {
            ++intersect_num;
            if (kFabs(point.y() - line2.y1()) < EPS9 ||
                    kFabs(point.y() - line2.y2()) < EPS9)
                ++bound_num;
        }
    }
    intersect_num -= bound_num / 2;
    if (intersect_num % 2 == 1)
        return true;
    return false;
}

QVector<KLineSegment2D> KPolygon2D::toLineSegment() const
{
    if (points_.isEmpty())
        return QVector<KLineSegment2D>();
    QVector<KLineSegment2D> lines(points_.size());
    int last = points_.size() - 1;
    for (int i = 0; i < last; ++i)
        lines.replace(i, KLineSegment2D(points_.at(i), points_.at(i + 1)));
    lines.replace(last, KLineSegment2D(points_.at(last), points_.at(0)));
    return lines;
}

KPolygon2D KPolygon2D::offseted(double o) const
{
    KPolygon2D pol;
    for (int i = 0; i < points_.size(); ++i) {
        int last = previousIndex(i, points_.size());
        int next = nextIndex(i, points_.size());
        KVector2D v1(points_.at(last), points_.at(i));
        v1.rotateNeg90();
        v1.normalize();
        v1 *= o;
        KVector2D v2(points_.at(i), points_.at(next));
        v2.rotateNeg90();
        v2.normalize();
        v2 *= o;
        KLineSegment2D line1(points_.at(last) + v1, points_.at(i) + v1);
        KLineSegment2D line2(points_.at(i) + v2, points_.at(next) + v2);

        KPointF inter;
        line1.intersect(line2, &inter);
        pol.append(inter);
    }
    return pol;
}

void KPolygon2D::triangulation(const QVector<KPointF> &points,
                               QVector<KTriangle2D> &triangles) const
{
    int size = points.size();
    if (size == 3) {
        KTriangle2D tri(points.at(0), points.at(1), points.at(2));
        triangles << tri;
        return;
    }

    int min_idx = xMinIndex(points);
    // 取多边形最左边的点与相邻两点构成三角形
    KTriangle2D tri(points.at(min_idx), points.at(nextIndex(min_idx, size)),
                    points.at(previousIndex(min_idx, size)));
    KRange xrange = tri.xRange();
    KRange yrange = tri.yRange();
    QVector<int> inrange_idx;
    int start = min_idx + 2;
    // 寻找在三角形包围盒里的点
    for (int i = 0; i < size - 3; ++i) {
        int index = (start + i) % size;
        if (xrange.contains(points.at(index).x()) &&
                yrange.contains(points.at(index).y()))
            inrange_idx << index;
    }
    // 判断点是否在三角形内部
    for (int i = inrange_idx.size() - 1; i >= 0; --i) {
        if (!tri.containsPoint(points.at(inrange_idx.at(i))))
            inrange_idx.removeAt(i);
    }

    if (inrange_idx.isEmpty()) {
        triangles << tri;
        QVector<KPointF> points1 = points;
        points1.removeAt(min_idx);
        return triangulation(points1, triangles);
    }
    KLineSegment2D line(tri.p2(), tri.p3());
    double maxdis = 0;
    int maxdis_idx = -1;
    // 寻找三角形内离p2p3直线最远的点
    for (int i = 0; i < inrange_idx.size(); ++i) {
        double dis = line.distanceSquareFromPointToLine(
                    points.at(inrange_idx.at(i)));
        if (dis >= maxdis) {
            maxdis_idx = inrange_idx.at(i);
            maxdis = dis;
        }
    }

    QVector<KPointF> points1;
    for (int i = min_idx; i != maxdis_idx; i = (i + 1) % size) {
        points1 << points.at(i);
    }
    points1 << points.at(maxdis_idx);

    QVector<KPointF> points2;
    for (int i = maxdis_idx; i != min_idx; i = (i + 1) % size) {
        points2 << points.at(i);
    }
    points2 << points.at(min_idx);

    triangulation(points1, triangles);
    triangulation(points2, triangles);
}

KPolyline KPolygon2D::arcOffseted(double o, int slices) const
{
    if (o > 0) {
        return arcOutOffseted(o, slices);
    }

    return KPolyline();
}

KPolyline KPolygon2D::arcOutOffseted(double o, int slices) const
{
    KPolyline pl;

    for (int i = 0; i < points_.size(); ++i) {
        int last = previousIndex(i, points_.size());
        int next = nextIndex(i, points_.size());
        KVector2D v1(points_.at(i), points_.at(last));
        KVector2D v2(points_.at(i), points_.at(next));
        if (KVector2D::crossProduct(v1, v2) < 0) {
            double rad = KVector2D::radian(v1, v2);
            rad = K_PI - rad;
            double bulge = kTan(rad / 4);
            v1.rotate90();
            v1.setLength(o);
            KPointF pos1 = points_.at(i) + v1;
            v2.rotateNeg90();
            v2.setLength(o);
            KPointF pos2 = points_.at(i) + v2;
            KVertex vertex = {pos1, bulge};
            pl << vertex;
            vertex = {pos2, 0};
            pl << vertex;
        } else {
            v1.rotate90();
            v1.setLength(o);
            v2.rotateNeg90();
            v2.setLength(o);
            KLineSegment2D line1(points_.at(last) + v1, points_.at(i) + v1);
            KLineSegment2D line2(points_.at(i) + v2, points_.at(next) + v2);
            KPointF inter;
            line1.intersect(line2, &inter);
            KVertex vertex = {inter, 0};
            pl << vertex;
        }
    }

    return pl;
}
