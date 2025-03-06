#ifndef KPOINT_H
#define KPOINT_H

#include "kmath.h"

class KING_EXPORT KPoint
{
public:
    KPoint();
    KPoint(int x, int y);

    inline void setX(int x);
    inline void setY(int y);
    inline void setXY(int x, int y);
    inline void translateX(int dx);
    inline void translateY(int dy);
    inline void translate(int dx, int dy);
    inline void translate(const KPoint &dv);
    inline void transpose(); // 交换x y;
    inline void invert(); // 关于原点对称

    inline bool isNull() const;
    /**
     * @brief 曼哈顿长度
     * @return x()和y()的绝对值之和
     */
    inline int manhattanLength() const;
    inline int &rx();
    inline int &ry();
    inline int x() const;
    inline int y() const;
    inline KPoint translated(int dx, int dy) const;
    inline KPoint translated(const KPoint &dv);
    inline KPoint transposed() const;
    inline KPoint inverted() const;

    static inline int dotProduct(const KPoint &p1, const KPoint &p2);

    inline KPoint &operator+=(const KPoint &other);
    inline KPoint &operator-=(const KPoint &other);
    inline KPoint &operator*=(int factor);
    inline KPoint &operator/=(int divisor);

    inline KPoint operator+(const KPoint &other) const;
    inline KPoint operator-(const KPoint &other) const;
    inline KPoint operator*(int factor) const;
    inline KPoint operator/(int factor) const;
    inline bool operator==(const KPoint &other) const;
    inline bool operator!=(const KPoint &other) const;

private:
    int x_;
    int y_;
};

inline void KPoint::setX(int x)
{
    x_ = x;
}

inline void KPoint::setY(int y)
{
    y_ = y;
}

inline void KPoint::setXY(int x, int y)
{
    x_ = x;
    y_ = y;
}

inline void KPoint::translateX(int dx)
{
    x_ += dx;
}

inline void KPoint::translateY(int dy)
{
    y_ += dy;
}

inline void KPoint::translate(int dx, int dy)
{
    x_ += dx;
    y_ += dy;
}

inline void KPoint::translate(const KPoint &dv)
{
    *this += dv;
}

inline void KPoint::transpose()
{
    double temp = x_;
    x_ = y_;
    y_ = temp;
}

inline void KPoint::invert()
{
    x_ = -x_;
    y_ = -y_;
}

inline bool KPoint::isNull() const
{
    return x_ == 0 && y_ == 0;
}

inline int KPoint::manhattanLength() const
{
    return kAbs(x_) + kAbs(y_);
}

inline int &KPoint::rx()
{
    return x_;
}

inline int &KPoint::ry()
{
    return y_;
}

inline int KPoint::x() const
{
    return x_;
}

inline int KPoint::y() const
{
    return y_;
}

inline KPoint KPoint::translated(int dx, int dy) const
{
    return KPoint(x_ + dx, y_ + dy);
}

inline KPoint KPoint::translated(const KPoint &dv)
{
    return *this + dv;
}

inline KPoint KPoint::transposed() const
{
    return KPoint(y_, x_);
}

inline KPoint KPoint::inverted() const
{
    return KPoint(-x_, -y_);
}

inline int KPoint::dotProduct(const KPoint &p1, const KPoint &p2)
{
    return p1.x_ * p2.x_ + p1.y_ * p2.y_;
}

inline KPoint &KPoint::operator+=(const KPoint &other)
{
    x_ += other.x_;
    y_ += other.y_;
    return *this;
}

inline KPoint &KPoint::operator-=(const KPoint &other)
{
    x_ -= other.x_;
    y_ -= other.y_;
    return *this;
}

inline KPoint &KPoint::operator*=(int factor)
{
    x_ *= factor;
    y_ *= factor;
    return *this;
}

inline KPoint &KPoint::operator/=(int divisor)
{
    x_ /= divisor;
    y_ /= divisor;
    return *this;
}

inline KPoint KPoint::operator+(const KPoint &other) const
{
    return KPoint(x_ + other.x_, y_ + other.y_);
}

inline KPoint KPoint::operator-(const KPoint &other) const
{
    return KPoint(x_ - other.x_, y_ - other.y_);
}

inline KPoint KPoint::operator*(int factor) const
{
    return KPoint(x_ * factor, y_ * factor);
}

inline KPoint KPoint::operator/(int factor) const
{
    return KPoint(x_ / factor, y_ / factor);
}

inline bool KPoint::operator==(const KPoint &other) const
{
    return x_ == other.x_ && y_ == other.y_;
}

inline bool KPoint::operator!=(const KPoint &other) const
{
    return !(*this == other);
}

inline KING_EXPORT KPoint operator*(int factor, const KPoint &p)
{
    return KPoint(factor * p.x(), factor * p.y());
}

inline KING_EXPORT KPoint operator-(const KPoint &p)
{
    return KPoint(-p.x(), -p.y());
}

#endif // KPOINT_H
