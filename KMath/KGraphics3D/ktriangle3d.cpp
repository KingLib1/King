#include "ktriangle3d.h"

#include "KEquation.h"
#include "kplane3d_2.h"

KTriangle3D::KTriangle3D()
{

}

KTriangle3D::KTriangle3D(const KVector3D &p1, const KVector3D &p2,
                         const KVector3D &p3) : p1_(p1), p2_(p2), p3_(p3)
{

}

KTriangle3D::KTriangle3D(const KTriangle2D &triangle) : p1_(triangle.p1()),
    p2_(triangle.p2()), p3_(triangle.p3())
{

}

KTriangle3D::KTriangle3D(const KTriangle2D &triangle, double z) :
    p1_(triangle.p1(), z), p2_(triangle.p2(), z), p3_(triangle.p3(), z)
{

}

KTriangle3D::KTriangle3D(const KTriangle3D &triangle) : p1_(triangle.p1_),
    p2_(triangle.p2_), p3_(triangle.p3_)
{

}

KTriangle3D::~KTriangle3D()
{

}

double KTriangle3D::radian1() const
{
    KVector3D v12 = p2_ - p1_;
    KVector3D v13 = p3_ - p1_;
    KVector3D v23 = p3_ - p2_;
    return (v13.lengthSquared() + v12.lengthSquared() - v23.lengthSquared()) /
            (2 * v13.length() * v12.length());
}

double KTriangle3D::radian2() const
{
    KVector3D v12 = p2_ - p1_;
    KVector3D v13 = p3_ - p1_;
    KVector3D v23 = p3_ - p2_;
    return (v23.lengthSquared() + v12.lengthSquared() - v13.lengthSquared()) /
            (2 * v23.length() * v12.length());
}

double KTriangle3D::radian3() const
{
    KVector3D v12 = p2_ - p1_;
    KVector3D v13 = p3_ - p1_;
    KVector3D v23 = p3_ - p2_;
    return (v23.lengthSquared() + v13.lengthSquared() - v12.lengthSquared()) /
            (2 * v23.length() * v13.length());
}

KCuboid KTriangle3D::boundingCuboid() const
{
    double xmin = xMin();
    double xmax = xMax();
    double ymin = yMin();
    double ymax = yMax();
    double zmin = zMin();
    double zmax = zMax();
    KCuboid volume(xmax - xmin, ymax - ymin, zmax - zmin);
    volume.translateByBase((xmin + xmax) / 2,
                           (ymin + ymax) / 2,
                           (zmin + zmax) / 2);
    return volume;
}

KBoundingVolume KTriangle3D::boundingVolume() const
{
    return KBoundingVolume(xMin(), yMin(), zMin(), xMax(), yMax(), zMax());
}

bool KTriangle3D::intersects(const KLineSegment3D &line) const
{
    KVector3D n = normal();
    KVector3D l = line.toVector();
    double l_n = KVector3D::dotProduct(l, n);
    if (kFabs(l_n) < EPS6)
        return false;
    double t = KVector3D::dotProduct(p1_ - line.p1(), n) / l_n;
    if (t < 0 || t > 1)
        return false;
    KVector3D intersection = line.p1() + l * t;
    KVector2D v1_2(p2_.x() - p1_.x(), p2_.y() - p1_.y());
    KVector2D v1_3(p3_.x() - p1_.x(), p3_.y() - p1_.y());
    KVector2D v(intersection.x() - p1_.x(), intersection.y() - p1_.y());
    KVector2D t12 = solveHomogeneousLinearEquations2x2(v1_2, v1_3, v);
    if (t12.x() < 0 || t12.y() < 0 || t12.x() + t12.y() > 1)
        return false;
    return true;
}

bool KTriangle3D::intersects(const KRay3D &ray) const
{
    KVector3D n = normal();
    double dot = KVector3D::dotProduct(ray.direction(), n);
    if (kFabs(dot) < EPS9)
        return false;
    double t = KVector3D::dotProduct(p1_ - ray.origin(), n) / dot;
    if (t < 0 || (ray.length() > 0 && t > ray.length()))
        return false;
    KVector3D p = ray.origin() + ray.direction() * t;
    KVector2D v1_2(p2_.x() - p1_.x(), p2_.y() - p1_.y());
    KVector2D v1_3(p3_.x() - p1_.x(), p3_.y() - p1_.y());
    KVector2D v(p.x() - p1_.x(), p.y() - p1_.y());
    KVector2D t12 = solveHomogeneousLinearEquations2x2(v1_2, v1_3, v);
    if (t12.x() < 0 || t12.y() < 0 || t12.x() + t12.y() > 1)
        return false;
    return true;
}

