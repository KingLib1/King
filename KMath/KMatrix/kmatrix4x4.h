#ifndef KMATRIX4X4_H
#define KMATRIX4X4_H

#include "kmatrix3x3.h"
#include "kvector4d.h"

class KING_EXPORT KMatrix4x4
{
public:
    KMatrix4x4();
    KMatrix4x4(const KMatrix3x3 &matrix);
    KMatrix4x4(const KMatrix3x3 &matrix, const KVector3D &translate);
    KMatrix4x4(const KMatrix4x4 &matrix);
    KMatrix4x4(const KVector3D &xaxis, const KVector3D &yaxis,
               const KVector3D &zaxis);
    KMatrix4x4(const KVector3D &xaxis, const KVector3D &yaxis,
               const KVector3D &zaxis, const KVector3D &translate);
    KMatrix4x4(double m11, double m12, double m13, double m14,
               double m21, double m22, double m23, double m24,
               double m31, double m32, double m33, double m34,
               double m41, double m42, double m43, double m44);
    KMatrix4x4(double m[16]);
    KMatrix4x4(double m[4][4]);
    KMatrix3x3 toMatrix3x3() const;

    double determinant();
    KMatrix4x4 inverted(bool *invertible = nullptr) const;
    void transpose();

    /**
     * @brief 围绕自己坐标系下的轴转
     */
    inline void rotateBySelf(double angle, const KVector3D &axis);
    void rotateXBySelf(double angle);
    void rotateYBySelf(double angle);
    void rotateZBySelf(double angle);
    inline void rotateByBase(double angle, const KVector3D &axis);

    inline void translateBySelf(double dx, double dy, double dz);
    inline void translateBySelf(const KVector3D &dv);
    inline void translateByBase(double dx, double dy, double dz);
    inline void translateByBase(const KVector3D &dv);
    inline void translateX(double x);
    inline void translateY(double y);
    inline void translateZ(double z);

    inline void scale(const KVector3D &vector);
    void scale(double x, double y, double z);
    inline void scale(double x, double y);
    void scale(double factor);

    inline void setColumn(int index, const KVector3D &value);
    inline void setColumn(int index, const KVector4D &value);
    void setToIdentity();

    void getData(double m[4][4]) const;
    inline double m11() const {return m_[0][0];}
    inline double m12() const {return m_[0][1];}
    inline double m13() const {return m_[0][2];}
    inline double m14() const {return m_[0][3];}
    inline double m21() const {return m_[1][0];}
    inline double m22() const {return m_[1][1];}
    inline double m23() const {return m_[1][2];}
    inline double m24() const {return m_[1][3];}
    inline double m31() const {return m_[2][0];}
    inline double m32() const {return m_[2][1];}
    inline double m33() const {return m_[2][2];}
    inline double m34() const {return m_[2][3];}
    inline double m41() const {return m_[3][0];}
    inline double m42() const {return m_[3][1];}
    inline double m43() const {return m_[3][2];}
    inline double m44() const {return m_[3][3];}
    inline double element(int row, int column) const {return m_[row][column];}
    inline KVector4D row(int index) const;
    inline KVector4D column(int index) const;
    inline KVector3D xAxis() const;
    inline KVector3D yAxis() const;
    inline KVector3D zAxis() const;
    inline KVector3D translation() const;

    static KMatrix4x4 rotateAroundMatrix(double angle, const KVector3D &axis);
    static KMatrix4x4 rotateAroundMatrix(const KVector3D &point, double angle,
                                         const KVector3D &axis);
    static KMatrix4x4 scaleMatrix(double factor, const KVector3D &axis);
    static KMatrix4x4 orthographicProjectionMatrix(const KVector3D &normal);
    static KMatrix4x4 orthographicProjectionMatrix(const KVector3D &point,
                                                   const KVector3D &normal);
    static KMatrix4x4 reflectionMatrix(const KVector3D &normal);
    static KMatrix4x4 reflectionMatrix(const KVector3D &point,
                                       const KVector3D &normal);

    KVector3D operator*(const KVector3D &vector) const;
    KMatrix4x4 operator*(const KMatrix4x4 &rhs) const;
    KMatrix4x4 &operator*=(const KMatrix4x4 &rhs);
    KMatrix4x4 &operator*=(double factor);
    KMatrix4x4 &operator=(const KMatrix4x4 &matrix);

    void debug();

private:
    void swapRow(int row1, int row2);

    /**
     * @brief 初等行变换之某行乘以c
     */
    inline void rowTimes(double c, int row);

    /**
     * @brief 初等行变换之row1行的c倍加到row2行
     */
    inline void addCTimesAnotherRow(double c, int row1, int row2);


    double determinant3(double m[3][3]) const;

    inline double determinant2(double m[2][2]) const
    {
        return m[0][0] * m[1][1] - m[0][1] * m[1][0];
    }

