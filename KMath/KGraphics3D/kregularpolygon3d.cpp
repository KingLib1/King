#include "kregularpolygon3d.h"

#include <QVector>

#include "KEquation.h"

KRegularPolygon3D::KRegularPolygon3D() : radius_(1), sides_(3)
{

}

KRegularPolygon3D::KRegularPolygon3D(const KRegularPolygon3D &polygon) :
    radius_(polygon.radius_), sides_(polygon.sides_), sys_(polygon.sys_)
{

}

KRegularPolygon3D::~KRegularPolygon3D()
{

}

void KRegularPolygon3D::setXYAxis(const KVector3D &xaxis,
                                  const KVector3D &yaxis)
{
    sys_.setXYAxis(xaxis, yaxis);
}

void KRegularPolygon3D::setZXAxis(const KVector3D &zaxis, const KVector3D &xaxis)
{
    sys_.setZXAxis(zaxis, xaxis);
}

void KRegularPolygon3D::rotateZBySelf(double angle)
{
    sys_.rotateZBySelf(angle);
}

QVector<KVector3D> KRegularPolygon3D::vertexes() const
{
    QVector<KVector3D> points;
    double per = K_2PI / sides_;
    int mid = sides_ >> 1;
    double r = per;
    QVector<KPointF> vertex2d;
    KPointF p2d(radius_, 0);
    vertex2d << p2d;

    if (sides_ % 2 == 0) {
        for (int i = 1; i < mid; ++i) {
            p2d.setXY(radius_ * kCos(r), radius_ * kSin(r));
            vertex2d << p2d;
            r += per;
        }
        for (int i = 0; i < mid; ++i) {
            vertex2d << -vertex2d.at(i);
        }
    } else {
        for (int i = 0; i < mid; ++i) {
            p2d.setXY(radius_ * kCos(r), radius_ * kSin(r));
            vertex2d << p2d;
            r += per;
        }
        for (int i = mid; i > 0; --i) {
            vertex2d << vertex2d.at(i).xAxisSymmetry();
        }
    }

    for (int i = 0; i < sides_; ++i) {
        p2d = vertex2d.at(i);
        points << p2d.x() * xAxis() + p2d.y() * yAxis() + center();
    }
    return points;
}

KCircle3D KRegularPolygon3D::circumcircle() const
{
    KCircle3D  circle;
    circle.setCenter(center());
    circle.setRadius(radius_);
    circle.setXYAxis(xAxis(), yAxis());
    return circle;
}

KCircle3D KRegularPolygon3D::incircle() const
{
    KCircle3D circle;
    circle.setCenter(center());
    circle.setRadius(apothem());
    circle.setXYAxis(xAxis(), yAxis());
    return circle;
}

bool KRegularPolygon3D::intersects(const KRay3D &ray) const
{
    double dot = KVector3D::dotProduct(ray.direction(), normal());
    if (isZero(dot))
        return false;
    double t = KVector3D::dotProduct(center() - ray.origin(), normal()) / dot;
    if (t < 0 || (ray.length() > 0 && t > ray.length()))
        return false;
    KVector3D p = ray.origin() + ray.direction() * t;
    KVector2D v1(xAxis());
    KVector2D v2(yAxis());
    KVector2D v3(p.x() - center().x(), p.y() - center().y());
    KVector2D xy = solveHomogeneousLinearEquations2x2(v1, v2, v3);
    if (xy.lengthSquared() > kSquare(radius_))
        return false;

    double per = K_2PI / sides_;
    int mid = sides_ >> 1;
    double r = per;
    QVector<KPointF> vertex2d;
    KPointF p2d(radius_, 0);
    vertex2d << p2d;

    if (sides_ % 2 == 0) {
        for (int i = 1; i < mid; ++i) {
            p2d.setXY(radius_ * kCos(r), radius_ * kSin(r));
            vertex2d << p2d;
            r += per;
        }
        for (int i = 0; i < mid; ++i) {
            vertex2d << -vertex2d.at(i);
        }
    } else {
        for (int i = 0; i < mid; ++i) {
            p2d.setXY(radius_ * kCos(r), radius_ * kSin(r));
            vertex2d << p2d;
            r += per;
        }
        for (int i = mid; i > 0; --i) {
            vertex2d << vertex2d.at(i).xAxisSymmetry();
        }
    }

    dot = KVector2D::crossProduct(KVector2D(vertex2d.at(0), vertex2d.at(1)),
                                  xy - vertex2d.at(0));
    int last = vertex2d.size() - 1;
    int i = 1;
    if (dot >= 0) {
        for (; i < last; ++i) {
            if (KVector2D::crossProduct(
                        KVector2D(vertex2d.at(i), vertex2d.at(i + 1)),
                        xy - vertex2d.at(i)) < 0)
                break;
        }
        if (i == last) {
            if (KVector2D::crossProduct(
                        KVector2D(vertex2d.at(last), vertex2d.at(0)),
                        xy - vertex2d.at(last)) >= 0)
                return true;
        }
    }
    if (dot <= 0) {
        i = 1;
        for (; i < last; ++i) {
            if (KVector2D::crossProduct(
                        KVector2D(vertex2d.at(i), vertex2d.at(i + 1)),
                        xy - vertex2d.at(i)) > 0)
                break;
        }
        if (i == last) {
            if (KVector2D::crossProduct(
                        KVector2D(vertex2d.at(last), vertex2d.at(0)),
                        xy - vertex2d.at(last)) <= 0)
                return true;
        }
    }
    return false;
}

