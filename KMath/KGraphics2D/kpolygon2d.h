#ifndef KPOLYGON2D_H
#define KPOLYGON2D_H

#include <QVector>

#include "ktriangle2d.h"
#include "krect.h"
#include "kpolyline.h"

class KING_EXPORT KPolygon2D
{
public:
    KPolygon2D();
    KPolygon2D(const QVector<KPointF> &points);
    KPolygon2D(const KPolygon2D &polygon);

    inline void setPoints(const QVector<KPointF> &points);
    inline void append(const KPointF &point);
    inline void append(const QVector<KPointF> &points);
    inline void clear();
    void translate(const KPointF &dv);
    void translate(double dx, double dy);
    inline void swap(KPolygon2D &polygon);
    void invert();

    inline const QVector<KPointF> &points() const;
    bool clockwise() const;
    void triangulation(QVector<KTriangle2D> &triangles) const;
//    QVector<Triangle> monotonePolygonTriangulation(
//            const QVector<KVertex> &vertexs);
    inline bool isEmpty() const;
    inline int size() const;
    KPointF left() const;
    KPointF right() const;
    KPointF top() const;
    KPointF bottom() const;
    KRect boungdingRect() const;
    KRange xRange() const;
    KRange yRange() const;
    double xMin() const;
    double xMax() const;
    double yMin() const;
    double yMax() const;
    double area() const;
    KPolygon2D translated(const KPointF &dv) const;
    KPolygon2D translated(double dx, double dy) const;
    bool containsPoint(const KPointF &point) const;
    QVector<KLineSegment2D> toLineSegment() const;
    KPolygon2D offseted(double o) const;

    inline KPolygon2D &operator<<(const KPointF &point);
    inline KPolygon2D &operator<<(const QVector<KPointF> &points);
    inline KPolygon2D &operator=(const KPolygon2D &polygon);

private:
    void triangulation(const QVector<KPointF> &points,
                       QVector<KTriangle2D> &triangles) const;
    KPolyline arcOffseted(double o, int slices) const;
    KPolyline arcOutOffseted(double o, int slices) const;

    QVector<KPointF> points_;
};

inline void KPolygon2D::setPoints(const QVector<KPointF> &points)
{
    points_ = points;
}

inline void KPolygon2D::append(const KPointF &point)
{
    points_ << point;
}

inline void KPolygon2D::append(const QVector<KPointF> &points)
{
    points_ << points;
}

inline void KPolygon2D::clear()
{
    points_.clear();
}

inline void KPolygon2D::swap(KPolygon2D &polygon)
{
    points_.swap(polygon.points_);
}

inline const QVector<KPointF> &KPolygon2D::points() const
{
    return points_;
}

inline bool KPolygon2D::isEmpty() const
{
    return points_.isEmpty();
}

inline int KPolygon2D::size() const
{
    return points_.size();
}

inline KPolygon2D &KPolygon2D::operator<<(const KPointF &point)
{
    points_ << point;
    return *this;
}

inline KPolygon2D &KPolygon2D::operator<<(const QVector<KPointF> &points)
{
    points_ << points;
    return *this;
}

inline KPolygon2D &KPolygon2D::operator=(const KPolygon2D &polygon)
{
    points_ = polygon.points_;
    return *this;
}

#endif // KPOLYGON2D_H
