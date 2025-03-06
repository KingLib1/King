#include "krevolve.h"

#include "karc2d.h"

KRevolve::KRevolve()
{

}

KRevolve::KRevolve(const OutlineData &data) : data_(data)
{

}

KVector3D KRevolve::posOnBlade(double lead, double t) const
{
    double dz = lead / K_2PI;
    double z = t * dz;

    int low = 0;
    int high = data_.size() - 1;
    while (high - low > 1) {
        int mid = (low + high) / 2;
        if (z > data_.at(mid).first.x())
            low = mid;
        else
            high = mid;
    }

    double radian = data_.at(high).second;
    if (isZero(radian, EPS3)) { // 直线
        KPointF p0 = data_.at(low).first;
        KPointF p1 = data_.at(high).first;
        KPointF dp = p1 - p0;
        double r = p0.y() + dp.y() * (z - p0.x()) / dp.x();
        return KVector3D(r * kCos(t), r * kSin(t), z);
    } else { // 圆弧
        KArc2D arc(data_.at(low).first, data_.at(high).first, radian);
        double r = pythagoreanTheorem_Right(z - arc.cx(), arc.radius()) + arc.cy();
        return KVector3D(r * kCos(t), r * kSin(t), z);
    }
}

KVector3D KRevolve::tangentOnBlade(double lead, double t) const
{
    double dz = lead / K_2PI;
    double z = t * dz;
    double cost = kCos(t);
    double sint = kSin(t);

    int low = 0;
    int high = data_.size() - 1;
    while (high - low > 1) {
        int mid = (low + high) / 2;
        if (z > data_.at(mid).first.x())
            low = mid;
        else
            high = mid;
    }

    double radian = data_.at(high).second;
    if (isZero(radian, EPS3)) { // 直线
        KPointF p0 = data_.at(low).first;
        KPointF p1 = data_.at(high).first;
        KPointF dp = p1 - p0;
        double r = p0.y() + dp.y() * (z - p0.x()) / dp.x();
        double r1 = dz * dp.y() / dp.x();
        double dx = r1 * cost - r * sint;
        double dy = r1 * sint + r * cost;
        return KVector3D(dx, dy, dz);
    } else { // 圆弧
        KArc2D arc(data_.at(low).first, data_.at(high).first, radian);
        double x0_x = arc.cx() - z;
        double pytha = pythagoreanTheorem_Right(x0_x, arc.radius());
        double r = pytha + arc.cy();
        double a1 = x0_x * dz / pytha;
        double dx = a1 * cost - r * sint;
        double dy = a1 * sint + r * cost;
        return KVector3D(dx, dy, dz);
    }
}

KPair<KVector3D, KVector3D> KRevolve::posAndTanOnBlade(double lead, double t)
const
{
    KPair<KVector3D, KVector3D> pair;

    double dz = lead / K_2PI;
    double z = t * dz;
    double cost = kCos(t);
    double sint = kSin(t);

    int low = 0;
    int high = data_.size() - 1;
    while (high - low > 1) {
        int mid = (low + high) / 2;
        if (z > data_.at(mid).first.x())
            low = mid;
        else
            high = mid;
    }

    double radian = data_.at(high).second;
    if (isZero(radian, EPS3)) { // 直线
        KPointF p0 = data_.at(low).first;
        KPointF p1 = data_.at(high).first;
        KPointF dp = p1 - p0;
        double r = p0.y() + dp.y() * (z - p0.x()) / dp.x();
        double x = r * cost;
        double y = r * sint;
        pair.first.setXYZ(x, y, z);

        double r1 = dz * dp.y() / dp.x();
        double dx = r1 * cost - y;
        double dy = r1 * sint + x;
        pair.second.setXYZ(dx, dy, dz);
    } else { // 圆弧
        KArc2D arc(data_.at(low).first, data_.at(high).first, radian);
        double x0_x = arc.cx() - z;
        double pytha = pythagoreanTheorem_Right(x0_x, arc.radius());
        double r = pytha + arc.cy();
        double x = r * cost;
        double y = r * sint;
        pair.first.setXYZ(x, y, z);

        double a1 = x0_x * dz / pytha;
        double dx = a1 * cost - y;
        double dy = a1 * sint + x;
        pair.second.setXYZ(dx, dy, dz);
    }

    return pair;
}
