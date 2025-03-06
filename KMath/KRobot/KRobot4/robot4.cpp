#include "robot4.h"

#include <QDebug>

#include "klinesegment2d.h"
#include "KDynamicMatrix.h"

Robot4::Robot4() : len1_(0), len2_(0)
{

}

Robot4::~Robot4()
{

}

KJointCoor4 Robot4::flangePosToJointCoor(
        const KPointF &pos, const KJointCoor4 &last_joint, bool &success)
{
    double a = len1_;
    double b = len2_;
    KLineSegment2D hypotenuse(0, 0, pos.x(), pos.y());
    double c = hypotenuse.length();
    double radian1 = kDegreesToRadians(last_joint.j1());
    double joint1_x = a * kCos(radian1);
    double joint1_y = a * kSin(radian1);
    KLineSegment2D upper_arm_line(0, 0, joint1_x, joint1_y);
    double degree_b = kRadiansToDegrees(kAcos((a*a + c*c - b*b) / (2*a*c)));
    double angle_ax = 0.0, angle_bx = 0.0;

    int mode = 0;

    // A轴变化最小解
//    if (hypotenuse.angleTo(upper_arm_line) > 180 + EPS) {
//        angle_ax = hypotenuse.angle() - degree_b;
//    } else {
//        angle_ax = hypotenuse.angle() + degree_b;
//        mode = 1;
//    }

    // B轴偏向不变解
    if (last_joint.j2() > EPS3) {
        angle_ax = hypotenuse.angle() - degree_b;
    } else if (last_joint.j2() < -EPS3){
        angle_ax = hypotenuse.angle() + degree_b;
        mode = 1;
    } else {
        if (hypotenuse.angleTo(upper_arm_line) > 180 + EPS3) {
            angle_ax = hypotenuse.angle() - degree_b;
        } else {
            angle_ax = hypotenuse.angle() + degree_b;
            mode = 1;
        }
    }

    radian1 = kDegreesToRadians(angle_ax);
    joint1_x = a * kCos(radian1);
    joint1_y = a * kSin(radian1);
    angle_bx = KLineSegment2D(joint1_x, joint1_y, pos.x(), pos.y()).angle();

    angle_ax = angleNormalized(angle_ax);
    angle_bx = angleNormalized(angle_bx - angle_ax);

    if (isAngle1Legal(angle_ax) && isAngle2Legal(angle_bx)) {
        success = true;
        return KJointCoor4(angle_ax, angle_bx, 0, 0);
    } else {
        if (mode == 0)
            angle_ax = hypotenuse.angle() + degree_b;
        else
            angle_ax = hypotenuse.angle() - degree_b;
        angle_ax = angleNormalized(angle_ax);
        angle_bx = -angle_bx;

        if (isAngle1Legal(angle_ax) && isAngle2Legal(angle_bx)) {
            success = true;
            return KJointCoor4(angle_ax, angle_bx, 0, 0);
        } else {
            success = false;
            return KJointCoor4();
        }
    }
}

