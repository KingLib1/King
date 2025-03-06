#include "jointrange6.h"

JointRange6::JointRange6()
{
    range1_.setRange(-170, 170);
    range2_.setRange(-75, 110);
    range3_.setRange(-120, 50);
    range4_.setRange(-160, 160);
    range5_.setRange(-120, 120);
    range6_.setRange(-360, 360);
}

JointRange6::JointRange6(
        const KRange &range1, const KRange &range2, const KRange &range3,
        const KRange &range4, const KRange &range5, const KRange &range6) :
    range1_(range1), range2_(range2), range3_(range3),
    range4_(range4), range5_(range5), range6_(range6)
{

}

JointRange6::JointRange6(const JointRange6 &range) :
    range1_(range.range1_), range2_(range.range2_), range3_(range.range3_),
    range4_(range.range4_), range5_(range.range5_), range6_(range.range6_)
{

}

JointRange6::~JointRange6()
{

}
