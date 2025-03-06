#include "karc3d.h"

#include <QDebug>

#include "KGraphics2D/klinesegment2d.h"
#include "KEquation.h"

KArc3D::KArc3D() : radius_(0), span_(0)
{

}

KArc3D::KArc3D(double radius, double span_angle, const KRectCoordSystem3D &sys)
    : radius_(radius), span_(kDegreesToRadians(span_angle)), sys_(sys)
{

}

KArc3D::KArc3D(const KArc2D &arc) : radius_(arc.radius()), span_(arc.spanRadian())
{   
    KVector3D center(arc.cx(), arc.cy());
    setCenter(center);
    KVector2D xaxis2d = arc.startVector();
    xaxis2d.normalize();
    KVector3D xaxis(xaxis2d.x(), xaxis2d.y());
    if (span_ < 0) {
        span_ = -span_;
        sys_.setZXAxis(-sys_.zAxis(), xaxis);
    } else {
        sys_.setZXAxis(sys_.zAxis(), xaxis);
    }
}

KArc3D::KArc3D(const KArc3D &arc) : radius_(arc.radius_), span_(arc.span_),
    sys_(arc.sys_)
{

}

KArc3D::KArc3D(const KVector3D &v1, const KVector3D &v2, const KVector3D &v3,
               King::ArcCreateMode mode)
{
    switch (mode) {
    case King::PointPointPoint : {
        KVector3D v12(v2 - v1);
        KVector3D v23(v3 - v2);
        KVector3D zaxis = KVector3D::crossProduct(v12, v23);
        if (zaxis.isNull()) {
            radius_ = 0;
            span_ = 0;
            return;
        }

        double b1 = v2.lengthSquared() - v1.lengthSquared();
        double b2 = v3.lengthSquared() - v2.lengthSquared();
        double b3 = KVector3D::dotProduct(zaxis, v2);
        KVector3D c1(2 * v12.x(), 2 * v23.x(), zaxis.x());
        KVector3D c2(2 * v12.y(), 2 * v23.y(), zaxis.y());
        KVector3D c3(2 * v12.z(), 2 * v23.z(), zaxis.z());
        KVector3D b(b1, b2, b3);
        sys_.setOrigin(solveHomogeneousLinearEquations3x3(c1, c2, c3, b));

        KVector3D xaxis = v1 - center();
        radius_ = xaxis.length();
        sys_.setZXAxis(zaxis, xaxis);

        KVector3D end = v3 - center();
        KVector2D xy = solveHomogeneousLinearEquations3x2(xAxis(), yAxis(), end);
        KLineSegment2D end_line(0, 0, xy.x(), xy.y());
        span_ = end_line.radian();
        break;
    }

    case King::TangentPointPoint : {
        KVector3D v23 = v3 - v2;
        KVector3D zaxis = KVector3D::crossProduct(v1, v23);
        if (zaxis.isNull()) {
            radius_ = 0;
            span_ = 0;
            return;
        }
        KVector3D v2o = KVector3D::crossProduct(zaxis, v1);
        double n = 0.5 * v23.lengthSquared() / KVector3D::dotProduct(v23, v2o);
        sys_.setXYAxis(-v2o, v1);
        v2o *= n;
        sys_.setOrigin(v2 + v2o);
        radius_ = v2o.length();

        KVector3D end = v3 - center();
        KVector2D xy = solveHomogeneousLinearEquations3x2(xAxis(), yAxis(), end);
        KLineSegment2D end_line(0, 0, xy.x(), xy.y());
        span_ = end_line.radian();
        break;
    }

    case King::PointPointTangent: {
        KVector3D v21 = v1 - v2;
        KVector3D zaxis = KVector3D::crossProduct(v3, v21);
        if (zaxis.isNull()) {
            radius_ = 0;
            span_ = 0;
            return;
        }
        KVector3D v2o = KVector3D::crossProduct(zaxis, v3);
        double n = 0.5 * v21.lengthSquared() / KVector3D::dotProduct(v21, v2o);
        v2o *= n;
        sys_.setOrigin(v2 + v2o);
        sys_.setZXAxis(zaxis, v1 - center());
        radius_ = v2o.length();

        KVector3D end = -v2o;
        KVector2D xy = solveHomogeneousLinearEquations3x2(xAxis(), yAxis(), end);
        KLineSegment2D end_line(0, 0, xy.x(), xy.y());
        span_ = end_line.radian();
        break;
    }
    }
}

QVector<KVector3D> KArc3D::splitToKVector3D(int slices) const
{
//    slices = int(slices * span_ / K_2PI);
    QVector<KVector3D> points;
    double rad = 0;
    double per_rad = span_ / slices;
    KVector3D p;
    for (int i = 0; i <= slices; ++i) {
        double x = radius_ * kCos(rad);
        double y = radius_ * kSin(rad);
        points << x * xAxis() + y * yAxis() + center();
        rad += per_rad;
    }
    return points;
}

KVector3D KArc3D::pos(double radian, bool &success)
{
    if (radian > span_ || radian < 0) {
        success = false;
        return KVector3D();
    }
    success = true;
    double x = radius_ * kCos(radian);
    double y = radius_ * kSin(radian);
    return x * xAxis() + y * yAxis() + center();
}
