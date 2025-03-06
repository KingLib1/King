#ifndef KFITTING_H
#define KFITTING_H

#include <QVector>

#include "kplane3d.h"
#include "kcircle2d.h"
#include "klinear.h"

class KING_EXPORT KFitting
{
public:
    KFitting();
    // 散点拟合直线方程
    KLinear fitLinear(const QVector<KPointF> &points) const;
    // 散点拟合二维圆
    KCircle2D fitCircle2D(const QVector<KPointF> &points) const;
    // 散点拟合三维平面
    KPlane3D fitPlane(const QVector<KVector3D> &points) const;
};

#endif // KFITTING_H
