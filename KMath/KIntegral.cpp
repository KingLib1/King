#include "KIntegral.h"

#include "kmath.h"

double kIntegral1_1(double lower, double upper)
{
    return kSin(upper) - kSin(lower);
}

double kIntegral1_2(double lower, double upper)
{
    return kCos(lower) - kCos(upper);
}

double kIntegral1_3(double lower, double upper)
{
    return kTan(upper) - kTan(lower);
}

double kIntegral1_4(double lower, double upper)
{
    return kCot(lower) - kCot(upper);
}

double kIntegral1_5(double lower, double upper)
{
    return kSec(upper) - kSec(lower);
}

double kIntegral1_6(double lower, double upper)
{
    return kCsc(lower) - kCsc(upper);
}

double kIntegral1_7(double lower, double upper)
{
    return kLog(kFabs(kCos(lower) / kCos(upper)));
}

double kIntegral1_8(double lower, double upper)
{
    return kLog(kFabs(kSin(upper) / kSin(lower)));
}

double kIntegral1_9(double lower, double upper)
{
    return kLog(kFabs((kSec(upper) + kTan(upper)) / (kSec(lower) + kTan(lower))));
}

double kIntegral1_10(double lower, double upper)
{
    return kLog(kFabs((kCsc(lower) + kCot(lower)) / (kCsc(upper) + kCot(upper))));
}

double kIntegral1_11(double lower, double upper)
{
    double lower2 = lower * 2;
    double upper2 = upper * 2;
    return (upper2 - lower2 + kSin(lower2) - kSin(upper2)) / 4;
}

double kIntegral1_12(double lower, double upper)
{
    double lower2 = lower * 2;
    double upper2 = upper * 2;
    return (upper2 - lower2 + kSin(upper2) - kSin(lower2)) / 4;
}

double kIntegral1_13(double lower, double upper)
{
    return kTan(upper) - kTan(lower) + lower - upper;
}

double kIntegral1_14(double lower, double upper)
{
    return kCot(lower) + lower - kCot(upper) - upper;
}

double kIntegral1_15(double lower, double upper)
{
    double secl = kSec(lower);
    double tanl = kTan(lower);
    double secu = kSec(upper);
    double tanu = kTan(upper);
    return (secu*tanu-secl*tanl+kLog(kFabs((secu+tanu)/(secl+tanl))))/2;
}

double kIntegral2_1(double lower, double upper)
{
    // xarcsinx + sqrt(1-x^2)
    return upper * kAsin(upper) + kSqrt(1 - upper * upper) -
            lower * kAsin(lower) - kSqrt(1 - lower * lower);
}

double kIntegral2_2(double lower, double upper)
{
    // xarccosx - sqrt(1-x^2)
    return upper * kAcos(upper) - kSqrt(1 - upper * upper) -
            lower * kAcos(lower) + kSqrt(1 - lower * lower);
}

double kIntegral2_3(double lower, double upper)
{
    // xarctanx - (ln(1+x^2)) / 2
    return upper * kAtan(upper) - lower * kAtan(lower) +
            kLog((1 + lower * lower)/(1 + upper * upper)) / 2;
}

double kIntegral3_1(double lower, double upper)
{
    return kExp(upper) - kExp(lower);
}

double kIntegral3_2(double a, double lower, double upper)
{
    // a^x / lna
    return (kPow(a, upper) - kPow(a, lower)) / kLog(a);
}

double kIntegral4_1(double a, double b, double lower, double upper)
{
    return kLog(kFabs((a + b * upper) / (a + b * lower))) / b;
}

double kIntegral4_2(double a, double b, double lower, double upper)
{
    return (b*(upper-lower)+a*kLog(kFabs((a + b*lower)/(a + b*upper)))) / (b*b);
}

double kIntegral4_3(double a, double b, double lower, double upper)
{
    double b2 = b * b;
    double b3 = b2 * b;
    double r1 = kSquareDifference(upper, lower) / (b * 2);
    double r2 = a * (lower - upper) / b2;
    double r3 = a * a * kLog(kFabs((a + b * upper) / (a + b * lower))) / b3;
    return r1 + r2 + r3;
}

double kIntegral4_4(double a, double b, double lower, double upper)
{
    return kLog(kFabs((a + b*lower)*upper / ((a + b*upper)*lower))) / a;
}

double kIntegral4_5(double a, double b, double lower, double upper)
{
    return b * kLog(kFabs((a + b*upper)*lower/((a + b*lower)*upper))) / (a*a) +
            (upper - lower) / (a * lower * upper);
}

double kIntegral5_1(double a, double b, double lower, double upper)
{
    if (isZero(b))
        return kSqrt(a) * (upper - lower);

    lower = a + b * lower;
    upper = a + b * upper;
    return (kPow(upper, 1.5) - kPow(lower, 1.5)) * 2 / (3 * b);
}

double kIntegral6_1(double a, double lower, double upper)
{
    return (kAtan(upper / a) - kAtan(lower / a)) / a;
}

double kIntegral6_2(double a, double lower, double upper)
{
    return kLog(kFabs((upper-a)*(lower+a)/((upper+a)*(lower-a)))) / (2*a);
}

double kIntegral6_3(double a, double lower, double upper)
{
    return kLog(kFabs((a+upper)*(a-lower)/((a-upper)*(a+lower)))) / (2*a);
}

