#include "kmath.h"

#include <math.h>

#define F1_3 0.16666666666666666667
#define F1_4 0.04166666666666666667
#define F1_5 0.0083333333333333333333
#define F1_6 0.0013888888888888888889
#define F1_7 0.0001984126984126984127
#define F1_8 0.0000248015873015873015873
#define F1_9 0.000002755731922398589065
#define F1_10 0.00000027557319223985890653
#define F1_11 0.000000025052108385441718775
#define F1_12 0.0000000020876756987868098979
#define F1_13 0.00000000016059043836821614599
#define F1_15 0.00000000000076471637318198164759
#define F1_17 0.0000000000000028114572543455207632
#define K_3PI_2 4.7123889803846898577
#define _1_K_2PI 0.15915494309189533577
#define _1_3 0.33333333333333333333
#define _1_6 0.16666666666666666667
#define _1_7 0.14285714285714285714
#define _1_9 0.11111111111111111111
#define _1_11 0.090909090909090909091
#define _1_13 0.076923076923076923077
#define _1_15 0.066666666666666666667
#define _1_17 0.058823529411764705882

double kSqrt(double n)
{
    return sqrt(n);
    if (n <= 0)
        return 0;
    double x = (1 + n) / 2;
    double last;
    do {
        last = x;
        x = (x + n / x) / 2;
    } while (last - x > EPS9);
    return x;
}

double kSin(double x)
{
    if (x < 0)
        x = K_PI - x;
    x -= static_cast<int>(x * _1_K_2PI) * K_2PI;
    if (x <= K_PI_2)
        ;
    else if (x < K_3PI_2)
        x = K_PI - x;
    else
        x -= K_2PI;

    double x2 = x * x;
    return x * (1 - (F1_3 - ((F1_5 - ((F1_7 - ((F1_9 - ((F1_11 - ((F1_13 -
           ((F1_15 - x2 * F1_17) * x2)) * x2)) * x2)) * x2)) * x2)) * x2)) * x2);
}

double kAsin(double n)
{
    return kAtan(n / kSqrt(1 - n * n));
}

double kAcos(double n)
{
    if (n <= -1)
        return K_PI;

    double radian = kAtan(kSqrt(1 - n * n) / n);
    return radian >= 0 ? radian : radian + K_PI;
}

double kAtan(double n)
{
    int times = 1;
    if (n < 0) {
        n = -n;
        times = -1;
    }

    double n_1;
    while (n >= 0.3) {
        times *= 2;
        n_1 = 1 / n;
        n = kSqrt(n_1 * n_1 + 1) - n_1;
    }

    double n2 = n * n;
    return n * (1 - n2 * (_1_3 - n2 * (0.2 - n2 * (_1_7 - n2 * (_1_9 - n2 *
           (_1_11 - n2 * (_1_13 - n2 * (_1_15 - n2 * _1_17)))))))) * times;
}

long double kFibonacci(unsigned int n)
{
    if (n < 2)
        return n;
    long double temp;
    long double f1 = 0;
    long double f2 = 1;
    for (unsigned int i = 2; i <= n; ++i) {
        temp = f2;
        f2 += f1;
        f1 = temp;
    }
    return f2;
}

long long kFactorial_ll(unsigned n)
{
    long long fact = 1;
    for (unsigned i = 2; i <= n; ++i)
        fact *= i;
    return fact;
}

long double kFactorial_ld(unsigned n)
{
    long double fact = 1;
    for (unsigned int i = 2; i <= n; ++i)
        fact *= i;
    return fact;
}

double kPow(double x, int y)
{
    if (y > 3) {
        if (y % 2 == 0)
            return kSquare(kPow(x, y >> 1));
        else
            return kSquare(kPow(x, y >> 1)) * x;
    }
    if (y == 3)
        return x * x * x;
    if (y == 2)
        return x * x;
    if (y == 1)
        return x;
    if (y == 0)
        return 1;
    return 1.0 / kPow(x, -y);
}

long double kPow(long double x, int y)
{
    if (y > 3) {
        if (y % 2 == 0)
            return kSquare(kPow(x, y >> 1));
        else
            return kSquare(kPow(x, y >> 1)) * x;
    }
    if (y == 3)
        return x * x * x;
    if (y == 2)
        return x * x;
    if (y == 1)
        return x;
    if (y == 0)
        return 1;
    return 1 / kPow(x, -y);
}

float kPow(float x, int y)
{
    if (y > 3) {
        if (y % 2 == 0)
            return kSquare(kPow(x, y >> 1));
        else
            return kSquare(kPow(x, y >> 1)) * x;
    }
    if (y == 3)
        return x * x * x;
    if (y == 2)
        return x * x;
    if (y == 1)
        return x;
    if (y == 0)
        return 1;
    return 1 / kPow(x, -y);
}

