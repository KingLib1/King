#include "ksquare3d.h"

KSquare3D::KSquare3D() : side_len_(0)
{

}

KSquare3D::KSquare3D(double side_length) : side_len_(side_length)
{

}

KSquare3D::KSquare3D(const KRectCoordSystem3D &sys, double side_length) :
    sys_(sys), side_len_(side_length)
{

}

KPair<KTriangle3D, KTriangle3D> KSquare3D::triangles() const
{
    double half = side_len_ / 2;
    KVector3D dh = sys_.xAxis() * half;
    KVector3D dv = sys_.yAxis() * half;
    KPair<KTriangle3D, KTriangle3D> pair;
    KTriangle3D tri;
    tri.setP1(sys_.origin() - dh + dv);
    tri.setP2(sys_.origin() - dh - dv);
    tri.setP3(sys_.origin() + dh + dv);
    pair.first = tri;
    tri.setP1(tri.p3());
    tri.setP3(sys_.origin() + dh - dv);
    pair.second = tri;
    return pair;
}