KDynamicVector<double> Robot4::calibration20_1(const QVector<KJointCoor4> &coors)
{
    KDynamicMatrix<double> jacobi(2, 6);
    KDynamicVector<double> dxy(2);
    KDynamicVector<double> dp(6, 0);
    double len1 = len1_;
    double len2 = len2_;

    for (int i = 0; i < 20; i += 2) {
        len1 -= dp.at(0);
        len2 -= dp.at(1);
        KJointCoor4 coor1 = coors.at(i).degreesToRadians();
        coor1.setJ1(coor1.j1() - dp.at(2));
        coor1.setJ2(coor1.j2() - dp.at(3));
        double sinj11 = kSin(coor1.j1());
        double cosj11 = kCos(coor1.j1());
        double r1 = coor1.j1() + coor1.j2();
        double sinr1 = kSin(r1);
        double cosr1 = kCos(r1);
        KJointCoor4 coor2 = coors.at(i + 1).degreesToRadians();
        coor2.setJ1(coor2.j1() - dp.at(4));
        coor2.setJ2(coor2.j2() - dp.at(5));
        double sinj21 = kSin(coor2.j1());
        double cosj21 = kCos(coor2.j1());
        double r2 = coor2.j1() + coor2.j2();
        double sinr2 = kSin(r2);
        double cosr2 = kCos(r2);

        jacobi(0, 0) = cosj11 - cosj21;
        jacobi(0, 1) = cosr1 - cosr2;
        jacobi(0, 2) = -len1 * sinj11 - len2 * sinr1;
        jacobi(0, 3) = -len2 * sinr1;
        jacobi(0, 4) = len1 * sinj21 + len2 * sinr2;
        jacobi(0, 5) = len2 * sinr2;

        jacobi(1, 0) = sinj11 - sinj21;
        jacobi(1, 1) = sinr1 - sinr2;
        jacobi(1, 2) = len1 * cosj11 + len2 * cosr1;
        jacobi(1, 3) = len2 * cosr1;
        jacobi(1, 4) = -len1 * cosj21 - len2 * cosr2;
        jacobi(1, 5) = -len2 * cosr2;

        KPointF pos1 = jointRadianCoorToFlangePos(coor1);
        KPointF pos2 = jointRadianCoorToFlangePos(coor2);
        KPointF dpos = pos1 - pos2;
        dxy[0] = dpos.x();
        dxy[1] = dpos.y();
        KDynamicMatrix<double> jt = jacobi.transposed();
        dp += (jt * jacobi).inverted() * jt * dxy;
    }

    KDynamicVector<double> dp1(4);
    dp1[0] = dp[0];
    dp1[1] = dp[1];
    dp1[2] = dp[2];
    dp1[3] = dp[3];
    return dp1;
}

