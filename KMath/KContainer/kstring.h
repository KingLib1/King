#ifndef KSTRING_H
#define KSTRING_H

#include "KVector.h"
#include "kchar.h"
#include <QString>

class KING_EXPORT KString
{
public:
    KString();
    KString(char s[]);
    KString(int size, char c);
    KString(char c);
    KString(KChar c);

    inline KString &append(const KString &other);
    inline KString &append(char c);
    inline KString &append(KChar c);
    KString &append(char s[]);
    KString &append(char s[], int len);

    inline int size() const;
    inline bool isEmpty() const;
    inline KChar at(int index) const;
    KString left(int n) const;

private:
    KVector<KChar> s_;
};

inline KString &KString::append(const KString &other)
{
    s_ << other.s_;
    return *this;
}

inline KString &KString::append(char c)
{
    s_ << c;
    return *this;
}

inline KString &KString::append(KChar c)
{
    s_ << c.toChar();
    return *this;
}

inline int KString::size() const
{
    return s_.size();
}

inline bool KString::isEmpty() const
{
    return s_.isEmpty();
}

inline KChar KString::at(int index) const
{
    return s_.at(index);
}

#endif // KSTRING_H
