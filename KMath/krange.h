#ifndef KRANGE_H
#define KRANGE_H

#include "kmath.h"

class KING_EXPORT KRange
{
public:
    KRange();
    KRange(double lower, double upper);
    KRange(const KRange &range);
    ~KRange();

    inline void setRange(double lower, double upper);
    inline void setLower(double lower);
    inline void setUpper(double upper);
    inline void normalize();
    inline void translate(double offset);
    inline void expandTo(const KRange &range);

    inline double lower() const;
    inline double upper() const;
    inline double middle() const;
    inline double range() const;
    inline bool isValid() const;
    inline bool contains(double n) const;
    inline bool contains(const KRange &range) const;
    inline bool intersects(const KRange &range) const;
    inline KRange intersected(const KRange &range) const;
    inline KRange normalized() const;
    inline KRange translated(double offset) const;
    inline KRange expandedTo(const KRange &range) const;

    inline KRange operator+(double offset) const;
    inline KRange operator-(double offset) const;
    inline KRange &operator+=(double offset);
    inline KRange &operator-=(double offset);
    inline KRange &operator=(const KRange &range);
    inline KRange &operator<<(double offset);
    inline KRange &operator>>(double offset);

private:
    double lower_;
    double upper_;
};

inline void KRange::setRange(double lower, double upper)
{
    lower_ = lower;
    upper_ = upper;
}

inline void KRange::setLower(double lower)
{
    lower_ = lower;
}

inline void KRange::setUpper(double upper)
{
    upper_ = upper;
}

inline void KRange::normalize()
{
    if (lower_ > upper_)
        kSwap(lower_, upper_);
}

inline void KRange::translate(double offset)
{
    lower_ += offset;
    upper_ += offset;
}

inline void KRange::expandTo(const KRange &range)
{
    if (range.lower_ < lower_)
        lower_ = range.lower_;
    if (upper_ < range.upper_)
        upper_ = range.upper_;
}

inline double KRange::lower() const
{
    return lower_;
}

inline double KRange::upper() const
{
    return upper_;
}

inline double KRange::middle() const
{
    return (lower_ + upper_) / 2;
}

inline double KRange::range() const
{
    return upper_ - lower_;
}

inline bool KRange::isValid() const
{
    return lower_ <= upper_;
}

inline bool KRange::contains(double n) const
{
    return n >= lower_ && n <= upper_;
}

inline bool KRange::contains(const KRange &range) const
{
    return lower_ <= range.lower_ && upper_ >= range.upper_;
}

inline bool KRange::intersects(const KRange &range) const
{
    if (range.lower_ > upper_ || range.upper_ < lower_)
        return false;
    return true;
}

inline KRange KRange::intersected(const KRange &range) const
{
    if (range.lower_ > upper_ || range.upper_ < lower_)
        return KRange();
    if (range.lower_ > lower_)
        return KRange(range.lower_, kMin(range.upper_, upper_));
    return KRange(lower_, kMin(range.upper_, upper_));
}

inline KRange KRange::normalized() const
{
    return lower_ < upper_ ? *this : KRange(upper_, lower_);
}

inline KRange KRange::translated(double offset) const
{
    return KRange(lower_ + offset, upper_ + offset);
}

inline KRange KRange::expandedTo(const KRange &range) const
{
    return KRange(kMin(range.lower_, lower_), kMax(range.upper_, upper_));
}

inline KRange KRange::operator+(double offset) const
{
    return KRange(lower_ + offset, upper_ + offset);
}

inline KRange KRange::operator-(double offset) const
{
    return KRange(lower_ - offset, upper_ - offset);
}

inline KRange &KRange::operator+=(double offset)
{
    translate(offset);
    return *this;
}

inline KRange &KRange::operator-=(double offset)
{
    translate(-offset);
    return *this;
}

inline KRange &KRange::operator=(const KRange &range)
{
    lower_ = range.lower_;
    upper_ = range.upper_;
    return *this;
}

inline KRange &KRange::operator<<(double offset)
{
    translate(-offset);
    return *this;
}

inline KRange &KRange::operator>>(double offset)
{
    translate(offset);
    return *this;
}

#endif // KRANGE_H
