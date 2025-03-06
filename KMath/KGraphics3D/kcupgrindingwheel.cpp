#include "kcupgrindingwheel.h"

#include "kspliter.h"

KCupGrindingWheel::KCupGrindingWheel()
{

}

double KCupGrindingWheel::externalRadiusAt(double height) const
{
    KPointF center(radius_ - fillet_, external_depth_ - fillet_);
    KArc2D arc(center, fillet_, -external_angle_, 90 + external_angle_);
    KPointF start = arc.startPos();
    if (height >= start.y()) {
        double x = pythagoreanTheorem_Right(height - center.y(), fillet_);
        return center.x() + x;
    }

    KPointF end = start;
    double h = end.y();
    end.setY(0);
    double radian = kDegreesToRadians(external_angle_);
    double tanr = kTan(radian);
    end.translateX(-h * tanr);
    return end.x() + (start.x() - end.x()) / h * height;
}

KFrustum KCupGrindingWheel::boundingFrustum() const
{
    double rad = kDegreesToRadians(external_angle_);
    double rad2 = (K_PI_2 - rad) / 2;
    double ext = fillet_ / kTan(rad2);
    double br = radius_ - fillet_ + ext;
    ext = external_depth_ * kTan(rad);
    double tr = br - ext;

    KFrustum frustum(tr, br, external_depth_);
    frustum.setBottomCenter(bottom_center_);
    frustum.setZAxis(normal_);
    return frustum;
}

KFlatGrindingWheel KCupGrindingWheel::toFlatGrindingWheel() const
{
    KFlatGrindingWheel wheel;
    wheel.setAngle(external_angle_);
    wheel.setBigRadius(radius_);
    wheel.setBottomCenter(bottom_center_);
    wheel.setNormal(normal_);
    wheel.setBottomFillet(0);
    wheel.setTopFillet(fillet_);
    wheel.setType(KFlatGrindingWheel::Type::Small);
    wheel.setWidth(external_depth_);
    return wheel;
}

bool KCupGrindingWheel::contains(const KVector3D &p) const
{
    double t = KVector3D::dotProduct(p - bottom_center_, normal_);
    if (t < 0 || t > external_depth_) {
        return false;
    }

    KPointF center(radius_ - fillet_, external_depth_ - fillet_);
    KArc2D arc(center, fillet_, -external_angle_,
               90 + external_angle_ + internal_angle_);
    KPointF start = arc.startPos();
    double r, r2;
    double x = 0;

    KVector3D pedal = bottom_center_ + normal_ * t;
    double dis2 = p.distanceSquaredToPoint(pedal);

    bool cal = false;
    double tanr = 0;
    if (t >= start.y()) {
        x = pythagoreanTheorem_Right(t - center.y(), fillet_);
        r = center.x() + x;
        r2 = kSquare(r);
        if (dis2 > r2)
            return false;
    } else {
        KPointF end = start;
        double h = end.y();
        end.setY(0);
        double radian = kDegreesToRadians(external_angle_);
        tanr = kTan(radian);
        end.translateX(-h * tanr);
        r = end.x() + (start.x() - end.x()) / h * t;
        r2 = kSquare(r);
        if (dis2 > r2)
            return false;
        cal = true;
    }

    if (t <= external_depth_ - internal_depth_)
        return true;

    KPointF end = arc.endPos();
    if (t >= end.y()) {
        r = center.x() - x;
        r2 = kSquare(r);
        if (dis2 < r2)
            return false;
        return true;
    }

    x = abrasive_width_ - (center.x() - end.x()) - fillet_;
    double rad2 = kDegreesToRadians(internal_angle_);
    double y = x * kTan(rad2);
    KPointF end2 = end.translated(-x, -y);
    if (t >= end2.y()) {
        r = end2.x() + (end.x() - end2.x()) / (end.y() - end2.y()) * (t - end2.y());
        r2 = kSquare(r);
        if (dis2 < r2)
            return false;
        return true;
    }

    KPointF end3 = end2;
    y = internal_depth_ - (external_depth_ - end2.y());
    if (!cal) {
        double radian = kDegreesToRadians(external_angle_);
        tanr = kTan(radian);
    }
    x = y * tanr;
    end3.translate(-x, -y);
    r = end3.x() + (end2.x() - end3.x()) / (end2.y() - end3.y()) * (t - end3.y());
    r2 = kSquare(r);
    if (dis2 < r2)
        return false;
    return true;
}

QVector<KCircle3D> KCupGrindingWheel::split() const
{
    QVector<KCircle3D> circles;
    double space = 0.02;
    int fillet_rings = K_2PI * fillet_ / space;
    if (fillet_rings < 2)
        fillet_rings = 2;

    KPointF center(radius_ - fillet_, external_depth_ - fillet_);
    KArc2D arc(center, fillet_, -external_angle_, 90 + external_angle_ + internal_angle_);
    KSpliter spliter;
    QVector<KPointF> points2;
    if (fillet_ < EPS6)
        points2 << center;
    else
        points2 = spliter.split(arc, arc.spanAngle() / 360 * fillet_rings);

    KPointF end2 = arc.endPos();
    double x = abrasive_width_ - (center.x() - end2.x()) - fillet_;
    double rad2 = kDegreesToRadians(internal_angle_);
    double y = x * kTan(rad2);
    KPointF start2 = end2.translated(-x, -y); // start2--p4
    int cone_rings = y / space + 1;
    if (cone_rings < 2)
        cone_rings = 2;
    QVector<KPointF> points3 = spliter.split(end2, start2, cone_rings,
                                             false, false);
    end2 = start2;
    y = internal_depth_ - (external_depth_ - start2.y());
    double radian = kDegreesToRadians(external_angle_);
    double tanr = kTan(radian);
    x = y * tanr;
    start2.translate(-x, -y);
    cone_rings = y / space + 1;
    if (cone_rings < 2)
        cone_rings = 2;
    QVector<KPointF> points4 = spliter.split(end2, start2, cone_rings,
                                             true, true);

    center = points2.first();
    double h = center.y();
    center.setY(0);
    center.translateX(-h * tanr);

    cone_rings = h / space + 1;
    if (cone_rings < 2)
        cone_rings = 2;
    QVector<KPointF> points1 = spliter.split(center, points2.first(),
                                             cone_rings, true, false);

    KCircle3D circle;
    circle.setNormal(normal_);

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

    for (int i = 0; i < points4.size(); ++i) {
        circle.setCenter(bottom_center_ + normal_ * points4.at(i).y());
        circle.setRadius(points4.at(i).x());
        circles << circle;
    }

    return circles;
}
