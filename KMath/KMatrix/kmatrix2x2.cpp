#include "kmatrix2x2.h"

#include "kquadratic.h"

KMatrix2x2::KMatrix2x2()
{
    m_[0][0] = 1;
    m_[0][1] = 0;
    m_[1][0] = 0;
    m_[1][1] = 1;
}

KMatrix2x2::KMatrix2x2(double m11, double m12, double m21, double m22)
{
    m_[0][0] = m11;
    m_[0][1] = m12;
    m_[1][0] = m21;
    m_[1][1] = m22;
}

KMatrix2x2::KMatrix2x2(const KVector2D &v1, const KVector2D &v2)
{
    m_[0][0] = v1.x();
    m_[0][1] = v2.x();
    m_[1][0] = v1.y();
    m_[1][1] = v2.y();
}

void KMatrix2x2::swapRow()
{
    double m11 = m_[0][0];
    double m12 = m_[0][1];
    m_[0][0] = m_[1][0];
    m_[0][1] = m_[1][1];
    m_[1][0] = m11;
    m_[1][1] = m12;
}

void KMatrix2x2::swapColumn()
{
    double m11 = m_[0][0];
    double m21 = m_[1][0];
    m_[0][0] = m_[0][1];
    m_[1][0] = m_[1][1];
    m_[0][1] = m11;
    m_[1][1] = m21;
}

void KMatrix2x2::transpose()
{
    double temp = m_[0][1];
    m_[0][1] = m_[1][0];
    m_[1][0] = temp;
}

void KMatrix2x2::setToIdentity()
{
    m_[0][0] = 1;
    m_[0][1] = 0;
    m_[1][0] = 0;
    m_[1][1] = 1;
}

KMatrix2x2 KMatrix2x2::transposed() const
{
    return KMatrix2x2(m_[0][0], m_[1][0], m_[0][1], m_[1][1]);
}

KMatrix2x2 KMatrix2x2::inverted(bool *invertible) const
{
    double d = determinant();
    if (isZero(d)) {
        if (invertible)
            *invertible = false;
        return KMatrix2x2();
    }

    if (invertible)
        *invertible = true;
    return KMatrix2x2(m22()/d, -m12()/d, -m21()/d, m11()/d);
}

bool KMatrix2x2::isSymmetric() const
{
    return isEqual(m12(), m21());
}

KPair<double, double> KMatrix2x2::eigenvalues() const
{
    KQuadratic qua(1, -m11() - m22(), m11()*m22() - m12()*m21());
    return qua.root();
}

KPair<KVector2D, KVector2D> KMatrix2x2::eigenvectors(
        KPair<double, double> &eigenvalues) const
{
    KPair<KVector2D, KVector2D> vs;
    eigenvalues = this->eigenvalues();
    double l1 = eigenvalues.first;
    double l2 = eigenvalues.second;
    if (!isEqual(l1, l2)) {
        KMatrix2x2 A(l1 - m11(), -m12(), -m21(), l1 - m22());
        if (isZero(A.m11())) {
            A.swapRow();
        }
        if (isZero(A.m11())) {
            vs.first.setXY(1, 0);
        } else {
            vs.first.setXY(-A.m12(), A.m11());
        }

        A.m_[0][0] = l2 - m11();
        A.m_[0][1] = -m12();
        A.m_[1][0] = -m21();
        A.m_[1][1] = l2 - m22();
        if (isZero(A.m11())) {
            A.swapRow();
        }
        if (isZero(A.m11())) {
            vs.second.setXY(1, 0);
        } else {
            vs.second.setXY(-A.m12(), A.m11());
        }
    } else {
        KMatrix2x2 A(l1 - m11(), -m12(), -m21(), l1 - m22());
        if (isZero(A.m11())) {
            A.swapRow();
        }
        if (isZero(A.m11())) {
            if (isZero(A.m12())) {
                A.swapRow();
            }
            if (isZero(A.m12())) {
                vs.first.setXY(1, 0);
                vs.second.setXY(0, 1);
            } else {
                vs.first.setXY(1, 0);
                vs.second = vs.first;
            }
        } else {
            vs.first.setXY(-A.m12(), A.m11());
            vs.second = vs.first;
        }
    }

    vs.first.normalize();
    vs.second.normalize();
    return vs;
}

