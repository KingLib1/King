#ifndef KPITCHGRADIENTSPRING_H
#define KPITCHGRADIENTSPRING_H

#include <QVector>

#include "kvector3d.h"
#include "KPair.h"
#include "kboundingvolume.h"

//enum SpiralDirection {
//    Left,
//    Right
//};

// 螺距渐变弹簧，沿着z轴正方向为正
class KING_EXPORT KPitchGradientSpring
{
public:
    KPitchGradientSpring();
    KPitchGradientSpring(
            double r1, double r2, double pitch1, double pitch2, double turns,
            double z0 = 0, double t0 = 0/*,
            SpiralDirection direction = SpiralDirection::Right*/);

    inline void setR1(double r1);
    inline void setR2(double r2);
    inline void setPitch1(double pitch1);
    inline void setPitch2(double pitch2);
    inline void setTurns(double turns);
    /**
     * @brief 保持其他参数不变，根据高度值修改pitch2
     */
    inline void setHeightOnlyChangePitch2(double height);
    /**
     * @brief 保持其他参数不变，根据高度值修改pitch1
     */
    inline void setHeightOnlyChangePitch1(double height);
    /**
     * @brief 保持其他参数不变，根据高度值修改turns
     */
    inline void setHeightOnlyChangeTurns(double height);

    inline double r1() const;
    inline double r2() const;
    inline double pitch1() const;
    inline double pitch2() const;
    inline double t0() const;
    inline double z0() const;
    /**
     * @param dt为起始点沿着弹簧到达所求点之间经过的弧度值
     */
    inline double pitchAt(double dt) const;
    inline double turns() const;
    inline double totalRadian() const;
//    inline SpiralDirection direction() const;
    /**
     * @brief 求某点处的z坐标值
     * @param dt为起始点沿着弹簧到达所求点之间经过的弧度值
     */
    double zAt(double dt) const;
    /**
     * @param dt为起始点沿着弹簧到达所求点之间经过的弧度值
     */
    KVector3D pos(double dt) const;
    /**
     * @brief 求某点处切向量
     * @param dt为起始点沿着弹簧到达所求点之间经过的弧度值
     */
    KVector3D tangentVector(double dt) const;
    KPair<KVector3D, KVector3D> posAndTan(double dt) const;
    inline double height() const; // 弹簧高度(起点与终点的z值之差)
    double length() const; // 弹簧线长
    /**
     * @brief 把弹簧拆分为slices段，包含位置和切向量
     */
    QVector<KPair<KVector3D, KVector3D>> split2(int slices);

    KBoundingVolume boundingVolume() const;
    KRange zRange() const;

private:
    double r1_;     // 起始外径
    double r2_;     // 末端外径
    double p1_;     // 起始螺距
    double p2_;     // 末端螺距
    double turns_;  // 圈数
    double z0_;     // 起点z坐标
    double t0_;     // 起点弧度
//    SpiralDirection dir_; // 螺旋方向
};

inline void KPitchGradientSpring::setR1(double r1)
{
    r1_ = r1;
}

inline void KPitchGradientSpring::setR2(double r2)
{
    r2_ = r2;
}

inline void KPitchGradientSpring::setPitch1(double pitch1)
{
    p1_ = pitch1;
}

inline void KPitchGradientSpring::setPitch2(double pitch2)
{
    p2_ = pitch2;
}

inline void KPitchGradientSpring::setTurns(double turns)
{
    turns_ = turns;
}

inline void KPitchGradientSpring::setHeightOnlyChangePitch2(double height)
{
    p2_ = height * 2 / turns_ - p1_;
}

inline void KPitchGradientSpring::setHeightOnlyChangePitch1(double height)
{
    p1_ = height * 2 / turns_ - p2_;
}

inline void KPitchGradientSpring::setHeightOnlyChangeTurns(double height)
{
    turns_ = height * 2 / (p1_ + p2_);
}

inline double KPitchGradientSpring::r1() const
{
    return r1_;
}

inline double KPitchGradientSpring::r2() const
{
    return r2_;
}

inline double KPitchGradientSpring::pitch1() const
{
    return p1_;
}

inline double KPitchGradientSpring::pitch2() const
{
    return p2_;
}

inline double KPitchGradientSpring::t0() const
{
    return t0_;
}

inline double KPitchGradientSpring::z0() const
{
    return z0_;
}

inline double KPitchGradientSpring::pitchAt(double dt) const
{
    return p1_ + (p2_ - p1_) / totalRadian() * dt;
}

inline double KPitchGradientSpring::turns() const
{
    return turns_;
}

inline double KPitchGradientSpring::height() const
{
    return (p1_ + p2_) * turns_ / 2;
}

inline double KPitchGradientSpring::totalRadian() const
{
//    return dir_ == SpiralDirection::Right ? turns_ * K_2PI : -turns_ * K_2PI;
    return turns_ * K_2PI;
}

//inline SpiralDirection KPitchGradientSpring::direction() const
//{
//    return dir_;
//}

#endif // KPITCHGRADIENTSPRING_H
