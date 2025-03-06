#include "ktrianglemesh.h"

KTriangleMesh::KTriangleMesh()
{

}

KTriangleMesh::KTriangleMesh(const KTriangleMesh &mesh) :
    p1_(mesh.p1_), p2_(mesh.p2_), p3_(mesh.p3_),
    normal1_(mesh.normal1_), normal2_(mesh.normal2_), normal3_(mesh.normal3_)
{

}

KTriangleMesh::~KTriangleMesh()
{

}

KTriangleMesh &KTriangleMesh::operator=(const KTriangleMesh &mesh)
{
    p1_ = mesh.p1_;
    p2_ = mesh.p2_;
    p3_ = mesh.p3_;
    normal1_ = mesh.normal1_;
    normal2_ = mesh.normal2_;
    normal3_ = mesh.normal3_;
    return *this;
}
