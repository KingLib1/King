#include "kfilletcylinder.h"

#include "KDerivative.h"
#include "KAlgorithm.h"

KFilletCylinder::KFilletCylinder() : radius_(0), fillet_(0), height_(0),
    eccentricity_(0)
{

}

KFilletCylinder::KFilletCylinder(double radius, double fillet, double inclination, double height,
    double eccentricity, double taper) :radius_(radius), fillet_(fillet),
    inclination_(inclination), height_(height), eccentricity_(eccentricity),
    taper_(taper)
{

}

KVector3D KFilletCylinder::posOnFilletBlade(double lead, double t) const
{
    if (isZero(eccentricity_)) {
        if (t >= 0) {
            double z = t * lead / K_2PI;
            double r = pythagoreanTheorem_Right(fillet_ - z, fillet_) + radius_ - fillet_;
            return KVector3D(r * kCos(t), r * kSin(t), z);
        }
        t = -t;
        double z = t * lead / K_2PI;
        double r = radius_ - fillet_ - pythagoreanTheorem_Right(fillet_ - z, fillet_);
        return KVector3D(r * kCos(t), r * kSin(t), z);
    }

    if (t >= 0) {
        double z = t * lead / K_2PI;
        double f_z = fillet_ - z;
        double r0 = pythagoreanTheorem_Right(f_z, fillet_);
        double r = r0 + radius_ - fillet_;
        double dy = (r0 - fillet_) * eccentricity_ / radius_;
        return KVector3D(r * kCos(t), r * kSin(t) + dy, z);
    }

    t = -t;
    double z = t * lead / K_2PI;
    double f_z = fillet_ - z;
    double r0 = pythagoreanTheorem_Right(f_z, fillet_);
    double r = radius_ - fillet_ - r0;
    double dy = -(fillet_ + r0) * eccentricity_ / radius_;
    return KVector3D(r * kCos(t), r * kSin(t) + dy, z);
}

KVector3D KFilletCylinder::tanOnFilletBlade(double lead, double t) const
{
    if (isZero(eccentricity_)) {
        if (isZero(t))
            return KVector3D::xAxis();

        double dz = lead / K_2PI;
        if (t > 0) {
            double f_z = fillet_ - t * dz;
            double r1 = pythagoreanTheorem_Right(f_z, fillet_);
            double r = r1 + radius_ - fillet_;
            double cost = kCos(t);
            double sint = kSin(t);
            double a1 = f_z * dz / r1;
            double dx = a1 * cost - r * sint;
            double dy = a1 * sint + r * cost;
            KVector3D tangent(dx, dy, dz);
            tangent.normalize();
            return tangent;
        }

        t = -t;
        double f_z = fillet_ - t * dz;
        double r1 = pythagoreanTheorem_Right(f_z, fillet_);
        double r = radius_ - fillet_ - r1;
        double cost = kCos(t);
        double sint = kSin(t);
        double a1 = -f_z * dz / r1;
        double dx = a1 * cost - r * sint;
        double dy = a1 * sint + r * cost;
        KVector3D tangent(-dx, -dy, -dz);
        tangent.normalize();
        return tangent;
    }

    if (isZero(t))
        return KVector3D(radius_, eccentricity_, 0);
    double dz = lead / K_2PI;
    if (t > 0) {
        double f_z = fillet_ - t * dz;
        double r1 = pythagoreanTheorem_Right(f_z, fillet_);
        double r = r1 + radius_ - fillet_;
        double cost = kCos(t);
        double sint = kSin(t);
        double a1 = f_z * dz / r1;
        double dx = a1 * cost - r * sint;
        double dy = a1 * sint + r * cost + eccentricity_ * f_z * dz / (radius_ * r1);
        KVector3D tangent(dx, dy, dz);
        tangent.normalize();
        return tangent;
    }

    t = -t;
    double f_z = fillet_ - t * dz;
    double r1 = pythagoreanTheorem_Right(f_z, fillet_);
    double r = radius_ - fillet_ - r1;
    double cost = kCos(t);
    double sint = kSin(t);
    double a1 = -f_z * dz / r1;
    double dx = a1 * cost - r * sint;
    double dy = a1 * sint + r * cost - eccentricity_ * f_z * dz / (radius_ * r1);
    KVector3D tangent(-dx, -dy, -dz);
    tangent.normalize();
    return tangent;
}

KVector3D KFilletCylinder::normalOnFilletBlade(double lead, double t) const
{
    if (t >= 0) {
        double f_z = fillet_ - t * lead / K_2PI;
        double r1 = pythagoreanTheorem_Right(f_z, fillet_);
        KVector3D normal(r1 * kCos(t), r1 * kSin(t), -f_z);
        normal.normalize();
        return normal;
    }

    t = -t;
    double f_z = fillet_ - t * lead / K_2PI;
    double r1 = pythagoreanTheorem_Right(f_z, fillet_);
    KVector3D normal(-r1 * kCos(t), -r1 * kSin(t), -f_z);
    normal.normalize();
    return normal;
}

