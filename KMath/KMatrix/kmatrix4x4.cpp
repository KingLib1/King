#include "kmatrix4x4.h"

#include <QDebug>

KMatrix4x4::KMatrix4x4()
{
    m_[0][0] = 1;
    m_[0][1] = 0;
    m_[0][2] = 0;
    m_[0][3] = 0;
    m_[1][0] = 0;
    m_[1][1] = 1;
    m_[1][2] = 0;
    m_[1][3] = 0;
    m_[2][0] = 0;
    m_[2][1] = 0;
    m_[2][2] = 1;
    m_[2][3] = 0;
    m_[3][0] = 0;
    m_[3][1] = 0;
    m_[3][2] = 0;
    m_[3][3] = 1;
}

KMatrix4x4::KMatrix4x4(const KMatrix3x3 &matrix)
{
    m_[0][0] = matrix.m11();
    m_[0][1] = matrix.m12();
    m_[0][2] = matrix.m13();
    m_[0][3] = 0;

    m_[1][0] = matrix.m21();
    m_[1][1] = matrix.m22();
    m_[1][2] = matrix.m23();
    m_[1][3] = 0;

    m_[2][0] = matrix.m31();
    m_[2][1] = matrix.m32();
    m_[2][2] = matrix.m33();
    m_[2][3] = 0;

    m_[3][0] = 0;
    m_[3][1] = 0;
    m_[3][2] = 0;
    m_[3][3] = 1;
}

KMatrix4x4::KMatrix4x4(const KMatrix3x3 &matrix, const KVector3D &translate)
{
    m_[0][0] = matrix.m11();
    m_[0][1] = matrix.m12();
    m_[0][2] = matrix.m13();
    m_[0][3] = translate.x();

    m_[1][0] = matrix.m21();
    m_[1][1] = matrix.m22();
    m_[1][2] = matrix.m23();
    m_[1][3] = translate.y();

    m_[2][0] = matrix.m31();
    m_[2][1] = matrix.m32();
    m_[2][2] = matrix.m33();
    m_[2][3] = translate.z();

    m_[3][0] = 0;
    m_[3][1] = 0;
    m_[3][2] = 0;
    m_[3][3] = 1;
}

KMatrix4x4::KMatrix4x4(const KMatrix4x4 &matrix)
{
    m_[0][0] = matrix.m_[0][0];
    m_[0][1] = matrix.m_[0][1];
    m_[0][2] = matrix.m_[0][2];
    m_[0][3] = matrix.m_[0][3];
    m_[1][0] = matrix.m_[1][0];
    m_[1][1] = matrix.m_[1][1];
    m_[1][2] = matrix.m_[1][2];
    m_[1][3] = matrix.m_[1][3];
    m_[2][0] = matrix.m_[2][0];
    m_[2][1] = matrix.m_[2][1];
    m_[2][2] = matrix.m_[2][2];
    m_[2][3] = matrix.m_[2][3];
    m_[3][0] = matrix.m_[3][0];
    m_[3][1] = matrix.m_[3][1];
    m_[3][2] = matrix.m_[3][2];
    m_[3][3] = matrix.m_[3][3];
}

KMatrix4x4::KMatrix4x4(const KVector3D &xaxis, const KVector3D &yaxis,
                       const KVector3D &zaxis)
{
    m_[0][0] = xaxis.x();
    m_[0][1] = yaxis.x();
    m_[0][2] = zaxis.x();
    m_[0][3] = 0;

    m_[1][0] = xaxis.y();
    m_[1][1] = yaxis.y();
    m_[1][2] = zaxis.y();
    m_[1][3] = 0;

    m_[2][0] = xaxis.z();
    m_[2][1] = yaxis.z();
    m_[2][2] = zaxis.z();
    m_[2][3] = 0;

    m_[3][0] = 0;
    m_[3][1] = 0;
    m_[3][2] = 0;
    m_[3][3] = 1;
}