KMatrix2x2 KMatrix2x2::operator+(const KMatrix2x2 &matrix) const
{
    return KMatrix2x2(m_[0][0] + matrix.m_[0][0], m_[0][1] + matrix.m_[0][1],
                      m_[1][0] + matrix.m_[1][0], m_[1][1] + matrix.m_[1][1]);
}

KMatrix2x2 KMatrix2x2::operator-(const KMatrix2x2 &matrix) const
{
    return KMatrix2x2(m_[0][0] - matrix.m_[0][0], m_[0][1] - matrix.m_[0][1],
                      m_[1][0] - matrix.m_[1][0], m_[1][1] - matrix.m_[1][1]);
}

KVector2D KMatrix2x2::operator*(const KVector2D &vector) const
{
    return KVector2D(m_[0][0]*vector.x() + m_[0][1]*vector.y(),
                     m_[1][0]*vector.x() + m_[1][1]*vector.y());
}

KMatrix2x2 KMatrix2x2::operator*(double factor) const
{
    return KMatrix2x2(m_[0][0] * factor, m_[0][1] * factor,
                      m_[1][0] * factor, m_[1][1] * factor);
}

KMatrix2x2 KMatrix2x2::operator/(double divisor) const
{
    return KMatrix2x2(m_[0][0] / divisor, m_[0][1] / divisor,
                      m_[1][0] / divisor, m_[1][1] / divisor);
}

KMatrix2x2 KMatrix2x2::operator*(const KMatrix2x2 &matrix) const
{
    return KMatrix2x2(m_[0][0]*matrix.m_[0][0] + m_[0][1]*matrix.m_[1][0],
                      m_[0][0]*matrix.m_[0][1] + m_[0][1]*matrix.m_[1][1],
                      m_[1][0]*matrix.m_[0][0] + m_[1][1]*matrix.m_[1][0],
                      m_[1][0]*matrix.m_[0][1] + m_[1][1]*matrix.m_[1][1]);
}

KMatrix2x2 &KMatrix2x2::operator=(const KMatrix2x2 &matrix)
{
    m_[0][0] = matrix.m_[0][0];
    m_[0][1] = matrix.m_[0][1];
    m_[1][0] = matrix.m_[1][0];
    m_[1][1] = matrix.m_[1][1];
    return *this;
}

KMatrix2x2 &KMatrix2x2::operator+=(const KMatrix2x2 &matrix)
{
    m_[0][0] += matrix.m_[0][0];
    m_[0][1] += matrix.m_[0][1];
    m_[1][0] += matrix.m_[1][0];
    m_[1][1] += matrix.m_[1][1];
    return *this;
}

KMatrix2x2 &KMatrix2x2::operator-=(const KMatrix2x2 &matrix)
{
    m_[0][0] -= matrix.m_[0][0];
    m_[0][1] -= matrix.m_[0][1];
    m_[1][0] -= matrix.m_[1][0];
    m_[1][1] -= matrix.m_[1][1];
    return *this;
}

KMatrix2x2 &KMatrix2x2::operator*=(double factor)
{
    m_[0][0] *= factor;
    m_[0][1] *= factor;
    m_[1][0] *= factor;
    m_[1][1] *= factor;
    return *this;
}

KMatrix2x2 &KMatrix2x2::operator*=(const KMatrix2x2 &matrix)
{
    double m11 = m_[0][0]*matrix.m_[0][0] + m_[0][1]*matrix.m_[1][0];
    double m12 = m_[0][0]*matrix.m_[0][1] + m_[0][1]*matrix.m_[1][1];
    double m21 = m_[1][0]*matrix.m_[0][0] + m_[1][1]*matrix.m_[1][0];
    double m22 = m_[1][0]*matrix.m_[0][1] + m_[1][1]*matrix.m_[1][1];
    m_[0][0] = m11;
    m_[0][1] = m12;
    m_[1][0] = m21;
    m_[1][1] = m22;
    return *this;
}

KMatrix2x2 &KMatrix2x2::operator/=(double divisor)
{
    m_[0][0] /= divisor;
    m_[0][1] /= divisor;
    m_[1][0] /= divisor;
    m_[1][1] /= divisor;
    return *this;
}