bool KTriangle3D::intersects(const KTriangle3D &other) const
{
    KVector3D n = normal();
    KVector2D v1_2(p2_.x() - p1_.x(), p2_.y() - p1_.y());
    KVector2D v1_3(p3_.x() - p1_.x(), p3_.y() - p1_.y());

    KVector3D l = other.v12();
    double l_n = KVector3D::dotProduct(l, n);
    if (!isZero(l_n)) {
        double t = KVector3D::dotProduct(p1_ - other.p1_, n) / l_n;
        if (t >= 0 && t <= 1) {
            KVector3D intersection = other.p1_ + l * t;
            KVector2D v(intersection.x() - p1_.x(), intersection.y() - p1_.y());
            KVector2D t12 = solveHomogeneousLinearEquations2x2(v1_2, v1_3, v);
            if (t12.x() >= 0 && t12.y() >= 0 && t12.x() + t12.y() <= 1)
                return true;
        }
    }

    l = other.v13();
    l_n = KVector3D::dotProduct(l, n);
    if (!isZero(l_n)) {
        double t = KVector3D::dotProduct(p1_ - other.p1_, n) / l_n;
        if (t >= 0 && t <= 1) {
            KVector3D intersection = other.p1_ + l * t;
            KVector2D v(intersection.x() - p1_.x(), intersection.y() - p1_.y());
            KVector2D t12 = solveHomogeneousLinearEquations2x2(v1_2, v1_3, v);
            if (t12.x() >= 0 && t12.y() >= 0 && t12.x() + t12.y() <= 1)
                return true;
        }
    }

    l = other.v23();
    l_n = KVector3D::dotProduct(l, n);
    if (!isZero(l_n)) {
        double t = KVector3D::dotProduct(p1_ - other.p2_, n) / l_n;
        if (t >= 0 && t <= 1) {
            KVector3D intersection = other.p2_ + l * t;
            KVector2D v(intersection.x() - p1_.x(), intersection.y() - p1_.y());
            KVector2D t12 = solveHomogeneousLinearEquations2x2(v1_2, v1_3, v);
            if (t12.x() >= 0 && t12.y() >= 0 && t12.x() + t12.y() <= 1)
                return true;
        }
    }

    n = other.normal();
    v1_2.setXY(other.p2_.x() - other.p1_.x(), other.p2_.y() - other.p1_.y());
    v1_3.setXY(other.p3_.x() - other.p1_.x(), other.p3_.y() - other.p1_.y());

    l = v12();
    l_n = KVector3D::dotProduct(l, n);
    if (!isZero(l_n)) {
        double t = KVector3D::dotProduct(other.p1_ - p1_, n) / l_n;
        if (t >= 0 && t <= 1) {
            KVector3D intersection = p1_ + l * t;
            KVector2D v(intersection.x() - other.p1_.x(), intersection.y() - other.p1_.y());
            KVector2D t12 = solveHomogeneousLinearEquations2x2(v1_2, v1_3, v);
            if (t12.x() >= 0 && t12.y() >= 0 && t12.x() + t12.y() <= 1)
                return true;
        }
    }

    l = v13();
    l_n = KVector3D::dotProduct(l, n);
    if (!isZero(l_n)) {
        double t = KVector3D::dotProduct(other.p1_ - p1_, n) / l_n;
        if (t >= 0 && t <= 1) {
            KVector3D intersection = p1_ + l * t;
            KVector2D v(intersection.x() - other.p1_.x(), intersection.y() - other.p1_.y());
            KVector2D t12 = solveHomogeneousLinearEquations2x2(v1_2, v1_3, v);
            if (t12.x() >= 0 && t12.y() >= 0 && t12.x() + t12.y() <= 1)
                return true;
        }
    }

    l = v23();
    l_n = KVector3D::dotProduct(l, n);
    if (!isZero(l_n)) {
        double t = KVector3D::dotProduct(other.p1_ - p2_, n) / l_n;
        if (t >= 0 && t <= 1) {
            KVector3D intersection = p2_ + l * t;
            KVector2D v(intersection.x() - other.p1_.x(), intersection.y() - other.p1_.y());
            KVector2D t12 = solveHomogeneousLinearEquations2x2(v1_2, v1_3, v);
            if (t12.x() >= 0 && t12.y() >= 0 && t12.x() + t12.y() <= 1)
                return true;
        }
    }

    return false;
}

