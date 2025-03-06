#ifndef KTIME_H
#define KTIME_H

#include "King_global.h"

class KING_EXPORT KTime
{
public:
    KTime();
    KTime(int ms);
    KTime(int hour, int minute, int second, int millisecond = 0);
    KTime(const KTime &time);
    ~KTime();

    inline void setHour(int hour);
    inline void setMinute(int minute);
    inline void setSecond(int second);
    inline void setMillisecond(int millisecond);
    inline void setTime(int hour, int minute, int second, int millisecond);
    inline void addHours(int hour);
    inline void addMinutes(int minute);
    inline void addMSecs(int ms);
    inline void addSecs(int s);
    void normalize();

    inline int hour() const;
    inline int minute() const;
    inline int second() const;
    inline int millisecond() const;
    inline bool isValid() const;
    inline int toMSecs() const;
    inline KTime normalized() const;

    inline KTime &operator=(const KTime &time);
    inline KTime &operator+=(const KTime &time);
    inline KTime &operator-=(const KTime &time);
    inline KTime operator+(const KTime &time) const;
    inline KTime operator-(const KTime &time) const;
    inline bool operator==(const KTime &time) const;
    inline bool operator!=(const KTime &time) const;
    inline bool operator>=(const KTime &time) const;
    inline bool operator>(const KTime &time) const;
    inline bool operator<=(const KTime &time) const;
    inline bool operator<(const KTime &time) const;

private:
    int hour_;
    int minute_;
    int second_;
    int millisecond_;
};

inline void KTime::setHour(int hour)
{
    hour_ = hour;
}

inline void KTime::setMinute(int minute)
{
    minute_ = minute;
}

inline void KTime::setSecond(int second)
{
    second_ = second;
}

inline void KTime::setMillisecond(int millisecond)
{
    millisecond_ = millisecond;
}

inline void KTime::setTime(int hour, int minute, int second, int millisecond)
{
    hour_ = hour;
    minute_ = minute;
    second_ = second;
    millisecond_ = millisecond;
}

inline void KTime::addHours(int hour)
{
    hour_ += hour;
}

inline void KTime::addMinutes(int minute)
{
    minute_ += minute;
}

inline void KTime::addMSecs(int ms)
{
    millisecond_ += ms;
}

inline void KTime::addSecs(int s)
{
    second_ += s;
}

inline int KTime::hour() const
{
    return hour_;
}

inline int KTime::minute() const
{
    return minute_;
}

inline int KTime::second() const
{
    return second_;
}

inline int KTime::millisecond() const
{
    return millisecond_;
}

inline bool KTime::isValid() const
{
    return hour_ >= 0 && hour_ < 24 && minute_ >= 0 && minute_ < 60 &&
            second_ >= 0 && second_ < 60 && millisecond_ >= 0 &&
            millisecond_ < 1000;
}

inline int KTime::toMSecs() const
{
    return hour_ * 3600000 + minute_ * 60000 + second_ * 1000 + millisecond_;
}

inline KTime KTime::normalized() const
{
    KTime time(*this);
    time.normalize();
    return time;
}

inline KTime &KTime::operator=(const KTime &time)
{
    hour_ = time.hour_;
    minute_ = time.minute_;
    second_ = time.second_;
    millisecond_ = time.millisecond_;
    return *this;
}

inline KTime &KTime::operator+=(const KTime &time)
{
    hour_ += time.hour_;
    minute_ += time.minute_;
    second_ += time.second_;
    millisecond_ += time.millisecond_;
    return *this;
}

inline KTime &KTime::operator-=(const KTime &time)
{
    hour_ -= time.hour_;
    minute_ -= time.minute_;
    second_ -= time.second_;
    millisecond_ -= time.millisecond_;
    return *this;
}

inline KTime KTime::operator+(const KTime &time) const
{
    return KTime(hour_ + time.hour_, minute_ + time.minute_,
                 second_ + time.second_, millisecond_ + time.millisecond_);
}

inline KTime KTime::operator-(const KTime &time) const
{
    return KTime(hour_ - time.hour_, minute_ - time.minute_,
                 second_ - time.second_, millisecond_ - time.millisecond_);
}

inline bool KTime::operator==(const KTime &time) const
{
    return toMSecs() == time.toMSecs();
}

inline bool KTime::operator!=(const KTime &time) const
{
    return toMSecs() != time.toMSecs();
}

inline bool KTime::operator>=(const KTime &time) const
{
    return toMSecs() >= time.toMSecs();
}

inline bool KTime::operator>(const KTime &time) const
{
    return toMSecs() > time.toMSecs();
}

inline bool KTime::operator<=(const KTime &time) const
{
    return toMSecs() <= time.toMSecs();
}

inline bool KTime::operator<(const KTime &time) const
{
    return toMSecs() < time.toMSecs();
}

#endif // KTIME_H
