#include "kquaternion.h"

KQuaternion::KQuaternion() : s_(1)
{
    
}

KQuaternion::KQuaternion(double scalar, double x, double y, double z) :
    s_(scalar)
{
    v_.setXYZ(x, y, z);
}

KQuaternion::KQuaternion(double scalar, const KVector3D &v) : s_(scalar), v_(v)
{
    
}

KQuaternion::KQuaternion(const KVector4D &v) : s_(v.w())
{
    v_.setXYZ(v.x(), v.y(), v.z());
}

KQuaternion::KQuaternion(const KQuaternion &q) : s_(q.s_), v_(q.v_)
{
    
}

KQuaternion::~KQuaternion()
{
    
}
