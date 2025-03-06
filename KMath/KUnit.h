#ifndef KUNIT_H
#define KUNIT_H

#include "King_global.h"

template<int Unit_M, int K, int Unit_S>
struct KING_EXPORT KUnit
{
    enum { m = Unit_M, kg = K, s = Unit_S };
};

template<typename U1, typename U2>
using UnitPlus = KUnit<U1::m + U2::m, U1::kg + U2::kg, U1::s + U2::s>;

template<typename U1, typename U2>
using UnitMinus = KUnit<U1::m - U2::m, U1::kg - U2::kg, U1::s - U2::s>;

using Unit_M = KUnit<1, 0, 0>;
using Unit_Kg = KUnit<0, 1, 0>;
using Unit_S = KUnit<0, 0, 1>;
using Unit_MpS = KUnit<1, 0, -1>; // 速度
using Unit_MpS2 = KUnit<1, 0, -2>; // 加速度
using Unit_N = KUnit<1, 1, -2>; // 力

template<typename U>
class KQuantity
{
public:
    explicit KQuantity(long double value) : value_(value) {}

    inline void setValue(long double value) {value_ = value;}

    inline long double value() const {return value_;}

private:
    long double value_;
};

inline KQuantity<Unit_M> operator"" _m(long double value)
{
    return KQuantity<Unit_M>(value);
}

inline KQuantity<Unit_M> operator"" _km(long double value)
{
    return KQuantity<Unit_M>(value * 1000);
}

inline KQuantity<Unit_M> operator"" _mm(long double value)
{
    return KQuantity<Unit_M>(value / 1000);
}

inline KQuantity<Unit_Kg> operator"" _kg(long double value)
{
    return KQuantity<Unit_Kg>(value);
}

inline KQuantity<Unit_Kg> operator"" _g(long double value)
{
    return KQuantity<Unit_Kg>(value / 1000);
}

inline KQuantity<Unit_S> operator"" _s(long double value)
{
    return KQuantity<Unit_S>(value);
}

inline KQuantity<Unit_S> operator"" _ms(long double value)
{
    return KQuantity<Unit_S>(value / 1000);
}

inline KQuantity<Unit_S> operator"" _h(long double value)
{
    return KQuantity<Unit_S>(value * 3600);
}

inline KQuantity<Unit_S> operator"" _min(long double value)
{
    return KQuantity<Unit_S>(value * 60);
}

inline KQuantity<Unit_MpS> operator"" _mps(long double value)
{
    return KQuantity<Unit_MpS>(value);
}

inline KQuantity<Unit_MpS> operator"" _kmph(long double value)
{
    return KQuantity<Unit_MpS>(value / 3.6l);
}

inline KQuantity<Unit_MpS2> operator"" _mps2(long double value)
{
    return KQuantity<Unit_MpS2>(value);
}

inline KQuantity<Unit_N> operator"" _N(long double value)
{
    return KQuantity<Unit_N>(value);
}

template<typename U>
inline KQuantity<U> operator+(const KQuantity<U> &q1, const KQuantity<U> &q2)
{
    return KQuantity<U>(q1.value() + q2.value());
}

template<typename U>
inline KQuantity<U> operator-(const KQuantity<U> &q1, const KQuantity<U> &q2)
{
    return KQuantity<U>(q1.value() - q2.value());
}

template<typename U1, typename U2>
inline KQuantity<UnitPlus<U1, U2>> operator*(const KQuantity<U1> &q1,
                                             const KQuantity<U2> &q2)
{
    return KQuantity<UnitPlus<U1, U2>>(q1.value() * q2.value());
}

template<typename U1, typename U2>
inline KQuantity<UnitMinus<U1, U2>> operator/(const KQuantity<U1> &q1,
                                              const KQuantity<U2> &q2)
{
    return KQuantity<UnitMinus<U1, U2>>(q1.value() / q2.value());
}

template<typename U>
inline KQuantity<U> operator*(const KQuantity<U> &q, long double factor)
{
    return KQuantity<U>(q.value() * factor);
}

template<typename U>
inline KQuantity<U> operator*(long double factor, const KQuantity<U> &q)
{
    return KQuantity<U>(factor * q.value());
}

template<typename U>
inline KQuantity<U> operator/(const KQuantity<U> &q, long double divisor)
{
    return KQuantity<U>(q.value() / divisor);
}

#endif // KUNIT_H
