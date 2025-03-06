#ifndef KPRISM_H
#define KPRISM_H

#include <QVector>

#include "kvector3d.h"

class KPrism
{
public:
    KPrism();
    KPrism(const QVector<KVector3D> &bottom, const KVector3D &direction,
           double height);

    inline void setBottom(const QVector<KVector3D> &bottom);
    inline void setDirection(const KVector3D &direction);
    inline void setHeight(double height);

    inline const QVector<KVector3D> &bottom() const;
    inline const KVector3D &direction() const;
    inline double height() const;

    QVector<QVector<KVector3D>> split(int rings) const;

private:
    QVector<KVector3D> bottom_; // 底面多边形
    KVector3D dir_; // 拉伸方向
    double height_; // 拉伸高度
};

inline void KPrism::setBottom(const QVector<KVector3D> &bottom)
{
    bottom_ = bottom;
}

inline void KPrism::setDirection(const KVector3D &direction)
{
    dir_ = direction;
    dir_.normalize();
}

inline void KPrism::setHeight(double height)
{
    height_ = height;
}

inline const QVector<KVector3D> &KPrism::bottom() const
{
    return bottom_;
}

inline const KVector3D &KPrism::direction() const
{
    return dir_;
}

inline double KPrism::height() const
{
    return height_;
}

#endif // KPRISM_H
