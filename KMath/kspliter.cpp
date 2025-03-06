#include "kspliter.h"

#include "kcompatibly.h"
#include "KAlgorithm.h"

KSpliter::KSpliter()
{

}

QVector<double> KSpliter::split(double t0, double t, double dt)
{
    int n = (t - t0) / dt;
    QVector<double> v;
    v << t0;
    for (int i = 1; i <= n; ++i) {
        t0 += dt;
        v << t0;
    }
    if (!isEqual(t, v.last()))
        v << t;
    return v;
}

QVector<double> KSpliter::split(const KRange &range, double dt)
{
    return split(range.lower(), range.upper(), dt);
}

QVector<double> KSpliter::split(double t0, double t, int slices,
                                bool contain_first, bool contain_last)
{
    QVector<double> ts;
    if (contain_first)
        ts << t0;
    double dt = (t - t0) / slices;
    for (int i = 1; i < slices; ++i) {
        t0 += dt;
        ts << t0;
    }
    if (contain_last)
        ts << t;
    return ts;
}

QVector<KVector3D> KSpliter::split(KVector3D v0, KVector3D v, int slices,
                                   bool contain_first, bool contain_last)
{
    QVector<KVector3D> vs;
    if (contain_first)
        vs << v0;
    KVector3D dv = (v - v0) / slices;
    for (int i = 1; i < slices; ++i) {
        v0 += dv;
        vs << v0;
    }
    if (contain_last)
        vs << v;
    return vs;
}

QVector<KVector2D> KSpliter::split(KVector2D v0, KVector2D v, int slices,
                                   bool contain_first, bool contain_last)
{
    QVector<KVector2D> vs;
    if (contain_first)
        vs << v0;
    KVector2D dv = (v - v0) / slices;
    for (int i = 1; i < slices; ++i) {
        v0 += dv;
        vs << v0;
    }
    if (contain_last)
        vs << v;
    return vs;
}

QVector<KPointF> KSpliter::split(KPointF p0, KPointF p, int slices, bool contain_first, bool contain_last)
{
    QVector<KPointF> ps;
    if (contain_first)
        ps << p0;
    KPointF dv = (p - p0) / slices;
    for (int i = 1; i < slices; ++i) {
        p0 += dv;
        ps << p0;
    }
    if (contain_last)
        ps << p;
    return ps;
}

QVector<KCircle3D> KSpliter::split(const KFrustum &frustum, int rings) const
{
    QVector<KCircle3D> circles;
    double dh = frustum.length() / (rings - 1);
    double dr = (frustum.topRadius() - frustum.bottomRadius()) /
            frustum.length() * dh;
    const KVector3D &zaxis = frustum.coordSystem().zAxis();
    KVector3D dv = zaxis * dh;
    KCircle3D circle(frustum.coordSystem().origin(), frustum.bottomRadius(),
                     frustum.coordSystem().zAxis());
    circles << circle;
    for (int i = 2; i < rings; ++i) {
        circle.translate(dv);
        circle.setRadius(circle.radius() + dr);
        circles << circle;
    }
    circles << frustum.topCircle();
    return circles;
}

QVector<QVector<KVector3D>> KSpliter::split(const KFrustum &frustum,
                                            int rings, int slices) const
{
    QVector<QVector<KVector3D>> pointses;
    double dh = frustum.length() / (rings - 1);
    double dr = (frustum.topRadius() - frustum.bottomRadius()) /
            frustum.length() * dh;
    const KVector3D &zaxis = frustum.coordSystem().zAxis();
    KVector3D dv = zaxis * dh;
    KCircle3D circle(frustum.coordSystem().origin(), frustum.bottomRadius(),
                     frustum.coordSystem().zAxis());
    pointses << split(circle, slices);
    for (int i = 2; i < rings; ++i) {
        circle.translate(dv);
        circle.setRadius(circle.radius() + dr);
        pointses << split(circle, slices);
    }
    pointses << split(frustum.topCircle(), slices);
    return pointses;
}

