#ifndef KINTEGRAL_H
#define KINTEGRAL_H

#include "King_global.h"

// 第一类:含三角函数
// cosx
double KING_EXPORT kIntegral1_1(double lower, double upper);
// sinx
double KING_EXPORT kIntegral1_2(double lower, double upper);
// (secx)^2
double KING_EXPORT kIntegral1_3(double lower, double upper);
// (cscx)^2
double KING_EXPORT kIntegral1_4(double lower, double upper);
// secxtanx
double KING_EXPORT kIntegral1_5(double lower, double upper);
// cscxcotx
double KING_EXPORT kIntegral1_6(double lower, double upper);
// tanx
double KING_EXPORT kIntegral1_7(double lower, double upper);
// cotx
double KING_EXPORT kIntegral1_8(double lower, double upper);
// secx
double KING_EXPORT kIntegral1_9(double lower, double upper);
// cscx
double KING_EXPORT kIntegral1_10(double lower, double upper);
// (sinx)^2
double KING_EXPORT kIntegral1_11(double lower, double upper);
// (cosx)^2
double KING_EXPORT kIntegral1_12(double lower, double upper);
// (tanx)^2
double KING_EXPORT kIntegral1_13(double lower, double upper);
// (cotx)^2
double KING_EXPORT kIntegral1_14(double lower, double upper);
// (secx)^3
double KING_EXPORT kIntegral1_15(double lower, double upper);


// 第二类：含反三角函数
// arcsinx
double KING_EXPORT kIntegral2_1(double lower, double upper);
// arccosx
double KING_EXPORT kIntegral2_2(double lower, double upper);
// arctanx
double KING_EXPORT kIntegral2_3(double lower, double upper);

// 第三类：含指数函数
// e^x
double KING_EXPORT kIntegral3_1(double lower, double upper);
// a^x
double KING_EXPORT kIntegral3_2(double a, double lower, double upper);

// 第四类：含a+bx
// 1/(a+bx)
double KING_EXPORT kIntegral4_1(double a, double b, double lower, double upper);
// x/(a+bx)
double KING_EXPORT kIntegral4_2(double a, double b, double lower, double upper);
// (x^2)/(a+bx)
double KING_EXPORT kIntegral4_3(double a, double b, double lower, double upper);
// 1/(x(a+bx))
double KING_EXPORT kIntegral4_4(double a, double b, double lower, double upper);
// 1/((x^2)(a+bx))
double KING_EXPORT kIntegral4_5(double a, double b, double lower, double upper);

// 第五类：含sqrt(a+bx)
// sqrt(a+bx)
double KING_EXPORT kIntegral5_1(double a, double b, double lower, double upper);

// 第六类：含x^2±a^2
// 1/(x^2+a^2)
double KING_EXPORT kIntegral6_1(double a, double lower, double upper);
// 1/(x^2-a^2)
double KING_EXPORT kIntegral6_2(double a, double lower, double upper);
// 1/(a^2-x^2)
double KING_EXPORT kIntegral6_3(double a, double lower, double upper);

// 第七类：含ax^2+b（a>0）
// 1/(ax^2+b)
double KING_EXPORT kIntegral7_1(double a, double b, double lower, double upper);

// 第八类：含sqrt(a^2+x^2)（a>0）,或sqrt(x^2 + a), (a > 0)
// sqrt(a^2+x^2)
double KING_EXPORT kIntegral8_1(double a, double lower, double upper);
// x^2 * sqrt(a^2+x^2)
double KING_EXPORT kIntegral8_2(double a, double lower, double upper);
// sqrt(a^2+x^2) / x
double KING_EXPORT kIntegral8_3(double a, double lower, double upper);
// sqrt(a^2+x^2) / x^2
double KING_EXPORT kIntegral8_4(double a, double lower, double upper);
// 1 / sqrt(a^2+x^2)
double KING_EXPORT kIntegral8_5(double a, double lower, double upper);
// x^2 / sqrt(a^2+x^2)
double KING_EXPORT kIntegral8_6(double a, double lower, double upper);
// 1 / (x*sqrt(a^2+x^2))
double KING_EXPORT kIntegral8_7(double a, double lower, double upper);
// 1 / (x^2 * sqrt(a^2+x^2))
double KING_EXPORT kIntegral8_8(double a, double lower, double upper);
// sqrt(x^2 + a)
double KING_EXPORT kIntegral8_9(double a, double lower, double upper);

// 第九类：含sqrt(a^2-x^2)（a>0）
// 1/sqrt(a^2-x^2)
double KING_EXPORT kIntegral9_1(double a, double lower, double upper);
// sqrt(a^2-x^2)
double KING_EXPORT kIntegral9_2(double a, double lower, double upper);
// (x^2)*sqrt(a^2-x^2)
double KING_EXPORT kIntegral9_3(double a, double lower, double upper);
// sqrt(a^2-x^2) / x
double KING_EXPORT kIntegral9_4(double a, double lower, double upper);
// sqrt(a^2-x^2) / x^2
double KING_EXPORT kIntegral9_5(double a, double lower, double upper);
// 1/(x*sqrt(a^2-x^2))
double KING_EXPORT kIntegral9_6(double a, double lower, double upper);
// (x^2)/sqrt(a^2-x^2)
double KING_EXPORT kIntegral9_7(double a, double lower, double upper);
// 1 / ((x^2)*sqrt(a^2-x^2))
double KING_EXPORT kIntegral9_8(double a, double lower, double upper);

#endif // KINTEGRAL_H
