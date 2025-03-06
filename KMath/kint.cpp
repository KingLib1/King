#include "kint.h"

#include "kmath.h"
#include <QDebug>

bool operator>(const QVector<short> &v1, const QVector<short> &v2)
{
    if (v1.size() > v2.size())
        return true;
    if (v1.size() < v2.size())
        return false;
    for (int i = v1.size() - 1; i > -1; --i) {
        if (v1.at(i) > v2.at(i))
            return true;
        if (v1.at(i) < v2.at(i))
            return false;
    }
    return false;
}

bool operator<(const QVector<short> &v1, const QVector<short> &v2)
{
    if (v1.size() > v2.size())
        return false;
    if (v1.size() < v2.size())
        return true;
    for (int i = v1.size() - 1; i > -1; --i) {
        if (v1.at(i) > v2.at(i))
            return false;
        if (v1.at(i) < v2.at(i))
            return true;
    }
    return false;
}

inline bool operator>=(const QVector<short> &v1, const QVector<short> &v2)
{
    return !(v1 < v2);
}

inline bool operator<=(const QVector<short> &v1, const QVector<short> &v2)
{
    return !(v1 > v2);
}

void intAdd(QVector<short> &v1, const QVector<short> &v2)
{
    int min_len = kMin(v1.size(), v2.size());
    bool carry = false;
    short bit;
    for (int i = 0; i < min_len; ++i) {
        bit = v1.at(i) + v2.at(i) + carry;
        if (bit < 10) {
            carry = false;
        } else {
            carry = true;
            bit -= 10;
        }
        v1[i] = bit;
    }
    if (v1.size() >= v2.size()) {
        for (int i = min_len; i < v1.size(); ++i) {
            bit = v1.at(i) + carry;
            if (bit < 10) {
                v1[i] = bit;
                return;
            }
            bit -= 10;
            v1[i] = bit;
        }
    } else {
        for (int i = min_len; i < v2.size(); ++i) {
            bit = v2.at(i) + carry;
            if (bit < 10) {
                v1 << bit;
                for (int j = i + 1; j < v2.size(); ++j)
                    v1 << v2.at(j);
                return;
            }
            bit -= 10;
            v1 << bit;
        }
    }
    if (carry)
        v1 << 1;
}

void intSubtract(QVector<short> &v1, const QVector<short> &v2)
{
    bool carry = false;
    short bit;
    for (int i = 0; i < v2.size(); ++i) {
        bit = v1.at(i) - v2.at(i) - carry;
        if (bit >= 0) {
            carry = false;
        } else {
            carry = true;
            bit += 10;
        }
        v1[i] = bit;
    }
    if (v1.size() > v2.size()) {
        for (int i = v2.size(); i < v1.size(); ++i) {
            bit = v1.at(i) - carry;
            if (bit >= 0) {
                v1[i] = bit;
                break;
            }
            bit += 10;
            v1[i] = bit;
        }
    }
    while (v1.size() > 1) {
        if (v1.last() == 0)
            v1.removeLast();
        else
            break;
    }
}

void intMul(QVector<short> &v, short digit)
{
    short bit;
    short carry = 0;
    for (int i = 0; i < v.size(); ++i) {
        bit = v.at(i) * digit + carry;
        carry = bit / 10;
        v[i] = bit % 10;
    }
    if (carry)
        v << carry;
}

void intMul(QVector<short> &v1, const QVector<short> &v2)
{
    auto temp1 = v1;
    intMul(v1, v2.at(0));
    for (int i = 1; i < v2.size(); ++i) {
        temp1.insert(i - 1, 1, 0);
        if (v2.at(i) == 0)
            continue;
        auto temp2 = temp1;
        intMul(temp2, v2.at(i));
        intAdd(v1, temp2);
    }
}

QVector<short> intDiv(const QVector<short> &v1, const QVector<short> &v2)
{
    auto tempv1 = v1;
    QVector<short> result;
    result << 0;
    QVector<short> one;
    one << 1;
    while (tempv1 >= v2) {
        intSubtract(tempv1, v2);
        intAdd(result, one);
    }
    return result;
}

KInt::KInt() : signed_(false)
{
    int_ << 0;
}

KInt::KInt(short num)
{
    intToKInt(num);
}

KInt::KInt(unsigned short num)
{
    unsignedToKInt(num);
}

KInt::KInt(int num)
{
    intToKInt(num);
}

KInt::KInt(unsigned int num)
{
    unsignedToKInt(num);
}

