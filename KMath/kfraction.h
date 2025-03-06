#ifndef KFRACTION_H
#define KFRACTION_H

#include "kmath.h"

class KING_EXPORT KFraction
{
public:
    KFraction();
    KFraction(long long num, long long den = 1);
    KFraction(const KFraction &other);
    ~KFraction();

    inline void setNumerator(long long num);
    inline void setDenominator(long long den);
    inline void signNormalize(); // 分母为正
    inline void normalize(); // 分母为正,并约分
    inline void makeReciprocal(); // 使变为倒数
    inline void makeOpposite(); // 使变为相反数
    inline void makeAbsolute(); // 使变为绝对值

    inline long long numerator() const;
    inline long long denominator() const;
    inline bool isValid() const;
    KFraction normalized() const; // 取约分式
    KFraction reciprocal() const; // 取倒数

    /**
     * @brief 通分
     */
    static void reductToCommonDenominator(KFraction &f1, KFraction &f2);

    KFraction &operator+=(const KFraction &other);
    KFraction &operator+=(long long n);
    inline KFraction &operator-=(const KFraction &other);
    inline KFraction &operator-=(long long n);
    KFraction &operator*=(const KFraction &other);
    KFraction &operator*=(long long n);
    inline KFraction &operator/=(const KFraction &other);
    KFraction &operator/=(long long n);
    inline KFraction &operator=(const KFraction &other);

    inline KFraction operator+(const KFraction &other) const;
    inline KFraction operator+(long long n) const;
    inline KFraction operator-(const KFraction &other) const;
    inline KFraction operator-(long long n) const;
    inline KFraction operator*(const KFraction &other) const;
    inline KFraction operator*(long long n) const;
    inline KFraction operator/(const KFraction &other) const;
    inline KFraction operator/(long long n) const;
    bool operator==(const KFraction &other) const;
    inline bool operator!=(const KFraction &other) const;
    inline bool operator>(const KFraction &other) const;
    inline bool operator>(long long n) const;
    inline bool operator<(const KFraction &other) const;
    inline bool operator<(long long n) const;
    bool operator>=(const KFraction &other) const;
    inline bool operator>=(long long n) const;
    bool operator<=(const KFraction &other) const;
    inline bool operator<=(long long n) const;

    friend KFraction operator-(const KFraction &f);

private:
    long long num_; // 分子
    long long den_; // 分母
};

inline void KFraction::setNumerator(long long num)
{
    num_ = num;
}

inline void KFraction::setDenominator(long long den)
{
    den_ = den;
}

inline void KFraction::signNormalize()
{
    if (den_ < 0) {
        den_ = -den_;
        num_ = -num_;
    }
}

inline long long KFraction::numerator() const
{
    return num_;
}

inline long long KFraction::denominator() const
{
    return den_;
}

inline bool KFraction::isValid() const
{
    return den_ != 0;
}

inline KFraction KFraction::reciprocal() const
{
    return KFraction(den_, num_);
}

inline KFraction &KFraction::operator-=(const KFraction &other)
{
    return *this += -other;
}

inline KFraction &KFraction::operator-=(long long n)
{
    return *this += -n;
}

inline KFraction &KFraction::operator/=(const KFraction &other)
{
    return *this *= other.reciprocal();
}

inline void KFraction::normalize()
{
    signNormalize();
    long long gcd = GCD(den_, num_);
    den_ /= gcd;
    num_ /= gcd;
}

inline void KFraction::makeReciprocal()
{
    kSwap(den_, num_);
}

inline void KFraction::makeOpposite()
{
    num_ = -num_;
}

inline void KFraction::makeAbsolute()
{
    num_ = kAbs(num_);
    den_ = kAbs(den_);
}

inline KFraction &KFraction::operator=(const KFraction &other)
{
    num_ = other.num_;
    den_ = other.den_;
    return *this;
}

inline KFraction KFraction::operator+(const KFraction &other) const
{
    KFraction f(*this);
    f += other;
    return f;
}

inline KFraction KFraction::operator+(long long n) const
{
    KFraction f(*this);
    f += n;
    return f;
}

inline KFraction KFraction::operator-(const KFraction &other) const
{
    KFraction f(*this);
    f -= other;
    return f;
}

inline KFraction KFraction::operator-(long long n) const
{
    KFraction f(*this);
    f -= n;
    return f;
}

inline KFraction KFraction::operator*(const KFraction &other) const
{
    KFraction f(*this);
    f *= other;
    return f;
}

inline KFraction KFraction::operator*(long long n) const
{
    KFraction f(*this);
    f *= n;
    return f;
}

inline KFraction KFraction::operator/(const KFraction &other) const
{
    KFraction f(*this);
    f /= other;
    return f;
}

inline KFraction KFraction::operator/(long long n) const
{
    KFraction f(*this);
    f /= n;
    return f;
}

inline bool KFraction::operator!=(const KFraction &other) const
{
    return !(*this == other);
}

inline bool KFraction::operator>(const KFraction &other) const
{
    return !(*this <= other);
}

inline bool KFraction::operator>(long long n) const
{
    return !(*this <= n);
}

inline bool KFraction::operator<(const KFraction &other) const
{
    return !(*this >= other);
}

inline bool KFraction::operator<(long long n) const
{
    return !(*this >= n);
}

inline bool KFraction::operator>=(long long n) const
{
    KFraction f = normalized();
    return f.num_ >= n * f.den_;
}

inline bool KFraction::operator<=(long long n) const
{
    KFraction f = normalized();
    return f.num_ <= n * f.den_;
}

inline KFraction operator-(const KFraction &f)
{
    return KFraction(-f.numerator(), f.denominator());
}

#endif // KFRACTION_H
