#ifndef KRECT3D_H
#define KRECT3D_H

#include "krect.h"
#include "kray3d.h"
#include "ksizef.h"
#include "krectcoordsystem3d.h"

class KING_EXPORT KRect3D
{
public:
    KRect3D();
    KRect3D(const KRect3D &rect);
    KRect3D(const KVector3D &center, double width, double height);
    KRect3D(const KVector3D &center, const KSizeF &size);
    KRect3D(const KRect &rect);
    ~KRect3D();

    inline void setWidth(double width);
    inline void setHeight(double height);
    inline void setSize(double width, double height);
    inline void setSize(const KSizeF &size);
    inline void setCenter(const KVector3D &center);
    inline void setXYAxis(const KVector3D &xaxis, const KVector3D &yaxis);
    inline void setZXAxis(const KVector3D &zaxis, const KVector3D &xaxis);
    inline void setYZAxis(const KVector3D &yaxis, const KVector3D &zaxis);
    inline void translate(const KVector3D &dv);
    inline void translate(double dx, double dy, double dz);

    inline double width() const;
    inline double height() const;
    inline KVector3D bottomLeft() const;
    inline KVector3D bottomRight() const;
    inline KVector3D topLeft() const;
    inline KVector3D topRight() const;
    inline const KVector3D &center() const;
    inline KLineSegment3D top() const;
    inline KLineSegment3D bottom() const;
    inline KLineSegment3D left() const;
    inline KLineSegment3D right() const;
    inline KRect3D translated(const KVector3D &dv) const;
    inline KRect3D translated(double dx, double dy, double dz) const;
    inline double perimeter() const;
    inline double area() const;
    inline const KVector3D &xAxis() const;
    inline const KVector3D &yAxis() const;
    inline const KVector3D &normal() const;
    inline const KSizeF &size() const;
    inline KMatrix4x4 matrix() const;
    bool intersects(const KRay3D &ray) const;
    KVector3D intersection(const KRay3D &ray, bool &intersects) const;

    inline KRect3D &operator=(const KRect3D &rect);

private:
    KSizeF size_;
    KRectCoordSystem3D sys_;
};

inline void KRect3D::setWidth(double width)
{
    size_.setWidth(width);
}

inline void KRect3D::setHeight(double height)
{
    size_.setHeight(height);
}

inline void KRect3D::setSize(double width, double height)
{
    size_.setWidth(width);
    size_.setHeight(height);
}

inline void KRect3D::setSize(const KSizeF &size)
{
    size_ = size;
}

inline void KRect3D::setCenter(const KVector3D &center)
{
    sys_.setOrigin(center);
}

inline void KRect3D::setXYAxis(const KVector3D &xaxis, const KVector3D &yaxis)
{
    sys_.setXYAxis(xaxis, yaxis);
}

inline void KRect3D::setZXAxis(const KVector3D &zaxis, const KVector3D &xaxis)
{
    sys_.setZXAxis(zaxis, xaxis);
}

inline void KRect3D::setYZAxis(const KVector3D &yaxis, const KVector3D &zaxis)
{
    sys_.setYZAxis(yaxis, zaxis);
}

inline void KRect3D::translate(const KVector3D &dv)
{
    sys_.translateByBase(dv);
}

inline void KRect3D::translate(double dx, double dy, double dz)
{
    sys_.translateByBase(dx, dy, dz);
}

inline double KRect3D::width() const
{
    return size_.width();
}

inline double KRect3D::height() const
{
    return size_.height();
}

inline KVector3D KRect3D::bottomLeft() const
{
    double x = -width() * 0.5;
    double y = -height() * 0.5;
    return x * xAxis() + y * yAxis() + center();
}

inline KVector3D KRect3D::bottomRight() const
{
    double x = width() * 0.5;
    double y = -height() * 0.5;
    return x * xAxis() + y * yAxis() + center();
}

inline KVector3D KRect3D::topLeft() const
{
    double x = -width() * 0.5;
    double y = height() * 0.5;
    return x * xAxis() + y * yAxis() + center();
}

inline KVector3D KRect3D::topRight() const
{
    double x = width() * 0.5;
    double y = height() * 0.5;
    return x * xAxis() + y * yAxis() + center();
}

inline const KVector3D &KRect3D::center() const
{
    return sys_.origin();
}

inline KLineSegment3D KRect3D::top() const
{
    KVector3D h = xAxis() * (width() / 2);
    KVector3D v = yAxis() * (height() / 2);
    KVector3D topcenter = center() + v;
    return KLineSegment3D(topcenter - h, topcenter + h);
}

inline KLineSegment3D KRect3D::bottom() const
{
    KVector3D h = xAxis() * (width() / 2);
    KVector3D v = yAxis() * (height() / 2);
    KVector3D bottomcenter = center() - v;
    return KLineSegment3D(bottomcenter - h, bottomcenter + h);
}

inline KLineSegment3D KRect3D::left() const
{
    KVector3D h = xAxis() * (width() / 2);
    KVector3D v = yAxis() * (height() / 2);
    KVector3D leftcenter = center() - h;
    return KLineSegment3D(leftcenter + v, leftcenter - v);
}

inline KLineSegment3D KRect3D::right() const
{
    KVector3D h = xAxis() * (width() / 2);
    KVector3D v = yAxis() * (height() / 2);
    KVector3D rightcenter = center() + h;
    return KLineSegment3D(rightcenter + v, rightcenter - v);
}

inline KRect3D KRect3D::translated(const KVector3D &dv) const
{
    KRect3D rect(*this);
    rect.sys_.translateByBase(dv);
    return rect;
}

inline KRect3D KRect3D::translated(double dx, double dy, double dz) const
{
    KRect3D rect(*this);
    rect.sys_.translateByBase(dx, dy, dz);
    return rect;
}

inline double KRect3D::perimeter() const
{
    return (width() + height()) * 2;
}

inline double KRect3D::area() const
{
    return size_.area();
}

inline const KVector3D &KRect3D::xAxis() const
{
    return sys_.xAxis();
}

inline const KVector3D &KRect3D::yAxis() const
{
    return sys_.yAxis();
}

inline const KVector3D &KRect3D::normal() const
{
    return sys_.zAxis();
}

inline const KSizeF &KRect3D::size() const
{
    return size_;
}

inline KMatrix4x4 KRect3D::matrix() const
{
    return sys_.toMatrix4x4();
}

inline KRect3D &KRect3D::operator=(const KRect3D &rect)
{
    size_ = rect.size_;
    sys_ = rect.sys_;
    return *this;
}

#endif // KRECT3D_H
