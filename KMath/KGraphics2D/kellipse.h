#ifndef KELLIPSE_H
#define KELLIPSE_H

#include "krect.h"
#include "klinear.h"
#include "kcircle2d.h"

class KING_EXPORT KEllipse
{
public:
    KEllipse();
    KEllipse(double a, double b);
    KEllipse(double center_x, double center_y, double a, double b);
    KEllipse(const KPointF &center, double a, double b);
    /**
     * @brief 椭圆圆心和椭圆上两点确定一个椭圆
     */
    KEllipse(const KPointF &center, const KPointF &p1, const KPointF &p2);
    /**
     * @brief 根据椭圆外的from点到椭圆最近的点为nearest，以及a,b值确定一个椭圆,
     * 返回最近点的t值
     */
    KEllipse(double a, double b, const KPointF &from, const KPointF &nearest,
             double &t);
    /**
     * @brief 根据椭圆外的from点到椭圆最远的点为farest，以及a,b值确定一个椭圆,
     * 返回最远点的t值
     */
    KEllipse(double a, double b, const KPointF &from, const KPointF &farest,
             double &t, int far_type);

    inline double centerX() const {return center_.x();}
    inline double centerY() const {return center_.y();}
    inline const KPointF &center() const;
    inline double a() const {return a_;}
    inline double a2() const {return kSquare(a_);}
    inline double b() const {return b_;}
    inline double b2() const {return kSquare(b_);}
    inline double c() const;
    inline KRect boundingRect() const;
    bool contains(const KPointF &point) const;
    /**
     * @brief 椭圆与圆求交, 返回相交点和椭圆t值
     */
    KPair<KPointF, KPointF> intersect(const KCircle2D &c,
                                      KPair<double, double> &tpair,
                                      bool *success = nullptr);
    /**
     * @brief 计算与给定圆相切并经过pos点的椭圆
     * @param circle 相切的圆
     * @param pos 椭圆上一点
     * @param count 返回椭圆数量
     */
    static KPair<KEllipse, KEllipse> tangentToCircleAndThroughPos(
            double a, double b, const KCircle2D &circle, const KPointF &pos);

    /**
     * @brief 在椭圆上离给定点距离最近的点
     */
    KPointF nearestPoint(const KPointF &p) const;
    /**
     * @brief 最近点的参数t值
     */
    double nearestPointTValue(const KPointF &p) const;
    /**
     * @brief 给定点到椭圆的最短距离的平方
     */
    inline double nearestDistanceSquare(const KPointF &p) const;
    /**
     * @brief 给定点到椭圆的最短距离
     */
    inline double nearestDistance(const KPointF &p) const;

    KPointF farestPoint(const KPointF &p) const;
    double farestPointTValue(const KPointF &p) const;
    inline double farestDistanceSquare(const KPointF &p) const;
    inline double farestDistance(const KPointF &p) const;
    /**
     * @brief 计算以tangent为切向量的点的t值
     * @param tangent切向量
     * @return
     */
    double tValueByTangent(const KVector2D &tangent) const;

    /**
     * @brief curvature
     * @param radian
     * @return 曲率
     */
    inline double curvature(double radian) const;
    inline double topY(double x) const;
    inline double rightX(double y) const;
    inline double tX(double t) const; // 参数t求x位置
    inline double tY(double t) const;  // 参数t求y位置
    inline KPointF tPos(double t) const; // 参数t求位置
    KPointF rPos(double radian) const; // 弧度求位置
    inline KVector2D tTangentVector(double t) const;
    inline KVector2D tNormal(double t) const;
    inline KLinear tTangent(double t) const;
    inline void setCenter(const KPointF &center);
    inline void setA(double a) {a_ = a;}
    inline void setB(double b) {b_ = b;}

private:
    KPointF center_;
    double a_;
    double b_;
};

inline const KPointF &KEllipse::center() const
{
    return center_;
}

inline double KEllipse::c() const
{
    return kSqrt(kFabs(kSquareDifference(a_, b_)));
}

inline KRect KEllipse::boundingRect() const
{
    return KRect(centerX() - a_, centerY() - b_,
                 centerX() + a_, centerY() + b_);
}

inline double KEllipse::nearestDistanceSquare(const KPointF &p) const
{
    return nearestPoint(p).distanceSquaredToPoint(p);
}

inline double KEllipse::nearestDistance(const KPointF &p) const
{
    return nearestPoint(p).distanceToPoint(p);
}

inline double KEllipse::farestDistanceSquare(const KPointF &p) const
{
    return farestPoint(p).distanceSquaredToPoint(p);
}

inline double KEllipse::farestDistance(const KPointF &p) const
{
    return farestPoint(p).distanceToPoint(p);
}

inline double KEllipse::curvature(double radian) const
{
    double sinr = kSin(radian);
    double cosr = kCos(radian);
    return a_ * b_ / kPow(a_ * a_ * sinr * sinr + b_ * b_ * cosr * cosr, 1.5);
}

inline double KEllipse::topY(double x) const
{
    x -= centerX();
    return b_ * kSqrt(1 - x * x / (a_ * a_)) + centerY();
}

inline double KEllipse::rightX(double y) const
{
    y-= centerY();
    return a_ * kSqrt(1 - y * y / (b_ * b_)) + centerX();
}

inline double KEllipse::tX(double t) const
{
    return a_ * kCos(t) + center_.x();
}

inline double KEllipse::tY(double t) const
{
    return b_ * kSin(t) + center_.y();
}

inline KPointF KEllipse::tPos(double t) const
{
    return KPointF(tX(t), tY(t));
}

inline KVector2D KEllipse::tTangentVector(double t) const
{
    return KVector2D(-a_ * kSin(t), b_ * kCos(t));
}

inline KVector2D KEllipse::tNormal(double t) const
{
    return tTangentVector(t).rotatedNeg90();
}

inline KLinear KEllipse::tTangent(double t) const
{
    double cosr = kCos(t);
    double sinr = kSin(t);
    return KLinear(a_ * cosr, b_ * sinr, -b_ * cosr / (a_ * sinr));
}

inline void KEllipse::setCenter(const KPointF &center)
{
    center_ = center;
}

#endif // KELLIPSE_H
