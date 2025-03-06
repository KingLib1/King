#include "kindex3d.h"

KIndex3D::KIndex3D() : i_(0), j_(0), k_(0)
{

}

KIndex3D::KIndex3D(int i, int j, int k) : i_(i), j_(j), k_(k)
{

}

KIndex3D::KIndex3D(const KIndex3D &index) :
    i_(index.i_), j_(index.j_), k_(index.k_)
{

}

KIndex3D::~KIndex3D()
{

}
