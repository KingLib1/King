#ifndef KPAIR_H
#define KPAIR_H

#include <QPair>

#include "King_global.h"

template<typename T1, typename T2>
struct KING_EXPORT KPair
{
    KPair();
    KPair(const T1 &t1, const T2 &t2);
    KPair(const KPair &other);

    template<typename TT1, typename TT2>
    KPair(const KPair<TT1, TT2> &p) : first(p.first), second(p.second) {}

    template<typename TT1, typename TT2>
    inline KPair &operator=(const KPair<TT1, TT2> &p)
    {
        first = p.first;
        second = p.second;
        return *this;
    }

    inline KPair &operator=(const KPair<T1, T2> &p)
    {
        first = p.first;
        second = p.second;
        return *this;
    }

    void swap(KPair &other);

    inline bool operator==(const KPair &other) const;
    inline bool operator!=(const KPair &other) const;
    inline bool operator<(const KPair &other) const;
    inline bool operator>(const KPair &other) const;
    inline bool operator<=(const KPair &other) const;
    inline bool operator>=(const KPair &other) const;

    T1 first;
    T2 second;
};

template<typename T1, typename T2>
KPair<T1, T2>::KPair()
{

}

template<typename T1, typename T2>
KPair<T1, T2>::KPair(const T1 &t1, const T2 &t2)
{
    first = t1;
    second = t2;
}

template<typename T1, typename T2>
KPair<T1, T2>::KPair(const KPair &other) :
    first(other.first), second(other.second)
{

}

template<typename T1, typename T2>
void KPair<T1, T2>::swap(KPair &other)
{
    T1 temp1 = first;
    first = other.first;
    other.first = temp1;

    T2 temp2 = second;
    second = other.second;
    other.second = temp2;
}

template<typename T1, typename T2>
inline bool KPair<T1, T2>::operator==(const KPair &other) const
{
    return first == other.first && second == other.second;
}

template<typename T1, typename T2>
inline bool KPair<T1, T2>::operator!=(const KPair &other) const
{
    return !(*this == other);
}

template<typename T1, typename T2>
inline bool KPair<T1, T2>::operator<(const KPair &other) const
{
    return first < other.first || (!(other.first < first) && second < other.second);
}

template<typename T1, typename T2>
inline bool KPair<T1, T2>::operator>(const KPair &other) const
{
    return other < *this;
}

template<typename T1, typename T2>
inline bool KPair<T1, T2>::operator<=(const KPair &other) const
{
    return !(other < *this);
}

template<typename T1, typename T2>
inline bool KPair<T1, T2>::operator>=(const KPair &other) const
{
    return !(*this < other);
}

template<typename T1, typename T2>
inline KPair<T1, T2> kMakePair(const T1 &t1, const T2 &t2)
{
    return KPair<T1, T2>(t1, t2);
}

#endif // KPAIR_H