KDynamicVector<double> Robot4::calibration20_2(const QVector<KJointCoor4> &coors)
{
    KDynamicMatrix<double> jacobi(2, 9);
    KDynamicVector<double> dxy(2);
    KDynamicVector<double> dp(9, 0);
    double len1 = len1_;
    double len2 = len2_;
    double len3 = tool_.offsetLength();

    for (int i = 0; i < 20; i += 2) {
        len1 -= dp.at(0);
        len2 -= dp.at(1);
        len3 -= dp.at(2);

        KJointCoor4 coor1 = coors.at(i).degreesToRadians();
        coor1.setJ1(coor1.j1() - dp.at(3));
        coor1.setJ2(coor1.j2() - dp.at(4));
        coor1.setJ4(coor1.j4() - dp.at(5));
        double sina1 = kSin(coor1.j1());
        double cosa1 = kCos(coor1.j1());
        double a12 = coor1.j1() + coor1.j2();
        double sina12 = kSin(a12);
        double cosa12 = kCos(a12);
        double a123 = coor1.j1() + coor1.j2() + coor1.j4() + tool_.offsetRadian();
        double sina123 = kSin(a123);
        double cosa123 = kCos(a123);

        KJointCoor4 coor2 = coors.at(i + 1).degreesToRadians();
        coor2.setJ1(coor2.j1() - dp.at(6));
        coor2.setJ2(coor2.j2() - dp.at(7));
        coor2.setJ4(coor2.j4() - dp.at(8));
        double sinb1 = kSin(coor2.j1());
        double cosb1 = kCos(coor2.j1());
        double b12 = coor2.j1() + coor2.j2();
        double sinb12 = kSin(b12);
        double cosb12 = kCos(b12);
        double b123 = coor2.j1() + coor2.j2() + coor2.j4() + tool_.offsetRadian();
        double sinb123 = kSin(b123);
        double cosb123 = kCos(b123);

        jacobi(0, 0) = cosa1 - cosb1;
        jacobi(0, 1) = cosa12 - cosb12;
        jacobi(0, 2) = cosa123 - cosb123;
        jacobi(0, 3) = -len1 * sina1 - len2 * sina12 - len3 * sina123;
        jacobi(0, 4) = -len2 * sina12 - len3 * sina123;
        jacobi(0, 5) = -len3 * sina123;
        jacobi(0, 6) = len1 * sinb1 + len2 * sinb12 + len3 * sinb123;
        jacobi(0, 7) = len2 * sinb12 + len3 * sinb123;
        jacobi(0, 8) = len3 * sinb123;

        jacobi(1, 0) = sina1 - sinb1;
        jacobi(1, 1) = sina12 - sinb12;
        jacobi(1, 2) = sina123 - sinb123;
        jacobi(1, 3) = len1 * cosa1 + len2 * cosa12 + len3 * cosa123;
        jacobi(1, 4) = len2 * cosa12 + len3 * cosa123;
        jacobi(1, 5) = len3 * cosa123;
        jacobi(1, 6) = -len1 * cosb1 - len2 * cosb12 - len3 * cosb123;
        jacobi(1, 7) = -len2 * cosb12 - len3 * cosb123;
        jacobi(1, 8) = -len3 * cosb123;

        KPointF pos1 = jointRadianCoorToToolPos(coor1);
        KPointF pos2 = jointRadianCoorToToolPos(coor2);
        KPointF dpos = pos1 - pos2;
        dxy[0] = dpos.x();
        dxy[1] = dpos.y();
        KDynamicMatrix<double> jt = jacobi.transposed();
        dp += (jt * jacobi).inverted() * jt * dxy;
    }

    double tradian = tool_.offsetRadian() - dp[5];
    double tlen = tool_.offsetLength() - dp[2];
    double tx = tlen * kCos(tradian);
    double ty = tlen * kSin(tradian);
    double dx = tool_.offsetPos().x() - tx;
    double dy = tool_.offsetPos().y() - ty;

    KDynamicVector<double> dp1(6);
    dp1[0] = dp[0];
    dp1[1] = dp[1];
    dp1[2] = dp[3];
    dp1[3] = dp[4];
    dp1[4] = dx;
    dp1[5] = dy;
    qDebug() << dp1[0] << dp1[1] << dp1[2] << dp1[3] << dp1[4] << dp1[5];
    return dp1;
}

void Robot4::test()
{
    QVector<KJointCoor4> coors;
    coors << KJointCoor4(-62.072,17.144,-27.076,40.929)
          << KJointCoor4(-39.670,-26.162,-27.076,47.940)
          << KJointCoor4(-33.272,-59.892,-27.578,75.272)
          << KJointCoor4(-86.180,43.266,-27.578,73.870)
          << KJointCoor4(-107.054,60.730,-27.777,77.278)
          << KJointCoor4(-35.404,-78.512,-27.777,73.018)
          << KJointCoor4(-117.325,91.203,-27.975,81.276)
          << KJointCoor4(-15.698,-108.442,-28.162,86.732)
          << KJointCoor4(-67.441,-21.755,-27.638,58.529)
          << KJointCoor4(-82.732,7.693,-27.638,57.905)
          << KJointCoor4(35.560,26.539,-26.666,10.428)
          << KJointCoor4(65.855,-30.960,-26.666,16.154)
          << KJointCoor4(92.986,-63.724,-27.252,17.497)
          << KJointCoor4(28.209,56.733,-27.166,22.822)
          << KJointCoor4(10.211,100.079,-27.767,29.294)
          << KJointCoor4(113.864,-105.563,-28.016,111.163)
          << KJointCoor4(113.431,-79.477,-27.405,17.074)
          << KJointCoor4(31.022,74.044,-27.296,13.966)
          << KJointCoor4(60.492,24.687,-26.957,26.107)
          << KJointCoor4(91.154,-32.846,-27.067,24.810);
    calibration20_2(coors);
}
