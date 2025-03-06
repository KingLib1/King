#ifndef KSPLITER_H
#define KSPLITER_H

#include <QVector>

#include "kfrustum.h"
#include "kcylinder.h"
#include "kellipse3d.h"
#include "karchimedesspiral3d.h"
#include "ksphere.h"
#include "kcircle2d.h"
#include "karc2d.h"
#include "ktriangle3d.h"
#include "kcupgrindingwheel.h"

class KING_EXPORT KSpliter
{
public:
    KSpliter();

    QVector<double> split(double t0, double t, double dt);
    QVector<double> split(const KRange &range, double dt);
    QVector<double> split(double t0, double t, int slices,
                          bool contain_first = true, bool contain_last = true);
    QVector<KVector3D> split(KVector3D v0, KVector3D v, int slices,
                             bool contain_first = true,
                             bool contain_last = true);
    QVector<KVector2D> split(KVector2D v0, KVector2D v, int slices,
                             bool contain_first = true,
                             bool contain_last = true);
    QVector<KPointF> split(KPointF p0, KPointF p, int slices,
                             bool contain_first = true,
                             bool contain_last = true);
    QVector<KCircle3D> split(const KFrustum &frustum, int rings) const;
    QVector<QVector<KVector3D>> split(const KFrustum &frustum,
                                      int rings, int slices) const;
    QVector<QVector<KVector3D>> split(const KCylinder &cylinder,
                                      int rings, int slices) const;
    QVector<KCircle3D> split(const KCylinder &cylinder, int rings) const;
    QVector<KPointF> split(const KCircle2D &circle, int slices) const;
    QVector<KVector3D> split(const KCircle3D &circle, int slices) const;
    QVector<KVector3D> split(const KEllipse3D &ellipse, int slices_4) const;
    QVector<KCircle3D> split(const KSphere &sphere, int rings) const;
    QVector<KPointF> split(const KLineSegment2D &line, int slices,
                           bool contain_first = true,
                           bool contain_last = true) const;
    /**
     * @brief 按弧度拆分螺旋线,分成slices段，共有slices + 1个点
     */
    QVector<KVector3D> split(const KArchimedesSpiral3D &spiral, double dt,
                             int slices) const;
    QVector<KPointF> split(const KArc2D &arc,int slices) const;

    QVector<KTriangle3D> triangulate(const KCircle3D &circle, int slices) const;
    QVector<KTriangle3D> triangulate(const QVector<KCircle3D> &circles,
                                     int slices) const;
};



#endif // KSPLITER_H
