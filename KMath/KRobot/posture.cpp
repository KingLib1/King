#include "posture.h"

Posture::Posture()
{

}

Posture::Posture(const KVector3D &pos, const KVector3D &euler_angles) :
    pos_(pos), euler_(euler_angles)
{

}

Posture::Posture(const KVector3D &pos, const KEulerAngles &euler_angles) :
    pos_(pos), euler_(euler_angles)
{

}

Posture::Posture(double x, double y, double z, double rx, double ry, double rz)
{
    pos_.setXYZ(x, y, z);
    euler_.setRxyz(rx, ry, rz);
}

Posture::Posture(const KMatrix4x4 &matrix) : euler_(matrix)
{
    pos_.setXYZ(matrix.m14(), matrix.m24(), matrix.m34());
}

Posture::Posture(const KRectCoordSystem3D &sys) :
    pos_(sys.origin()), euler_(sys)
{

}

Posture::Posture(const Posture &other) : pos_(other.pos_), euler_(other.euler_)
{

}

Posture::~Posture()
{

}