QVector<PosTanNor> KFilletCylinder::posTanNorOnBlade_Linear(
        double helix, double r0, double r1, double dlen, QVector<double> &ts) const
{
    if (isZero(helix)) {
        return posTanNorOnBlade_Straight(r0, r1, dlen, ts);
    }

    QVector<PosTanNor> results;
    PosTanNor result;
    ts.clear();
    double ir = radius_ - fillet_;
    r0 -= ir;
    r1 -= ir;
    if (isZero(r0))
        r0 = 0;
    if (isEqual(r1, fillet_))
        r1 = fillet_;
    double dlen2 = dlen * dlen;

    if (r0 < 0) {
        QVector<PosTanNor> results2;
        QVector<double> ts2;
        double r = 0;
        double delta_r = -0.001;
        double t = 0;
        double helix_rad = kDegreesToRadians(helix);
        double der = 0;
        double der2 = 0;
        while (1) {
            if (isZero(r)) {
                double ecc_dy = -fillet_ * eccentricity_ / radius_;
                result.pos.setXYZ(ir, ecc_dy, 0);
                result.normal.setXYZ(0, 0, -1);
                result.tangent.setXYZ(radius_, eccentricity_, 0);
                result.tangent.normalize();
                der = 0;
                der2 = 0;
                t = 0;
            } else {
                double ar = r + ir;
                double f_z2 = kSquareDifference(fillet_, r);
                double f_z = kSqrt(f_z2);
                t += delta_r * der + der2 * delta_r * delta_r / 2;
                double h_r = helix_rad / radius_;
                double x = ar * h_r;
                double tan1 = kTan(x);
                double sec2 = kDerivative8(x);
                double rt = r * tan1;
                der = rt / (ar * f_z);
                der2 = ((tan1 + r*sec2*h_r)*ar*f_z - rt*(f_z - ar*r/f_z)) / (ar*ar*f_z2);
                double cost = kCos(t);
                double sint = kSin(t);
                double ecc_dy = -(fillet_ - r) * eccentricity_ / radius_;
                result.pos.setXYZ(ar * cost, ar * sint + ecc_dy, fillet_ - f_z);
                result.tangent = results2.last().pos - result.pos;
                result.tangent.normalize();
                result.normal.setXYZ(r * cost, r * sint, -f_z);
                result.normal.normalize();
            }

            if (r >= r0) {
                results2 << result;
                ts2 << -t;
            }
            if (isEqual(r, r0))
                break;
            r += delta_r;
            if (r < r0) {
                delta_r += r0 - r;
                r = r0;
            }
        }

        reverse(results2);
        results2.removeLast();
        reverse(ts2);
        ts2.removeLast();
        results << results2;
        ts << ts2;
        r0 = 0;
    }
    {
    double r = 0;
    double delta_r = 0.001;
    double t = 0;
    double helix_rad = kDegreesToRadians(helix);
    double h_f = helix_rad / fillet_;
    double der = 0;
    double der2 = 0;
    KVector3D last_pos;
    while (1) {
        if (isZero(r)) {
            double ecc_dy = -fillet_ * eccentricity_ / radius_;
            result.pos.setXYZ(ir, ecc_dy, 0);
            result.normal.setXYZ(0, 0, -1);
            result.tangent.setXYZ(radius_, eccentricity_, 0);
            result.tangent.normalize();
            der = 0;
            der2 = 0;
            t = 0;
        } else {
            double ar = r + ir;
            double f_z2 = kSquareDifference(fillet_, r);
            double f_z = kSqrt(f_z2);
            t += delta_r * der + der2 * delta_r * delta_r / 2;
            double cost = kCos(t);
            double sint = kSin(t);
            double ecc_dy = -(1 - ar / radius_) * eccentricity_;
            double h = fillet_ - f_z;
            result.pos.setXYZ(ar * cost, ar * sint + ecc_dy, fillet_ - f_z);
            double arclen2 = result.pos.distanceSquaredToPoint(last_pos);
            if (arclen2 > dlen2) {
                delta_r /= 2;
                r -= delta_r;
                t = ts.last();
                continue;
            }

            double x = h * h_f;
            double tan1 = kTan(x);
            double sec2 = kDerivative8(x);
            double rt = r * kTan(x);
            if (!isZero(f_z, EPS3)) {
                der = rt / (ar * f_z);
                der2 = ((tan1 + r*sec2*h_f*r/f_z)*ar*f_z - rt*(f_z - ar*r/f_z)) / (ar*ar*f_z2);
                result.tangent.setXYZ(cost - ar*sint*der, sint + ar*cost*der + eccentricity_/radius_, r/f_z);
            } else {
                result.tangent.setXYZ(-sint*tan1, cost*tan1, 1);
            }
            result.tangent.normalize();
            result.normal.setXYZ(r * cost, r * sint, -f_z);
            result.normal.normalize();
        }

        last_pos = result.pos;
        if (r >= r0) {
            results << result;
            ts << t;
        }
        if (isEqual(r, r1))
            break;
        r += delta_r;
        if (r > r1) {
            delta_r += r1 - r;
            r = r1;
        }
    }
    }

    return results;
}

