#ifndef KJOINTCOOR4_H
#define KJOINTCOOR4_H

#include "kmath.h"

class KJointCoor4
{
public:
    KJointCoor4();
    KJointCoor4(double j1, double j2, double j3, double j4);
    KJointCoor4(const KJointCoor4 &other);
    ~KJointCoor4();

    inline void setJ1(double j1);
    inline void setJ2(double j2);
    inline void setJ3(double j3);
    inline void setJ4(double j4);

    inline double j1() const;
    inline double j2() const;
    inline double j3() const;
    inline double j4() const;
    /**
     * @brief 返回新的关节坐标，角度转成弧度，3轴平移轴不修改
     */
    inline KJointCoor4 degreesToRadians() const;
    /**
     * @brief 返回新的关节坐标，弧度转成角度，3轴平移轴不修改
     */
    inline KJointCoor4 radiansToDegrees() const;

    inline KJointCoor4 &operator=(const KJointCoor4 &other);

private:
    double j1_; // A
    double j2_; // B
    double j3_; // 平移轴Z
    double j4_; //C
};

inline void KJointCoor4::setJ1(double j1)
{
    j1_ = j1;
}

inline void KJointCoor4::setJ2(double j2)
{
    j2_ = j2;
}

inline void KJointCoor4::setJ3(double j3)
{
    j3_ = j3;
}

inline void KJointCoor4::setJ4(double j4)
{
    j4_ = j4;
}

inline double KJointCoor4::j1() const
{
    return j1_;
}

inline double KJointCoor4::j2() const
{
    return j2_;
}

inline double KJointCoor4::j3() const
{
    return j3_;
}

inline double KJointCoor4::j4() const
{
    return j4_;
}

inline KJointCoor4 KJointCoor4::degreesToRadians() const
{
    return KJointCoor4(kDegreesToRadians(j1_), kDegreesToRadians(j2_),
                       j3_, kDegreesToRadians(j4_));
}

inline KJointCoor4 KJointCoor4::radiansToDegrees() const
{
    return KJointCoor4(kRadiansToDegrees(j1_), kRadiansToDegrees(j2_),
                       j3_, kRadiansToDegrees(j4_));
}

inline KJointCoor4 &KJointCoor4::operator=(const KJointCoor4 &other)
{
    j1_ = other.j1_;
    j2_ = other.j2_;
    j3_ = other.j3_;
    j4_ = other.j4_;
    return *this;
}

#endif // KJOINTCOOR4_H
