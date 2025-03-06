#include "krect.h"

#include "kmath.h"

KRect::KRect()
{

}

KRect::KRect(const KPointF &bottomleft, const KPointF &topright) :
    left_(bottomleft.x()), bottom_(bottomleft.y()), right_(topright.x()),
    top_(topright.y())
{

}

KRect::KRect(double left, double bottom, double width, double height) :
    left_(left), bottom_(bottom), right_(left + width), top_(bottom + height)
{

}

KRect::KRect(const KRect &rect) : left_(rect.left_), bottom_(rect.bottom_),
    right_(rect.right_), top_(rect.top_)
{

}

KRect::~KRect()
{

}

bool KRect::intersects(const KLineSegment2D &line) const
{
    if (contains(line.p1()) || contains(line.p2()))
        return true;
    KLineSegment2D line1(left_, top_, right_, bottom_);
    if (line.intersects(line1))
        return true;
    line1.setLine(left_, bottom_, right_, top_);
    return line.intersects(line1);
}

void KRect::normalize()
{
    if (left_ > right_) {
        double t = left_;
        left_ = right_;
        right_ = t;
    }
    if (top_ < bottom_) {
        double t = top_;
        top_ = bottom_;
        bottom_ = t;
    }
}

KRect KRect::intersected(const KRect &rectangle) const
{
    if (!intersects(rectangle))
        return KRect();

    KRect intersect;
    intersect.setTop(kMin(top_, rectangle.top_));
    intersect.setBottom(kMax(bottom_, rectangle.bottom_));
    intersect.setLeft(kMax(left_, rectangle.left_));
    intersect.setRight(kMin(right_, rectangle.right_));
    return intersect;
}

KRect KRect::united(const KRect &rectangle) const
{ 
    KRect unite;
    unite.setLeft(kMin(left_, rectangle.left_));
    unite.setRight(kMax(right_, rectangle.right_));
    unite.setTop(kMax(top_, rectangle.top_));
    unite.setBottom(kMin(bottom_, rectangle.bottom_));
    return unite;
}
