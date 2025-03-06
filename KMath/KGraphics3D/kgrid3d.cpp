#include "kgrid3d.h"

KGrid3D::KGrid3D(double xspace, double yspace, double zspace,
                 const KVector3D start, int xnum, int ynum, int znum) :
    xspace_(xspace), yspace_(yspace), zspace_(zspace), start_(start),
    xnum_(xnum), ynum_(ynum), znum_(znum)
{

}