KVector3D KRegularPolygon3D::intersection(const KRay3D &ray, bool *success) const
{
    double dot = KVector3D::dotProduct(ray.direction(), normal());
    if (isZero(dot)) {
        if (success)
            *success = false;
        return KVector3D();
    }
    double t = KVector3D::dotProduct(center() - ray.origin(), normal()) / dot;
    if (t < 0 || (ray.length() > 0 && t > ray.length())) {
        if (success)
            *success = false;
        return KVector3D();
    }
    KVector3D p = ray.origin() + ray.direction() * t;
    KVector2D v1(xAxis());
    KVector2D v2(yAxis());
    KVector2D v3(p.x() - center().x(), p.y() - center().y());
    KVector2D xy = solveHomogeneousLinearEquations2x2(v1, v2, v3);
    if (xy.lengthSquared() > kSquare(radius_)) {
        if (success)
            *success = false;
        return KVector3D();
    }

    double per = K_2PI / sides_;
    int mid = sides_ >> 1;
    double r = per;
    QVector<KPointF> vertex2d;
    KPointF p2d(radius_, 0);
    vertex2d << p2d;

    if (sides_ % 2 == 0) {
        for (int i = 1; i < mid; ++i) {
            p2d.setXY(radius_ * kCos(r), radius_ * kSin(r));
            vertex2d << p2d;
            r += per;
        }
        for (int i = 0; i < mid; ++i) {
            vertex2d << -vertex2d.at(i);
        }
    } else {
        for (int i = 0; i < mid; ++i) {
            p2d.setXY(radius_ * kCos(r), radius_ * kSin(r));
            vertex2d << p2d;
            r += per;
        }
        for (int i = mid; i > 0; --i) {
            vertex2d << vertex2d.at(i).xAxisSymmetry();
        }
    }

    dot = KVector2D::crossProduct(KVector2D(vertex2d.at(0), vertex2d.at(1)),
                                  xy - vertex2d.at(0));
    int last = vertex2d.size() - 1;
    int i = 1;
    if (dot >= 0) {
        for (; i < last; ++i) {
            if (KVector2D::crossProduct(
                        KVector2D(vertex2d.at(i), vertex2d.at(i + 1)),
                        xy - vertex2d.at(i)) < 0)
                break;
        }
        if (i == last) {
            if (KVector2D::crossProduct(
                        KVector2D(vertex2d.at(last), vertex2d.at(0)),
                        xy - vertex2d.at(last)) >= 0) {
                if (success)
                    *success = true;
                return p;
            }
        }
    }
    if (dot <= 0) {
        i = 1;
        for (; i < last; ++i) {
            if (KVector2D::crossProduct(
                        KVector2D(vertex2d.at(i), vertex2d.at(i + 1)),
                        xy - vertex2d.at(i)) > 0)
                break;
        }
        if (i == last) {
            if (KVector2D::crossProduct(
                        KVector2D(vertex2d.at(last), vertex2d.at(0)),
                        xy - vertex2d.at(last)) <= 0) {
                if (success)
                    *success = true;
                return p;
            }
        }
    }

    if (success)
        *success = false;
    return KVector3D();
}
