#ifndef KTRIANGLEMESH_H
#define KTRIANGLEMESH_H

#include "kvector3d.h"

class KING_EXPORT KTriangleMesh
{
public:
    KTriangleMesh();
    KTriangleMesh(const KTriangleMesh &mesh);
    ~KTriangleMesh();

    inline void setP1(const KVector3D &p1);
    inline void setP2(const KVector3D &p2);
    inline void setP3(const KVector3D &p3);
    inline void setNormal1(const KVector3D &normal1);
    inline void setNormal2(const KVector3D &normal2);
    inline void setNormal3(const KVector3D &norma33);

    inline const KVector3D &p1() const;
    inline const KVector3D &p2() const;
    inline const KVector3D &p3() const;
    inline const KVector3D &normal1() const;
    inline const KVector3D &normal2() const;
    inline const KVector3D &normal3() const;

    KTriangleMesh &operator=(const KTriangleMesh &mesh);

private:
    KVector3D p1_;
    KVector3D p2_;
    KVector3D p3_;
    KVector3D normal1_;
    KVector3D normal2_;
    KVector3D normal3_;
};

inline void KTriangleMesh::setP1(const KVector3D &p1)
{
    p1_ = p1;
}

inline void KTriangleMesh::setP2(const KVector3D &p2)
{
    p2_ = p2;
}

inline void KTriangleMesh::setP3(const KVector3D &p3)
{
    p3_ = p3;
}

inline void KTriangleMesh::setNormal1(const KVector3D &normal1)
{
    normal1_ = normal1;
}

inline void KTriangleMesh::setNormal2(const KVector3D &normal2)
{
    normal2_ = normal2;
}

inline void KTriangleMesh::setNormal3(const KVector3D &normal3)
{
    normal3_ = normal3;
}

inline const KVector3D &KTriangleMesh::p1() const
{
    return p1_;
}

inline const KVector3D &KTriangleMesh::p2() const
{
    return p2_;
}

inline const KVector3D &KTriangleMesh::p3() const
{
    return p3_;
}

inline const KVector3D &KTriangleMesh::normal1() const
{
    return normal1_;
}

inline const KVector3D &KTriangleMesh::normal2() const
{
    return normal2_;
}

inline const KVector3D &KTriangleMesh::normal3() const
{
    return normal3_;
}

#endif // KTRIANGLEMESH_H
