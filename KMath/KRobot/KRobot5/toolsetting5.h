#ifndef TOOLSETTING5_H
#define TOOLSETTING5_H

#include "KPair.h"

/**
 * @brief calculateToolOffset
 * @param len1 第一臂长
 * @param len2 第二臂长
 * @param a1 b1 第一次对点的两关节角度
 * @param a2 b2 第二次对点的两关节角度
 * @return 零度状态下刀具相对于第二臂末端的长度偏移和弧度偏移
 */
KPair<double, double> calculateToolOffset(double len1, double len2, double a1,
                                          double b1, double a2, double b2);

#endif // TOOLSETTING5_H
