#include "kcompatibly.h"
#include "qpolygon.h"

QMatrix4x4 toQMatrix4x4(const KMatrix4x4 &matrix)
{
    return QMatrix4x4(float(matrix.m11()), float(matrix.m12()), float(matrix.m13()),
                      float(matrix.m14()), float(matrix.m21()), float(matrix.m22()),
                      float(matrix.m23()), float(matrix.m24()), float(matrix.m31()),
                      float(matrix.m32()), float(matrix.m33()), float(matrix.m34()),
                      float(matrix.m41()), float(matrix.m42()), float(matrix.m43()),
                      float(matrix.m44()));
}

KMatrix4x4 toKMatrix4x4(const QMatrix4x4 &matrix)
{
    const float *data = matrix.constData();
    return KMatrix4x4(double(data[0]), double(data[1]), double(data[2]),
                      double(data[3]), double(data[4]), double(data[5]),
                      double(data[6]), double(data[7]), double(data[8]),
                      double(data[9]), double(data[10]), double(data[11]),
                      double(data[12]), double(data[13]), double(data[14]),
                      double(data[15]));
}

QVector<KPointF> toKPointF(const QVector<KVector3D> &v)
{
    QVector<KPointF> points2d;
    for (int i = 0; i < v.size(); ++i)
        points2d << v.at(i).toKPointF();
    return points2d;
}

QVector<QPointF> toQPointF(const QVector<KVector3D> &v)
{
    QVector<QPointF> points;
    for (int i = 0; i < v.size(); ++i)
        points << toQPointF(v.at(i));
    return points;
}

QVector<KTriangle3D> toKTriangle3D(const QVector<KTriangle2D> &tris, double z)
{
    QVector<KTriangle3D> tris3d;
    for (int i = 0; i < tris.size(); ++i) {
        tris3d << KTriangle3D(KVector3D(tris.at(i).p1(), z),
                              KVector3D(tris.at(i).p2(), z),
                              KVector3D(tris.at(i).p3(), z));
    }
    return tris3d;
}

void translate(QVector<KVector3D> &points, const KVector3D &translation)
{
    for (int i = 0; i < points.size(); ++i)
        points.replace(i, points.at(i) + translation);
}

void translateZ(QVector<KVector3D> &points, double dz)
{
    for (int i = 0; i < points.size(); ++i)
        points[i].translateZ(dz);
}

QVector<KVector3D> translated(const QVector<KVector3D> &points,
                              const KVector3D &translation)
{
    QVector<KVector3D> newpoints(points.size());
    for (int i = 0; i < points.size(); ++i)
        newpoints.replace(i, points.at(i) + translation);
    return newpoints;
}

QVector<KVector3D> translatedZ(const QVector<KVector3D> &points, double dz)
{
    QVector<KVector3D> newpoints(points.size());
    for (int i = 0; i < points.size(); ++i)
        newpoints.replace(i, points.at(i).translatedZ(dz));
    return newpoints;
}

QDebug operator<<(QDebug debug, const KVector3D &v)
{
    debug.nospace() << "KVector3D(" << QString::number(v.x(), 'f', 6) << ","
                    << QString::number(v.y(),'f',6) << ","
                    << QString::number(v.z(),'f',6) << ")";
    return debug;
}

QDebug operator<<(QDebug debug, const KPointF &p)
{
    debug.nospace() << "KPointF(" << QString::number(p.x(), 'f', 6) << ","
                    << QString::number(p.y(),'f',6) << ")";
    return debug;
}

QDebug operator<<(QDebug debug, const KCircle3D &c)
{
    const KVector3D &center = c.center();
    const KVector3D &normal = c.normal();
    debug.nospace() << "圆心("
                    << QString::number(center.x(), 'f', 6) << ","
                    << QString::number(center.y(),'f',6) << ","
                    << QString::number(center.z(),'f',6) << ")"
                    << " 法向量("
                    << QString::number(normal.x(), 'f', 6) << ","
                    << QString::number(normal.y(),'f',6) << ","
                    << QString::number(normal.z(),'f',6) << ")";
    return debug;
}

QDebug operator<<(QDebug debug, const KRange &range)
{
    debug.nospace() << "范围(" << QString::number(range.lower(), 'f', 6) << ", "
                  << QString::number(range.upper(), 'f', 6);
    return debug;
}

QVector<KVector3D> toKVector3D(const QVector<KPointF> &v, double z)
{
    QVector<KVector3D> ret;
    for (int i = 0; i < v.size(); ++i)
        ret << KVector3D(v.at(i), z);
    return ret;
}

QVector<KVector3D> toKVector3D(const QVector<QPointF> &v, double z)
{
    QVector<KVector3D> ret;
    for (int i = 0; i < v.size(); ++i)
        ret << toKVector3D(v.at(i), z);
    return ret;
}

QVector<KVector3D> toKVector3D(const QPolygonF &p, double z)
{
    QVector<KVector3D> ret;
    for (int i = 0; i < p.size(); ++i)
        ret << toKVector3D(p.at(i), z);
    return ret;
}

QVector<QVector3D> toQVector3D(const QVector<KVector3D> &v)
{
    QVector<QVector3D> ret;
    for (int i = 0; i < v.size(); ++i) {
        ret << toQVector3D(v.at(i));
    }
    return ret;
}
