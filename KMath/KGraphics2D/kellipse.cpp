#include "kellipse.h"
#include <QDebug>

KEllipse::KEllipse() : a_(0), b_(0)
{

}

KEllipse::KEllipse(double a, double b) : a_(a), b_(b)
{

}

KEllipse::KEllipse(double center_x, double center_y, double a, double b) :
    center_(center_x, center_y), a_(a), b_(b)
{

}

KEllipse::KEllipse(const KPointF &center, double a, double b) :
    center_(center), a_(a), b_(b)
{

}

KEllipse::KEllipse(const KPointF &center, const KPointF &p1,
                   const KPointF &p2) : center_(center)
{
    KPointF tp1 = p1 - center;
    KPointF tp2 = p2 - center;
    double x1s = tp1.xSquare();
    double y1s = tp1.ySquare();
    double x2s = tp2.xSquare();
    double y2s = tp2.ySquare();
    double bs = (x2s*y1s - y2s*x1s) / (x2s - x1s);
    double as = bs * x1s / (bs - y1s);
    b_ = kSqrt(bs);
    a_ = kSqrt(as);
}

KEllipse::KEllipse(double a, double b, const KPointF &from,
                   const KPointF &nearest, double &t)
    : a_(a), b_(b)
{
    KVector2D n(nearest, from);
    KRange range;
    if (n.x() >= 0)
        n.y() >= 0 ? range.setUpper(K_PI_2) : range.setLower(-K_PI_2);
    else
        n.y() >= 0 ? range.setRange(K_PI_2, K_PI) : range.setRange(-K_PI, -K_PI_2);

    double dot;
    do {
        t = range.middle();
        KVector2D tangent(-a_ * kSin(t), b_ * kCos(t));
        dot = KVector2D::dotProduct(n, tangent);
        dot >= 0 ? range.setLower(t) : range.setUpper(t);
    } while (!isZero(dot));

    KPointF tpos(a_ * kCos(t), b_ * kSin(t));
    center_ = nearest - tpos;
}

KEllipse::KEllipse(double a, double b, const KPointF &from,
                   const KPointF &farest, double &t, int far_type) :
    a_(a), b_(b)
{
    KVector2D n(farest, from);
    KRange range;
    if (n.x() >= 0)
        n.y() >= 0 ? range.setRange(-K_PI, -K_PI_2) : range.setRange(K_PI_2, K_PI);
    else
        n.y() >= 0 ? range.setLower(-K_PI_2) : range.setUpper(K_PI_2);
    n.normalize();

    double dot;
    do {
        t = range.middle();
        KVector2D tangent(-a_ * kSin(t), b_ * kCos(t));
        tangent.normalize();
        dot = KVector2D::dotProduct(n, tangent);
        dot >= 0 ? range.setUpper(t) : range.setLower(t);
    } while (!isZero(dot));

    KPointF tpos(a_ * kCos(t), b_ * kSin(t));
    center_ = farest - tpos;
}

bool KEllipse::contains(const KPointF &point) const
{
    KPointF offset = point - center_;
    return kSquare(offset.x() / a_) + kSquare(offset.y() / b_) <= 1;
}

