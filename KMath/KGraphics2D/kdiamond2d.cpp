#include "kdiamond2d.h"

KDiamond2D::KDiamond2D(double a, double b, int mode)
{
    if (mode == 0) {
        a_ = a;
        b_ = b;
    } else {
        double rad = kDegreesToRadians(b / 2);
        a_ = a * kCos(rad);
        b_ = a * kSin(rad);
    }
}
