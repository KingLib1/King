#include "krect2d.h"

KRect2D::KRect2D() : width_(0), height_(0)
{

}

KRect2D::KRect2D(const KPointF &pos, double width, double height) :
    width_(width), height_(height)
{
    sys_.setOrigin(pos);
}

void KRect2D::setPos(const KPointF &pos)
{
    sys_.setOrigin(pos);
}

void KRect2D::setRotation(double angle)
{
    KVector2D xaxis(1, 0);
    xaxis.rotate(angle);
    sys_.setXAxis(xaxis);
}

KPointF KRect2D::pos() const
{
    return sys_.origin().toPointF();
}

KPointF KRect2D::topLeft() const
{
    KPointF pos = sys_.origin().toPointF();
    double dx = -width_ / 2;
    double dy = height_ / 2;
    pos += sys_.xAxis() * dx + sys_.yAxis() * dy;
    return pos;
}

KPointF KRect2D::topRight() const
{
    KPointF pos = sys_.origin().toPointF();
    double dx = width_ / 2;
    double dy = height_ / 2;
    pos += sys_.xAxis() * dx + sys_.yAxis() * dy;
    return pos;
}

KPointF KRect2D::bottomLeft() const
{
    KPointF pos = sys_.origin().toPointF();
    double dx = -width_ / 2;
    double dy = -height_ / 2;
    pos += sys_.xAxis() * dx + sys_.yAxis() * dy;
    return pos;
}

KPointF KRect2D::bottomRight() const
{
    KPointF pos = sys_.origin().toPointF();
    double dx = width_ / 2;
    double dy = -height_ / 2;
    pos += sys_.xAxis() * dx + sys_.yAxis() * dy;
    return pos;
}

bool KRect2D::contains(const KPointF &p) const
{
    KVector2D map = sys_.mapFromBase(p);
    double hwidth = width_ / 2;
    double hheight = height_ / 2;
    if (map.x() > hwidth || map.x() < -hwidth)
        return false;
    if (map.y() > hheight || map.y() < -hheight)
        return false;
    return true;
}