KPair<KPointF, KPointF> KEllipse::intersect(
        const KCircle2D &c, KPair<double, double> &tpair, bool *success)
{
    KPair<KPointF, KPointF> pair;

    double t1 = nearestPointTValue(c.center());
    KPointF nearest(a() * kCos(t1), b() * kSin(t1));
    nearest += center();
    double dis2 = nearest.distanceSquaredToPoint(c.center());
    double cr2 = c.radiusSquared();

    // 圆心到椭圆的距离大于半径
    if (cr2 < dis2) {
        if (success)
            *success = false;
        return pair;
    }

    // 圆心到椭圆的距离不大于半径
    double t2 = farestPointTValue(c.center());
    KPointF farest(a() * kCos(t2), b() * kSin(t2));
    farest += center();
    // 整个椭圆在圆内
    if (c.contains(farest)) {
        if (success)
            *success = false;
        return pair;
    }

    if (success)
        *success = true;
    // 椭圆部分在圆内(暂时只考虑两个交点的情况)
    KRange range1, range2; // range1最近点为lower，range2最远点为lower
    if (t2 >= t1) {
        range1.setRange(t1, t2);
        range2.setRange(t2, t1 + K_2PI);
    } else {
        range1.setRange(t1, t2 + K_2PI);
        range2.setRange(t2, t1);
    }

    KPointF tpos;
    do { // range1二分迭代
        double mid = range1.middle();
        tpos = tPos(mid);
        dis2 = c.center().distanceSquaredToPoint(tpos);
        tpair.first = mid;
        dis2 <= cr2 ? range1.setLower(mid) : range1.setUpper(mid);
    } while (!isEqual(dis2, cr2));
    pair.first = tpos;

    do { // range2二分迭代
        double mid = range2.middle();
        tpos = tPos(mid);
        dis2 = c.center().distanceSquaredToPoint(tpos);
        tpair.second = mid;
        dis2 <= cr2 ? range2.setUpper(mid) : range2.setLower(mid);
    } while (!isEqual(dis2, cr2));
    pair.second = tpos;
    return pair;
}

KPair<KEllipse, KEllipse> KEllipse::tangentToCircleAndThroughPos(
        double a, double b, const KCircle2D &circle, const KPointF &pos)
{
    KPair<KEllipse, KEllipse> pair;
    double dis;
    double t;
    KEllipse ell(a, b, circle.center(), pos, t);
    KRange range1(t - K_PI, t);
    KRange range2(t, t + K_PI);

    double mid;
    do {
        mid = range1.middle();
        KPointF midpos(ell.a_ * kCos(mid), ell.b_ * kSin(mid));
        ell.center_ = pos - midpos;
        dis = ell.nearestDistance(circle.center());
        if (dis < circle.radius()) {
            range1.setLower(mid);
        } else {
            range1.setUpper(mid);
        }
    } while (!isEqual(dis, circle.radius()));
    pair.first = ell;

    do {
        mid = range2.middle();
        KPointF midpos(ell.a_ * kCos(mid), ell.b_ * kSin(mid));
        ell.center_ = pos - midpos;
        dis = ell.nearestDistance(circle.center());
        if (dis < circle.radius()) {
            range2.setUpper(mid);
        } else {
            range2.setLower(mid);
        }
    } while (!isEqual(dis, circle.radius()));
    pair.second = ell;

    return pair;
}

KPointF KEllipse::nearestPoint(const KPointF &p) const
{
    KRange range;
    KPointF tp = p - center_;
    if (tp.x() >= 0) {
        if (tp.y() >= 0) {
            range.setUpper(K_PI_2);
        } else {
            range.setLower(-K_PI_2);
        }
    } else {
        if (tp.y() >= 0) {
            range.setRange(K_PI_2, K_PI);
        } else {
            range.setRange(-K_PI, -K_PI_2);
        }
    }

    double t, cost, sint, dot;
    KPointF pos;
    do {
        t = range.middle();
        cost = kCos(t);
        sint = kSin(t);
        pos.setXY(a_ * cost, b_ * sint);
        KVector2D n(pos, tp);
        KVector2D tangent(-a_ * sint, b_ * cost);
        dot = KVector2D::dotProduct(n, tangent);
        if (dot > 0)
            range.setLower(t);
        else
            range.setUpper(t);
    } while (!isZero(dot));

    return pos + center_;
}

double KEllipse::nearestPointTValue(const KPointF &p) const
{
    KRange range;
    KPointF tp = p - center_;
    if (tp.x() >= 0) {
        if (tp.y() >= 0) {
            range.setUpper(K_PI_2);
        } else {
            range.setLower(-K_PI_2);
        }
    } else {
        if (tp.y() >= 0) {
            range.setRange(K_PI_2, K_PI);
        } else {
            range.setRange(-K_PI, -K_PI_2);
        }
    }

    double t, cost, sint, dot;
    KPointF pos;
    do {
        t = range.middle();
        cost = kCos(t);
        sint = kSin(t);
        pos.setXY(a_ * cost, b_ * sint);
        KVector2D n(pos, tp);
        KVector2D tangent(-a_ * sint, b_ * cost);
        dot = KVector2D::dotProduct(n, tangent);
        if (dot > 0)
            range.setLower(t);
        else
            range.setUpper(t);
    } while (!isZero(dot));

    return t;
}

