#ifndef KINT_H
#define KINT_H

#include <QVector>

#include "King_global.h"

class KING_EXPORT KInt
{
public:
    KInt();
    KInt(short num);
    KInt(unsigned short num);
    KInt(int num);
    KInt(unsigned int num);
    KInt(long long num);
    KInt(unsigned long long num);
    KInt(const QString &num);
    KInt(const KInt &other);
    ~KInt();

    inline void setToZero();

    QString toString() const;
    inline bool isZero() const;

    inline KInt &operator=(short num);
    inline KInt &operator=(unsigned short num);
    inline KInt &operator=(int num);
    inline KInt &operator=(unsigned int num);
    inline KInt &operator=(long long num);
    inline KInt &operator=(unsigned long long num);
    inline KInt &operator=(const QString &num);
    inline KInt &operator=(const KInt &num);
    KInt &operator+=(const KInt &other);
    KInt &operator-=(const KInt &other);
    KInt &operator*=(const KInt &other);
    KInt &operator/=(const KInt &other);
    KInt &operator<<(unsigned bit);
    KInt &operator>>(unsigned bit);

    inline bool operator==(const KInt &other) const;
    inline bool operator!=(const KInt &other) const;
    bool operator>(const KInt &other) const;
    bool operator<(const KInt &other) const;
    inline bool operator>=(const KInt &other) const;
    inline bool operator<=(const KInt &other) const;
    inline KInt operator+(const KInt &other) const;
    inline KInt operator-(const KInt &other) const;
    inline KInt operator*(const KInt &other) const;
    inline KInt operator/(const KInt &other) const;

    friend KInt operator-(const KInt &i);

private:
    void stringToKInt(const QString &num);
    template<typename I>
    void intToKInt(I num);
    template<typename U>
    void unsignedToKInt(U num);

    QVector<short> int_;
    bool signed_; // 0为正，1为负
};

inline void KInt::setToZero()
{
    signed_ = false;
    int_.clear();
    int_ << 0;
}

inline bool KInt::isZero() const
{
    return int_.size() == 1 && int_.first() == 0;
}

inline KInt &KInt::operator=(short num)
{
    int_.clear();
    intToKInt(num);
    return *this;
}

inline KInt &KInt::operator=(unsigned short num)
{
    int_.clear();
    unsignedToKInt(num);
    return *this;
}

inline KInt &KInt::operator=(int num)
{
    int_.clear();
    intToKInt(num);
    return *this;
}

inline KInt &KInt::operator=(unsigned int num)
{
    int_.clear();
    unsignedToKInt(num);
    return *this;
}

inline KInt &KInt::operator=(long long num)
{
    int_.clear();
    intToKInt(num);
    return *this;
}

inline KInt &KInt::operator=(unsigned long long num)
{
    int_.clear();
    unsignedToKInt(num);
    return *this;
}

inline KInt &KInt::operator=(const QString &num)
{
    int_.clear();
    stringToKInt(num);
    return *this;
}

inline KInt &KInt::operator=(const KInt &num)
{
    signed_ = num.signed_;
    int_ = num.int_;
    return *this;
}

inline bool KInt::operator==(const KInt &other) const
{
    if (signed_ != other.signed_)
        return false;
    return int_ == other.int_;
}

inline bool KInt::operator!=(const KInt &other) const
{
    if (signed_ != other.signed_)
        return true;
    return int_ != other.int_;
}

inline bool KInt::operator>=(const KInt &other) const
{
    return !(*this < other);
}

inline bool KInt::operator<=(const KInt &other) const
{
    return !(*this > other);
}

inline KInt KInt::operator+(const KInt &other) const
{
    KInt temp(*this);
    return temp += other;
}

inline KInt KInt::operator-(const KInt &other) const
{
    KInt temp(*this);
    return temp -= other;
}

inline KInt KInt::operator*(const KInt &other) const
{
    KInt temp(*this);
    return temp *= other;
}

inline KInt KInt::operator/(const KInt &other) const
{
    KInt temp(*this);
    return temp /= other;
}

template<typename I>
void KInt::intToKInt(I num)
{
    if (num < 0) {
        signed_ = true;
        num = -num;
    } else {
        signed_ = false;
    }

    do {
        int_ << num % 10;
        num /= 10;
    } while (num);
}

template<typename U>
void KInt::unsignedToKInt(U num)
{
    signed_ = false;

    do {
        int_ << num % 10;
        num /= 10;
    } while (num);
}

KInt operator-(const KInt &i);

#endif // KINT_H
