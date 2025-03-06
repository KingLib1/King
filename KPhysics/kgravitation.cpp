#include "kgravitation.h"

KGravitation::KGravitation() : m1_(0), m2_(0), distance_(1)
{

}

KGravitation::KGravitation(double m1, double m2, double distance) :
    m1_(m1), m2_(m2), distance_(distance)
{

}

KGravitation::KGravitation(const KGravitation &gra) :
    m1_(gra.m1_), m2_(gra.m2_), distance_(gra.distance_)
{

}

KGravitation::~KGravitation()
{

}