KInt::KInt(long long num)
{
    intToKInt(num);
}

KInt::KInt(unsigned long long num)
{
    unsignedToKInt(num);
}

KInt::KInt(const QString &num)
{
    stringToKInt(num);
}

KInt::KInt(const KInt &other) : int_(other.int_), signed_(other.signed_)
{

}

KInt::~KInt()
{

}

QString KInt::toString() const
{
    QString num;
    if (signed_)
        num += '-';
    for (int i = int_.size() - 1; i > -1; --i)
        num += QString::number(int_.at(i));
    return num;
}

KInt &KInt::operator+=(const KInt &other)
{
    if (signed_) {
        if (other.signed_) {
            intAdd(int_, other.int_);
        } else {
            if (other.int_ >= int_) {
                signed_ = 0;
                auto temp = other.int_;
                intSubtract(temp, int_);
                int_ = temp;
            } else {
                intSubtract(int_, other.int_);
            }
        }
    } else {
        if (other.signed_) {
            if (int_ >= other.int_) {
                intSubtract(int_, other.int_);
            } else {
                signed_ = 1;
                auto temp = other.int_;
                intSubtract(temp, int_);
                int_ = temp;
            }
        } else {
            intAdd(int_, other.int_);
        }
    }

    return *this;
}

KInt &KInt::operator-=(const KInt &other)
{
    if (signed_) {
        if (other.signed_) {
            if (other.int_ >= int_) {
                signed_ = 0;
                auto temp = other.int_;
                intSubtract(temp, int_);
                int_ = temp;
            } else {
                intSubtract(int_, other.int_);
            }
        } else {
            intAdd(int_, other.int_);
        }
    } else {
        if (other.signed_) {
            intAdd(int_, other.int_);
        } else {
            if (int_ >= other.int_) {
                intSubtract(int_, other.int_);
            } else {
                signed_ = 1;
                auto temp = other.int_;
                intSubtract(temp, int_);
                int_ = temp;
            }
        }
    }

    return *this;
}

KInt &KInt::operator*=(const KInt &other)
{
    if (isZero())
        return *this;
    if (other.isZero()) {
        setToZero();
        return *this;
    }

    signed_ ^= other.signed_;
    intMul(int_, other.int_);
    return *this;
}

KInt &KInt::operator/=(const KInt &other)
{
    if (other.isZero())
        return *this;
    if (int_ < other.int_) {
        setToZero();
        return *this;
    }

    KInt result;
    int bit = int_.size() - other.int_.size();
    while (bit > 0) {
        auto temp1 = int_.mid(bit);
        if (temp1 >= other.int_) {
            KInt result1= 1;
            result1 << unsigned(bit);
            auto temp2 = other;
            temp2 << unsigned(bit);
            intSubtract(int_, temp2.int_);
            intAdd(result.int_, result1.int_);
            bit = int_.size() - other.int_.size();
        } else {
            break;
        }
    }

    auto result1 = intDiv(int_, other.int_);
    intAdd(result.int_, result1);
    int_ = result.int_;
    signed_ ^= other.signed_;
    return *this;
}

bool KInt::operator>(const KInt &other) const
{
    if (signed_ > other.signed_)
        return false;
    if (signed_ < other.signed_)
        return true;

    if (signed_)
        return int_ < other.int_;
    return int_ > other.int_;
}

bool KInt::operator<(const KInt &other) const
{
    if (signed_ > other.signed_)
        return true;
    if (signed_ < other.signed_)
        return false;

    if (signed_)
        return int_ > other.int_;
    return int_ < other.int_;
}

KInt operator-(const KInt &i)
{
    KInt i1;
    if (i == i1)
        return i;
    i1.signed_ = !i.signed_;
    i1.int_ = i.int_;
    return i1;
}

void KInt::stringToKInt(const QString &num)
{
    int start = 0;

    if (num.at(0) == '-') {
        signed_ = true;
        start = 1;
    } else {
        signed_ = false;
    }

    for (int i = num.size() - 1; i >= start; --i)
        int_ << num.at(i).toLatin1() - 48;
}

KInt &KInt::operator<<(unsigned bit)
{
    if (isZero())
        return *this;

    int_.insert(0, int(bit), 0);
    return *this;
}

KInt &KInt::operator>>(unsigned bit)
{
    if (int(bit) >= int_.size())
        setToZero();
    else
        int_.remove(0, int(bit));

    return *this;
}
