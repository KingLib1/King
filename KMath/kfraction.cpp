#include "kfraction.h"

#include <QDebug>

KFraction::KFraction() : num_(0), den_(1)
{

}

KFraction::KFraction(long long num, long long den) : num_(num), den_(den)
{

}

KFraction::KFraction(const KFraction &other) : num_(other.num_), den_(other.den_)
{

}

KFraction::~KFraction()
{

}

KFraction KFraction::normalized() const
{
    KFraction f(*this);
    f.normalize();
    return f;
}

void KFraction::reductToCommonDenominator(KFraction &f1, KFraction &f2)
{
    f1.normalize();
    f2.normalize();
    long long gcd = GCD(f1.den_, f2.den_);
    long long k1 = f2.den_ / gcd;
    long long k2 = f1.den_ / gcd;
    f1.num_ *= k1;
    f1.den_ *= k1;
    f2.num_ *= k2;
    f2.den_ = f1.den_;
}

KFraction &KFraction::operator+=(const KFraction &other)
{
    normalize();
    KFraction o = other.normalized();
    long long gcd = GCD(den_, o.den_); // 最大公约数
    long long k1 = o.den_ / gcd;
    long long k2 = den_ / gcd;
    num_ = num_ * k1 + o.num_ * k2;
    den_ *= k1;
    gcd = GCD(den_, num_);
    num_ /= gcd;
    den_ /= gcd;
    return *this;
}

KFraction &KFraction::operator+=(long long n)
{
    normalize();
    num_ += n * den_;
    return *this;
}

KFraction &KFraction::operator*=(const KFraction &other)
{
    normalize();
    KFraction o = other.normalized();
    long long gcd = GCD(num_, o.den_);
    num_ /= gcd;
    o.den_ /= gcd;
    gcd = GCD(den_, o.num_);
    den_ /= gcd;
    o.num_ /= gcd;
    num_ *= o.num_;
    den_ *= o.den_;
    return *this;
}

KFraction &KFraction::operator*=(long long n)
{
    normalize();
    long long gcd = GCD(den_, n);
    den_ /= gcd;
    num_ *= n / gcd;
    return *this;
}

KFraction &KFraction::operator/=(long long n)
{
    normalize();
    long long gcd = GCD(num_, n);
    num_ /= gcd;
    den_ *= n / gcd;
    return *this;
}

bool KFraction::operator==(const KFraction &other) const
{
    KFraction f1 = normalized();
    KFraction f2 = other.normalized();
    return f1.num_ == f2.num_ && f1.den_ == f2.den_;
}

bool KFraction::operator>=(const KFraction &other) const
{
    KFraction f1(*this);
    KFraction f2(other);
    reductToCommonDenominator(f1, f2);
    return f1.num_ >= f2.num_;
}

bool KFraction::operator<=(const KFraction &other) const
{
    KFraction f1(*this);
    KFraction f2(other);
    reductToCommonDenominator(f1, f2);
    return f1.num_ <= f2.num_;
}
