#ifndef KMATH_H
#define KMATH_H

#include "King_global.h"

#define K_DBL_MAX 1.79769e+308
#define K_DBL_MIN 2.22507e-308
#define K_FLT_MAX 3.40282e+38
#define K_FLT_MIN 1.17549e-38
#define K_INT_MAX 2147483647
#define K_INT_MIN -2147483648
#define K_LONG_LONG_MAX 9223372036854775807
#define K_LONG_LONG_MIN -9223372036854775808

#define K_PI 3.14159265358979323846
#define K_PI_2 1.57079632679489661923
#define K_PI_4 0.78539816339744830962
#define K_2PI 6.283185307179586476925
#define K_4PI 12.56637061435917295385
#define K_1_2PI 0.15915494309189533576888
#define K_E 2.71828182845904523536028747

#define EPS1 1e-1
#define EPS2 1e-2
#define EPS3 1e-3
#define EPS6 1e-6
#define EPS9 1e-9

template<typename T>
KING_EXPORT inline void kSwap(T &a, T &b)
{
    T t = a;
    a = b;
    b = t;
}

KING_EXPORT inline int kAbs(int n){return n < 0 ? -n : n;}
KING_EXPORT inline long long kAbs(long long n) {return n < 0 ? -n : n;}
KING_EXPORT inline double kFabs(double n){return n < 0 ? -n : n;}
KING_EXPORT inline float kFabs(float n){return n < 0 ? -n : n;}
KING_EXPORT double kRound(double x);
KING_EXPORT double kSqrt(double n);
KING_EXPORT long double kPow(long double x, int y);
KING_EXPORT double kPow(double x, int y);
KING_EXPORT float kPow(float x, int y);
KING_EXPORT double kExp(double x);
KING_EXPORT double kLog(double x);
KING_EXPORT inline double kPow(double x, double y)
{
    return kExp(y * kLog(x));
}
KING_EXPORT inline double kFloor(double x)
{
    return static_cast<long long>(x);
}

KING_EXPORT inline double kCeil(double x)
{
    double ceil = static_cast<long long>(x);
    return ceil >= x ? ceil : ceil + 1;
}

KING_EXPORT inline long double kSquare(long double n)
{
    return n * n;
}

KING_EXPORT inline double kSquare(double n)
{
    return n * n;
}

KING_EXPORT inline float kSquare(float n)
{
    return n * n;
}

KING_EXPORT inline int kSquare(int n)
{
    return n * n;
}

KING_EXPORT inline double kSquareSum(double a, double b)
{
    return a * a + b * b;
}

KING_EXPORT inline double kSquareSum(double a, double b, double c)
{
    return a * a + b * b + c * c;
}

KING_EXPORT inline double kSquareDifference(double a, double b)
{
    return (a + b) * (a - b);
}

KING_EXPORT inline double kSumSquare(double a, double b)
{
    return kSquare(a + b);
}

KING_EXPORT inline double kSumSquare(double a, double b, double c)
{
    return kSquare(a + b + c);
}

KING_EXPORT inline double kDifferenceSquare(double a, double b)
{
    return kSquare(a - b);
}

KING_EXPORT inline long double kCube(long double n)
{
    return n * n * n;
}

KING_EXPORT inline double kCube(double n)
{
    return n * n * n;
}

KING_EXPORT inline float kCube(float n)
{
    return n * n * n;
}

KING_EXPORT inline int kCube(int n)
{
    return n * n * n;
}

KING_EXPORT inline double kLength(double a, double b)
{
    return kSqrt(kSquareSum(a, b));
}

KING_EXPORT inline double kLength(double a, double b, double c)
{
    return kSqrt(kSquareSum(a, b, c));
}

KING_EXPORT inline float kSqrt(float n)
{
    return float(kSqrt(double(n)));
}

KING_EXPORT inline double kRadiansToDegrees(double radians)
{
    return radians * 57.2957795130823208768;
}

KING_EXPORT inline float kRadiansToDegrees(float radians)
{
    return float(double(radians) * 57.2957795130823208768);
}

KING_EXPORT inline double kDegreesToRadians(double degrees)
{
    return degrees * 0.0174532925199432957692;
}

KING_EXPORT inline float kDegreesToRadians(float degrees)
{
    return float(double(degrees) * 0.0174532925199432957692);
}

KING_EXPORT double kSin(double x);

KING_EXPORT inline double kSin2(double degree)
{
    return kSin(kDegreesToRadians(degree));
}

KING_EXPORT inline float kSin(float x)
{
    return float(kSin(double(x)));
}

KING_EXPORT inline double kCos(double x)
{
    return kSin(K_PI_2 - x);
}

KING_EXPORT inline double kCos2(double degree)
{
    return kSin(K_PI_2 - kDegreesToRadians(degree));
}

KING_EXPORT inline float kCos(float x)
{
    return float(kCos(double(x)));
}

KING_EXPORT inline double kTan(double radian)
{
    return kSin(radian) / kCos(radian);
}

KING_EXPORT inline double kTan2(double degree)
{
    return kTan(kDegreesToRadians(degree));
}

