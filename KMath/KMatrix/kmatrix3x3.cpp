#include "kmatrix3x3.h"

#include <QDebug>

KMatrix3x3::KMatrix3x3()
{
    m_[0][0] = 1;
    m_[0][1] = 0;
    m_[0][2] = 0;
    m_[1][0] = 0;
    m_[1][1] = 1;
    m_[1][2] = 0;
    m_[2][0] = 0;
    m_[2][1] = 0;
    m_[2][2] = 1;
}

KMatrix3x3::KMatrix3x3(const KMatrix3x3 &matrix)
{
    m_[0][0] = matrix.m_[0][0];
    m_[0][1] = matrix.m_[0][1];
    m_[0][2] = matrix.m_[0][2];
    m_[1][0] = matrix.m_[1][0];
    m_[1][1] = matrix.m_[1][1];
    m_[1][2] = matrix.m_[1][2];
    m_[2][0] = matrix.m_[2][0];
    m_[2][1] = matrix.m_[2][1];
    m_[2][2] = matrix.m_[2][2];
}

KMatrix3x3::KMatrix3x3(const KVector3D &v1, const KVector3D &v2,
                       const KVector3D &v3)
{
    m_[0][0] = v1.x();
    m_[0][1] = v2.x();
    m_[0][2] = v3.x();
    m_[1][0] = v1.y();
    m_[1][1] = v2.y();
    m_[1][2] = v3.y();
    m_[2][0] = v1.z();
    m_[2][1] = v2.z();
    m_[2][2] = v3.z();
}

KMatrix3x3::KMatrix3x3(double m[9])
{
    m_[0][0] = m[0];
    m_[0][1] = m[1];
    m_[0][2] = m[2];
    m_[1][0] = m[3];
    m_[1][1] = m[4];
    m_[1][2] = m[5];
    m_[2][0] = m[6];
    m_[2][1] = m[7];
    m_[2][2] = m[8];
}

KMatrix3x3::KMatrix3x3(double m11, double m12, double m13,
                       double m21, double m22, double m23,
                       double m31, double m32, double m33)
{
    m_[0][0] = m11;
    m_[0][1] = m12;
    m_[0][2] = m13;
    m_[1][0] = m21;
    m_[1][1] = m22;
    m_[1][2] = m23;
    m_[2][0] = m31;
    m_[2][1] = m32;
    m_[2][2] = m33;
}

void KMatrix3x3::rotateByBase(double angle, const KVector3D &axis)
{
    KVector3D n(axis);
    n.normalize();
    double radian = kDegreesToRadians(angle);
    double cosr = kCos(radian);
    double sinr = kSin(radian);

    KVector3D v = xAxis();
    KVector3D z = KVector3D::dotProduct(n, v) * n;
    KVector3D x = v - z;
    KVector3D y = KVector3D::crossProduct(n, x);
    v = cosr * x + sinr * y + z;
    m_[0][0] = v.x();
    m_[1][0] = v.y();
    m_[2][0] = v.z();

    v = yAxis();
    z = KVector3D::dotProduct(n, v) * n;
    x = v - z;
    y = KVector3D::crossProduct(n, x);
    v = cosr * x + sinr * y + z;
    m_[0][1] = v.x();
    m_[1][1] = v.y();
    m_[2][1] = v.z();

    v = zAxis();
    z = KVector3D::dotProduct(n, v) * n;
    x = v - z;
    y = KVector3D::crossProduct(n, x);
    v = cosr * x + sinr * y + z;
    m_[0][2] = v.x();
    m_[1][2] = v.y();
    m_[2][2] = v.z();
}

void KMatrix3x3::rotateX(double angle)
{
    double radian = kDegreesToRadians(angle);
    double sina = kSin(radian);
    double cosa = kCos(radian);
    double m[3][2];
    for (int i = 0; i < 3; ++i) {
        m[i][0] = m_[i][1];
        m[i][1] = m_[i][2];
    }
    for (int i = 0; i < 3; ++i) {
        m_[i][1] = m[i][0]*cosa + m[i][1]*sina;
        m_[i][2] = m[i][1]*cosa - m[i][0]*sina;
    }
}

