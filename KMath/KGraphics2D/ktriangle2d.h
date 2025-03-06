#ifndef KTRIANGLE2D_H
#define KTRIANGLE2D_H

#include "kvector2d.h"
#include "krect.h"
#include "krange.h"

class KING_EXPORT KTriangle2D
{
public:
    KTriangle2D();
    KTriangle2D(const KPointF &p1, const KPointF &p2, const KPointF &p3);
    KTriangle2D(const KTriangle2D &triangle);
    ~KTriangle2D();

    inline void setTriangle(const KPointF &p1, const KPointF &p2,
                            const KPointF &p3);
    inline void setP1(const KPointF &p1);
    inline void setP1(double x, double y);
    inline void setP2(const KPointF &p2);
    inline void setP2(double x, double y);
    inline void setP3(const KPointF &p3);
    inline void setP3(double x, double y);

    /**
     * @brief 转成顺时针方向
     */
    inline void toClockwise();
    /**
     * @brief 转成逆时针方向
     */
    inline void toAnticlockwise();
    inline void translate(double x, double y);
    inline void translate(const KVector2D &dv);

    inline const KPointF &p1() const;
    inline const KPointF &p2() const;
    inline const KPointF &p3() const;
    inline KVector2D v12() const;
    inline KVector2D v21() const;
    inline KVector2D v13() const;
    inline KVector2D v31() const;
    inline KVector2D v23() const;
    inline KVector2D v32() const;
    inline bool clockwise() const;
    inline double perimeter() const;
    inline double area() const;
    inline double top() const;
    inline double bottom() const;
    inline double left() const;
    inline double right() const;
    inline bool containsPoint(const KPointF &point) const;
    inline KRect boundingRect() const;
    inline KRange xRange() const;
    inline KRange yRange() const;
    inline KTriangle2D translated(double dx, double dy) const;
    inline KTriangle2D translated(const KVector2D &dv) const;

    inline KTriangle2D operator-(const KVector2D &dv) const;
    inline KTriangle2D operator+(const KVector2D &dv) const;
    inline KTriangle2D &operator-=(const KVector2D &dv);
    inline KTriangle2D &operator+=(const KVector2D &dv);
    inline KTriangle2D &operator=(const KTriangle2D &triangle);

private:
    KPointF p1_;
    KPointF p2_;
    KPointF p3_;
};

inline void KTriangle2D::setTriangle(const KPointF &p1, const KPointF &p2,
                                     const KPointF &p3)
{
    p1_ = p1;
    p2_ = p2;
    p3_ = p3;
}

inline void KTriangle2D::setP1(const KPointF &p1)
{
    p1_ = p1;
}

inline void KTriangle2D::setP1(double x, double y)
{
    p1_.setXY(x, y);
}

inline void KTriangle2D::setP2(const KPointF &p2)
{
    p2_ = p2;
}

inline void KTriangle2D::setP2(double x, double y)
{
    p2_.setXY(x, y);
}

inline void KTriangle2D::setP3(const KPointF &p3)
{
    p3_ = p3;
}

inline void KTriangle2D::setP3(double x, double y)
{
    p3_.setXY(x, y);
}

inline void KTriangle2D::toClockwise()
{
    if (!clockwise()) {
        KPointF temp(p2_);
        p2_ = p3_;
        p3_ = temp;
    }
}

inline void KTriangle2D::toAnticlockwise()
{
    if (clockwise()) {
        KPointF temp(p2_);
        p2_ = p3_;
        p3_ = temp;
    }
}

inline void KTriangle2D::translate(double x, double y)
{
    p1_.translate(x, y);
    p2_.translate(x, y);
    p3_.translate(x, y);
}

inline void KTriangle2D::translate(const KVector2D &dv)
{
    p1_ += dv;
    p2_ += dv;
    p3_ += dv;
}

inline const KPointF &KTriangle2D::p1() const
{
    return p1_;
}