double kAtan2(double y, double x)
{
    if (x > 0)
        return kAtan(y / x);
    if (x < 0) {
        if (y >= 0)
            return kAtan(y / x) + K_PI;
        return kAtan(y / x) - K_PI;
    }
    if (y > 0)
        return K_PI_2;
    if (y < 0)
        return -K_PI_2;
    return 0;
}

double angleNormalized(double angle)
{
    if (angle < 0) {
        angle += int(angle / 360) * 360;
        return angle <= -180 ? angle + 360 : angle;
    }

    angle -= int(angle / 360) * 360;
    return angle > 180 ? angle - 360 : angle;
}

double radianNormalized(double radian)
{
    if (radian < 0) {
        radian += int(radian / K_2PI) * K_2PI;
        return radian <= -K_PI ? radian + K_2PI : radian;
    }

    radian -= int(radian / K_2PI) * K_2PI;
    return radian > K_PI ? radian - K_2PI : radian;
}

int GCD(int a, int b)
{
    if (a == 0 || b == 0)
        return 1;
    a = kAbs(a);
    b = kAbs(b);

    if (a < b)
        kSwap(a, b);
    int c;
    do {
        c = a % b;
        a = b;
        b = c;
    } while (c != 0);
    return a;
}

long long GCD(long long a, long long b)
{
    if (a == 0 || b == 0)
        return 1;
    a = kAbs(a);
    b = kAbs(b);

    if (a < b)
        kSwap(a, b);
    long long c;
    do {
        c = a % b;
        a = b;
        b = c;
    } while (c != 0);
    return a;
}

unsigned LCM(unsigned a, unsigned b)
{
    if (a == 0 || b == 0)
        return 0;
    unsigned a1 = a;
    unsigned b1 = b;

    if (a < b)
        kSwap(a, b);
    unsigned c;
    do {
        c = a % b;
        a = b;
        b = c;
    } while (c != 0);
    return a1 / a * b1;
}

unsigned long long LCM(unsigned long long a, unsigned long long b)
{
    if (a == 0 || b == 0)
        return 0;
    unsigned long long a1 = a;
    unsigned long long b1 = b;

    if (a < b)
        kSwap(a, b);
    unsigned long long c;
    do {
        c = a % b;
        a = b;
        b = c;
    } while (c != 0);
    return a1 / a * b1;
}

double kRound(double x)
{
    double floor = kFloor(x);
    if (x - floor >= 0.5)
        return floor + 1;
    return floor;
}

double kExp(double x)
{
    int i = int(x);
    double d = x - i;
    double result = 1;
    if (d >= 0.5) {
        result = 1.6487212707001281468486507878142;
        d -= 0.5;
    } else if (d <= -0.5) {
        result = 0.60653065971263342360379953499118;
        d += 0.5;
    }

    if (d >= 0.25) {
        result *= 1.2840254166877414840734205680624;
        d -= 0.25;
    } else if (d <= -0.25) {
        result *= 0.77880078307140486824517026697832;
        d += 0.25;
    }

    if (d >= 0.125) {
        result *= 1.1331484530668263168290072278118;
        d -= 0.125;
    } else if (d <= -0.125) {
        result *= 0.88249690258459540286489214322905;
        d += 0.125;
    }

    result *= 1+d*(1+d*(0.5+d*(F1_3+d*(F1_4+d*(F1_5+d*(F1_6+d*(F1_7+d*(F1_8+d*
    (F1_9+d*F1_10)))))))));
    return kPow(K_E, i) * result;
}

double kLog(double x)
{
    if (x <= 0)
        return K_DBL_MIN;
    bool sign;
    if (x < 1) {
        sign = true;
        x = 1.0 / x;
    } else {
        sign = false;
    }

    int n = 0;
    while (x >= 16) {
        x /= 16;
        ++n;
    }
    double result = n * 2.7725887222397812376689284858327;

    n = 0;
    while (x >= 2) {
        x /= 2;
        ++n;
    }
    result += n * 0.69314718055994530941723212145818;

    n = 0;
    while (x >= 1.1) {
        x /= 1.1;
        ++n;
    }
    result += n * 0.09531017980432486004395212328077;

    x -= 1;
    result += x*(1+x*(-0.5+x*(_1_3+x*(-0.25+x*(0.2+x*(-_1_6+x*(_1_7+x*
    (-0.125+x*(_1_9+x*(-0.1+x*_1_11))))))))));

    if (sign)
        result = -result;
    return result;
}

double cosineTheorem_Edge(double edge1, double edge2, double c)
{
    return kSqrt(kSquareSum(edge1, edge2) - kCos(c) * edge1 * edge2 * 2);
}

double cosineTheorem_Radian3(double edge1, double edge2, double edge3)
{
    return kAcos((edge1*edge1 + edge2*edge2 - edge3*edge3) / (edge1*edge2*2));
}
