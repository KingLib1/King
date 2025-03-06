#ifndef KREGULARPOLYGON_H
#define KREGULARPOLYGON_H

#include <QVector>

#include "kvector2d.h"
#include "kcircle2d.h"

class KING_EXPORT KRegularPolygon
{
public:
    KRegularPolygon();
    KRegularPolygon(const KPointF &center, double radius, int sides_count,
                    const KVector2D &xaxis = KVector2D(1, 0));
    KRegularPolygon(const KRegularPolygon &polygon);
    inline void setCenter(const KPointF &center);
    inline void setRadius(double radius);
    inline void setSideCount(int count);
    inline void setXAxis(const KVector2D &xaxis);
    inline void translate(const KVector2D &dv);
    inline void translate(double dx, double dy);

    inline const KPointF &center() const;
    inline double radius() const {return radius_;}
    inline double sideCount() const {return sides_;}
    inline const KVector2D &xaxis() const;
    inline double sideLength() const;
    inline double interiorAngle() const; // 内角角度
    inline double interiorRadian() const; // 内角弧度
    inline double apothem() const; // 边心距
    inline double centralAngle() const; // 中心角角度
    inline double centralRadian() const; // 中心角弧度
    inline double exteriorAngle() const; // 外角角度
    inline double exteriorRadian() const; //外角弧度
    inline KCircle2D circumcircle() const; // 外接圆
    inline KCircle2D incircle() const; // 内切圆
    inline double area() const;
    inline double perimeter() const;
    inline KRegularPolygon translated(const KVector2D &dv);
    inline KRegularPolygon translated(double dx, double dy);

    void vertex(QVector<KPointF> &points) const;

    KRegularPolygon &operator=(const KRegularPolygon &polygon);

private:
    KPointF center_;
    double radius_;  // 半径（中心到顶点距离）
    int sides_;      // 边数
    KVector2D xaxis_;
};

inline void KRegularPolygon::setCenter(const KPointF &center)
{
    center_ = center;
}

inline void KRegularPolygon::setRadius(double radius)
{
    radius_ = radius;
}

inline void KRegularPolygon::setSideCount(int count)
{
    sides_ = count;
}

inline void KRegularPolygon::setXAxis(const KVector2D &xaxis)
{
    xaxis_ = xaxis;
}

inline void KRegularPolygon::translate(const KVector2D &dv)
{
    center_.translate(dv.x(), dv.y());
}

inline void KRegularPolygon::translate(double dx, double dy)
{
    center_.translate(dx, dy);
}

inline const KPointF &KRegularPolygon::center() const
{
    return center_;
}

inline const KVector2D &KRegularPolygon::xaxis() const
{
    return xaxis_;
}

inline double KRegularPolygon::sideLength() const
{
    return 2 * radius_ * kSin(K_PI / sides_);
}

inline double KRegularPolygon::interiorAngle() const
{
    return 180 - 360.0 / sides_;
}

inline double KRegularPolygon::interiorRadian() const
{
    return K_PI - K_2PI / sides_;
}

inline double KRegularPolygon::apothem() const
{
    return radius_ * kCos(K_PI / sides_);
}

inline double KRegularPolygon::centralAngle() const
{
    return 360.0 / sides_;
}

inline double KRegularPolygon::centralRadian() const
{
    return K_2PI / sides_;
}

inline double KRegularPolygon::exteriorAngle() const
{
    return 360.0 / sides_;
}

inline double KRegularPolygon::exteriorRadian() const
{
    return K_2PI / sides_;
}

inline KCircle2D KRegularPolygon::circumcircle() const
{
    return KCircle2D(center_, radius_);
}

inline KCircle2D KRegularPolygon::incircle() const
{
    return KCircle2D(center_, apothem());
}

inline double KRegularPolygon::area() const
{
    return 0.5 * radius_ * radius_ * sides_ * kSin(K_2PI / sides_);
}

inline double KRegularPolygon::perimeter() const
{
    return sides_ * sideLength();
}

inline KRegularPolygon KRegularPolygon::translated(const KVector2D &dv)
{
    KRegularPolygon polygon(*this);
    polygon.center_.translate(dv.x(), dv.y());
    return polygon;
}

inline KRegularPolygon KRegularPolygon::translated(double dx, double dy)
{
    KRegularPolygon polygon(*this);
    polygon.center_.translate(dx, dy);
    return polygon;
}

#endif // KREGULARPOLYGON_H
