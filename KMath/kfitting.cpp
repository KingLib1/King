#include "kfitting.h"

#include "KEquation.h"

KFitting::KFitting()
{

}

KLinear KFitting::fitLinear(const QVector<KPointF> &points) const
{
    double x2 = 0;
    double x = 0;
    double y = 0;
    double xy = 0;
    for (int i = 0; i < points.size(); ++i) {
        x2 += points.at(i).xSquare();
        x += points.at(i).x();
        y += points.at(i).y();
        xy += points.at(i).x() * points.at(i).y();
    }

    KVector2D v1(x2, x);
    KVector2D v2(x, points.size());
    KVector2D v3(xy, y);
    KVector2D solve = solveHomogeneousLinearEquations2x2(v1, v2, v3);
    return KLinear(solve.x(), solve.y());
}

KCircle2D KFitting::fitCircle2D(const QVector<KPointF> &points) const
{
    double sum_x = 0;
    double sum_y = 0;
    double sum_x2 = 0;
    double sum_y2 = 0;
    double sum_x3 = 0;
    double sum_y3 = 0;
    double sum_xy = 0;
    double sum_x2y = 0;
    double sum_xy2 = 0;
    for (int i = 0; i < points.size(); ++i) {
        double x = points.at(i).x();
        double y = points.at(i).y();
        double x2 = x * x;
        double y2 = y * y;
        double x3 = x2 * x;
        double y3 = y2 * y;
        sum_x += x;
        sum_y += y;
        sum_x2 += x2;
        sum_y2 += y2;
        sum_x3 += x3;
        sum_y3 += y3;
        sum_xy += x * y;
        sum_x2y += x2 * y;
        sum_xy2 += x * y2;
    }

    KVector3D v1(sum_x2, sum_xy, sum_x);
    KVector3D v2(sum_xy, sum_y2, sum_y);
    KVector3D v3(sum_x, sum_y, points.size());
    KVector3D v4(-sum_x3 - sum_xy2, -sum_x2y - sum_y3, -sum_x2 - sum_y2);
    KVector3D solve = solveHomogeneousLinearEquations3x3(v1, v2, v3, v4);

    KPointF center(-solve.x() / 2, -solve.y() / 2);
    double radius = kSqrt(center.originDistanceSquared() - solve.z());
    return KCircle2D(center, radius);
}

KPlane3D KFitting::fitPlane(const QVector<KVector3D> &points) const
{
    double sum_x2 = 0;
    double sum_y2 = 0;
    double sum_z2 = 0;
    double sum_xy = 0;
    double sum_xz = 0;
    double sum_yz = 0;
    double sum_x = 0;
    double sum_y = 0;
    double sum_z = 0;

    for (int i = 0; i < points.size(); ++i) {
        double x = points.at(i).x();
        double y = points.at(i).y();
        double z = points.at(i).z();
        sum_x += x;
        sum_y += y;
        sum_z += z;
        sum_x2 += x * x;
        sum_y2 += y * y;
        sum_z2 += z * z;
        sum_xy += x * y;
        sum_xz += x * z;
        sum_yz += y * z;
    }

    KVector3D v1(sum_x2, sum_xy, sum_xz);
    KVector3D v2(sum_xy, sum_y2, sum_yz);
    KVector3D v3(sum_xz, sum_yz, sum_z2);
    KVector3D v4(sum_x, sum_y, sum_z);
    KVector3D normal = solveHomogeneousLinearEquations3x3(v1, v2, v3, v4);
    double len = normal.length();
    double d = 1.0 / len;
    normal /= len;

    return KPlane3D(normal, d);
}