void KMatrix3x3::rotateY(double angle)
{
    double radian = kDegreesToRadians(angle);
    double sina = kSin(radian);
    double cosa = kCos(radian);
    double m[3][2];
    for (int i = 0; i < 3; ++i) {
        m[i][0] = m_[i][0];
        m[i][1] = m_[i][2];
    }
    for (int i = 0; i < 3; ++i) {
        m_[i][0] = m[i][0]*cosa - m[i][1]*sina;
        m_[i][2] = m[i][0]*sina + m[i][1]*cosa;
    }
}

void KMatrix3x3::rotateZ(double angle)
{
    double radian = kDegreesToRadians(angle);
    double sina = kSin(radian);
    double cosa = kCos(radian);
    double m[3][2];
    for (int i = 0; i < 3; ++i) {
        m[i][0] = m_[i][0];
        m[i][1] = m_[i][1];
    }
    for (int i = 0; i < 3; ++i) {
        m_[i][0] = m[i][0]*cosa + m[i][1]*sina;
        m_[i][1] = m[i][1]*cosa - m[i][0]*sina;
    }
}

KMatrix3x3 KMatrix3x3::rotateAroundMatrix(double angle, const KVector3D &axis)
{
    KVector3D n(axis.normalized());
    double radian = kDegreesToRadians(angle);
    double cosr = kCos(radian);
    double sinr = kSin(radian);
    double xsinr = n.x() * sinr;
    double ysinr = n.y() * sinr;
    double zsinr = n.z() * sinr;
    double _1_cosr = 1 - cosr;
    double xy1_cosr = n.x() * n.y() * _1_cosr;
    double xz1_cosr = n.x() * n.z() * _1_cosr;
    double yz1_cosr = n.y() * n.z() * _1_cosr;
    KMatrix3x3 matrix;
    matrix.m_[0][0] = n.xSquare() * _1_cosr + cosr;
    matrix.m_[1][0] = xy1_cosr + zsinr;
    matrix.m_[2][0] = xz1_cosr - ysinr;
    matrix.m_[0][1] = xy1_cosr - zsinr;
    matrix.m_[1][1] = n.ySquare() * _1_cosr + cosr;
    matrix.m_[2][1] = yz1_cosr + xsinr;
    matrix.m_[0][2] = xz1_cosr + ysinr;
    matrix.m_[1][2] = yz1_cosr - xsinr;
    matrix.m_[2][2] = n.zSquare() * _1_cosr + cosr;
    return matrix;
}

KMatrix3x3 KMatrix3x3::scaleMatrix(double factor, const KVector3D &axis)
{
    KVector3D n(axis.normalized());
    double f_1 = factor - 1;
    KMatrix3x3 matrix;
    matrix.m_[0][0] = 1 + f_1 * n.xSquare();
    matrix.m_[1][0] = f_1 * n.x() * n.y();
    matrix.m_[2][0] = f_1 * n.x() * n.z();

    matrix.m_[0][1] = matrix.m_[1][0];
    matrix.m_[1][1] = 1 + f_1 * n.ySquare();
    matrix.m_[2][1] = f_1 * n.y() * n.z();

    matrix.m_[0][2] = matrix.m_[2][0];
    matrix.m_[1][2] = matrix.m_[2][1];
    matrix.m_[2][2] = 1 + f_1 * n.zSquare();

    return matrix;
}

KMatrix3x3 KMatrix3x3::orthographicProjectionMatrix(const KVector3D &normal)
{
    KVector3D n(normal.normalized());
    KMatrix3x3 matrix;
    matrix.m_[0][0] = 1 - n.xSquare();
    matrix.m_[1][0] = -n.x() * n.y();
    matrix.m_[2][0] = -n.x() * n.z();

    matrix.m_[0][1] = matrix.m_[1][0];
    matrix.m_[1][1] = 1 - n.ySquare();
    matrix.m_[2][1] = -n.y() * n.z();

    matrix.m_[0][2] = matrix.m_[2][0];
    matrix.m_[1][2] = matrix.m_[2][1];
    matrix.m_[2][2] = 1 - n.zSquare();

    return matrix;
}

