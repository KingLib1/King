#include "kflatgrindingwheel.h"

#include "karc2d.h"
#include "kspliter.h"

#include <QDebug>

KFlatGrindingWheel::KFlatGrindingWheel()
{

}



double KFlatGrindingWheel::radiusAt(double height) const
{
    if (type_ == Type::Big) {
        double cx = big_radius_ - bottom_fillet_;
        if (height <= bottom_fillet_) {
            double x = pythagoreanTheorem_Right(bottom_fillet_ - height,
                                                bottom_fillet_);
            return cx + x;
        }

        KPointF center(cx, bottom_fillet_);
        KArc2D arc(center, bottom_fillet_, -90, 90 + angle_);
        KPointF end = arc.endPos();
        if (height <= end.y()) {
            double x = pythagoreanTheorem_Right(height - bottom_fillet_,
                                                bottom_fillet_);
            return cx + x;
        }

        center = end;
        double h = width_ - center.y();
        center.setY(width_ - top_fillet_);
        double radian = kDegreesToRadians(angle_);
        center.translateX(-h * kTan(radian));
        radian = (K_PI_2 - radian) / 2;
        center.translateX(-top_fillet_ * kTan(radian));
        KArc2D arc2(center, top_fillet_, angle_, 90 - angle_);
        KPointF start = arc2.startPos();
        if (height <= start.y()) {
            KFrustum frustum(end.x(), start.x(), start.y() - end.y());
            frustum.setBottomCenter(KVector3D(0, 0, end.y()));
            return frustum.radiusAt(height - end.y());
        }

        double x = pythagoreanTheorem_Right(height - center.y(), top_fillet_);
        return center.x() + x;
    }

    height = width_ - height;
    double cx = big_radius_ - top_fillet_;
    if (height <= top_fillet_) {
        double x = pythagoreanTheorem_Right(top_fillet_ - height,
                                            top_fillet_);
        return cx + x;
    }

    KPointF center(cx, top_fillet_);
    KArc2D arc(center, top_fillet_, -90, 90 + angle_);
    KPointF end = arc.endPos();
    if (height <= end.y()) {
        double x = pythagoreanTheorem_Right(height - top_fillet_,
                                            top_fillet_);
        return cx + x;
    }

    center = end;
    double h = width_ - center.y();
    center.setY(width_ - bottom_fillet_);
    double radian = kDegreesToRadians(angle_);
    center.translateX(-h * kTan(radian));
    radian = (K_PI_2 - radian) / 2;
    center.translateX(-bottom_fillet_ * kTan(radian));
    KArc2D arc2(center, bottom_fillet_, angle_, 90 - angle_);
    KPointF start = arc2.startPos();
    if (height <= start.y()) {
        KFrustum frustum(end.x(), start.x(), start.y() - end.y());
        frustum.setBottomCenter(KVector3D(0, 0, end.y()));
        return frustum.radiusAt(height - end.y());
    }

    double x = pythagoreanTheorem_Right(height - center.y(), bottom_fillet_);
    return center.x() + x;
}

bool KFlatGrindingWheel::contains(const KVector3D &p) const
{
    double t = KVector3D::dotProduct(p - bottomCenter(), normal_);
    if (t < 0 || t > width_) {
        return false;
    }

    KVector3D pedal = bottomCenter() + normal_ * t;
    double r2 = kSquare(radiusAt(t));
    double dis2 = p.distanceSquaredToPoint(pedal);
    if (dis2 > r2)
        return false;

    return true;
}

KFrustum KFlatGrindingWheel::boundingFrustum() const
{
    double rad = kDegreesToRadians(angle_);
    double rad2 = (K_PI_2 - rad) / 2;
    if (type_ == Type::Big) {
        double ext = bottom_fillet_ / kTan(rad2);
        double br = big_radius_ - bottom_fillet_ + ext;
        ext = width_ * kTan(rad);
        double tr = br - ext;
        KFrustum frustum(br, tr, width_);
        frustum.setBottomCenter(bottom_center_);
        frustum.setZAxis(normal_);
        return frustum;
    }

    double ext = top_fillet_ / kTan(rad2);
    double br = big_radius_ - top_fillet_ + ext;
    ext = width_ * kTan(rad);
    double tr = br - ext;
    KFrustum frustum(tr, br, width_);
    frustum.setBottomCenter(bottom_center_);
    frustum.setZAxis(normal_);
    return frustum;
}

double KFlatGrindingWheel::topRadius() const
{
    if (type_ == Type::Big) {
        KPointF center(big_radius_ - bottom_fillet_, bottom_fillet_);
        KArc2D arc(center, bottom_fillet_, -90, 90 + angle_);
        center = arc.endPos();
        double h = width_ - center.y();
        double radian = kDegreesToRadians(angle_);
        center.translateX(-h * kTan(radian));
        radian = (K_PI_2 - radian) / 2;
        center.translateX(-top_fillet_ * kTan(radian));
        return center.x();
    }

    return big_radius_ - top_fillet_;
}

double KFlatGrindingWheel::bottomRadius() const
{
    if (type_ == Type::Big)
        return big_radius_ - top_fillet_;

    KPointF center(big_radius_ - top_fillet_, width_ - top_fillet_);
    KArc2D arc(center, top_fillet_, -angle_, 90 + angle_);
    center = arc.startPos();
    double h = center.y();
    double radian = kDegreesToRadians(angle_);
    center.translateX(-h * kTan(radian));
    radian = (K_PI_2 - radian) / 2;
    center.translateX(-bottom_fillet_ * kTan(radian));
    return center.x();
}

