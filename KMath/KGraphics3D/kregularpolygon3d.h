#ifndef KREGULARPOLYGON3D_H
#define KREGULARPOLYGON3D_H

#include "kcircle3d.h"
#include "krectcoordsystem3d.h"
#include "kray3d.h"
#include "kpolygon3d.h"

class KING_EXPORT KRegularPolygon3D
{
public:
    KRegularPolygon3D();
    KRegularPolygon3D(const KRegularPolygon3D &polygon);
    ~KRegularPolygon3D();

    inline void setCenter(const KVector3D &center);
    inline void setRadius(double radius);
    inline void setSidesCount(int count);
    void setXYAxis(const KVector3D &xaxis, const KVector3D &yaxis);
    void setZXAxis(const KVector3D &zaxis, const KVector3D &xaxis);
    inline void translate(const KVector3D &dv);
    inline void translate(double dx, double dy, double dz);
    void rotateZBySelf(double angle);

    inline const KVector3D &center() const;
    inline double radius() const;
    inline int sidesCount() const;
    inline double sideLength() const;
    inline double interiorAngle() const; // 内角角度
    inline double interiorRadian() const; // 内角弧度
    inline double apothem() const; // 边心距
    inline double centralAngle() const; // 中心角角度
    inline double centralRadian() const; // 中心角弧度
    inline double exteriorAngle() const; // 外角角度
    inline double exteriorRadian() const; //外角弧度
    inline const KVector3D &xAxis() const;
    inline const KVector3D &yAxis() const;
    inline KVector3D normal() const;
    inline KRegularPolygon3D translated(const KVector3D &dv) const;
    inline KRegularPolygon3D translated(double dx, double dy, double dz) const;
    KCircle3D circumcircle() const; // 外接圆
    KCircle3D incircle() const; // 内切圆
    inline double area() const;
    inline double perimeter() const;
    bool intersects(const KRay3D &ray) const;
    KVector3D intersection(const KRay3D &ray, bool *success = nullptr) const;

    QVector<KVector3D> vertexes() const;
    inline KPolygon3D toPolygon() const;
    inline QVector<KLineSegment3D> toLineSegment() const;

    inline KRegularPolygon3D &operator=(const KRegularPolygon3D &polygon);

private:
    double radius_;
    int sides_;
    KRectCoordSystem3D sys_;
};

inline void KRegularPolygon3D::setCenter(const KVector3D &center)
{
    sys_.setOrigin(center);
}

inline void KRegularPolygon3D::setRadius(double radius)
{
    radius_ = radius;
}

inline void KRegularPolygon3D::setSidesCount(int count)
{
    sides_ = count;
}

inline void KRegularPolygon3D::translate(const KVector3D &dv)
{
    sys_.translateByBase(dv);
}

inline void KRegularPolygon3D::translate(double dx, double dy, double dz)
{
    sys_.translateByBase(dx, dy, dz);
}

inline const KVector3D &KRegularPolygon3D::center() const
{
    return sys_.origin();
}

inline double KRegularPolygon3D::radius() const
{
    return radius_;
}

inline int KRegularPolygon3D::sidesCount() const
{
    return sides_;
}

inline double KRegularPolygon3D::sideLength() const
{
    return 2 * radius_ * kSin(K_PI / sides_);
}

inline double KRegularPolygon3D::interiorAngle() const
{
    return 180 - 360.0 / sides_;
}

inline double KRegularPolygon3D::interiorRadian() const
{
    return K_PI - K_2PI / sides_;
}

inline double KRegularPolygon3D::apothem() const
{
    return radius_ * kCos(K_PI / sides_);
}

inline double KRegularPolygon3D::centralAngle() const
{
    return 360.0 / sides_;
}

inline double KRegularPolygon3D::centralRadian() const
{
    return K_2PI / sides_;
}

inline double KRegularPolygon3D::exteriorAngle() const
{
    return 360.0 / sides_;
}

inline double KRegularPolygon3D::exteriorRadian() const
{
    return K_2PI / sides_;
}

inline const KVector3D &KRegularPolygon3D::xAxis() const
{
    return sys_.xAxis();
}

inline const KVector3D &KRegularPolygon3D::yAxis() const
{
    return sys_.yAxis();
}

inline KVector3D KRegularPolygon3D::normal() const
{
    return sys_.zAxis();
}

inline KRegularPolygon3D KRegularPolygon3D::translated(const KVector3D &dv) const
{
    KRegularPolygon3D polygon(*this);
    polygon.sys_.translateByBase(dv);
    return polygon;
}

inline KRegularPolygon3D KRegularPolygon3D::translated(
        double dx, double dy, double dz) const
{
    KRegularPolygon3D polygon(*this);
    polygon.sys_.translateByBase(dx, dy, dz);
    return polygon;
}

inline double KRegularPolygon3D::area() const
{
    return 0.5 * radius_ * radius_ * sides_ * kSin(K_2PI / sides_);
}

inline double KRegularPolygon3D::perimeter() const
{
    return sides_ * sideLength();
}

inline KPolygon3D KRegularPolygon3D::toPolygon() const
{
    return KPolygon3D(vertexes());
}

inline QVector<KLineSegment3D> KRegularPolygon3D::toLineSegment() const
{
    return KPolygon3D(vertexes()).toLineSegment();
}

inline KRegularPolygon3D &KRegularPolygon3D::operator=(
        const KRegularPolygon3D &polygon)
{
    radius_ = polygon.radius_;
    sides_ = polygon.sides_;
    sys_ = polygon.sys_;
    return *this;
}

#endif // KREGULARPOLYGON3D_H