KING_EXPORT double kAsin(double n);
KING_EXPORT double kAcos(double n);
KING_EXPORT double kAtan(double n);
KING_EXPORT double kAtan2(double y, double x);

KING_EXPORT inline double kCot(double radian)
{
    return kCos(radian) / kSin(radian);
}

KING_EXPORT inline double kCsc(double radian)
{
    return 1.0 / kSin(radian);
}

KING_EXPORT inline double kSec(double radian)
{
    return 1.0 / kCos(radian);
}

/**
 * @brief 把角度规范到(-180, 180]
 */
KING_EXPORT double angleNormalized(double angle);
/**
 * @brief 把弧度规范到(-pi, pi]
 */
KING_EXPORT double radianNormalized(double radian);

/**
 * @brief 勾股定理计算斜边长度
 * @param right1 直角边1长度
 * @param right2 直角边2长度
 */
KING_EXPORT inline double pythagoreanTheorem_Bevel(double right1, double right2)
{
    return kSqrt(kSquareSum(right1, right2));
}

/**
 * @brief 勾股定理计算直角边长度
 * @param right 直角边长度
 * @param bevel 斜边长度
 */
KING_EXPORT inline double pythagoreanTheorem_Right(double right, double bevel)
{
    return kSqrt(kSquareDifference(bevel, right));
}

/**
 * @brief 余弦定理计算第三边长度
 * @param edge1 第一边长
 * @param edge2 第二边长
 * @param c 两边夹角弧度
 * @return 第三边长度
 */
KING_EXPORT double cosineTheorem_Edge(double edge1, double edge2, double c);

/**
 * @brief 余弦定理计算第三边对角弧度
 * @param edge1 第一边长
 * @param edge2 第二边长
 * @param edge3 第三边长
 * @return 第三边对角弧度
 */
KING_EXPORT double cosineTheorem_Radian3(double edge1, double edge2, double edge3);

// 等差数列求和(首项，递增量，项数)
KING_EXPORT inline double kArithmeticSequenceSum(double a1, double d, int n)
{
    return n * (a1 + 0.5 * (n - 1) * d);
}

KING_EXPORT inline float kArithmeticSequenceSum(float a1, float d, int n)
{
    return n * (a1 + 0.5f * (n - 1) * d);
}

KING_EXPORT inline int kArithmeticSequenceSum(int a1, int d, int n)
{
    return (a1 + a1 + n * d - d) * n / 2;
}

// 等比数列求和(首项，公比，项数)
KING_EXPORT inline long double proportionalSequenceSum(long double a1, long double q, int n)
{
    return a1 * (1 - kPow(q, n)) / (1 - q);
}

KING_EXPORT inline double proportionalSequenceSum(double a1, double q, int n)
{
    return a1 * (1 - kPow(q, n)) / (1 - q);
}

KING_EXPORT inline float proportionalSequenceSum(float a1, float q, int n)
{
    return a1 * (1 - kPow(q, n)) / (1 - q);
}

template<typename T>
KING_EXPORT inline T kMax(const T &a, const T &b){return a > b ? a : b;}

template<typename T>
KING_EXPORT inline T kMin(const T &a, const T &b){return a < b ? a : b;}

template<typename T>
KING_EXPORT inline T kMax(const T &a, const T &b, const T &c)
{
    return kMax(kMax(a, b), c);
}

template<typename T>
KING_EXPORT inline T kMin(const T &a, const T &b, const T &c)
{
    return kMin(kMin(a, b), c);
}

template <typename T>
KING_EXPORT inline void kMinAndMax(const T &a, const T &b, T &min, T &max)
{
    if (a < b) {
        min = a;
        max = b;
    } else {
        min = b;
        max = a;
    }
}

template <typename T>
KING_EXPORT inline void kMinAndMax(const T &a, const T &b, const T &c, T &min, T &max)
{
    if (a < b) {
        if (a < c) {
            min = a;
            max = b < c ? c : b;
        } else {
            min = c;
            max = b;
        }
    } else {
        if (b < c) {
            min = b;
            max = a < c ? c : a;
        } else {
            min = c;
            max = a;
        }
    }
}

// 斐波那契数列第n项
KING_EXPORT long double kFibonacci(unsigned int n);
// n的阶乘
KING_EXPORT long double kFactorial_ld(unsigned int n);

KING_EXPORT inline bool isZero(double n, double fuzziness = EPS6)
{
    return kFabs(n) <= fuzziness;
}

KING_EXPORT inline bool isEqual(double a, double b, double fuzziness = EPS6)
{
    return kFabs(a - b) <= fuzziness;
}

/**
 * @brief 最大公约数
 */
KING_EXPORT int GCD(int a, int b);
/**
 * @brief 最大公约数
 */
KING_EXPORT long long GCD(long long a, long long b);

/**
 * @brief 最小公倍数
 */
KING_EXPORT unsigned LCM(unsigned a, unsigned b);
/**
 * @brief 最小公倍数
 */
KING_EXPORT unsigned long long LCM(unsigned long long a, unsigned long long b);

#endif // KMATH_H
