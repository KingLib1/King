#ifndef KPOLYGON3D_H
#define KPOLYGON3D_H

#include <QVector>

#include "klinesegment3d.h"

class KING_EXPORT KPolygon3D
{
public:
    KPolygon3D();
    KPolygon3D(const QVector<KVector3D> &points);
    KPolygon3D(const KPolygon3D &polygon);
    ~KPolygon3D();

    inline void append(const KVector3D &point);
    inline void append(const QVector<KVector3D> &points);
    inline void setPoints(const QVector<KVector3D> &points);
    inline void clear();

    inline const QVector<KVector3D> &points() const;
    inline int size() const;
    QVector<KLineSegment3D> toLineSegment() const;

    inline KPolygon3D &operator<<(const KVector3D &point);
    inline KPolygon3D &operator<<(const QVector<KVector3D> &points);
    inline KPolygon3D &operator=(const KPolygon3D &polygon);

private:
    QVector<KVector3D> points_;
};

inline void KPolygon3D::append(const KVector3D &point)
{
    points_ << point;
}

inline void KPolygon3D::append(const QVector<KVector3D> &points)
{
    points_ << points;
}

inline void KPolygon3D::setPoints(const QVector<KVector3D> &points)
{
    points_ = points;
}

inline void KPolygon3D::clear()
{
    points_.clear();
}

inline const QVector<KVector3D> &KPolygon3D::points() const
{
    return points_;
}

inline int KPolygon3D::size() const
{
    return points_.size();
}

inline KPolygon3D &KPolygon3D::operator<<(const KVector3D &point)
{
    points_ << point;
    return *this;
}

inline KPolygon3D &KPolygon3D::operator<<(const QVector<KVector3D> &points)
{
    points_ << points;
    return *this;
}

inline KPolygon3D &KPolygon3D::operator=(const KPolygon3D &polygon)
{
    points_ = polygon.points_;
    return *this;
}

#endif // KPOLYGON3D_H
