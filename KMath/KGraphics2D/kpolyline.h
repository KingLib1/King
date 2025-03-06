#ifndef KPOLYLINE_H
#define KPOLYLINE_H

#include <QVector>

#include "karc2d.h"

struct KVertex {
    KPointF pos;
    double bulge; // 凸度（四分之一角度正切值）,与下一个点组合
};

class KING_EXPORT KPolyline
{
public:
    KPolyline();
    KPolyline(const QVector<KVertex> &vertexes);

    inline void setVertexes(const QVector<KVertex> &vertexes);
    inline const QVector<KVertex> &vertexes() const;

    bool isLine(int index);
    bool isArc(int index);

    KLineSegment2D toLineSegment(int index) const;
    KArc2D toArc(int index) const;

    inline const int vertexSize() const;
    inline const KVertex &at(int index) const;

    KPolyline &operator<<(const KVertex &vertex);

private:
    QVector<KVertex> vertexes_;
};

inline void KPolyline::setVertexes(const QVector<KVertex> &vertexes)
{
    vertexes_ = vertexes;
}

inline const QVector<KVertex> &KPolyline::vertexes() const
{
    return vertexes_;
}

inline const int KPolyline::vertexSize() const
{
    return vertexes_.size();
}

inline const KVertex &KPolyline::at(int index) const
{
    return vertexes_.at(index);
}

#endif // KPOLYLINE_H