bool KTriangle3D::intersects_fast(const KTriangle3D &other) const
{
    KVector3D n1 = normal();
    double dot = KVector3D::dotProduct(other.p1_ - p1_, n1);
    int side1;
    if (dot > EPS6) side1 = 1;
    else if (dot < -EPS6) side1 = -1;
    else side1 = 0;

    dot = KVector3D::dotProduct(other.p2_ - p1_, n1);
    int side2;
    if (dot > EPS6) side2 = 1;
    else if (dot < -EPS6) side2 = -1;
    else side2 = 0;

    dot = KVector3D::dotProduct(other.p3_ - p1_, n1);
    int side3;
    if (dot > EPS6) side3 = 1;
    else if (dot < -EPS6) side3 = -1;
    else side3 = 0;

    int side = side1 + side2 + side3;
    if (side == 3 || side == -3)
        return false;

    KVector3D n2 = other.normal();
    dot = KVector3D::dotProduct(p1_ - other.p1_, n2);
    if (dot > EPS6) side1 = 1;
    else if (dot < -EPS6) side1 = -1;
    else side1 = 0;

    dot = KVector3D::dotProduct(p2_ - other.p1_, n2);
    if (dot > EPS6) side2 = 1;
    else if (dot < -EPS6) side2 = -1;
    else side2 = 0;

    dot = KVector3D::dotProduct(p3_ - other.p1_, n2);
    if (dot > EPS6) side3 = 1;
    else if (dot < -EPS6) side3 = -1;
    else side3 = 0;

    side = side1 + side2 + side3;
    if (side == 3 || side == -3)
        return false;

    KPlane3D_2 plane1(p1_, n1);
    KPlane3D_2 plane2(other.p1_, n2);
    KLine3D inter = plane1.intersected(plane2);


    return false;
}

KVector3D KTriangle3D::intersected(const KLineSegment3D &line, bool &success)
const
{
    KVector3D n = normal();
    KVector3D l = line.toVector();
    double l_n = KVector3D::dotProduct(l, n);
    if (kFabs(l_n) < EPS9) {
        success = false;
        return KVector3D();
    }
    double t = KVector3D::dotProduct(p1_ - line.p1(), n) / l_n;
    if (t < 0 || t > 1) {
        success = false;
        return KVector3D();
    }
    KVector3D intersection = line.p1() + l * t;
    KVector3D p12 = v12();
    KVector3D p13 = v13();
    KVector2D v1_2(p12.x(), p12.y());
    KVector2D v1_3(p13.x(), p13.y());
    KVector2D v(intersection.x() - p1_.x(), intersection.y() - p1_.y());
    KVector2D t12 = solveHomogeneousLinearEquations2x2(v1_2, v1_3, v);
    if (t12.x() < 0 || t12.y() < 0 || t12.x() + t12.y() > 1) {
        success = false;
        return KVector3D();
    }
    success = true;
    return line.p1() + l * t;
}

bool KTriangle3D::containsPoint(const KVector3D &point) const
{
    KVector3D n = normal();
    if (kFabs(KVector3D::dotProduct(n, point - p1_)) > EPS9)
        return false;
    KVector2D v1_2(p2_.x() - p1_.x(), p2_.y() - p1_.y());
    KVector2D v1_3(p3_.x() - p1_.x(), p3_.y() - p1_.y());
    KVector2D v(point.x() - p1_.x(), point.y() - p1_.y());
    KVector2D t12 = solveHomogeneousLinearEquations2x2(v1_2, v1_3, v);
    if (t12.x() < 0 || t12.y() < 0 || t12.x() + t12.y() > 1)
        return false;
    return true;
}

KPair<KTriangle3D, KTriangle3D> KTriangle3D::divide() const
{
    KPair<KTriangle3D, KTriangle3D> tris;
    double len1 = lengthSquared1();
    double len2 = lengthSquared2();
    double len3 = lengthSquared3();
    if (len1 > len2) {
        if (len1 > len3) {
            KTriangle3D t(p1_, p2_, KVector3D::midpoint(p2_, p3_));
            tris.first = t;
            t.setP2(t.p3());
            t.setP3(p3_);
            tris.second = t;
            return tris;
        }

        KTriangle3D t(p3_, p1_, KVector3D::midpoint(p1_, p2_));
        tris.first = t;
        t.setP2(t.p3());
        t.setP3(p2_);
        tris.second = t;
        return tris;
    }

    if (len2 > len3) {
        KTriangle3D t(p2_, p3_, KVector3D::midpoint(p3_, p1_));
        tris.first = t;
        t.setP2(t.p3());
        t.setP3(p1_);
        tris.second = t;
        return tris;
    }

    KTriangle3D t(p3_, p1_, KVector3D::midpoint(p1_, p2_));
    tris.first = t;
    t.setP2(t.p3());
    t.setP3(p2_);
    tris.second = t;
    return tris;
}
