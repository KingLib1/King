#ifndef KRECT2D_H
#define KRECT2D_H

#include "krectcoordsystem2d.h"

class KING_EXPORT KRect2D
{
public:
    KRect2D();
    KRect2D(const KPointF &pos, double width, double height);

    void setPos(const KPointF &pos);
    void setRotation(double angle); // 以绝对值绕自身中心点旋转到angle角
    inline void setWidth(double width);
    inline void setHeight(double height);

    KPointF pos() const;
    double width() const {return width_;}
    double height() const {return height_;}

    KPointF topLeft() const;
    KPointF topRight() const;
    KPointF bottomLeft() const;
    KPointF bottomRight() const;

    bool contains(const KPointF &p) const;

private:
    KRectCoordSystem2D sys_;
    double width_;
    double height_;
};

inline void KRect2D::setWidth(double width)
{
    width_ = width;
}

inline void KRect2D::setHeight(double height)
{
    height_ = height;
}

#endif // KRECT2D_H
