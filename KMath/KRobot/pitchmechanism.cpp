#include "pitchmechanism.h"

#include"klinesegment2d.h"

PitchMechanism::PitchMechanism()
{
    init();
}

void PitchMechanism::parameter(double p1, double p2, double p3)
{
    p1_ = p1;
    p2_ = p2;
    p3_ = p3;
    init();
}

KPair<double, double> PitchMechanism::toAngle(double d, bool &success) const
{
    KPointF p = farest_.translatedX(-d);
    double dis = p.originDistance();
    double max_dis = p1_ + p3_;
    double min_dis = p3_ - p1_;
//    qDebug() << dis << max_dis << min_dis;
    if (dis > max_dis + EPS6 || dis < min_dis - EPS6) {
        success = false;
        return KPair<double, double>(0, 0);
    }

    KLineSegment2D line(p);
    double rad = line.radian();
    double r3 = cosineTheorem_Radian3(p1_, dis, p3_);
    double rad1 = rad - r3;
    double rad2 = rad + r3;

    double angle1 = kRadiansToDegrees(rad1);
    double angle2 = kRadiansToDegrees(rad2);
    angle1 -= farest_angle_;
    angle2 -= farest_angle_;

    success = true;
    return KPair<double, double>(angle1, angle2);
}

void PitchMechanism::init()
{
    double x = pythagoreanTheorem_Right(p2_, p1_ + p3_);
    farest_.setXY(x, p2_);
    KLineSegment2D line(farest_);
    farest_angle_ = line.angle();
}