double kIntegral7_1(double a, double b, double lower, double upper)
{
    double sa_b = kSqrt(a / b);
    return (kAtan(sa_b*upper) - kAtan(sa_b*lower)) / (sa_b*b);
}

double kIntegral8_1(double a, double lower, double upper)
{
    double a2 = a * a;
    double sa2l2 = kSqrt(a2 + lower * lower);
    double sa2u2 = kSqrt(a2 + upper * upper);
    return (upper*sa2u2-lower*sa2l2+a2*kLog((upper+sa2u2)/(lower+sa2l2)))/2;
}

double kIntegral8_2(double a, double lower, double upper)
{
    double a2 = a * a;
    double l2 = lower * lower;
    double u2 = upper * upper;
    double a2l2 = a2 + l2;
    double a2u2 = a2 + u2;
    double sa2l2 = kSqrt(a2l2);
    double sa2u2 = kSqrt(a2u2);
    return (upper*sa2u2*(a2u2+u2) - lower*sa2l2*(a2l2+l2) +
            a2*a2*kLog((lower+sa2l2)/(upper+sa2u2))) / 8;
}

double kIntegral8_3(double a, double lower, double upper)
{
    double a2 = a * a;
    double sa2l2 = kSqrt(a2 + lower * lower);
    double sa2u2 = kSqrt(a2 + upper * upper);
    return sa2u2-sa2l2+kLog(kFabs((a+sa2l2)*upper/((a+sa2u2)*lower)))/a;
}

double kIntegral8_4(double a, double lower, double upper)
{
    double a2 = a * a;
    double sa2l2 = kSqrt(a2 + lower * lower);
    double sa2u2 = kSqrt(a2 + upper * upper);
    return kLog((upper+sa2u2)/(lower+sa2l2)) + sa2l2/lower - sa2u2/upper;
}

double kIntegral8_5(double a, double lower, double upper)
{
    double a2 = a * a;
    return kLog((upper+kSqrt(a2+upper*upper))/(lower+kSqrt(a2+lower*lower)));
}

double KING_EXPORT kIntegral8_6(double a, double lower, double upper)
{
    double a2 = a * a;
    double sa2l2 = kSqrt(a2 + lower * lower);
    double sa2u2 = kSqrt(a2 + upper * upper);
    return (upper*sa2u2-lower*sa2l2+a2*(kLog((lower+sa2l2)/(upper+sa2u2))))/2;
}

double KING_EXPORT kIntegral8_7(double a, double lower, double upper)
{
    double a2 = a * a;
    return kLog(kFabs(upper*(kSqrt(a2+lower*lower)+a)/(lower*(kSqrt(a2+upper*upper)+a))))/a;
}

double KING_EXPORT kIntegral8_8(double a, double lower, double upper)
{
    double a2 = a * a;
    return (kSqrt(a2+lower*lower)/lower-kSqrt(a2+upper*upper)/upper)/a2;
}

double kIntegral8_9(double a, double lower, double upper)
{
    double sa2l2 = kSqrt(a + lower * lower);
    double sa2u2 = kSqrt(a + upper * upper);
    return (upper*sa2u2-lower*sa2l2+a*kLog((upper+sa2u2)/(lower+sa2l2)))/2;
}

double kIntegral9_1(double a, double lower, double upper)
{
    return kAsin(upper / a) - kAsin(lower / a);
}

double kIntegral9_2(double a, double lower, double upper)
{
    double a2 = a * a;
    return (upper*kSqrt(a2 - upper*upper) - lower*kSqrt(a2 - lower*lower) +
            a2*(kAsin(upper/a) - kAsin(lower/a))) / 2;
}

double kIntegral9_3(double a, double lower, double upper)
{
    double a2 = a * a;
    double a4 = a2 * a2;
    double l2 = lower * lower;
    double u2 = upper * upper;
    return (a4*(kAsin(upper/a)-kAsin(lower/a)) + lower*kSqrt(a2-l2)*(a2-2*l2) -
            upper*kSqrt(a2-u2)*(a2-2*u2)) / 8;
}

double kIntegral9_4(double a, double lower, double upper)
{
    double a2 = a * a;
    double l2 = lower * lower;
    double u2 = upper * upper;
    double sa2_l2 = kSqrt(a2-l2);
    double sa2_u2 = kSqrt(a2-u2);
    return sa2_u2-sa2_l2 + a*kLog(kFabs((a+sa2_l2)*upper/(lower*(a+sa2_u2))));
}

double kIntegral9_5(double a, double lower, double upper)
{
    double a2 = a * a;
    return kSqrt(a2 - lower*lower)/lower + kAsin(lower/a) -
            kSqrt(a2 - upper*upper)/upper - kAsin(upper/a);
}

double kIntegral9_6(double a, double lower, double upper)
{
    double a2 = a * a;
    return kLog(kFabs(upper*(a+kSqrt(a2-lower*lower))/(lower*(a+kSqrt(a2-upper*upper)))))/a;
}

double kIntegral9_7(double a, double lower, double upper)
{
    double a2 = a * a;
    return (a2*(kAsin(upper/a)-kAsin(lower/a))+lower*kSqrt(a2-lower*lower)-
            upper*kSqrt(a2-upper*upper)) / 2;
}

double kIntegral9_8(double a, double lower, double upper)
{
    double a2 = a * a;
    return (kSqrt(a2-lower*lower)/lower - kSqrt(a2-upper*upper)/upper) / a2;
}
