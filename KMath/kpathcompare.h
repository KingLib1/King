#ifndef KPATHCOMPARE_H
#define KPATHCOMPARE_H

#include <QVector>

#include "kvector3d.h"
#include "kindex2d.h"

// 3D点路径对比
class KING_EXPORT KPathCompare
{
public:
    KPathCompare(const QVector<KVector3D> &path1,
                 const QVector<KVector3D> &path2);

    inline void setPath1(const QVector<KVector3D> &path1);
    inline void setPath2(const QVector<KVector3D> &path2);
    // 设置判断坐标为相等的误差值
    inline void setErrorValue(double delta);
    void compare();

    inline double errorValue() const;
    inline double matchRatio1() const;
    inline double matchRatio2() const;

private:
    QVector<KVector3D> interpolation(const QVector<KVector3D> &path,
                                     const QVector<double> &dis,
                                     double delta, double &mindis) const;
    QVector<KVector3D> LCS(const QVector<KVector3D> &v1,
                           const QVector<KVector3D> &v2,
                           QVector<KIndex2D> &indexes);
    QVector<double> calculateDistance(const QVector<KVector3D> &v1, double &mindis) const;
    void duplicationRemoval(QVector<KVector3D> &ring);


    QVector<KVector3D> path1_;
    QVector<KVector3D> path2_;
    double delta_ = EPS2; // 坐标相等判断的误差值

    double match_ratio1_ = 0; // 路径1中与路径2吻合的占比
    double match_ratio2_ = 0; // 路径2中与路径1吻合的占比
};

inline void KPathCompare::setPath1(const QVector<KVector3D> &path1)
{
    path1_ = path1;
}

inline void KPathCompare::setPath2(const QVector<KVector3D> &path2)
{
    path2_ = path2;
}

inline void KPathCompare::setErrorValue(double delta)
{
    delta_ = delta;
}

inline double KPathCompare::errorValue() const
{
    return delta_;
}

inline double KPathCompare::matchRatio1() const
{
    return match_ratio1_;
}

inline double KPathCompare::matchRatio2() const
{
    return match_ratio2_;
}

#endif // KPATHCOMPARE_H
