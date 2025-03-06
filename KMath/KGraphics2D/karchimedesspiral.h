#ifndef KARCHIMEDESSPIRAL_H
#define KARCHIMEDESSPIRAL_H

#include "kpointf.h"

class KING_EXPORT KArchimedesSpiral
{
public:
    KArchimedesSpiral();

    /**
     * @brief 阿基米德螺旋线
     * @param a 起点到原点距离
     * @param b 单位弧度极径增量
     */
    KArchimedesSpiral(double a, double b);

    KPointF pos(double radian) const;

private:
    double a_ = 0;
    double b_ = 0;
};

#endif // KSPRING_H
