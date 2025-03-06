#ifndef KCONVEXPOLYGON_H
#define KCONVEXPOLYGON_H

#include <QVector>

#include "krect.h"

class KING_EXPORT KConvexPolygon
{
public:
    KConvexPolygon();
    KConvexPolygon(const QVector<KPointF> &points);

    inline void setPoints(const QVector<KPointF> &points);

    inline const QVector<KPointF> &points() const;
    KRect boundingRect() const;
    bool isClockwise() const;
    bool containsPoint(const KPointF &point) const;

    inline KConvexPolygon &operator=(const KConvexPolygon &other);

private:
    KRect boundingRectWithValid() const;
    bool isClockwiseWithValid() const;
    bool containsPointWithClockwise(const KPointF &point) const;
    bool containsPointWithAntiClockwise(const KPointF &point) const;

    QVector<KPointF> points_;
};

inline void KConvexPolygon::setPoints(const QVector<KPointF> &points)
{
    points_ = points;
}

inline const QVector<KPointF> &KConvexPolygon::points() const
{
    return points_;
}

inline KConvexPolygon &KConvexPolygon::operator=(const KConvexPolygon &other)
{
    points_ = other.points_;
    return *this;
}

#endif // KCONVEXPOLYGON_H
