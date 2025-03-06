#include "kjointcoor4.h"

KJointCoor4::KJointCoor4() : j1_(0), j2_(0), j3_(0), j4_(0)
{

}

KJointCoor4::KJointCoor4(double j1, double j2, double j3, double j4) :
    j1_(j1), j2_(j2), j3_(j3), j4_(j4)
{

}

KJointCoor4::KJointCoor4(const KJointCoor4 &other) :
    j1_(other.j1_), j2_(other.j2_), j3_(other.j3_), j4_(other.j4_)
{

}

KJointCoor4::~KJointCoor4()
{

}