QVector<QVector<KVector3D>> KSpliter::split(
        const KCylinder &cylinder, int rings, int slices) const
{
    QVector<QVector<KVector3D>> pointses;

    KVector3D bc = cylinder.bottomCenter();
    KRectCoordSystem3D sys = cylinder.coordinateSystem();
    sys.setOrigin(bc);
    KCircle3D circle(cylinder.radius(), sys);
    KVector3D dv = cylinder.zAxis() * (cylinder.height() / (rings - 1));
    QVector<KVector3D> points = split(circle, slices);
    pointses << points;
    for (int i = 1; i < rings; ++i) {
        translate(points, dv);
        pointses << points;
    }
    return pointses;
}

QVector<KCircle3D> KSpliter::split(const KCylinder &cylinder, int rings) const
{
    QVector<KCircle3D> circles;
    KVector3D bc = cylinder.bottomCenter();
    KCircle3D circle(bc, cylinder.radius(), cylinder.zAxis());
    KVector3D dv = cylinder.zAxis() * (cylinder.height() / (rings - 1));
    circles << circle;
    for (int i = 2; i < rings; ++i) {
        circle.translate(dv);
        circles << circle;
    }
    circle.setCenter(bc + cylinder.zAxis() * cylinder.height());
    circles << circle;
    return circles;
}

QVector<KPointF> KSpliter::split(const KCircle2D &circle, int slices) const
{
    int slices_4 = slices / 4;
    double per_radian = K_PI_2 / slices_4;
    double radian = 0;
    QVector<KPointF> pos2d;
    KPointF p2d(circle.radius(), 0);
    pos2d << p2d;
    for (int i = 1; i < slices_4; ++i) {
        radian += per_radian;
        p2d.setXY(circle.radius() * kCos(radian),
                  circle.radius() * kSin(radian));
        pos2d << p2d;
    }

    p2d.setXY(0, circle.radius());
    pos2d << p2d;

    for (int i = slices_4 - 1; i >= 0; --i) {
        p2d.setXY(-pos2d.at(i).x(), pos2d.at(i).y());
        pos2d << p2d;
    }
    for (int i = 2 * slices_4 - 1; i > 0; --i) {
        p2d.setXY(pos2d.at(i).x(), -pos2d.at(i).y());
        pos2d << p2d;
    }

    for (int i = 0; i < pos2d.size(); ++i)
        pos2d[i].translate(circle.center());

    return pos2d;
}

QVector<KVector3D> KSpliter::split(const KCircle3D &circle, int slices) const
{
    QVector<KVector3D> points;
    double rad = 0;
    double per_rad = K_2PI / slices;
    points << circle.radius() * circle.xAxis() + circle.center();
    for (int i = 1; i < slices; ++i) {
        rad += per_rad;
        points << circle.radius() * (kCos(rad) * circle.xAxis() +
                                     kSin(rad) * circle.yAxis()) +
                  circle.center();
    }
    return points;
}

QVector<KVector3D> KSpliter::split(const KEllipse3D &ellipse, int slices_4) const
{
    QVector<KVector3D> points;
    double a = ellipse.a();
    double b = ellipse.b();
    QVector<KPointF> pos2d;
    KPointF p2d(a, 0);
    pos2d << p2d;
    if (a > b) {
        double d = 2.0 * b / (slices_4 * (slices_4 + 1));
        double y = 0;
        for (int i = slices_4; i > 1; --i) {
            y += i * d;
            p2d.setXY(a * kSqrt(1 - y * y / (b * b)), y);
            pos2d << p2d;
        }
    } else {
        double d = 2.0 * a / (slices_4 * (slices_4 + 1));
        double x = a;
        for (int i = 1; i < slices_4; ++i) {
            x -= i * d;
            p2d.setXY(x, b * kSqrt(1 - x * x / (a * a)));
            pos2d << p2d;
        }
    }
    p2d.setXY(0, b);
    pos2d << p2d;
    for (int i = slices_4 - 1; i >= 0; --i) {
        p2d.setXY(-pos2d.at(i).x(), pos2d.at(i).y());
        pos2d << p2d;
    }
    for (int i = 2 * slices_4 - 1; i > 0; --i) {
        p2d.setXY(pos2d.at(i).x(), -pos2d.at(i).y());
        pos2d << p2d;
    }

    KVector3D p3d;
    for (int i = 0; i < pos2d.size(); ++i) {
        p3d = pos2d.at(i).x() * ellipse.xAxis() +
                pos2d.at(i).y() * ellipse.yAxis() + ellipse.center();
        points << p3d;
    }
    return points;
}

