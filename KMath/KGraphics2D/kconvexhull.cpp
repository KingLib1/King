#include "kconvexhull.h"

#include <QDebug>

#include "KVector/kvector2d.h"

inline bool operator<=(const KPointF &p1, const KPointF &p2)
{
    if (kFabs(p1.x() - p2.x()) < 1e-9) {
        return p1.y() <= p2.y();
    } else {
        return p1.x() < p2.x();
    }
}

void ascendSort(QVector<KPointF> &points, int low, int high)
{
    if (low >= high)
        return;
    int low1 = low;
    int high1 = high;
    int middle = (low + high) >> 1;
    KPointF base(points.at(middle));
    points.replace(middle, points.at(high));
    points.replace(high, base);
    do {
        while (low < high) {
            if (points.at(low) <= base) {
                ++low;
            } else {
                points.replace(high, points.at(low));
                --high;
                break;
            }
        }
        while (low < high) {
            if (base <= points.at(high)) {
                --high;
            } else {
                points.replace(low, points.at(high));
                ++low;
                break;
            }
        }
    } while (low != high);
    points.replace(low, base);
    ascendSort(points, low1, low - 1);
    ascendSort(points, low + 1, high1);
}

KConvexHull::KConvexHull()
{

}

KConvexHull::KConvexHull(const QVector<KPointF> &points) : points_(points)
{
    calculateHull();
}

KConvexHull::~KConvexHull()
{

}

void KConvexHull::setPoints(const QVector<KPointF> &points)
{
    points_ = points;
    calculateHull();
}

void KConvexHull::sort()
{
    int low = 0;
    int high = points_.size() - 1;
    ascendSort(points_, low, high);
}

void KConvexHull::calculateHull()
{
    if (points_.size() < 3)
        return;
    sort();
    QVector<KPointF> hull;
    hull << points_.at(0) << points_.at(1);
    for (int i = 2; i < points_.size(); ++i) {
        while (hull.size() >= 2) {
            KVector2D v1(hull.at(hull.size() - 2), hull.at(hull.size() - 1));
            KVector2D v2(hull.at(hull.size() - 1), points_.at(i));
            if (KVector2D::crossProduct(v1, v2) <= 0)
                break;
            else
                hull.removeLast();
        }
        hull << points_.at(i);
    }
    hull << points_.at(points_.size() - 2);
    int lower = hull.size();
    for (int i = points_.size() - 3; i > -1; --i) {
        while (hull.size() >= lower) {
            KVector2D v1(hull.at(hull.size() - 2), hull.at(hull.size() - 1));
            KVector2D v2(hull.at(hull.size() - 1), points_.at(i));
            if (KVector2D::crossProduct(v1, v2) <= 0)
                break;
            else
                hull.removeLast();
        }
        hull << points_.at(i);
    }
    hull_.setPoints(hull);
}
