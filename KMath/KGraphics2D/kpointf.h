#ifndef KPOINTF_H
#define KPOINTF_H

#include "kpoint.h"

class KING_EXPORT KPointF
{
public:
    KPointF();
    KPointF(double x, double y);
    KPointF(const KPointF &p);
    KPointF(const KPoint &p);
    inline double x() const {return x_;}
    inline double y() const {return y_;}
    inline double xSquare() const {return kSquare(x_);}
    inline double ySquare() const {return kSquare(y_);}
    inline double &rx() {return x_;}
    inline double &ry() {return y_;}
    inline void setX(double x) {x_ = x;}
    inline void setY(double y) {y_ = y;}
    inline void setXY(double x, double y);
    inline void setXY(const KPointF &p);
    inline void translate(double dx, double dy);
    inline void translate(const KPointF &dv);
    inline void translateX(double dx);
    inline void translateY(double dy);

    inline double manhattanLength() const;
    inline double distanceToPoint(const KPointF &p) const;
    inline double distanceSquaredToPoint(const KPointF &p) const;
    inline double originDistance() const;
    inline double originDistanceSquared() const;
    inline KPointF translated(double dx, double dy) const;
    inline KPointF translated(const KPointF &dv) const;
    inline KPointF translatedX(double dx) const;
    inline KPointF translatedY(double dy) const;
    inline KPointF originSymmetry() const;
    inline KPointF xAxisSymmetry() const;
    inline KPointF yAxisSymmetry() const;
    inline KPointF ceil() const;
    inline KPointF floor() const;
    inline KPointF round() const;
    inline KPoint toPoint() const;

    inline static KPointF midPoint(const KPointF &p1, const KPointF &p2);
    inline static double dotProduct(const KPointF &p1, const KPointF &p2);

    inline KPointF operator-(const KPointF &rhs) const;
    inline KPointF operator+(const KPointF &rhs) const;
    inline KPointF operator*(double factor) const;
    inline KPointF operator/(double divisor) const;
    inline bool operator==(const KPointF &rhs) const;
    inline bool operator!=(const KPointF &rhs) const;
    inline KPointF &operator=(const KPointF &rhs);
    inline KPointF &operator+=(const KPointF &rhs);
    inline KPointF &operator-=(const KPointF &rhs);
    inline KPointF &operator*=(double factor);
    inline KPointF &operator/=(double divisor);

private:
    double x_;
    double y_;
};

inline void KPointF::setXY(double x, double y)
{
    x_ = x;
    y_ = y;
}

inline void KPointF::setXY(const KPointF &p)
{
    x_ = p.x_;
    y_ = p.y_;
}

inline void KPointF::translate(double dx, double dy)
{
    x_ += dx;
    y_ += dy;
}

inline void KPointF::translate(const KPointF &dv)
{
    x_ += dv.x_;
    y_ += dv.y_;
}

inline void KPointF::translateX(double dx)
{
    x_ += dx;
}

inline void KPointF::translateY(double dy)
{
    y_ += dy;
}

inline double KPointF::manhattanLength() const
{
    return kFabs(x_) + kFabs(y_);
}

inline double KPointF::distanceToPoint(const KPointF &p) const
{
    return kSqrt(distanceSquaredToPoint(p));
}

inline double KPointF::distanceSquaredToPoint(const KPointF &p) const
{
    double dx = x_ - p.x_;
    double dy = y_ - p.y_;
    return dx*dx + dy*dy;
}

inline double KPointF::originDistance() const
{
    return kSqrt(originDistanceSquared());
}

inline double KPointF::originDistanceSquared() const
{
    return x_ * x_ + y_ * y_;
}

inline KPointF KPointF::translated(double dx, double dy) const
{
    return KPointF(x_ + dx, y_ + dy);
}

inline KPointF KPointF::translated(const KPointF &dv) const
{
    return *this + dv;
}

inline KPointF KPointF::translatedX(double dx) const
{
    return KPointF(x_ + dx, y_);
}

inline KPointF KPointF::translatedY(double dy) const
{
    return KPointF(x_, y_ + dy);
}

inline KPointF KPointF::originSymmetry() const
{
    return KPointF(-x_, -y_);
}

inline KPointF KPointF::xAxisSymmetry() const
{
    return KPointF(x_, -y_);
}

inline KPointF KPointF::yAxisSymmetry() const
{
    return KPointF(-x_, y_);
}

inline KPointF KPointF::ceil() const
{
    return KPointF(kCeil(x_), kCeil(y_));
}

inline KPointF KPointF::floor() const
{
    return KPointF(kFloor(x_), kFloor(y_));
}

inline KPointF KPointF::round() const
{
    return KPointF(kRound(x_), kRound(y_));
}

inline KPoint KPointF::toPoint() const
{
    return KPoint(x_, y_);
}

inline KPointF KPointF::midPoint(const KPointF &p1, const KPointF &p2)
{
    return KPointF((p1.x_ + p2.x_) / 2, (p1.y_ + p2.y_) / 2);
}

inline double KPointF::dotProduct(const KPointF &p1, const KPointF &p2)
{
    return p1.x_ * p2.x_ + p1.y_ * p2.y_;
}

inline KPointF KPointF::operator-(const KPointF &rhs) const
{
    return KPointF(x_ - rhs.x_, y_ - rhs.y_);
}

inline KPointF KPointF::operator+(const KPointF &rhs) const
{
    return KPointF(x_ + rhs.x_, y_ + rhs.y_);
}

inline KPointF KPointF::operator*(double factor) const
{
    return KPointF(x_ * factor, y_ * factor);
}

inline KPointF KPointF::operator/(double divisor) const
{
    return KPointF(x_ / divisor, y_ / divisor);
}

inline bool KPointF::operator==(const KPointF &rhs) const
{
    return isEqual(x_, rhs.x_) && isEqual(y_, rhs.y_);
}

inline bool KPointF::operator!=(const KPointF &rhs) const
{
    return !(*this == rhs);
}

inline KPointF &KPointF::operator=(const KPointF &rhs)
{
    x_ = rhs.x_;
    y_ = rhs.y_;
    return *this;
}

inline KPointF &KPointF::operator+=(const KPointF &rhs)
{
    x_ += rhs.x_;
    y_ += rhs.y_;
    return *this;
}

inline KPointF &KPointF::operator-=(const KPointF &rhs)
{
    x_ -= rhs.x_;
    y_ -= rhs.y_;
    return *this;
}

inline KPointF &KPointF::operator*=(double factor)
{
    x_ *= factor;
    y_ *= factor;
    return *this;
}

inline KPointF &KPointF::operator/=(double divisor)
{
    x_ /= divisor;
    y_ /= divisor;
    return *this;
}

inline KPointF operator-(const KPointF &point)
{
    return KPointF(-point.x(), -point.y());
}

#endif // KPOINTF_H
