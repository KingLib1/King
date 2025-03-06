#ifndef KFILLETCYLINDER_H
#define KFILLETCYLINDER_H

#include <QVector>

#include "kvector3d.h"

struct PosTanNor {
    KVector3D pos;
    KVector3D tangent;
    KVector3D normal;
};

class KING_EXPORT KFilletCylinder
{
public:
    KFilletCylinder();
    KFilletCylinder(double radius, double fillet, double inclination, double height,
                    double eccentricity = 0, double taper = 0);

    inline void setRadius(double radius) {radius_ = radius;}
    inline void setFillet(double fillet) {fillet_ = fillet;}
    inline void setInclination(double inclination) {inclination_ = inclination;}
    inline void setHeight(double height) {height_ = height;}
    inline void setEccentricity(double eccentricity) {eccentricity_ = eccentricity;}

    inline double radius() const {return radius_;}
    inline double fillet() const {return fillet_;}
    inline double height() const {return height_;}
    inline double inclination() const {return inclination_;}
    inline double eccentricity() const {return eccentricity_;}

    // 等导程
    KVector3D posOnFilletBlade(double lead, double t) const; // 刃线位置,t<0则计算刃倾角内部刃线，下同
    KVector3D tanOnFilletBlade(double lead, double t) const; // 刃线切向量
    KVector3D normalOnFilletBlade(double lead, double t) const; // 法向量
    /**
     * @brief lowerHalfBlade
     * @param lead 导程弧
     * @param dlen 拆分的长不超过dlen
     * @param ts 返回每个点的弧度
     * @return 每个点的坐标
     */
    QVector<PosTanNor> posTanNorOnBlade_Equal(double lead, double dlen, double t0,
                                              double t1, QVector<double> &ts) const;

    // 螺旋角现性增加(以高度拆分球面螺旋角，计算球体刃线)
    QVector<PosTanNor> posTanNorOnBlade_Linear(
            double helix, double r0, double r1, double dlen,
            QVector<double> &ts) const;
    // 螺旋角现性增加(以高度拆分,以柱体螺旋角等导程计算球体刃线,未完善)
    QVector<PosTanNor> posTanNorOnBlade_Linear2(
            double helix, double r0, double r1, double dlen,
            QVector<double> &ts) const;
    // 直槽
    QVector<PosTanNor> posTanNorOnBlade_Straight(double r0, double r1, double dlen,
            QVector<double> &ts) const;

private:
    double radius_;
    double fillet_;
    double inclination_; // 刃倾角
    double height_;
    double eccentricity_; // 偏心距
    double taper_; // 锥度(正扩大，负缩小)
};

#endif // KFILLETCYLINDER_H
