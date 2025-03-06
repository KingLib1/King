#ifndef K01DISTRIBUTION_H
#define K01DISTRIBUTION_H

#include "King_global.h"

class KING_EXPORT K01Distribution
{
public:
    K01Distribution();
    K01Distribution(double p);
    K01Distribution(const K01Distribution &dis);
    ~K01Distribution();

    inline void setP(double p);

    inline double p() const;
    /**
     * @brief 期望
     */
    inline double E() const;
    /**
     * @brief 方差
     */
    inline double D() const;

    inline K01Distribution &operator=(const K01Distribution &other);

private:
    double p_;
};

inline void K01Distribution::setP(double p)
{
    p_ = p;
}

inline double K01Distribution::p() const
{
    return p_;
}

inline double K01Distribution::E() const
{
    return p_;
}

inline double K01Distribution::D() const
{
    return p_ * (1 - p_);
}

inline K01Distribution &K01Distribution::operator=(const K01Distribution &other)
{
    p_ = other.p_;
    return *this;
}

#endif // K01DISTRIBUTION_H
