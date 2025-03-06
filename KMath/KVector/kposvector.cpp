#include "kposvector.h"

KPosVector::KPosVector()
{

}

KPosVector::KPosVector(const KVector3D &pos, const KVector3D &vector) :
    pos(pos), vector(vector)
{

}

void KPosVector::rotateX(double angle)
{
    pos.rotateX(angle);
    vector.rotateX(angle);
}

void KPosVector::rotateY(double angle)
{
    pos.rotateY(angle);
    vector.rotateY(angle);
}

void KPosVector::rotateZ(double angle)
{
    pos.rotateZ(angle);
    vector.rotateZ(angle);
}

void KPosVector::rotate(const KVector3D &point, double angle,
                        const KVector3D &axis)
{
    pos.rotate(point, angle, axis);
    vector.rotate(angle, axis);
}
