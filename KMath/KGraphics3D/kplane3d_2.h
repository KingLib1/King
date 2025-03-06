#ifndef KPLANE3D_2_H
#define KPLANE3D_2_H

#include "kline3d.h"

// 与KPlane3D不同的是，此类不对法向量进行单位化以提高效率
class KPlane3D_2
{
public:
    KPlane3D_2();
    KPlane3D_2(const KVector3D &point, const KVector3D &normal);
    KPlane3D_2(const KVector3D &normal, double d); // 矢量表示法

    KLine3D intersected(const KPlane3D_2 &plane) const;

private:
    KVector3D n_;
    double d_; // p.n = d;(矢量表示法，n为法向量, p为平面上任意点)
};

#endif // KPLANE3D_2_H
