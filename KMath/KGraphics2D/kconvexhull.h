#ifndef CONVEXHULL_H
#define CONVEXHULL_H

#include <QVector>

#include "kpolygon2d.h"

class KING_EXPORT KConvexHull
{
public:
    KConvexHull();
    KConvexHull(const QVector<KPointF> &points);
    ~KConvexHull();

    void setPoints(const QVector<KPointF> &points);

    inline const KPolygon2D &convexHull() const;

private:
    void sort();
    void calculateHull();

    QVector<KPointF> points_;
    KPolygon2D hull_;
};

inline const KPolygon2D &KConvexHull::convexHull() const
{
    return hull_;
}

#endif // CONVEXHULL_H