inline const KPointF &KTriangle2D::p2() const
{
    return p2_;
}

inline const KPointF &KTriangle2D::p3() const
{
    return p3_;
}

inline KVector2D KTriangle2D::v12() const
{
    return KVector2D(p1_, p2_);
}

inline KVector2D KTriangle2D::v21() const
{
    return KVector2D(p2_, p1_);
}

inline KVector2D KTriangle2D::v13() const
{
    return KVector2D(p1_, p3_);
}

inline KVector2D KTriangle2D::v31() const
{
    return KVector2D(p3_, p1_);
}

inline KVector2D KTriangle2D::v23() const
{
    return KVector2D(p2_, p3_);
}

inline KVector2D KTriangle2D::v32() const
{
    return KVector2D(p3_, p2_);
}

inline bool KTriangle2D::clockwise() const
{
    return KVector2D::crossProduct(KVector2D(p1_, p2_), KVector2D(p1_, p3_))
            < 0 ? true : false;
}

inline double KTriangle2D::perimeter() const
{
    return v12().length() + v13().length() + v23().length();
}

inline double KTriangle2D::area() const
{
    return 0.5 * KVector2D::crossProduct(v12(), v13());
}

inline double KTriangle2D::top() const
{
    return kMax(p1_.y(), p2_.y(), p3_.y());
}

inline double KTriangle2D::bottom() const
{
    return kMin(p1_.y(), p2_.y(), p3_.y());
}

inline double KTriangle2D::left() const
{
    return kMin(p1_.x(), p2_.x(), p3_.x());
}

inline double KTriangle2D::right() const
{
    return kMax(p1_.x(), p2_.x(), p3_.x());
}

inline bool KTriangle2D::containsPoint(const KPointF &point) const
{
    double dot = KVector2D::crossProduct(v12(), KVector2D(p1_, point));
    if (dot >= 0) {
        if (KVector2D::crossProduct(v23(), KVector2D(p2_, point)) >= 0 &&
                KVector2D::crossProduct(v31(), KVector2D(p3_, point)) >= 0)
            return true;
    }
    if (dot <= 0) {
        if (KVector2D::crossProduct(v23(), KVector2D(p2_, point)) <= 0 &&
                KVector2D::crossProduct(v31(), KVector2D(p3_, point)) <= 0)
            return true;
    }
    return false;
}

inline KRect KTriangle2D::boundingRect() const
{
    return KRect(KPointF(left(), bottom()), KPointF(right(), top()));
}

inline KRange KTriangle2D::xRange() const
{
    return KRange(left(), right());
}

inline KRange KTriangle2D::yRange() const
{
    return KRange(bottom(), top());
}

inline KTriangle2D KTriangle2D::translated(double dx, double dy) const
{
    return KTriangle2D(p1_.translated(dx, dy),
                       p2_.translated(dx, dy),
                       p3_.translated(dx, dy));
}

inline KTriangle2D KTriangle2D::translated(const KVector2D &dv) const
{
    return *this + dv;
}

inline KTriangle2D KTriangle2D::operator-(const KVector2D &dv) const
{
    return KTriangle2D(p1_ - dv, p2_ - dv, p3_ - dv);
}

inline KTriangle2D KTriangle2D::operator+(const KVector2D &dv) const
{
    return KTriangle2D(p1_ + dv, p2_ + dv, p3_ + dv);
}

inline KTriangle2D &KTriangle2D::operator-=(const KVector2D &dv)
{
    translate(-dv);
    return *this;
}

inline KTriangle2D &KTriangle2D::operator+=(const KVector2D &dv)
{
    translate(dv);
    return *this;
}

inline KTriangle2D &KTriangle2D::operator=(const KTriangle2D &triangle)
{
    p1_ = triangle.p1_;
    p2_ = triangle.p2_;
    p3_ = triangle.p3_;
    return *this;
}

#endif // KTRIANGLE2D_H
