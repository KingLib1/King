#ifndef KSIZEF_H
#define KSIZEF_H

#include "King.h"
#include "kmath.h"

class KING_EXPORT KSizeF
{
public:
    KSizeF();
    KSizeF(double width, double height);
    KSizeF(const KSizeF &size);
    inline double &rwidth() {return width_;}
    inline double &rheight() {return height_;}
    inline double width() const {return width_;}
    inline double height() const {return height_;}
    inline KSizeF boundedTo(const KSizeF &other) const;
    inline KSizeF expandedTo(const KSizeF &other) const;
    inline bool isEmpty() const; // <= 0
    inline bool isNull() const;  // == 0
    inline bool isValid() const; // >= 0
    inline void setWidth(double width) {width_ = width;}
    inline void setHeight(double height) {height_ = height;}
    inline void transpose();
    inline KSizeF transposed() const;
    void scale(double width, double height, King::AspectRatioMode mode);
    inline void scale(const KSizeF &size, King::AspectRatioMode mode);
    inline KSizeF scaled(double width, double height, King::AspectRatioMode mode) const;
    inline KSizeF scaled(const KSizeF &size, King::AspectRatioMode mode) const;
    inline double area() const;

    inline KSizeF &operator*=(double factor);
    inline KSizeF &operator/=(double divisor);
    inline KSizeF &operator+=(const KSizeF &size);
    inline KSizeF &operator-=(const KSizeF &size);
    inline KSizeF operator+(const KSizeF &size) const;
    inline KSizeF operator-(const KSizeF &size) const;
    inline KSizeF operator*(double factor) const;
    inline KSizeF operator/(double divisor) const;
    inline KSizeF &operator=(const KSizeF &size);
    inline bool operator==(const KSizeF &size) const;
    inline bool operator!=(const KSizeF &size) const;

private:
    double width_;
    double height_;
};

inline KSizeF KSizeF::boundedTo(const KSizeF &other) const
{
    return KSizeF(kMin(width_, other.width_),
                  kMin(height_, other.height_));
}

inline KSizeF KSizeF::expandedTo(const KSizeF &other) const
{
    return KSizeF(kMax(width_, other.width_),
                  kMax(height_, other.height_));
}

inline bool KSizeF::isEmpty() const
{
    return width_ < 1e-9 && height_ < 1e-9;
}

inline bool KSizeF::isNull() const
{
    return kFabs(width_) < 1e-9 && kFabs(height_) < 1e-9;
}

inline bool KSizeF::isValid() const
{
    return width_ >= 0 && height_ >= 0;
}

inline void KSizeF::transpose()
{
    double temp = width_;
    width_ = height_;
    height_ = temp;
}

inline KSizeF KSizeF::transposed() const
{
    return KSizeF(height_, width_);
}

inline void KSizeF::scale(const KSizeF &size, King::AspectRatioMode mode)
{
    scale(size.width_, size.height_, mode);
}

inline KSizeF KSizeF::scaled(double width, double height, King::AspectRatioMode mode) const
{
    KSizeF size(*this);
    size.scale(width, height, mode);
    return size;
}

inline KSizeF KSizeF::scaled(const KSizeF &size, King::AspectRatioMode mode) const
{
    return scaled(size.width_, size.height_, mode);
}

inline double KSizeF::area() const
{
    return width_ * height_;
}

inline KSizeF &KSizeF::operator*=(double factor)
{
    width_ *= factor;
    height_ *= factor;
    return *this;
}

inline KSizeF &KSizeF::operator/=(double divisor)
{
    width_ /= divisor;
    height_ /= divisor;
    return *this;
}

inline KSizeF &KSizeF::operator+=(const KSizeF &size)
{
    width_ += size.width_;
    height_ += size.height_;
    return *this;
}

inline KSizeF &KSizeF::operator-=(const KSizeF &size)
{
    width_ -= size.width_;
    height_ -= size.height_;
    return *this;
}

inline KSizeF KSizeF::operator+(const KSizeF &size) const
{
    return KSizeF(width_ + size.width_, height_ + size.height_);
}

inline KSizeF KSizeF::operator-(const KSizeF &size) const
{
    return KSizeF(width_ - size.width_, height_ - size.height_);
}

inline KSizeF KSizeF::operator*(double factor) const
{
    return KSizeF(width_ * factor, height_ * factor);
}

inline KSizeF KSizeF::operator/(double divisor) const
{
    return KSizeF(width_ / divisor, height_ / divisor);
}

inline KSizeF &KSizeF::operator=(const KSizeF &size)
{
    width_ = size.width_;
    height_ = size.height_;
    return *this;
}

inline bool KSizeF::operator==(const KSizeF &size) const
{
    return kFabs(width_ - size.width_) < 1e-9 &&
            kFabs(height_ - size.height_) < 1e-9;
}

inline bool KSizeF::operator!=(const KSizeF &size) const
{
    return !(*this == size);
}

#endif // KSIZEF_H
