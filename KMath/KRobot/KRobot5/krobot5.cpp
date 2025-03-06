#include "krobot5.h"

KRobot5::KRobot5()
{

}

void KRobot5::setToolOffset(double tool_len, double offset_rad)
{
    offset_rad_ = offset_rad;
    tool_len_ = tool_len;
}

void KRobot5::setUserCoorSys(double x, double y, double z, double rz)
{
    user_mat_.setToIdentity();
    user_mat_.translateBySelf(x, y, z);
    user_mat_.rotateZBySelf(rz);
    user_invert_ = user_mat_.inverted();
    user_rz_ = rz;
}

RectCoor5 KRobot5::JointToRect(const JointCoor5 &coor)
{
    double r1 = kDegreesToRadians(coor.a + 90);
    double r12 = kDegreesToRadians(coor.b) + r1;
    double r = r12 + offset_rad_;

    double x = len1_*kCos(r1) + len2_*kCos(r12) + tool_len_*kCos(r);
    double y = len1_*kSin(r1) + len2_*kSin(r12) + tool_len_*kSin(r) + coor.y;
    double z = coor.z;
    double c = coor.a + 90 + coor.b;
    c -= user_rz_;

    KVector3D pos(x, y, z);
    pos = user_invert_ * pos;

    return RectCoor5(pos.x(), pos.y(), pos.z(), c);
}

JointCoor5 KRobot5::RectToJoint(const RectCoor5 &coor, double lasty,
                                bool &success)
{
    KVector3D pos(coor.x, coor.y, coor.z);
    double coor_c = coor.c + user_rz_;
    pos = user_mat_ * pos;

    // 计算二臂末端位置相对于刀具位置的偏移量
    double r3 = kDegreesToRadians(coor_c) + offset_rad_ + K_PI;
    double dx3 = tool_len_ * kCos(r3);
    double dy3 = tool_len_ * kSin(r3);

    // 计算二关节相对于二臂末端的偏移量
    double bx = coor_c;
    double c2 = bx + 180;
    double r2 = kDegreesToRadians(c2);
    double dx2 = len2_ * kCos(r2);
    double dy2 = len2_ * kSin(r2);

    // 计算二关节位置
    double x2 = pos.x() + dx3 + dx2;
    double y2 = pos.y() + dy3 + dy2;

    if (kFabs(x2) > len1_ - EPS3) {
        success = false;
        return JointCoor5();
    }

    // 求第一关节y坐标
    double dy = pythagoreanTheorem_Right(x2, len1_);
    double y1_1 = y2 - dy;
    double y1_2 = y2 + dy;

    // 选择y轴移动最小解
    double y1 = kFabs(y1_1 - lasty) < kFabs(y1_2 - lasty) ? y1_1 : y1_2;

    double r1x = kAtan2(y2 - y1, x2);
    double ax = kRadiansToDegrees(r1x);
    double a = ax - 90;
    double b = bx - ax;

    success = true;
    return JointCoor5(a, b, y1, pos.z());
}
