#ifndef KCHAR_H
#define KCHAR_H

#include "King_global.h"

class KING_EXPORT KChar
{
public:
    KChar();
    KChar(char c);
    KChar(int c);

    inline KChar toLower() const;
    inline KChar toUpper() const;
    inline char toChar() const;
    inline bool isDigit() const;
    inline bool isLetter() const;
    inline bool isLower() const;
    inline bool isUpper() const;
    inline bool isNull() const;

    inline bool operator==(const KChar &other) const;
    inline bool operator!=(const KChar &other) const;
    inline bool operator<(const KChar &other) const;
    inline bool operator>(const KChar &other) const;
    inline bool operator<=(const KChar &other) const;
    inline bool operator>=(const KChar &other) const;

private:
    char ch_;
};

inline KChar KChar::toLower() const
{
    return isUpper() ? KChar(ch_ + 32) : KChar(ch_);
}

inline KChar KChar::toUpper() const
{
    return isLower() ? KChar(ch_ - 32) : KChar(ch_);
}

inline char KChar::toChar() const
{
    return ch_;
}

inline bool KChar::isDigit() const
{
    return ch_ >= 48 && ch_ <= 57;
}

inline bool KChar::isLetter() const
{
    return isLower() || isUpper();
}

inline bool KChar::isLower() const
{
    return ch_ >= 65 && ch_ <= 90;
}

inline bool KChar::isUpper() const
{
    return ch_ >= 97 && ch_ <= 122;
}

inline bool KChar::isNull() const
{
    return ch_ == 0;
}

inline bool KChar::operator==(const KChar &other) const
{
    return ch_ == other.ch_;
}

inline bool KChar::operator!=(const KChar &other) const
{
    return ch_ != other.ch_;
}

inline bool KChar::operator<(const KChar &other) const
{
    return ch_ < other.ch_;
}

inline bool KChar::operator>(const KChar &other) const
{
    return ch_ > other.ch_;
}

inline bool KChar::operator<=(const KChar &other) const
{
    return ch_ <= other.ch_;
}

inline bool KChar::operator>=(const KChar &other) const
{
    return ch_ >= other.ch_;
}

#endif // KCHAR_H
