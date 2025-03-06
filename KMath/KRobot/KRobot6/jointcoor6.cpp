#include "jointcoor6.h"

JointCoor6::JointCoor6() : j1_(0), j2_(0), j3_(0), j4_(0), j5_(0), j6_(0)
{

}

JointCoor6::JointCoor6(double j1, double j2, double j3,
                         double j4, double j5, double j6) :
    j1_(j1), j2_(j2), j3_(j3), j4_(j4), j5_(j5), j6_(j6)
{

}

JointCoor6::JointCoor6(const JointCoor6 &other) :
    j1_(other.j1_), j2_(other.j2_), j3_(other.j3_),
    j4_(other.j4_), j5_(other.j5_), j6_(other.j6_)
{

}

JointCoor6::~JointCoor6()
{

}
