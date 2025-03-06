#ifndef KRECT_H
#define KRECT_H

#include "ksizef.h"
#include "krange.h"
#include "klinesegment2d.h"

class KING_EXPORT KRect
{
public:
    KRect();
    KRect(const KPointF &bottomleft, const KPointF &topright);
    KRect(double left, double bottom, double width, double height);
    KRect(const KRect &rect);
    ~KRect();

    inline double left() const {return left_;}
    inline double right() const {return right_;}
    inline double top() const {return top_;}
    inline double bottom() const {return bottom_;}
    inline double width() const {return right_ - left_;}
    inline double height() const {return top_ - bottom_;}
    inline double centerX() const {return (left_ + right_) * 0.5;}
    inline double centerY() const {return (top_ + bottom_) * 0.5;}

    inline void setLeft(double left) {left_ = left;}
    inline void setTop(double top) {top_ = top;}
    inline void setRight(double right) {right_ = right;}
    inline void setBottom(double bottom) {bottom_ = bottom;}
    inline void setWidth(double width) {right_ = left_ + width;}
    inline void setHeight(double height) {top_ = bottom_ + height;}
    inline void translate(double dx, double dy);
    inline void translate(const KPointF &dv);

    inline KPointF topLeft() const {return KPointF(left_, top_);}
    inline KPointF topRight() const {return KPointF(right_, top_);}
    inline KPointF bottomLeft() const {return KPointF(left_, bottom_);}
    inline KPointF bottomRight() const {return KPointF(right_, bottom_);}
    inline KPointF center() const;
    inline KSizeF size() const;
    inline KRange xRange() const;
    inline KRange yRange() const;
    inline KLineSegment2D topLeftToBottomRight() const;
    inline KLineSegment2D topRightToBottomLeft() const;

    inline bool contains(const KPointF &point) const;
    inline bool contains(double x, double y) const;
    inline bool contains(const KRect &rectangle) const;
    inline bool contains(const KLineSegment2D &line) const;
    inline bool isValid() const;
    /**
     * @brief 判断是否相交
     */
    inline bool intersects(const KRect &rectangle) const;
    bool intersects(const KLineSegment2D &line) const;
    /**
     * @brief 返回相交部分的矩形
     */
    KRect intersected(const KRect &rectangle) const;
    /**
     * @brief 返回两矩形的边界矩形
     */
    KRect united(const KRect &rectangle) const;

    void normalize();

    inline KRect &operator=(const KRect &rect);

private:
    double left_ = 0;
    double bottom_ = 0;
    double right_ = 0;
    double top_ = 0;
};

inline KPointF KRect::center() const
{
    return KPointF((left_ + right_) * 0.5, (top_ + bottom_) * 0.5);
}

inline KSizeF KRect::size() const
{
    return KSizeF(width(), height());
}

inline KRange KRect::xRange() const
{
    return KRange(left_, right_);
}

inline KRange KRect::yRange() const
{
    return KRange(bottom_, top_);
}

inline KLineSegment2D KRect::topLeftToBottomRight() const
{
    return KLineSegment2D(left_, top_, right_, bottom_);
}

inline KLineSegment2D KRect::topRightToBottomLeft() const
{
    return KLineSegment2D(right_, top_, left_, bottom_);
}

inline bool KRect::contains(const KPointF &point) const
{
    return left_ <= point.x() && right_ >= point.x() &&
            bottom_ <= point.y() && top_ >= point.y();
}

inline bool KRect::contains(double x, double y) const
{
    return left_ <= x && right_ >= x && bottom_ <= y && top_ >= y;
}

inline bool KRect::contains(const KRect &rectangle) const
{
    return left_ <= rectangle.left_ && right_ >= rectangle.right_ &&
            top_ >= rectangle.top_ && bottom_ <= rectangle.bottom_;
}

inline bool KRect::contains(const KLineSegment2D &line) const
{
    return contains(line.p1()) && contains(line.p2());
}

inline void KRect::translate(double dx, double dy)
{
    left_ += dx;
    right_ += dx;
    top_ += dy;
    bottom_ += dy;
}

inline void KRect::translate(const KPointF &dv)
{
    left_ += dv.x();
    right_ += dv.x();
    top_ += dv.y();
    bottom_ += dv.y();
}

inline bool KRect::isValid() const
{
    return right_ > left_ && top_ > bottom_;
}

inline bool KRect::intersects(const KRect &rectangle) const
{
    if (left_ > rectangle.right_ || right_ < rectangle.left_ ||
            top_ < rectangle.bottom_ || bottom_ > rectangle.top_)
        return false;
    return true;
}

inline KRect &KRect::operator=(const KRect &rect)
{
    left_ = rect.left_;
    bottom_ = rect.bottom_;
    right_ = rect.right_;
    top_ = rect.top_;
    return *this;
}

#endif // KRECT_H
