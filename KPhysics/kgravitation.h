#ifndef KGRAVITATION_H
#define KGRAVITATION_H

#include "KPhysics.h"
#include "kmath.h"

class KGravitation
{
public:
    KGravitation();
    KGravitation(double m1, double m2, double distance);
    KGravitation(const KGravitation &gra);
    ~KGravitation();

    inline void setM1(double m);
    inline void setM2(double m);
    inline void setDistance(double distance);

    inline double m1() const;
    inline double m2() const;
    inline double distance() const;
    /**
     * @brief 计算万有引力
     */
    inline double gravitation() const;

    inline KGravitation &operator=(const KGravitation &gra);

private:
    double m1_;
    double m2_;
    double distance_;
};

inline void KGravitation::setM1(double m)
{
    m1_ = m;
}

inline void KGravitation::setM2(double m)
{
    m2_ = m;
}

inline void KGravitation::setDistance(double distance)
{
    distance_ = distance;
}

inline double KGravitation::m1() const
{
    return m1_;
}

inline double KGravitation::m2() const
{
    return m2_;
}

inline double KGravitation::distance() const
{
    return distance_;
}

inline double KGravitation::gravitation() const
{
    return GRAVITATIONALCONST * m1_ * m2_ / kSquare(distance_);
}

inline KGravitation &KGravitation::operator=(const KGravitation &gra)
{
    m1_ = gra.m1_;
    m2_ = gra.m2_;
    distance_ = gra.distance_;
    return *this;
}

#endif // KGRAVITATION_H