KMatrix3x3 KMatrix3x3::reflectionMatrix(const KVector3D &normal)
{
    KVector3D n(normal.normalized());
    KMatrix3x3 matrix;
    matrix.m_[0][0] = 1 - 2 * n.xSquare();
    matrix.m_[1][0] = -2 * n.x() * n.y();
    matrix.m_[2][0] = -2 * n.x() * n.z();

    matrix.m_[0][1] = matrix.m_[1][0];
    matrix.m_[1][1] = 1 - 2 * n.ySquare();
    matrix.m_[2][1] = -2 * n.y() * n.z();

    matrix.m_[0][2] = matrix.m_[2][0];
    matrix.m_[1][2] = matrix.m_[2][1];
    matrix.m_[2][2] = 1 - 2 * n.zSquare();

    return matrix;
}

void KMatrix3x3::transpose()
{
    for (int i = 1; i < 3; i++)
        for (int j = 0; j < i; j++) {
            double temp = m_[i][j];
            m_[i][j] = m_[j][i];
            m_[j][i] = temp;
        }
}

KMatrix3x3 KMatrix3x3::transposed() const
{
    KMatrix3x3 matrix(*this);
    matrix.transpose();
    return matrix;
}

bool KMatrix3x3::isOrthonormal() const
{
    KVector3D vx(m_[0][0], m_[1][0], m_[2][0]);
    KVector3D vy(m_[0][1], m_[1][1], m_[2][1]);
    if (kFabs(KVector3D::dotProduct(vx, vy)) > EPS6)
        return false;
    KVector3D vz(m_[0][2], m_[1][2], m_[2][2]);
    if (kFabs(KVector3D::dotProduct(vy, vz)) > EPS6)
        return false;
    if (kFabs(KVector3D::dotProduct(vz, vx)) > EPS6)
        return false;
    if (kFabs(vx.lengthSquared() - 1) > EPS6)
        return false;
    if (kFabs(vy.lengthSquared() - 1) > EPS6)
        return false;
    if (kFabs(vz.lengthSquared() - 1) > EPS6)
        return false;
    return true;
}

void KMatrix3x3::getData(double m[3][3]) const
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            m[i][j] = m_[i][j];
}

void KMatrix3x3::getData(double m[9]) const
{
    int k = 0;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) {
            m[k++] = m_[i][j];
        }
}

KMatrix3x3 KMatrix3x3::operator*(const KMatrix3x3 &rhs) const
{
    KMatrix3x3 matrix1;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            matrix1.m_[i][j] = m_[i][0] * rhs.m_[0][j] +
                               m_[i][1] * rhs.m_[1][j] +
                               m_[i][2] * rhs.m_[2][j];
        }
    }
    return matrix1;
}

KVector3D KMatrix3x3::operator*(const KVector3D &vector) const
{
    double x, y, z;
    x = vector.x() * m_[0][0] + vector.y() * m_[0][1] + vector.z() * m_[0][2];
    y = vector.x() * m_[1][0] + vector.y() * m_[1][1] + vector.z() * m_[1][2];
    z = vector.x() * m_[2][0] + vector.y() * m_[2][1] + vector.z() * m_[2][2];
    return KVector3D(x, y, z);
}

KMatrix3x3 &KMatrix3x3::operator*=(const KMatrix3x3 &matrix)
{
    KMatrix3x3 matrix1;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            matrix1.m_[i][j] = m_[i][0] * matrix.m_[0][j] +
                               m_[i][1] * matrix.m_[1][j] +
                               m_[i][2] * matrix.m_[2][j];
        }
    }
    *this = matrix1;
    return  *this;
}

KMatrix3x3 &KMatrix3x3::operator=(const KMatrix3x3 &rhs)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            m_[i][j] = rhs.m_[i][j];
    return *this;
}

void KMatrix3x3::debug()
{
    for (int i = 0; i < 3; i++)
        qDebug() << m_[i][0] << m_[i][1] << m_[i][2];
}
