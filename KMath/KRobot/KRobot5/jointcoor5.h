#ifndef JOINTCOOR5_H
#define JOINTCOOR5_H

#include "King_global.h"

class KING_EXPORT JointCoor5
{
public:
    JointCoor5();
    JointCoor5(double a, double b, double y, double z);

    double a;
    double b;
    double y;
    double z;
};

class KING_EXPORT RectCoor5
{
public:
    RectCoor5();
    RectCoor5(double x, double y, double z, double c);

    double x;
    double y;
    double z;
    double c;
};

#endif // JOINTCOOR5_H
