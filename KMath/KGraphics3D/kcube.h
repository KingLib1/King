#ifndef KCUBE_H
#define KCUBE_H

#include "ktriangle3d.h"

/**
 * @brief 正方体，无坐标系
 */
class KING_EXPORT KCube
{
public:
    KCube(double side_length = 0);
    KCube(const KVector3D &center, double side_length);

    inline void setCenter(const KVector3D &center);
    inline const KVector3D &center() const;

    inline void setSideLength(double side_length);
    inline double sideLength() const;

    inline void translate(const KVector3D &dv);
    inline void translateX(double dx);
    inline void translateY(double dy);
    inline void translateZ(double dz);

    inline double surfaceArea() const;
    inline double volume() const;
    bool intersects(const KCube &other) const;
    inline KVector3D min() const;
    inline KVector3D max() const;
    /**
     * @brief 表面三角形
     */
    QVector<KTriangle3D> triangulate() const;
    /**
     * @brief 八分
     */
    QVector<KCube> octuple() const;

    inline KCube &operator=(const KCube &other);

private:
    KVector3D center_;
    double side_length_;
};

inline void KCube::setCenter(const KVector3D &center)
{
    center_ = center;
}

inline const KVector3D &KCube::center() const
{
    return center_;
}

inline void KCube::setSideLength(double side_length)
{
    side_length_ = side_length;
}

inline double KCube::sideLength() const
{
    return side_length_;
}

inline void KCube::translate(const KVector3D &dv)
{
    center_ += dv;
}

inline void KCube::translateX(double dx)
{
    center_.translateX(dx);
}

inline void KCube::translateY(double dy)
{
    center_.translateY(dy);
}

inline void KCube::translateZ(double dz)
{
    center_.translateZ(dz);
}

inline double KCube::surfaceArea() const
{
    return kSquare(side_length_) * 6;
}

inline double KCube::volume() const
{
    return kCube(side_length_);
}

inline KCube &KCube::operator=(const KCube &other)
{
    center_ = other.center_;
    side_length_ = other.side_length_;
    return *this;
}

#endif // KCUBE_H
