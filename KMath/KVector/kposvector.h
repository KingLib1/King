#ifndef KPOSVECTOR_H
#define KPOSVECTOR_H

#include "kvector3d.h"

// 用于表示点的位置和方向矢量
class KING_EXPORT KPosVector
{
public:
    KPosVector();
    KPosVector(const KVector3D &pos, const KVector3D &vector);

    void rotateX(double angle);
    void rotateY(double angle);
    void rotateZ(double angle);
    void rotate(const KVector3D &point, double angle, const KVector3D &axis);
    inline void translate(const KVector3D &dv);
    inline void translateZ(double dz);

    KVector3D pos;
    KVector3D vector;
};


inline void KPosVector::translate(const KVector3D &dv)
{
    pos.translate(dv);
}

inline void KPosVector::translateZ(double dz)
{
    pos.translateZ(dz);
}

#endif // KPOSVECTOR_H
