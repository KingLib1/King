#include "kindex2d.h"

KIndex2D::KIndex2D() : i_(0), j_(0)
{

}

KIndex2D::KIndex2D(int i, int j) : i_(i), j_(j)
{

}

KIndex2D::KIndex2D(const KIndex2D &index) : i_(index.i_), j_(index.j_)
{

}

KIndex2D::~KIndex2D()
{

}
