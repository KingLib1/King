#ifndef JOINTCOOR6_H
#define JOINTCOOR6_H

#include "kmath.h"

class JointCoor6
{
public:
    JointCoor6();
    JointCoor6(double j1, double j2, double j3,
                double j4, double j5, double j6);
    JointCoor6(const JointCoor6 &other);
    ~JointCoor6();

    inline void setJ1(double j1);
    inline void setJ2(double j2);
    inline void setJ3(double j3);
    inline void setJ4(double j4);
    inline void setJ5(double j5);
    inline void setJ6(double j6);

    inline double j1() const;
    inline double j2() const;
    inline double j3() const;
    inline double j4() const;
    inline double j5() const;
    inline double j6() const;

    inline JointCoor6 degreesToRadians() const;
    inline JointCoor6 radiansToDegrees() const;

    inline JointCoor6 &operator=(const JointCoor6 &other);

private:
    double j1_;
    double j2_;
    double j3_;
    double j4_;
    double j5_;
    double j6_;
};

inline void JointCoor6::setJ1(double j1)
{
    j1_ = j1;
}

inline void JointCoor6::setJ2(double j2)
{
    j2_ = j2;
}

inline void JointCoor6::setJ3(double j3)
{
    j3_ = j3;
}

inline void JointCoor6::setJ4(double j4)
{
    j4_ = j4;
}

inline void JointCoor6::setJ5(double j5)
{
    j5_ = j5;
}

inline void JointCoor6::setJ6(double j6)
{
    j6_ = j6;
}

inline double JointCoor6::j1() const
{
    return j1_;
}

inline double JointCoor6::j2() const
{
    return j2_;
}

inline double JointCoor6::j3() const
{
    return j3_;
}

inline double JointCoor6::j4() const
{
    return j4_;
}

inline double JointCoor6::j5() const
{
    return j5_;
}

inline double JointCoor6::j6() const
{
    return j6_;
}

inline JointCoor6 JointCoor6::degreesToRadians() const
{
    return JointCoor6(kDegreesToRadians(j1_), kDegreesToRadians(j2_),
                       kDegreesToRadians(j3_), kDegreesToRadians(j4_),
                       kDegreesToRadians(j5_), kDegreesToRadians(j6_));
}

inline JointCoor6 JointCoor6::radiansToDegrees() const
{
    return JointCoor6(kRadiansToDegrees(j1_), kRadiansToDegrees(j2_),
                       kRadiansToDegrees(j3_), kRadiansToDegrees(j4_),
                       kRadiansToDegrees(j5_), kRadiansToDegrees(j6_));

}

inline JointCoor6 &JointCoor6::operator=(const JointCoor6 &other)
{
    j1_ = other.j1_;
    j2_ = other.j2_;
    j3_ = other.j3_;
    j4_ = other.j4_;
    j5_ = other.j5_;
    j6_ = other.j6_;
    return *this;
}

#endif // JOINTCOOR6_H