KCircle3D KFlatGrindingWheel::topCircle() const
{
    if (type_ == Type::Big) {
        KPointF center(big_radius_ - bottom_fillet_, bottom_fillet_);
        KArc2D arc(center, bottom_fillet_, -90, 90 + angle_);
        center = arc.endPos();
        double h = width_ - center.y();
        double radian = kDegreesToRadians(angle_);
        center.translateX(-h * kTan(radian));
        radian = (K_PI_2 - radian) / 2;
        center.translateX(-top_fillet_ * kTan(radian));
        return KCircle3D(topCenter(), center.x(), normal_);
    }

    double radius = big_radius_ - top_fillet_;
    return KCircle3D(topCenter(), radius, normal_);
}

KCircle3D KFlatGrindingWheel::bottomCircle() const
{
    if (type_ == Type::Big) {
        double radius = big_radius_ - top_fillet_;
        return KCircle3D(bottom_center_, radius, normal_);
    }

    KPointF center(big_radius_ - top_fillet_, width_ - top_fillet_);
    KArc2D arc(center, top_fillet_, -angle_, 90 + angle_);
    center = arc.startPos();
    double h = center.y();
    double radian = kDegreesToRadians(angle_);
    center.translateX(-h * kTan(radian));
    radian = (K_PI_2 - radian) / 2;
    center.translateX(-bottom_fillet_ * kTan(radian));
    return KCircle3D(bottom_center_, center.x(), normal_);
}

QVector<KCircle3D> KFlatGrindingWheel::split(int *num1, int *num2, int *num3) const
{
    QVector<KCircle3D> circles;

    if (type_ == Type::Big) {
        QVector<KPointF> points1;
        KPointF center(big_radius_ - bottom_fillet_, bottom_fillet_);
        KArc2D arc(center, bottom_fillet_, -90, 90 + angle_);
        KSpliter spliter;
        if (bottom_fillet_ < EPS6)
            points1 << center;
        else
            points1 = spliter.split(arc, arc.spanAngle() / 360 * fillet_rings_);

        center = points1.last();
        double h = width_ - center.y();
        center.setY(width_ - top_fillet_);
        double radian = kDegreesToRadians(angle_);
        center.translateX(-h * kTan(radian));
        radian = (K_PI_2 - radian) / 2;
        center.translateX(-top_fillet_ * kTan(radian));
        arc.setCenter(center);
        arc.setRadius(top_fillet_);
        arc.setStartAngle(angle_);
        arc.setSpanAngle(90 - angle_);
        QVector<KPointF> points3;
        if (top_fillet_ < EPS6)
            points3 << center;
        else
            points3 = spliter.split(arc, arc.spanAngle() / 360 * fillet_rings_);

        QVector<KPointF> points2 = spliter.split(points1.last(), points3.first(),
                                                 cone_rings_, false, false);

        KCircle3D circle;
        circle.setNormal(normal_);
        circle.setCenter(bottom_center_);
        for (int i = 0; i < points1.size(); ++i) {
            circle.setCenter(bottom_center_ + normal_ * points1.at(i).y());
            circle.setRadius(points1.at(i).x());
            circles << circle;
        }

        for (int i = 0; i < points2.size(); ++i) {
            circle.setCenter(bottom_center_ + normal_ * points2.at(i).y());
            circle.setRadius(points2.at(i).x());
            circles << circle;
        }

        for (int i = 0; i < points3.size(); ++i) {
            circle.setCenter(bottom_center_ + normal_ * points3.at(i).y());
            circle.setRadius(points3.at(i).x());
            circles << circle;
        }
        if (num1)
            *num1 = points1.size();
        if (num2)
            *num2 = points2.size();
        if (num3)
            *num3 = points3.size();

    } else {
        KPointF center(big_radius_ - top_fillet_, width_ - top_fillet_);
        KArc2D arc(center, top_fillet_, -angle_, 90 + angle_);
        KSpliter spliter;
        QVector<KPointF> points3;
        if (top_fillet_ < EPS6)
            points3 << center;
        else
            points3 = spliter.split(arc, arc.spanAngle() / 360 * fillet_rings_);

        center = points3.first();
        double h = center.y();
        center.setY(bottom_fillet_);
        double radian = kDegreesToRadians(angle_);
        center.translateX(-h * kTan(radian));
        radian = (K_PI_2 - radian) / 2;
        center.translateX(-bottom_fillet_ * kTan(radian));
        arc.setCenter(center);
        arc.setRadius(bottom_fillet_);
        arc.setStartAngle(-90);
        arc.setSpanAngle(90 - angle_);
        QVector<KPointF> points1;
        if (bottom_fillet_ < EPS6)
            points1 << center;
        else
            points1 = spliter.split(arc, arc.spanAngle() / 360 * fillet_rings_);

        QVector<KPointF> points2 = spliter.split(points1.last(), points3.first(),
                                                 cone_rings_, false, false);

        KCircle3D circle;
        circle.setNormal(normal_);
        circle.setCenter(bottom_center_);
        for (int i = 0; i < points1.size(); ++i) {
            circle.setCenter(bottom_center_ + normal_ * points1.at(i).y());
            circle.setRadius(points1.at(i).x());
            circles << circle;
        }

        for (int i = 0; i < points2.size(); ++i) {
            circle.setCenter(bottom_center_ + normal_ * points2.at(i).y());
            circle.setRadius(points2.at(i).x());
            circles << circle;
        }

        for (int i = 0; i < points3.size(); ++i) {
            circle.setCenter(bottom_center_ + normal_ * points3.at(i).y());
            circle.setRadius(points3.at(i).x());
            circles << circle;
        }

        if (num1)
            *num1 = points1.size();
        if (num2)
            *num2 = points2.size();
        if (num3)
            *num3 = points3.size();
    }

    return circles;
}
