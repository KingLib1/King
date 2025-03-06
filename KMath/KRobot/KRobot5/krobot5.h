#ifndef KROBOT5_H
#define KROBOT5_H

#include "jointcoor5.h"
#include "kmatrix4x4.h"

class KING_EXPORT KRobot5
{
public:
    KRobot5();

    inline void setLength1(double len);
    inline void setLength2(double len);

    // 没有刀具参数(长度和与第二臂的偏移弧度)
    void setToolOffset(double tool_len, double offset_rad);
    void setUserCoorSys(double x, double y, double z, double rz);

    RectCoor5 JointToRect(const JointCoor5 &coor);
    JointCoor5 RectToJoint(const RectCoor5 &coor, double lasty, bool &success);

private:
    double len1_;
    double len2_;

    // 刀具
    double offset_rad_; // 刀具位置与二臂末端的连线 与 二臂的夹角
    double tool_len_;

    KMatrix4x4 user_mat_;
    KMatrix4x4 user_invert_;
    double user_rz_;
};

inline void KRobot5::setLength1(double len)
{
    len1_ = len;
}

inline void KRobot5::setLength2(double len)
{
    len2_ = len;
}

#endif // KROBOT5_H
