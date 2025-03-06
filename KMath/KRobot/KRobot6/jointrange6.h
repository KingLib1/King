#ifndef JOINTRANGE6_H
#define JOINTRANGE6_H

#include "krange.h"
#include "jointcoor6.h"

class JointRange6
{
public:
    JointRange6();
    JointRange6(const KRange &range1, const KRange &range2,
               const KRange &range3, const KRange &range4,
               const KRange &range5, const KRange &range6);
    JointRange6(const JointRange6 &range);
    ~JointRange6();

    inline void setRange1(const KRange &range);
    inline void setRange2(const KRange &range);
    inline void setRange3(const KRange &range);
    inline void setRange4(const KRange &range);
    inline void setRange5(const KRange &range);
    inline void setRange6(const KRange &range);

    inline const KRange &range1() const;
    inline const KRange &range2() const;
    inline const KRange &range3() const;
    inline const KRange &range4() const;
    inline const KRange &range5() const;
    inline const KRange &range6() const;

    inline bool contains1(double j1) const;
    inline bool contains2(double j2) const;
    inline bool contains3(double j3) const;
    inline bool contains4(double j4) const;
    inline bool contains5(double j5) const;
    inline bool contains6(double j6) const;
    inline bool contains(const JointCoor6 &coor) const;

    inline JointRange6 &operator=(const JointRange6 &other);

private:
    KRange range1_;
    KRange range2_;
    KRange range3_;
    KRange range4_;
    KRange range5_;
    KRange range6_;
};

inline void JointRange6::setRange1(const KRange &range)
{
    range1_ = range;
}

inline void JointRange6::setRange2(const KRange &range)
{
    range2_ = range;
}

inline void JointRange6::setRange3(const KRange &range)
{
    range3_ = range;
}

inline void JointRange6::setRange4(const KRange &range)
{
    range4_ = range;
}

inline void JointRange6::setRange5(const KRange &range)
{
    range5_ = range;
}

inline void JointRange6::setRange6(const KRange &range)
{
    range6_ = range;
}

inline const KRange &JointRange6::range1() const
{
    return range1_;
}

inline const KRange &JointRange6::range2() const
{
    return range2_;
}

inline const KRange &JointRange6::range3() const
{
    return range3_;
}

inline const KRange &JointRange6::range4() const
{
    return range4_;
}

inline const KRange &JointRange6::range5() const
{
    return range5_;
}

inline const KRange &JointRange6::range6() const
{
    return range6_;
}

inline bool JointRange6::contains1(double j1) const
{
    return range1_.contains(j1);
}

inline bool JointRange6::contains2(double j2) const
{
    return range2_.contains(j2);
}

inline bool JointRange6::contains3(double j3) const
{
    return range3_.contains(j3);
}

inline bool JointRange6::contains4(double j4) const
{
    return range4_.contains(j4);
}

inline bool JointRange6::contains5(double j5) const
{
    return range5_.contains(j5);
}

inline bool JointRange6::contains6(double j6) const
{
    return range6_.contains(j6);
}

inline bool JointRange6::contains(const JointCoor6 &coor) const
{
    return contains1(coor.j1()) && contains2(coor.j2()) &&
            contains3(coor.j3()) && contains4(coor.j4()) &&
            contains5(coor.j5()) && contains6(coor.j6());
}

inline JointRange6 &JointRange6::operator=(const JointRange6 &other)
{
    range1_ = other.range1_;
    range2_ = other.range2_;
    range3_ = other.range3_;
    range4_ = other.range4_;
    range5_ = other.range5_;
    range6_ = other.range6_;
    return *this;
}

#endif // JOINTRANGE6_H
