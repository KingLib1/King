#ifndef KCOMPATIBLY_H
#define KCOMPATIBLY_H

#include <QMatrix4x4>
#include <QVector>
#include <QPolygonF>

#include "kmatrix4x4.h"
#include "ktriangle3d.h"
#include "kcircle3d.h"
#include "KVector.h"
#include "KDynamicMatrix.h"

KING_EXPORT QMatrix4x4 toQMatrix4x4(const KMatrix4x4 &matrix);
KING_EXPORT KMatrix4x4 toKMatrix4x4(const QMatrix4x4 &matrix);

KING_EXPORT inline QVector3D toQVector3D(const KVector3D &v)
{
    return QVector3D(float(v.x()), float(v.y()), float(v.z()));
}

KING_EXPORT QVector<QVector3D> toQVector3D(const QVector<KVector3D> &v);

KING_EXPORT inline KVector3D toKVector3D(const QVector3D &v)
{
    return KVector3D(double(v.x()), double(v.y()), double(v.z()));
}

KING_EXPORT inline KVector3D toKVector3D(const QPointF &p, double z)
{
    return KVector3D(p.x(), p.y(), z);
}

KING_EXPORT QVector<KVector3D> toKVector3D(const QVector<KPointF> &v, double z);
KING_EXPORT QVector<KVector3D> toKVector3D(const QVector<QPointF> &v, double z);
KING_EXPORT QVector<KVector3D> toKVector3D(const QPolygonF &p, double z);

KING_EXPORT inline KPointF toKPointF(const QPointF &point)
{
    return KPointF(point.x(), point.y());
}

KING_EXPORT QVector<KPointF> toKPointF(const QVector<KVector3D> &v);
KING_EXPORT inline QPointF toQPointF(const KVector3D &v)
{
    return QPointF(v.x(), v.y());
}
KING_EXPORT QVector<QPointF> toQPointF(const QVector<KVector3D> &v);

KING_EXPORT QVector<KTriangle3D> toKTriangle3D(
        const QVector<KTriangle2D> &tris, double z);

KING_EXPORT void translate(QVector<KVector3D> &points,
                            const KVector3D &translation);
KING_EXPORT void translateZ(QVector<KVector3D> &points, double dz);

KING_EXPORT QVector<KVector3D> translated(const QVector<KVector3D> &points,
                                           const KVector3D &translation);
KING_EXPORT QVector<KVector3D> translatedZ(const QVector<KVector3D> &points,
                                            double dz);

template<typename T>
KING_EXPORT QVector<T> toQVector(const KVector<T> &v)
{
    QVector<T> ret;
    for (int i = 0; i < v.size(); ++i)
        ret << v.at(i);
    return ret;
}

template<typename T>
KING_EXPORT QVector<QVector<T>> toQVector(const KVector<KVector<T>> &v)
{
    QVector<QVector<T>> ret;
    for (int i = 0; i < v.size(); ++i)
        ret << toQVector<T>(v.at(i));
    return ret;
}

KING_EXPORT QDebug operator<<(QDebug debug, const KVector3D &v);
KING_EXPORT QDebug operator<<(QDebug debug, const KPointF &p);
KING_EXPORT QDebug operator<<(QDebug debug, const KCircle3D &c);
KING_EXPORT QDebug operator<<(QDebug debug, const KRange &range);
template<typename T>
KING_EXPORT QDebug operator<<(QDebug debug, const KVector<T> &v)
{
    if (v.isEmpty())
        return debug;

    int last = v.size() - 1;
    for (int i = 0; i < last; ++i)
        debug << v.at(i) << ",\n";
    debug << v.at(last);
    return debug;
}

template<typename T>
KING_EXPORT QDebug operator<<(QDebug debug, const KDynamicMatrix<T> &v)
{
    debug << "\n";
    for (int i = 0; i < v.row(); ++i) {
        for (int j = 0; j < v.column(); ++j) {
            debug << v(i, j);
        }
        debug << "\n";
    }
    return debug;
}

#endif // KCOMPATIBLY_H