KMatrix4x4::KMatrix4x4(const KVector3D &xaxis, const KVector3D &yaxis,
                       const KVector3D &zaxis, const KVector3D &translate)
{
    m_[0][0] = xaxis.x();
    m_[0][1] = yaxis.x();
    m_[0][2] = zaxis.x();
    m_[0][3] = translate.x();

    m_[1][0] = xaxis.y();
    m_[1][1] = yaxis.y();
    m_[1][2] = zaxis.y();
    m_[1][3] = translate.y();

    m_[2][0] = xaxis.z();
    m_[2][1] = yaxis.z();
    m_[2][2] = zaxis.z();
    m_[2][3] = translate.z();

    m_[3][0] = 0;
    m_[3][1] = 0;
    m_[3][2] = 0;
    m_[3][3] = 1;
}

KMatrix4x4::KMatrix4x4(double m11, double m12, double m13, double m14,
                       double m21, double m22, double m23, double m24,
                       double m31, double m32, double m33, double m34,
                       double m41, double m42, double m43, double m44)
{
    m_[0][0] = m11;
    m_[0][1] = m12;
    m_[0][2] = m13;
    m_[0][3] = m14;
    m_[1][0] = m21;
    m_[1][1] = m22;
    m_[1][2] = m23;
    m_[1][3] = m24;
    m_[2][0] = m31;
    m_[2][1] = m32;
    m_[2][2] = m33;
    m_[2][3] = m34;
    m_[3][0] = m41;
    m_[3][1] = m42;
    m_[3][2] = m43;
    m_[3][3] = m44;
}

KMatrix4x4::KMatrix4x4(double m[16])
{
    int k = 0;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            m_[i][j] = m[k++];
}

KMatrix4x4::KMatrix4x4(double m[4][4])
{
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            m_[i][j] = m[i][j];
}

KMatrix3x3 KMatrix4x4::toMatrix3x3() const
{
    return KMatrix3x3(m11(), m12(), m13(),
                      m21(), m22(), m23(),
                      m31(), m32(), m33());
}

