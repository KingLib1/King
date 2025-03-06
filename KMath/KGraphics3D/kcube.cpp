#include "kcube.h"

KCube::KCube(double side_length) : side_length_(side_length)
{

}

KCube::KCube(const KVector3D &center, double side_length) :
    center_(center), side_length_(side_length)
{

}

bool KCube::intersects(const KCube &other) const
{
    double half1 = side_length_ / 2;
    double half2 = other.side_length_ / 2;
    if (other.center_.x() - half2 > center_.x() + half1)
        return false;
    if (other.center_.y() - half2 > center_.y() + half1)
        return false;
    if (other.center_.z() - half2 > center_.z() + half1)
        return false;
    if (other.center_.x() + half2 < center_.x() - half1)
        return false;
    if (other.center_.y() + half2 < center_.y() - half1)
        return false;
    if (other.center_.z() + half2 < center_.z() - half1)
        return false;
    return true;
}

KVector3D KCube::min() const
{
    double half = side_length_ / 2;
    return KVector3D(center_.x() - half,
                     center_.y() - half,
                     center_.z() - half);
}

KVector3D KCube::max() const
{
    double half = side_length_ / 2;
    return KVector3D(center_.x() + half,
                     center_.y() + half,
                     center_.z() + half);
}

QVector<KTriangle3D> KCube::triangulate() const
{
    QVector<KTriangle3D> tris;
    double half = side_length_ / 2;
    KVector3D min(center_.x() - half, center_.y() - half, center_.z() - half);
    KVector3D max(center_.x() + half, center_.y() + half, center_.z() + half);
    KTriangle3D tri1, tri2;

    tri1.setP1(min);
    tri1.setP2(min.translatedX(side_length_));
    tri1.setP3(tri1.p2().translatedZ(side_length_));
    tris << tri1;

    tri2.setP1(tri1.p2().translatedY(side_length_));
    tri2.setP2(tri1.p1().translatedY(side_length_));
    tri2.setP3(tri1.p3().translatedY(side_length_));
    tris << tri2;

    tri1.setP2(tri1.p3());
    tri1.setP3(tri1.p1().translatedZ(side_length_));
    tris << tri1;

    tri2.setP1(tri2.p3());
    tri2.setP3(tri1.p3().translatedY(side_length_));
    tris << tri2;

    tri1.setP2(tri1.p1());
    tri1.setP1(tri2.p2());
    tris << tri1;

    tri2.setP1(tri1.p2().translatedX(side_length_));
    tri2.setP2(tri1.p1().translatedX(side_length_));
    tri2.setP3(tri1.p3().translatedX(side_length_));
    tris << tri2;

    tri1.setP2(tri1.p3());
    tri1.setP3(tri1.p1().translatedZ(side_length_));
    tris << tri1;

    tri2.setP1(tri2.p3());
    tri2.setP3(tri1.p3().translatedX(side_length_));
    tris << tri2;

    tri1.setP1(tri1.p3());
    tri1.setP3(tri1.p2().translatedX(side_length_));
    tris << tri1;

    tri2.setP1(tri1.p2().translatedZ(-side_length_));
    tri2.setP2(tri1.p1().translatedZ(-side_length_));
    tri2.setP3(tri1.p3().translatedZ(-side_length_));
    tris << tri2;

    tri1.setP2(tri1.p3());
    tri1.setP3(tri1.p1().translatedX(side_length_));
    tris << tri1;

    tri2.setP1(tri2.p3());
    tri2.setP3(tri1.p3().translatedZ(-side_length_));
    tris << tri2;

    return tris;
}

QVector<KCube> KCube::octuple() const
{
    QVector<KCube> cubes;
    double half = side_length_ / 2;
    double quar = side_length_ / 4;

    KCube cube(center_.translated(quar, quar, quar), half);
    cubes << cube;

    cube.translateX(-half);
    cubes << cube;

    cube.translateY(-half);
    cubes << cube;

    cube.translateX(half);
    cubes << cube;

    cube.translateY(half);
    cube.translateZ(-half);
    cubes << cube;

    cube.translateX(-half);
    cubes << cube;

    cube.translateY(-half);
    cubes << cube;

    cube.translateX(half);
    cubes << cube;

    return cubes;
}
