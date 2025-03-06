#ifndef KLINE2D_H
#define KLINE2D_H

#include "kvector2d.h"

class KING_EXPORT KLine2D
{
public:
    KLine2D();
    KLine2D(const KPointF &p1, const KPointF &p2);
    ~KLine2D();

    inline const KVector2D &direction() const;
    inline double distanceFromPoint(const KPointF &point) const;

private:
    KPointF p_;
    KVector2D direction_;
};

inline const KVector2D &KLine2D::direction() const
{
    return direction_;
}

inline double KLine2D::distanceFromPoint(const KPointF &point) const
{
    KVector2D p13(p_, point);
    return kFabs(KVector2D::crossProduct(direction_, p13));
}

#endif // KLINE2D_H
