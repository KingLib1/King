#ifndef KLINEARREGRESSION_H
#define KLINEARREGRESSION_H

#include <QVector>

#include "klinear.h"

/**
 * @brief 一元线性回归（梯度下降法），导数法在KFitting实现
 */
KING_EXPORT KLinear kLinearRegression(QVector<KPointF> points);

/**
 * @brief 二分类逻辑回归（直线划分 ax + by + c = 0）
 * @param points 坐标值
 * @param labels 标签值
 * @param a, b, c 返回决策边界直线参数
 */
KING_EXPORT void LogisticRegression(QVector<KPointF> points,
    const QVector<int> &labels, double &a, double &b, double &c);

#endif // KLINEARREGRESSION_H
