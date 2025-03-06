#ifndef KMATRIX3X3_H
#define KMATRIX3X3_H

#include "kvector3d.h"

class KING_EXPORT KMatrix3x3
{
public:
    KMatrix3x3();
    KMatrix3x3(const KMatrix3x3 &matrix);
    KMatrix3x3(const KVector3D &v1, const KVector3D &v2, const KVector3D&v3);
    KMatrix3x3(double m[9]);
    KMatrix3x3(double m11, double m12, double m13,
               double m21, double m22, double m23,
               double m31, double m32, double m33);

    void rotateByBase(double angle, const KVector3D &axis);
    inline void rotateBySelf(double angle, const KVector3D &axis);
    void rotateX(double angle);
    void rotateY(double angle);
    void rotateZ(double angle);

    inline double m11() const {return m_[0][0];}
    inline double m12() const {return m_[0][1];}
    inline double m13() const {return m_[0][2];}
    inline double m21() const {return m_[1][0];}
    inline double m22() const {return m_[1][1];}
    inline double m23() const {return m_[1][2];}
    inline double m31() const {return m_[2][0];}
    inline double m32() const {return m_[2][1];}
    inline double m33() const {return m_[2][2];}
    inline double element(int row, int column) const {return m_[row][column];}
    inline double determinant() const;
    inline KVector3D row(int index) const;
    inline KVector3D column(int index) const;
    inline KVector3D xAxis() const;
    inline KVector3D yAxis() const;
    inline KVector3D zAxis() const;
    static KMatrix3x3 rotateAroundMatrix(double angle, const KVector3D &axis);
    static KMatrix3x3 scaleMatrix(double factor, const KVector3D &axis);
    static KMatrix3x3 orthographicProjectionMatrix(const KVector3D &normal);
    static KMatrix3x3 reflectionMatrix(const KVector3D &normal);

    /**
     * @brief 转置此矩阵
     */
    void transpose();

    /**
     * @brief 返回新的转置矩阵，不改变此矩阵
     */
    KMatrix3x3 transposed() const;

    bool isOrthonormal() const;

    void getData(double m[3][3]) const;
    void getData(double m[9]) const;

    KMatrix3x3 operator*(const KMatrix3x3 &rhs) const;
    KVector3D operator*(const KVector3D &vector) const;
    KMatrix3x3 &operator*=(const KMatrix3x3 &matrix);
    KMatrix3x3 &operator=(const KMatrix3x3 &rhs);

    void debug();

private:
    inline bool isZero(double n) const;
    inline bool isEqual(double a, double b) const;

    double m_[3][3];
};

inline void KMatrix3x3::rotateBySelf(double angle, const KVector3D &axis)
{
    *this *= rotateAroundMatrix(angle, axis);
}

inline double KMatrix3x3::determinant() const
{
    return m11()*m22()*m33() + m12()*m23()*m31() + m13()*m21()*m32() -
            m13()*m22()*m31() - m12()*m21()*m33() - m11()*m23()*m32();
}

inline KVector3D KMatrix3x3::row(int index) const
{
    if (index < 0 || index > 2)
        return KVector3D();
    return KVector3D(m_[index][0], m_[index][1], m_[index][2]);
}

inline KVector3D KMatrix3x3::column(int index) const
{
    if (index < 0 || index > 2)
        return KVector3D();
    return KVector3D(m_[0][index], m_[1][index], m_[2][index]);
}

inline KVector3D KMatrix3x3::xAxis() const
{
    return KVector3D(m11(), m21(), m31());
}

inline KVector3D KMatrix3x3::yAxis() const
{
    return KVector3D(m12(), m22(), m32());
}

inline KVector3D KMatrix3x3::zAxis() const
{
    return KVector3D(m13(), m23(), m33());
}

inline bool KMatrix3x3::isZero(double n) const
{
    return kFabs(n) < EPS3;
}

inline bool KMatrix3x3::isEqual(double a, double b) const
{
    return kFabs(a - b) < EPS3;
}

#endif // KMATRIX3X3_H
