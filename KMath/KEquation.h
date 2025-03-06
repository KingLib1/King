#ifndef KEQUATION_H
#define KEQUATION_H

#include "kvector2d.h"
#include "KPair.h"
#include "KDynamicMatrix.h"

/**
 * @brief 解线性方程组2x2
 * @param v1 第一列系数
 * @param v2 第二列系数
 * @param v3 常数列
 * @return x1 x2
 */
KING_EXPORT KVector2D solveHomogeneousLinearEquations2x2(
        const KVector2D &v1, const KVector2D &v2, const KVector2D &v3);

/**
 * @brief 解线性方程组3x2
 * @param v1 第一列系数
 * @param v2 第二列系数
 * @param v3 常数列
 * @return x1 x2
 */
KING_EXPORT KVector2D solveHomogeneousLinearEquations3x2(
        const KVector3D &v1, const KVector3D &v2, const KVector3D &v3);

/**
 * @brief 解线性方程组3x3
 * @param v1 第一列系数
 * @param v2 第二列系数
 * @param v3 第三列系数
 * @param v4 常数列
 * @return x1 x2 x3
 */
KING_EXPORT KVector3D solveHomogeneousLinearEquations3x3(
        const KVector3D &v1, const KVector3D &v2,
        const KVector3D &v3, const KVector3D &v4);

/**
 * @brief 解齐次线性方程组 m x n（通用）
 * @param coefficient_matrix:系数矩阵
 */
KING_EXPORT KDynamicMatrix<double> solveHomogeneousLinearEquations(
        const KDynamicMatrix<double> &coefficient_matrix);

/**
 * @brief 解非齐次线性方程组 m x n（通用）
 * @param augmented_matrix:增广矩阵
 * @param solution是否有解
 */
KING_EXPORT KDynamicMatrix<double> solveNonhomogeneousLinearEquations(
        const KDynamicMatrix<double> &augmented_matrix, bool &solution);

// 解方程 x * lnx = y, 求x
KING_EXPORT KPair<double, double> solution1_1(double y, int &count);
// 解方程 x - lnx = y, 求x
KING_EXPORT KPair<double, double> solution1_2(double y, int &count);
/* 解方程组 (相当于圆和直线求交点)
{
x^2 + y^2 = r2
ax + by = c
}*/
KING_EXPORT KPair<KPointF, KPointF> solution2_1(double r2, double a, double b,
                                                double c, int &count);

#endif // KEQUATION_H
