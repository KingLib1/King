#include "robot6.h"

Robot6::Robot6()
{

}

Robot6::~Robot6()
{

}

void Robot6::jointCoorToFlangeCoor(const JointCoor6 &joint)
{
    KMatrix4x4 matrix;
    matrix.rotateZBySelf(joint.j1());

    // 对下面注释部分的优化
//    double angle_a = 90 - joint.j2();
//    double angle_b = angle_a - joint.j3() - arm2_triangle_angleb_;
//    double radian_a = kDegreesToRadians(angle_a);
//    double radian_b = kDegreesToRadians(angle_b);
//    double dx = cos(radian_a) * para_.l2() + cos(radian_b) * arm2_triangle_.c();
//    double dz = sin(radian_a) * para_.l2() + sin(radian_b) * arm2_triangle_.c();
//    dx += para_.l1x();
//    dz += para_.l1z();
//    matrix.translateX(dx);
//    matrix.translateZ(dz);
//    matrix.rotateYBySelf(joint.j2() + joint.j3() + 90);

    matrix.translateBySelf(para_.l1x(), para_.l1y(), para_.l1z());
    matrix.rotateYBySelf(joint.j2());
    matrix.translateZ(para_.l2());
    matrix.rotateYBySelf(joint.j3() + 90);
    matrix.translateX(-para_.l3());
    matrix.translateZ(para_.l4());

    matrix.rotateZBySelf(joint.j4());
    matrix.rotateYBySelf(joint.j5());
    matrix.translateZ(para_.l5());
    matrix.rotateZBySelf(joint.j6());
}
