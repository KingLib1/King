#include "ktime.h"

KTime::KTime() : hour_(0), minute_(0), second_(0), millisecond_(0)
{

}

KTime::KTime(int ms)
{
    hour_ = ms / 3600000;
    ms %= 3600000;
    minute_ = ms / 60000;
    ms %= 60000;
    second_ = ms / 1000;
    millisecond_ = ms % 1000;
}

KTime::KTime(int hour, int minute, int second, int millisecond) :
    hour_(hour), minute_(minute), second_(second), millisecond_(millisecond)
{

}

KTime::KTime(const KTime &time) : hour_(time.hour_), minute_(time.minute_),
    second_(time.second_), millisecond_(time.millisecond_)
{

}

KTime::~KTime()
{

}

void KTime::normalize()
{
    int ms = hour_ * 3600000 + minute_ * 60000 + second_ * 1000 + millisecond_;
    hour_ = ms / 3600000;
    ms %= 3600000;
    minute_ = ms / 60000;
    ms %= 60000;
    second_ = ms / 1000;
    millisecond_ = ms % 1000;
}