    /**
     * @brief 计算3阶代数余子式
     */
    double algebraicCofactor3(double m[4][4], int row, int column) const;

    /**
     * @brief 计算2阶代数余子式
     */
    double algebraicCofactor2(double m[3][3], int row, int column) const;

    inline bool isZero(double n) const;

    double m_[4][4];
};

inline void KMatrix4x4::rotateBySelf(double angle, const KVector3D &axis)
{
    (*this) *= rotateAroundMatrix(angle, axis);
}

inline void KMatrix4x4::rotateByBase(double angle, const KVector3D &axis)
{
    (*this) = rotateAroundMatrix(angle, axis) * (*this);
}

inline void KMatrix4x4::translateBySelf(double dx, double dy, double dz)
{
    m_[0][3] += m_[0][0] * dx + m_[0][1] * dy + m_[0][2] * dz;
    m_[1][3] += m_[1][0] * dx + m_[1][1] * dy + m_[1][2] * dz;
    m_[2][3] += m_[2][0] * dx + m_[2][1] * dy + m_[2][2] * dz;
    m_[3][3] += m_[3][0] * dx + m_[3][1] * dy + m_[3][2] * dz;
}

inline void KMatrix4x4::translateBySelf(const KVector3D &dv)
{
    translateBySelf(dv.x(), dv.y(), dv.z());
}

inline void KMatrix4x4::translateByBase(double dx, double dy, double dz)
{
    m_[0][3] += dx;
    m_[1][3] += dy;
    m_[2][3] += dz;
}

inline void KMatrix4x4::translateByBase(const KVector3D &dv)
{
    m_[0][3] += dv.x();
    m_[1][3] += dv.y();
    m_[2][3] += dv.z();
}

inline void KMatrix4x4::translateX(double x)
{
    m_[0][3] += m_[0][0] * x;
    m_[1][3] += m_[1][0] * x;
    m_[2][3] += m_[2][0] * x;
    m_[3][3] += m_[3][0] * x;
}

inline void KMatrix4x4::translateY(double y)
{
    m_[0][3] += m_[0][1] * y;
    m_[1][3] += m_[1][1] * y;
    m_[2][3] += m_[2][1] * y;
    m_[3][3] += m_[3][1] * y;
}

inline void KMatrix4x4::translateZ(double z)
{
    m_[0][3] += m_[0][2] * z;
    m_[1][3] += m_[1][2] * z;
    m_[2][3] += m_[2][2] * z;
    m_[3][3] += m_[3][2] * z;
}

inline void KMatrix4x4::scale(const KVector3D &vector)
{
    scale(vector.x(), vector.y(), vector.z());
}

inline void KMatrix4x4::scale(double x, double y)
{
    m_[0][0] *= x;
    m_[1][0] *= x;
    m_[2][0] *= x;
    m_[3][0] *= x;
    m_[0][1] *= y;
    m_[1][1] *= y;
    m_[2][1] *= y;
    m_[3][1] *= y;
}

inline void KMatrix4x4::setColumn(int index, const KVector3D &value)
{
    m_[0][index] = value.x();
    m_[1][index] = value.y();
    m_[2][index] = value.z();
}

inline void KMatrix4x4::setColumn(int index, const KVector4D &value)
{
    m_[0][index] = value.x();
    m_[1][index] = value.y();
    m_[2][index] = value.z();
    m_[3][index] = value.w();
}

inline KVector4D KMatrix4x4::row(int index) const
{
    if (index < 0 || index > 3)
        return KVector4D();
    return KVector4D(m_[index][0], m_[index][1], m_[index][2], m_[index][3]);
}

inline KVector4D KMatrix4x4::column(int index) const
{
    if (index < 0 || index > 3)
        return KVector4D();
    return KVector4D(m_[0][index], m_[1][index], m_[2][index], m_[3][index]);
}

inline KVector3D KMatrix4x4::xAxis() const
{
    return KVector3D(m11(), m21(), m31());
}

inline KVector3D KMatrix4x4::yAxis() const
{
    return KVector3D(m12(), m22(), m32());
}

inline KVector3D KMatrix4x4::zAxis() const
{
    return KVector3D(m13(), m23(), m33());
}

inline KVector3D KMatrix4x4::translation() const
{
    return KVector3D(m14(), m24(), m34());
}

inline void KMatrix4x4::rowTimes(double c, int row)
{
    m_[row][0] *= c;
    m_[row][1] *= c;
    m_[row][2] *= c;
    m_[row][3] *= c;
}

inline void KMatrix4x4::addCTimesAnotherRow(double c, int row1, int row2)
{
    m_[row2][0] += m_[row1][0] * c;
    m_[row2][1] += m_[row1][1] * c;
    m_[row2][2] += m_[row1][2] * c;
    m_[row2][3] += m_[row1][3] * c;
}

inline bool KMatrix4x4::isZero(double n) const
{
    return kFabs(n) < EPS3;
}

#endif // KMATRIX4X4_H
