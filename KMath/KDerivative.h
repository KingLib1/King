#ifndef KDERIVATIVE_H
#define KDERIVATIVE_H

#include "kmath.h"

// 求导

// a^x
inline double KING_EXPORT kDerivative1(double a, double x)
{
    return kPow(a, x) * kLog(a);
}

// e^x
inline double KING_EXPORT kDerivative2(double x)
{
    return kExp(x);
}

// x^n
inline double KING_EXPORT kDerivative3(double x, double n)
{
    return n * kPow(x, n - 1);
}

// loga(x)
inline double KING_EXPORT kDerivative4(double a, double x)
{
    return 1.0 / (x * kLog(a));
}

// lnx
inline double KING_EXPORT kDerivative5(double x)
{
    return 1.0 / x;
}

// sinx
inline double KING_EXPORT kDerivative6(double x)
{
    return kCos(x);
}

// cosx
inline double KING_EXPORT kDerivative7(double x)
{
    return -kSin(x);
}

// tanx
inline double KING_EXPORT kDerivative8(double x)
{
    return kSquare(kSec(x));
}

// cotx
inline double KING_EXPORT kDerivative9(double x)
{
    return -kSquare(kCsc(x));
}

// secx
inline double KING_EXPORT kDerivative10(double x)
{
    return kSec(x) * kTan(x);
}

// cscx
inline double KING_EXPORT kDerivative11(double x)
{
    return -kCsc(x) * kCot(x);
}

// arcsinx
inline double KING_EXPORT kDerivative12(double x)
{
    return 1.0 / kSqrt(1.0 - x * x);
}

// arccosx
inline double KING_EXPORT kDerivative13(double x)
{
    return -1.0 / kSqrt(1.0 - x * x);
}

// arctanx
inline double KING_EXPORT kDerivative14(double x)
{
    return 1.0 / (1.0 + x * x);
}

// arccotx
inline double KING_EXPORT kDerivative15(double x)
{
    return -1.0 / (1.0 + x * x);
}

#endif // KDERIVATIVE_H