double KMatrix4x4::determinant()
{
    double m[4][4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            m[i][j] = double(m_[i][j]);

    double value = 0;
    for (int i = 0; i < 4; i++)
        value += m[0][i] * algebraicCofactor3(m, 0, i);
    return value;
}

void KMatrix4x4::rotateXBySelf(double angle)
{
    double radian = kDegreesToRadians(angle);
    double sina = kSin(radian);
    double cosa = kCos(radian);
    double m[4][2];
    for (int i = 0; i < 4; ++i) {
        m[i][0] = m_[i][1];
        m[i][1] = m_[i][2];
    }
    for (int i = 0; i < 4; ++i) {
        m_[i][1] = m[i][0]*cosa + m[i][1]*sina;
        m_[i][2] = m[i][1]*cosa - m[i][0]*sina;
    }
}

void KMatrix4x4::rotateYBySelf(double angle)
{
    double radian = kDegreesToRadians(angle);
    double sina = kSin(radian);
    double cosa = kCos(radian);
    double m[4][2];
    for (int i = 0; i < 4; ++i) {
        m[i][0] = m_[i][0];
        m[i][1] = m_[i][2];
    }
    for (int i = 0; i < 4; ++i) {
        m_[i][0] = m[i][0]*cosa - m[i][1]*sina;
        m_[i][2] = m[i][0]*sina + m[i][1]*cosa;
    }
}

void KMatrix4x4::rotateZBySelf(double angle)
{
    double radian = kDegreesToRadians(angle);
    double sina = kSin(radian);
    double cosa = kCos(radian);
    double m[4][2];
    for (int i = 0; i < 4; ++i) {
        m[i][0] = m_[i][0];
        m[i][1] = m_[i][1];
    }
    for (int i = 0; i < 4; ++i) {
        m_[i][0] = m[i][0]*cosa + m[i][1]*sina;
        m_[i][1] = m[i][1]*cosa - m[i][0]*sina;
    }
}

void KMatrix4x4::scale(double x, double y, double z)
{
    m_[0][0] *= x;
    m_[1][0] *= x;
    m_[2][0] *= x;
    m_[3][0] *= x;

    m_[0][1] *= y;
    m_[1][1] *= y;
    m_[2][1] *= y;
    m_[3][1] *= y;

    m_[0][2] *= z;
    m_[1][2] *= z;
    m_[2][2] *= z;
    m_[3][2] *= z;
}

void KMatrix4x4::scale(double factor)
{
    m_[0][0] *= factor;
    m_[1][0] *= factor;
    m_[2][0] *= factor;
    m_[3][0] *= factor;

    m_[0][1] *= factor;
    m_[1][1] *= factor;
    m_[2][1] *= factor;
    m_[3][1] *= factor;

    m_[0][2] *= factor;
    m_[1][2] *= factor;
    m_[2][2] *= factor;
    m_[3][2] *= factor;
}

void KMatrix4x4::setToIdentity()
{
    m_[0][0] = 1;
    m_[0][1] = 0;
    m_[0][2] = 0;
    m_[0][3] = 0;
    m_[1][0] = 0;
    m_[1][1] = 1;
    m_[1][2] = 0;
    m_[1][3] = 0;
    m_[2][0] = 0;
    m_[2][1] = 0;
    m_[2][2] = 1;
    m_[2][3] = 0;
    m_[3][0] = 0;
    m_[3][1] = 0;
    m_[3][2] = 0;
    m_[3][3] = 1;
}

KMatrix4x4 KMatrix4x4::inverted(bool *invertible) const
{
    if (isZero(m_[3][0]) && isZero(m_[3][1]) && isZero(m_[3][2])) {
        KMatrix3x3 rot_mat = toMatrix3x3();
        if (rot_mat.isOrthonormal()) {
            rot_mat.transpose();
            KMatrix4x4 invert(rot_mat);
            invert.translateBySelf(-m_[0][3], -m_[1][3], -m_[2][3]);
            return invert;
        }
    }

    KMatrix4x4 A(*this);
    KMatrix4x4 E;

    for (int turn = 0; turn < 4; ++turn) {
        int i;
        for (i = turn; i < 4; ++i)
            if (kFabs(A.m_[i][turn]) > EPS3)
                break;
        if (i == 4) {
            if (invertible)
                *invertible = false;
            return KMatrix4x4();
        }

        if (i != turn) {
            A.swapRow(turn, i);
            E.swapRow(turn, i);
        }
        double c = 1 / A.m_[turn][turn];
        A.rowTimes(c, turn);
        E.rowTimes(c, turn);

        for (int j = turn + 1; j < 4; j++) {
            c = -A.m_[j][turn];
            A.addCTimesAnotherRow(c, turn, j);
            E.addCTimesAnotherRow(c, turn, j);
        }
    }

    for (int turn = 3; turn > 0; --turn) {
        for (int i = turn - 1; i >= 0; --i) {
            double c = -A.m_[i][turn];
            A.m_[i][turn] = 0;
            E.addCTimesAnotherRow(c, turn, i);
        }
    }

    if (invertible)
        *invertible = true;
    return E;
}

void KMatrix4x4::transpose()
{
    for (int i = 1; i < 4; ++i)
        for (int j = 0; j < i; ++j) {
            double temp = m_[i][j];
            m_[i][j] = m_[j][i];
            m_[j][i] = temp;
        }
}

void KMatrix4x4::getData(double m[4][4]) const
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            m[i][j] = m_[i][j];
}

KMatrix4x4 KMatrix4x4::rotateAroundMatrix(double angle, const KVector3D &axis)
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
    KMatrix4x4 matrix;
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

KMatrix4x4 KMatrix4x4::rotateAroundMatrix(const KVector3D &point, double angle,
                                          const KVector3D &axis)
{
    KVector3D n = axis;
    n.normalize();
    double radian = kDegreesToRadians(angle);
    double cosr = kCos(radian);
    double sinr = kSin(radian);
    KVector3D pos = -point;
    KVector3D z = KVector3D::dotProduct(n, pos) * n;
    KVector3D x = pos - z;
    KVector3D y = KVector3D::crossProduct(n, x);
    pos = cosr * x + sinr * y + z + point;
    double xy = n.x() * n.y();
    double xz = n.x() * n.z();
    double yz = n.y() * n.z();
    double xsinr = n.x() * sinr;
    double ysinr = n.y() * sinr;
    double zsinr = n.z() * sinr;
    double _1_cosr = 1 - cosr;
    KMatrix4x4 matrix;
    matrix.m_[0][0] = n.xSquare() * _1_cosr + cosr;
    matrix.m_[1][0] = xy * _1_cosr + zsinr;
    matrix.m_[2][0] = xz * _1_cosr - ysinr;
    matrix.m_[0][1] = xy * _1_cosr - zsinr;
    matrix.m_[1][1] = n.ySquare() * _1_cosr + cosr;
    matrix.m_[2][1] = yz * _1_cosr + xsinr;
    matrix.m_[0][2] = xz * _1_cosr + ysinr;
    matrix.m_[1][2] = yz * _1_cosr - xsinr;
    matrix.m_[2][2] = n.zSquare() * _1_cosr + cosr;
    matrix.m_[0][3] = pos.x();
    matrix.m_[1][3] = pos.y();
    matrix.m_[2][3] = pos.z();
    return matrix;
}

