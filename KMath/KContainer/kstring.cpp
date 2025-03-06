#include "kstring.h"

KString::KString()
{

}

KString::KString(char s[])
{
    for (int i = 0; s[i] != 0; ++i)
        s_ << s[i];
}

KString::KString(int size, char c)
{
    for (int i = 0; i < size; ++i)
        s_ << c;
}

KString::KString(char c)
{
    s_ << c;
}

KString::KString(KChar c)
{
    s_ << c.toChar();
}

KString &KString::append(char s[])
{
    for (int i = 0; s[i] != 0; ++i)
        s_ << s[i];
    return *this;
}

KString &KString::append(char s[], int len)
{
    for (int i = 0; i < len; ++i)
        s_ << s[i];
    return *this;
}

KString KString::left(int n) const
{
    KString s;
    s.s_ = s_.mid(0, n);
    return s;
}


