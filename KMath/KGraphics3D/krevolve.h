#ifndef KREVOLVE_H
#define KREVOLVE_H

#include <QVector>

#include "KPair.h"
#include "kpointf.h"
#include "kvector3d.h"

using OutlineData = QVector<KPair<KPointF, double>>;

class KING_EXPORT KRevolve
{
public:
    KRevolve();
    KRevolve(const OutlineData &data);

    KVector3D posOnBlade(double lead, double t) const;
    KVector3D tangentOnBlade(double lead, double t) const;
    KPair<KVector3D, KVector3D> posAndTanOnBlade(double lead, double t) const;

private:
    OutlineData data_;
};

#endif // KREVOLVE_H