KMatrix4x4 KMatrix4x4::scaleMatrix(double factor, const KVector3D &axis)
{
    KVector3D n(axis.normalized());
    double f_1 = factor - 1;
    KMatrix4x4 matrix;
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

KMatrix4x4 KMatrix4x4::orthographicProjectionMatrix(const KVector3D &normal)
{
    KVector3D n(normal.normalized());
    KMatrix4x4 matrix;
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

KMatrix4x4 KMatrix4x4::orthographicProjectionMatrix(const KVector3D &point,
                                                    const KVector3D &normal)
{
    KVector3D n(normal.normalized());
    KVector3D pos = -point;
    pos += n * (-KVector3D::dotProduct(n, pos)) + point;
    KMatrix4x4 matrix;
    matrix.m_[0][0] = 1 - n.xSquare();
    matrix.m_[1][0] = -n.x() * n.y();
    matrix.m_[2][0] = -n.x() * n.z();

    matrix.m_[0][1] = matrix.m_[1][0];
    matrix.m_[1][1] = 1 - n.ySquare();
    matrix.m_[2][1] = -n.y() * n.z();

    matrix.m_[0][2] = matrix.m_[2][0];
    matrix.m_[1][2] = matrix.m_[2][1];
    matrix.m_[2][2] = 1 - n.zSquare();

    matrix.m_[0][3] = pos.x();
    matrix.m_[1][3] = pos.y();
    matrix.m_[2][3] = pos.z();

    return matrix;
}

KMatrix4x4 KMatrix4x4::reflectionMatrix(const KVector3D &normal)
{
    KVector3D n(normal.normalized());
    KMatrix4x4 matrix;
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

KMatrix4x4 KMatrix4x4::reflectionMatrix(const KVector3D &point,
                                        const KVector3D &normal)
{
    KVector3D n(normal.normalized());
    KVector3D pos = -point;
    pos += n * (-2 * KVector3D::dotProduct(n, pos)) + point;
    KMatrix4x4 matrix;
    matrix.m_[0][0] = 1 - 2 * n.xSquare();
    matrix.m_[1][0] = -2 * n.x() * n.y();
    matrix.m_[2][0] = -2 * n.x() * n.z();

    matrix.m_[0][1] = matrix.m_[1][0];
    matrix.m_[1][1] = 1 - 2 * n.ySquare();
    matrix.m_[2][1] = -2 * n.y() * n.z();

    matrix.m_[0][2] = matrix.m_[2][0];
    matrix.m_[1][2] = matrix.m_[2][1];
    matrix.m_[2][2] = 1 - 2 * n.zSquare();

    matrix.m_[0][3] = pos.x();
    matrix.m_[1][3] = pos.y();
    matrix.m_[2][3] = pos.z();

    return matrix;
}

KVector3D KMatrix4x4::operator*(const KVector3D &vector) const
{
    double x, y, z, w;
    x = vector.x()*m_[0][0] + vector.y()*m_[0][1] + vector.z()*m_[0][2] +
            m_[0][3];
    y = vector.x()*m_[1][0] + vector.y()*m_[1][1] + vector.z()*m_[1][2] +
            m_[1][3];
    z = vector.x()*m_[2][0] + vector.y()*m_[2][1] + vector.z()*m_[2][2] +
            m_[2][3];
    w = vector.x()*m_[3][0] + vector.y()*m_[3][1] + vector.z()*m_[3][2] +
            m_[3][3];
    if (kFabs(w - 1) < EPS3)
        return KVector3D(x, y, z);
    else
        return KVector3D(x / w, y / w, z / w);
}

KMatrix4x4 KMatrix4x4::operator*(const KMatrix4x4 &rhs) const
{
    KMatrix4x4 matrix;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            matrix.m_[i][j] = m_[i][0] * rhs.m_[0][j] +
                              m_[i][1] * rhs.m_[1][j] +
                              m_[i][2] * rhs.m_[2][j] +
                              m_[i][3] * rhs.m_[3][j];
    return matrix;
}

KMatrix4x4 &KMatrix4x4::operator*=(const KMatrix4x4 &rhs)
{
    KMatrix4x4 matrix;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            matrix.m_[i][j] = m_[i][0] * rhs.m_[0][j] +
                              m_[i][1] * rhs.m_[1][j] +
                              m_[i][2] * rhs.m_[2][j] +
                              m_[i][3] * rhs.m_[3][j];
    *this = matrix;
    return *this;
}

KMatrix4x4 &KMatrix4x4::operator*=(double factor)
{
    m_[0][0] *= factor;
    m_[0][1] *= factor;
    m_[0][2] *= factor;
    m_[0][3] *= factor;
    m_[1][0] *= factor;
    m_[1][1] *= factor;
    m_[1][2] *= factor;
    m_[1][3] *= factor;
    m_[2][0] *= factor;
    m_[2][1] *= factor;
    m_[2][2] *= factor;
    m_[2][3] *= factor;
    m_[3][0] *= factor;
    m_[3][1] *= factor;
    m_[3][2] *= factor;
    m_[3][3] *= factor;
    return *this;
}

KMatrix4x4 &KMatrix4x4::operator=(const KMatrix4x4 &matrix)
{
    m_[0][0] = matrix.m_[0][0];
    m_[0][1] = matrix.m_[0][1];
    m_[0][2] = matrix.m_[0][2];
    m_[0][3] = matrix.m_[0][3];
    m_[1][0] = matrix.m_[1][0];
    m_[1][1] = matrix.m_[1][1];
    m_[1][2] = matrix.m_[1][2];
    m_[1][3] = matrix.m_[1][3];
    m_[2][0] = matrix.m_[2][0];
    m_[2][1] = matrix.m_[2][1];
    m_[2][2] = matrix.m_[2][2];
    m_[2][3] = matrix.m_[2][3];
    m_[3][0] = matrix.m_[3][0];
    m_[3][1] = matrix.m_[3][1];
    m_[3][2] = matrix.m_[3][2];
    m_[3][3] = matrix.m_[3][3];
    return *this;
}

void KMatrix4x4::debug()
{
    for (int i = 0; i < 4; i++)
        qDebug() << m_[i][0] << m_[i][1] << m_[i][2] << m_[i][3];
}

void KMatrix4x4::swapRow(int row1, int row2)
{
    double a[4] = {m_[row2][0], m_[row2][1], m_[row2][2], m_[row2][3]};

    m_[row2][0] = m_[row1][0];
    m_[row2][1] = m_[row1][1];
    m_[row2][2] = m_[row1][2];
    m_[row2][3] = m_[row1][3];

    m_[row1][0] = a[0];
    m_[row1][1] = a[1];
    m_[row1][2] = a[2];
    m_[row1][3] = a[3];
}

double KMatrix4x4::determinant3(double m[3][3]) const
{
    double value = 0;
    for (int i = 0; i < 3; i++)
        value += m[0][i] * algebraicCofactor2(m, 0, i);
    return value;
}

double KMatrix4x4::algebraicCofactor3(double m[4][4], int row, int column) const
{
    int r = 0, c = 0;
    double m1[3][3];
    for (int i = 0 ; i < 3; ++i) {
        if (r == row)
            ++r;
        for (int j = 0; j < 3; ++j) {
            if (c == column)
                ++c;
            m1[i][j] = m[r][c];
            c++;
        }
        r++;
        c = 0;
    }

    int sign = 1;
    int rc = row + column;
    if (rc % 2 == 1)
        sign = -1;
    return sign * determinant3(m1);
}

double KMatrix4x4::algebraicCofactor2(double m[3][3], int row, int column) const
{
    int r = 0, c = 0;
    double m1[2][2];
    for (int i = 0 ; i < 2; i++) {
        if (r == row)
            r++;
        for (int j = 0; j < 2; j++) {
            if (c == column)
                c++;
            m1[i][j] = m[r][c];
            c++;
        }
        r++;
        c = 0;
    }
    int sign = 1;
    int rc = row + column;
    if (rc % 2 == 1)
        sign = -1;
    return sign * determinant2(m1);
}
