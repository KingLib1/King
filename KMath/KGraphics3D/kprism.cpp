#include "kprism.h"

#include "kcompatibly.h"

KPrism::KPrism() : dir_(0, 0, 1), height_(0)
{

}

KPrism::KPrism(const QVector<KVector3D> &bottom, const KVector3D &direction,
               double height) :
    bottom_(bottom), dir_(direction), height_(height)
{
    dir_.normalize();
}

QVector<QVector<KVector3D>> KPrism::split(int rings) const
{
    KVector3D dv = dir_ * (height_ / (rings - 1));
    QVector<QVector<KVector3D>> points;
    QVector<KVector3D> point = bottom_;
    points << point;
    for (int i = 1; i < rings; ++i) {
        translate(point, dv);
        points << point;
    }
    return points;
}
