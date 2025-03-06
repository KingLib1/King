#ifndef PITCHMECHANISM_H
#define PITCHMECHANISM_H

#include "kpointf.h"
#include "KPair.h"

class KING_EXPORT PitchMechanism
{
public:
    PitchMechanism();
    /**
     * @brief parameter
     * @param p1 凸轮半径
     * @param p2 偏心距
     * @param p3 杆长
     */
    void parameter(double p1, double p2, double p3);

    KPair<double, double> toAngle(double x, bool &success) const;

private:
    void init();

    double p1_ = 25;
    double p2_ = 74.5;
    double p3_ = 200;

    KPointF farest_;
    double farest_angle_;
};

#endif // PITCHMECHANISM_H
