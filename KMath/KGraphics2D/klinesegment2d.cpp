#include "klinesegment2d.h"

#include "KGraphics2D/krect.h"
#include <QDebug>

KLineSegment2D::KLineSegment2D()
{

}

KLineSegment2D::KLineSegment2D(double x1, double y1, double x2, double y2)
{
    p1_.setXY(x1, y1);
    p2_.setXY(x2, y2);
}

KLineSegment2D::KLineSegment2D(const KPointF &p1, const KPointF &p2) :
    p1_(p1), p2_(p2)
{

}

KLineSegment2D::KLineSegment2D(const KLineSegment2D &line) :
    p1_(line.p1_), p2_(line.p2_)
{

}

KLineSegment2D::KLineSegment2D(const KVector2D &v)
{
    p2_.setXY(v.x(), v.y());
}

KLineSegment2D::KLineSegment2D(const KVector2D &v1, const KVector2D &v2)
{
    p1_.setXY(v1.x(), v1.y());
    p2_.setXY(v2.x(), v2.y());
}

KLineSegment2D::~KLineSegment2D()
{

}

KRect KLineSegment2D::boundingRect() const
{
    KRect rect(p1_, p2_);
    rect.normalize();
    return rect;
}

QVector<KPointF> KLineSegment2D::DDA() const
{
    QVector<KPointF> points;
    KPointF p1 = p1_.round();
    KPointF p2 = p2_.round();
    KPointF p = p1;

    double dx = p2.x() - p1.x();
    double dy = p2.y() - p1.y();
    if (isZero(dx) && isZero(dy)) {
        points << p;
        return points;
    }

    if (kFabs(dx) >= kFabs(dy)) {
        double k = dy / dx;
        double y = p1.y();
        if (p1.x() < p2.x()) {
            do {
                points << p;
                y += k;
                p.rx() += 1;
                p.setY(kRound(y));
            } while (p.x() <= p2.x());
        } else {
            do {
                points << p;
                y -= k;
                p.rx() -= 1;
                p.setY(kRound(y));
                qDebug() << p.x() << p2.x() << y;
            } while (p.x() >= p2.x());
        }
//        if (isEqual(kRound(p2.x()), p.x()))
//            points << p;
    } else {
        double k = dx / dy;
        double x = p1.x();
        if (p1.y() < p2.y()) {
            do {
                points << p;
                x += k;
                p.ry() += 1;
                p.setX(kRound(x));
            } while (p.y() <= p2.y());
        } else {
            do {
                points << p;
                x -= k;
                p.ry() -= 1;
                p.setX(kRound(x));
            } while (p.y() >= p2.y());
        }
//        if (isEqual(kRound(p2.y()), p.y()))
//            points << p;
    }

    return points;
}

double KLineSegment2D::angleTo(const KLineSegment2D &line) const
{
    double radian1 = radian();
    double radian2 = line.radian();
    if (radian2 < radian1)
        radian2 += K_2PI;
    return kRadiansToDegrees(radian2 - radian1);
}

double KLineSegment2D::radianTo(const KLineSegment2D &line) const
{
    double radian1 = radian();
    double radian2 = line.radian();
    if (radian2 < radian1)
        radian2 += K_2PI;
    return radian2 - radian1;
}

void KLineSegment2D::setAngle(double angle)
{
    double len = length();
    double radian = kDegreesToRadians(angle);
    p2_.setXY(len * kCos(radian) + p1_.x(), len * kSin(radian) + p1_.y());
}

void KLineSegment2D::invert()
{
    KPointF temp = p1_;
    p1_ = p2_;
    p2_ = temp;
}

void KLineSegment2D::setLength(double length)
{
    double len1 = this->length();
    if (len1 <= 0)
        return;
    double times = length / len1;
    p2_.setXY(p1_.x() + dx() * times, p1_.y() + dy() * times);
}

bool KLineSegment2D::intersects(const KLineSegment2D &line) const
{
    if (!xRange().intersects(line.xRange()))
        return false;
    if (!yRange().intersects(line.yRange()))
        return false;
    KVector2D v1(p1_, p2_);
    if (KVector2D::crossProduct(v1, KVector2D(p1_, line.p1_)) *
            KVector2D::crossProduct(v1, KVector2D(p1_, line.p2_)) > EPS9)
        return false;
    KVector2D v2(line.p1_, line.p2_);
    if (KVector2D::crossProduct(v2, KVector2D(line.p1_, p1_)) *
            KVector2D::crossProduct(v2, KVector2D(line.p1_, p2_)) > EPS9)
        return false;
    return true;
}

KLineSegment2D::IntersectType KLineSegment2D::intersect(
        const KLineSegment2D &line, KPointF *intersection) const
{
    double a11 = dx();
    double a21 = dy();
    double a12 = line.p1_.x() - line.p2_.x();
    double a22 = line.p1_.y() - line.p2_.y();
    double D = a11 * a22 - a12 * a21;
    if (kFabs(D) < EPS9) {
        return KLineSegment2D::IntersectType::NoIntersection;
    }
    double b1 = line.p1_.x() - p1_.x();
    double b2 = line.p1_.y() - p1_.y();
    double D1 = b1 * a22 - a12 * b2;
    double D2 = a11 * b2 - b1 * a21;
    double t1 = D1 / D;
    double t2 = D2 / D;
    double x = p1_.x() + a11 * t1;
    double y = p1_.y() + a21 * t1;
    if (intersection)
        intersection->setXY(x, y);
    if (t1 >= 0 && t1 <= 1 && t2 >= 0 && t2 <= 1)
        return KLineSegment2D::IntersectType::BoundedIntersection;
    return KLineSegment2D::IntersectType::UnboundedIntersection;
}

KPointF KLineSegment2D::nearestPoint(const KPointF &point) const
{
    KVector2D p12(dx(), dy());
    KVector2D p13(p1_, point);
    double dot = KVector2D::dotProduct(p12, p13);
    if (dot < 0)
        return p1_;
    double p12_len_square = p12.lengthSquared();
    if (dot > p12_len_square)
        return p2_;
    double t = dot / p12_len_square;
    return KPointF(p1_.x() + t * p12.x(), p1_.y() + t * p12.y());
}

double KLineSegment2D::nearestPointScale(const KPointF &p) const
{
    KVector2D p12(dx(), dy());
    KVector2D p13(p1_, p);
    double dot = KVector2D::dotProduct(p12, p13);
    if (dot < 0)
        return 0;
    double p12_len_square = p12.lengthSquared();
    if (dot > p12_len_square)
        return 1;
    return dot / p12_len_square;
}

double KLineSegment2D::nearestDistanceFromPoint(double x, double y) const
{
    KVector2D p12(dx(), dy());
    KVector2D p13(x - p1_.x(), y - p1_.y());
    double dot = KVector2D::dotProduct(p12, p13);
    if (dot < 0)
        return p13.length();
    if (dot > p12.lengthSquared())
        return kSqrt(kSquare(x - p2_.x()) + kSquare(y - p2_.y()));
    return kFabs(KVector2D::crossProduct(p12, p13)) / p12.length();
}

double KLineSegment2D::nearestDistanceSquareFromPoint(double x, double y) const
{
    KVector2D p12(dx(), dy());
    KVector2D p13(x - p1_.x(), y - p1_.y());
    double dot = KVector2D::dotProduct(p12, p13);
    if (dot < 0)
        return p13.lengthSquared();
    if (dot > p12.lengthSquared())
        return kSquare(x - p2_.x()) + kSquare(y - p2_.y());
    return kSquare(KVector2D::crossProduct(p12, p13)) / p12.lengthSquared();
}
