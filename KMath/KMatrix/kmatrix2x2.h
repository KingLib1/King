#ifndef KMATRIX2X2_H
#define KMATRIX2X2_H

#include "kvector2d.h"
#include "KPair.h"

class KING_EXPORT KMatrix2x2
{
public:
    KMatrix2x2();
    KMatrix2x2(double m11, double m12, double m21, double m22);
    KMatrix2x2(const KVector2D &v1, const KVector2D &v2);

    void swapRow();
    void swapColumn();
    void transpose();
    void setToIdentity();
    inline void setXAxis(const KVector2D &xaxis);
    inline void setXAxis(double x, double y);
    inline void setYAxis(const KVector2D &yaxis);
    inline void setYAxis(double x, double y);

    inline double m11() const {return m_[0][0];}
    inline double m12() const {return m_[0][1];}
    inline double m21() const {return m_[1][0];}
    inline double m22() const {return m_[1][1];}
    inline KVector2D xAxis() const;
    inline KVector2D yAxis() const;
    inline double determinant() const;
    KMatrix2x2 transposed() const;
    KMatrix2x2 inverted(bool *invertible = nullptr) const;
    bool isSymmetric() const; // 是否为对称矩阵
    KPair<double, double> eigenvalues() const;
    KPair<KVector2D, KVector2D> eigenvectors(KPair<double, double> &eigenvalues) const;

    KMatrix2x2 operator+(const KMatrix2x2 &matrix) const;
    KMatrix2x2 operator-(const KMatrix2x2 &matrix) const;
    KVector2D operator*(const KVector2D &vector) const;
    KMatrix2x2 operator*(const KMatrix2x2 &matrix) const;
    KMatrix2x2 operator*(double factor) const;
    KMatrix2x2 operator/(double divisor) const;
    KMatrix2x2 &operator=(const KMatrix2x2 &matrix);
    KMatrix2x2 &operator+=(const KMatrix2x2 &matrix);
    KMatrix2x2 &operator-=(const KMatrix2x2 &matrix);
    KMatrix2x2 &operator*=(double factor);
    KMatrix2x2 &operator*=(const KMatrix2x2 &matrix);
    KMatrix2x2 &operator/=(double divisor);

private:
    double m_[2][2];
};

inline void KMatrix2x2::setXAxis(const KVector2D &xaxis)
{
    m_[0][0] = xaxis.x();
    m_[1][0] = xaxis.y();
}

inline void KMatrix2x2::setXAxis(double x, double y)
{
    m_[0][0] = x;
    m_[1][0] = y;
}

inline void KMatrix2x2::setYAxis(const KVector2D &yaxis)
{
    m_[0][1] = yaxis.x();
    m_[1][1] = yaxis.y();
}

inline void KMatrix2x2::setYAxis(double x, double y)
{
    m_[0][1] = x;
    m_[1][1] = y;
}

inline KVector2D KMatrix2x2::xAxis() const
{
    return KVector2D(m_[0][0], m_[1][0]);
}

inline KVector2D KMatrix2x2::yAxis() const
{
    return KVector2D(m_[0][1], m_[1][1]);
}

inline double KMatrix2x2::determinant() const
{
    return m_[0][0] * m_[1][1] - m_[0][1] * m_[1][0];
}

#endif // KMATRIX2X2_H