QVector<KCircle3D> KSpliter::split(const KSphere &sphere, int rings) const
{      
    double per = K_PI / rings;
    double r = -K_PI_2 + per / 2;

    QVector<KCircle3D> circles;
    KCircle3D circle;
    int i = 0;
    do {
        circle.setCenter(KVector3D(0, 0, sphere.center().z() +
                                   sphere.radius() * kSin(r)));
        circle.setRadius(sphere.radius() * kCos(r));
        circles << circle;
        r += per;
    } while (++i < rings);
    return circles;
}

QVector<KPointF> KSpliter::split(const KLineSegment2D &line, int slices,
                                 bool contain_first, bool contain_last) const
{
    KPointF v0 = line.p1();
    KPointF v = line.p2();

    QVector<KPointF> vs;
    if (contain_first)
        vs << v0;
    KPointF dv = (v - v0) / slices;
    for (int i = 1; i < slices; ++i) {
        v0 += dv;
        vs << v0;
    }
    if (contain_last)
        vs << v;
    return vs;
}

QVector<KVector3D> KSpliter::split(const KArchimedesSpiral3D &spiral, double dt, int slices) const
{
    QVector<KVector3D> points;
    for (int i = 0; i <= slices; ++i)
        points << spiral.pos(dt * i);
    return points;
}

QVector<KPointF> KSpliter::split(const KArc2D &arc, int slices) const
{
    double space = arc.spanAngle() / slices;
    double angle = arc.startAngle();
    QVector<KPointF> points;
    for (int i = 0; i < slices; ++i) {
        points << arc.pos(angle);
        angle += space;
    }
    points << arc.endPos();
    return points;
}

QVector<KTriangle3D> KSpliter::triangulate(const KCircle3D &circle, int slices) const
{
    KSpliter spliter;
    QVector<KVector3D> points = spliter.split(circle, slices);
    QVector<KTriangle3D> tris;
    for (int i = 0; i < points.size(); ++i) {
        tris << KTriangle3D(circle.center(), points.at(i),
                            points.at(nextIndex(i, points.size())));
    }
    return tris;
}

QVector<KTriangle3D> KSpliter::triangulate(const QVector<KCircle3D> &circles,
                                           int slices) const
{
    QVector<KTriangle3D> tris;
    QVector<QVector<KVector3D>> points;
    KSpliter spliter;
    for (int i = 0; i < circles.size(); ++i)
        points << spliter.split(circles.at(i), slices);

    KTriangle3D tri;
    for (int i = 1; i < points.size(); ++i) {
        int i1 = i - 1;
        for (int j = 1; j < slices; ++j) {
            int j1 = j - 1;
            tri.setP1(points.at(i).at(j1));
            tri.setP2(points.at(i1).at(j1));
            tri.setP3(points.at(i1).at(j));
            tris << tri;

            tri.setP2(tri.p3());
            tri.setP3(points.at(i).at(j));
            tris << tri;
        }
        tri.setP1(points.at(i).last());
        tri.setP2(points.at(i1).last());
        tri.setP3(points.at(i1).first());
        tris << tri;

        tri.setP2(tri.p3());
        tri.setP3(points.at(i).first());
        tris << tri;
    }

    return tris;
}