KPointF KEllipse::farestPoint(const KPointF &p) const
{
    KRange range;
    KPointF tp = p - center_;

    if (tp.x() >= 0)
        tp.y() >= 0 ? range.setRange(-K_PI, -K_PI_2) : range.setRange(K_PI_2, K_PI);
    else
        tp.y() >= 0 ? range.setLower(-K_PI_2) : range.setUpper(K_PI_2);

    double t, cost, sint, dot;
    KPointF pos;
    do {
        t = range.middle();
        cost = kCos(t);
        sint = kSin(t);
        pos.setXY(a_ * cost, b_ * sint);
        KVector2D n(pos, tp);
        KVector2D tangent(-a_ * sint, b_ * cost);
        dot = KVector2D::dotProduct(n, tangent);
        if (dot > 0)
            range.setUpper(t);
        else
            range.setLower(t);
    } while (!isZero(dot));

    return pos + center_;
}

double KEllipse::farestPointTValue(const KPointF &p) const
{
    KRange range;
    KPointF tp = p - center_;

    if (tp.x() >= 0)
        tp.y() >= 0 ? range.setRange(-K_PI, -K_PI_2) : range.setRange(K_PI_2, K_PI);
    else
        tp.y() >= 0 ? range.setLower(-K_PI_2) : range.setUpper(K_PI_2);

    double t, cost, sint, dot;
    KPointF pos;
    do {
        t = range.middle();
        cost = kCos(t);
        sint = kSin(t);
        pos.setXY(a_ * cost, b_ * sint);
        KVector2D n(pos, tp);
        KVector2D tangent(-a_ * sint, b_ * cost);
        dot = KVector2D::dotProduct(n, tangent);
        if (dot > 0)
            range.setUpper(t);
        else
            range.setLower(t);
    } while (!isZero(dot));

    return t;
}

double KEllipse::tValueByTangent(const KVector2D &tangent) const
{
    KVector2D tan1 = tangent.normalized();
    KRange range;
    if (tangent.x() >= 0) {
        if (tangent.y() >= 0) {
            range.setRange(-K_PI_2, 0);
        } else {
            range.setRange(-K_PI, -K_PI_2);
        }
    } else {
        if (tangent.y() >= 0) {
            range.setRange(0, K_PI_2);
        } else {
            range.setRange(K_PI_2, K_PI);
        }
    }

    double mid;
    double cross;
    do {
        mid = range.middle();
        KVector2D tan2 = tTangentVector(mid);
        tan2.normalize();
        cross = KVector2D::crossProduct(tan2, tan1);
        if (cross >= 0) {
            range.setLower(mid);
        } else {
            range.setUpper(mid);
        }
    } while (!isZero(cross));

    return mid;
}

KPointF KEllipse::rPos(double radian) const
{
    radian = radianNormalized(radian);
    double k = kTan(radian);
    double a2_ = a2();
    double b2_ = b2();
    double x2 = a2_ * b2_ / (a2_ * kSquare(k) + b2_);
    double y2 = b2_ * (1 - x2 / a2_);

    if (radian < -K_PI_2)
        return KPointF(-kSqrt(x2) + center_.x(), -kSqrt(y2) + center_.y());
    if (radian < 0)
        return KPointF(kSqrt(x2) + center_.x(), -kSqrt(y2) + center_.y());
    if (radian < K_PI_2)
        return KPointF(kSqrt(x2) + center_.x(), kSqrt(y2) + center_.y());
    return KPointF(-kSqrt(x2) + center_.x(), kSqrt(y2) + center_.y());
}
