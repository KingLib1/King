#ifndef KFLAGS_H
#define KFLAGS_H

#include "King_global.h"
//#include <QFlag>

enum KFlagBit{
    first = 0x1,
    second = 0x2,
    third = 0x4,
    fourth = 0x8,
    fifth = 0x10,
    sixth = 0x20,
    seventh = 0x40,
    eighth = 0x80,
    ninth = 0x100,
    tenth = 0x200,
    eleventh = 0x400,
    twelfth = 0x800,
};

template<typename Enum>
class KING_EXPORT KFlags
{
public:
    KFlags();
    KFlags(Enum flags);
    KFlags(int flags);

    inline void setFlag(Enum flag, bool on = true);

    inline bool testFlag(Enum flag) const;

    inline KFlags &operator=(KFlags flag);
    inline KFlags &operator|=(KFlags other);
    inline KFlags &operator|=(Enum other);
    inline KFlags &operator^=(KFlags other);
    inline KFlags &operator^=(Enum other);
    inline KFlags &operator&=(Enum other);
    
    inline KFlags operator|(KFlags other) const;
    inline KFlags operator|(Enum other) const;
    inline KFlags operator^(KFlags other) const;
    inline KFlags operator^(Enum other) const;
    inline KFlags operator&(Enum other) const;
    inline KFlags operator~() const;
    inline bool operator!() const;
    inline operator bool() const;

private:
    int i_;
};

template<typename Enum>
KFlags<Enum>::KFlags() : i_(0)
{

}

template<typename Enum>
KFlags<Enum>::KFlags(Enum flags) : i_(flags)
{

}

template<typename Enum>
KFlags<Enum>::KFlags(int flags) : i_(flags)
{

}

template<typename Enum>
inline void KFlags<Enum>::setFlag(Enum flag, bool on)
{
    on ? (i_ |= flag) : (i_ &= (~flag));
}

template<typename Enum>
inline bool KFlags<Enum>::testFlag(Enum flag) const
{
    return i_ & flag;
}

template<typename Enum>
inline KFlags<Enum> &KFlags<Enum>::operator=(KFlags<Enum> flag)
{
    i_ = flag.i_;
}

template<typename Enum>
inline KFlags<Enum> &KFlags<Enum>::operator|=(KFlags<Enum> other)
{
    i_ |= other.i_;
    return *this;
}

template<typename Enum>
inline KFlags<Enum> &KFlags<Enum>::operator|=(Enum other)
{
    i_ |= other;
    return *this;
}

template<typename Enum>
inline KFlags<Enum> &KFlags<Enum>::operator^=(KFlags<Enum> other)
{
    i_ ^= other.i_;
    return *this;
}

template<typename Enum>
inline KFlags<Enum> &KFlags<Enum>::operator^=(Enum other)
{
    i_ ^= other;
    return *this;
}

template<typename Enum>
inline KFlags<Enum> &KFlags<Enum>::operator&=(Enum other)
{
    i_ &= other;
    return *this;
}

template<typename Enum>
inline KFlags<Enum> KFlags<Enum>::operator|(KFlags<Enum> other) const
{
    return KFlags<Enum>(i_ | other.i_);
}

template<typename Enum>
inline KFlags<Enum> KFlags<Enum>::operator|(Enum other) const
{
    return KFlags<Enum>(i_ | other);
}

template<typename Enum>
inline KFlags<Enum> KFlags<Enum>::operator^(KFlags<Enum> other) const
{
    return KFlags<Enum>(i_ ^ other.i_);
}

template<typename Enum>
inline KFlags<Enum> KFlags<Enum>::operator^(Enum other) const
{
    return KFlags<Enum>(i_ ^ other);
}

template<typename Enum>
inline KFlags<Enum> KFlags<Enum>::operator&(Enum other) const
{
    return KFlags<Enum>(i_ & other);
}

template<typename Enum>
inline KFlags<Enum> KFlags<Enum>::operator~() const
{
    return KFlags<Enum>(~i_);
}

template<typename Enum>
inline bool KFlags<Enum>::operator!() const
{
    return !i_;
}

template<typename Enum>
inline KFlags<Enum>::operator bool() const
{
    return i_;
}

#endif // KFLAGS_H
