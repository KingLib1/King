#ifndef KGRID3D_H
#define KGRID3D_H

#include <QVector>

#include "kvector3d.h"

class KGrid3D
{
public:
    KGrid3D(double xspace, double yspace, double zspace,
            const KVector3D start, int xnum, int ynum, int znum);



private:
    double xspace_;
    double yspace_;
    double zspace_;

    KVector3D start_;

    int xnum_;
    int ynum_;
    int znum_;
};

#endif // KGRID3D_H