QVector<PosTanNor> KFilletCylinder::posTanNorOnBlade_Linear2(
        double helix, double r0, double r1, double dlen, QVector<double> &ts) const
{
    if (isZero(helix)) {
        return posTanNorOnBlade_Straight(r0, r1, dlen, ts);
    }

    QVector<PosTanNor> results;
    PosTanNor result;
    ts.clear();
    double ir = radius_ - fillet_;
    r0 -= ir;
    r1 -= ir;
    if (isZero(r0))
        r0 = 0;
    if (isEqual(r1, fillet_))
        r1 = fillet_;

    {
    double r = 0;
    double last_r = 0;
    double t = 0;
    double delta_t = 0.0001;
    double helix_rad = kDegreesToRadians(helix);
    double h_f = helix_rad / fillet_;
    double f_h = fillet_ / helix_rad;

    while (1) {
        if (isZero(t)) {
            double ecc_dy = -fillet_ * eccentricity_ / radius_;
            result.pos.setXYZ(ir, ecc_dy, 0);
            result.normal.setXYZ(0, 0, -1);
            result.tangent.setXYZ(radius_, eccentricity_, 0);
            result.tangent.normalize();
        } else {
            double z = f_h * kAcos(kExp(-h_f*radius_*t));
            double f_z = fillet_ - z;
            double r2 = kSquareDifference(fillet_, f_z);
            r = kSqrt(r2);
            double cost = kCos(t);
            double sint = kSin(t);
            double ar = r + ir;
            double ecc_dy = -(1 - ar / radius_) * eccentricity_;
            double x = ar * cost;
            double y = ar * sint + ecc_dy;
            result.pos.setXYZ(x, y, z);

            double dz_dt = radius_ / kTan(z * h_f);
            double dr_dt = f_z / r * dz_dt;
            double dx_dt = dr_dt * cost - ar * sint;
            double dy_dt = dr_dt * sint + ar * cost + eccentricity_ / radius_ * dr_dt;
            result.tangent.setXYZ(dx_dt, dy_dt, dz_dt);

            result.tangent.normalize();
            result.normal.setXYZ(r * cost, r * sint, -f_z);
            result.normal.normalize();
        }

        if (last_r > r)
            break;
        if (r >= r0) {
            results << result;
            ts << t;
        }
        t += delta_t;
        last_r = r;
    }
    }

    return results;
}

QVector<PosTanNor> KFilletCylinder::posTanNorOnBlade_Equal(
        double lead, double dlen, double t0, double t1, QVector<double> &ts) const
{
    ts.clear();
    ts << t0;
    QVector<PosTanNor> results;
    KVector3D pos = posOnFilletBlade(lead, t0);
    KVector3D tangent = tanOnFilletBlade(lead, t0);
    KVector3D normal = normalOnFilletBlade(lead, t0);
    PosTanNor ptn = {pos, tangent, normal};
    results << ptn;

    double dt = 0.02;
    while (t0 < t1) {
        double t = t0 + dt;
        if (t > t1) {
            t = t1;
            dt = t1 - t0;
        }
        KVector3D next = posOnFilletBlade(lead, t);
        if (next.distanceToPoint(pos) > dlen) {
            dt /= 2;
            continue;
        }
        t0 = t;
        ts << t;
        pos = next;
        ptn.pos = pos;
        ptn.tangent = tanOnFilletBlade(lead, t);
        ptn.normal = normalOnFilletBlade(lead, t);
        results << ptn;
    }

    return results;
}

QVector<PosTanNor> KFilletCylinder::posTanNorOnBlade_Straight(
        double r0, double r1, double dlen, QVector<double> &ts) const
{
    double dt = dlen / fillet_; // 每小段旋转角度
    double ir = radius_ - fillet_;
    double t0 = kAsin((r0 - ir) / fillet_);
    double t1 = kAsin((r1 - ir) / fillet_);
    int slices = (t1 - t0) / dt + 1;
    dt = (t1 - t0) / slices;
    KVector3D cp(0, 0, -1);
    cp.rotateY_Radian(-t0);
    KVector3D center(ir, 0, fillet_);

    QVector<PosTanNor> results;
    ts.clear();
    for (int i = 0; i <= slices; ++i) {
        KVector3D pos = center + cp * fillet_;
        KVector3D tangent = cp.rotatedY_Radian(-K_PI_2);
        results << PosTanNor{pos, tangent, cp};
        ts << t0;
        cp.rotateY_Radian(-dt);
        t0 += dt;
    }

    return results;
}
