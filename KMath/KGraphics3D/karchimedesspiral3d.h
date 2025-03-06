#ifndef KARCHIMEDESSPIRAL3D_H
#define KARCHIMEDESSPIRAL3D_H

#include "kvector3d.h"

class KING_EXPORT KArchimedesSpiral3D
{
public:
    KArchimedesSpiral3D();
    KArchimedesSpiral3D(double r0, double t0, double z0, double dr, double dz);
    KArchimedesSpiral3D(double helix_angle, double radius);
    /**
     * @brief KArchimedesSpiral3D 等导程螺旋线
     * @param helix_angle 螺旋角
     * @param taper 锥度（>0半径扩大，<0半径缩小）
     * @param radius 半径
     */
    KArchimedesSpiral3D(double helix_angle, double taper, double radius);
    /**
     * @param start 起点
     * @param helix_angle 螺旋角
     */
    KArchimedesSpiral3D(const KVector3D &start, double helix_angle);
    /**
     * @brief KArchimedesSpiral3D 两点构造螺旋线
     * @param p0 起点
     * @param p1 任意点
     */
    KArchimedesSpiral3D(const KVector3D &p0, const KVector3D &p1);

    inline void setR0(double r0) {r0_ = r0;}
    inline void setT0(double t0) {t0_ = t0;}
    inline void setZ0(double z0) {z0_ = z0;}
    inline void setDr(double dr) {dr_ = dr;}
    inline void setDz(double dz) {dz_ = dz;}
    void setHelixAngle(double angle);
    inline void rotate(double angle);
    inline void rotateRadian(double radian);

    inline double r0() const {return r0_;}
    inline double t0() const {return t0_;}
    inline double z0() const {return z0_;}
    inline double dr() const {return dr_;}
    inline double dz() const {return dz_;}
    inline double radiusAt(double dt) const;
    double helixAngle() const;
    /**
     * @brief 计算从弧度lower到upper的线长
     * @param lower 相对于起点的段起点弧度
     * @param upper 相对于起点的段终点弧度
     */
    double length(double lower, double upper) const;
    /**
     * @brief 导程
     */
    inline double lead() const;
    /**
     * @brief 通过螺旋半径计算与此螺旋线相等导程的螺旋角
     */
    double helixAngleOfEqualLeadByRadius(double radius) const;
    /**
     * @brief 根据缠绕的弧度计算坐标
     */
    KVector3D pos(double dt) const;
    KVector3D tangentVector(double dt) const;
    KArchimedesSpiral3D rotated(double angle) const;
    KArchimedesSpiral3D rotatedRadian(double radian) const;
    inline double radianAtZ(double z) const;
    inline double radianAtHeight(double height) const;

private:
    double r0_; // 起点极径
    double t0_; // 起点弧度
    double z0_; // 起点z值
    double dr_; // 单位弧度极径增量
    double dz_; // 单位弧度z轴增量
};

inline void KArchimedesSpiral3D::rotate(double angle)
{
    t0_ += kDegreesToRadians(angle);
}

inline void KArchimedesSpiral3D::rotateRadian(double radian)
{
    t0_ += radian;
}

inline double KArchimedesSpiral3D::radiusAt(double dt) const
{
    return r0_ + dr_ * dt;
}

inline double KArchimedesSpiral3D::lead() const
{
    return K_2PI * dz_;
}

inline double KArchimedesSpiral3D::radianAtZ(double z) const
{
    return (z - z0_) / dz_ + t0_;
}

inline double KArchimedesSpiral3D::radianAtHeight(double height) const
{
    return height / dz_ + t0_;
}

#endif // KARCHIMEDESSPIRAL3D_H
