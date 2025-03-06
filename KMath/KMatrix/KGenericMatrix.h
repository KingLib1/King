#ifndef KGENERICMATRIX_H
#define KGENERICMATRIX_H

#include "KGenericVector.h"

// M行数，N列数，T类型
template<int M, int N, typename T>
class KING_EXPORT KGenericMatrix
{
public:
    KGenericMatrix();
    KGenericMatrix(const T &value);
    KGenericMatrix(const T *values);
    KGenericMatrix(const KGenericMatrix<M, N, T> &other);
    KGenericMatrix(const T m[M][N]);
    ~KGenericMatrix();

    void setToIdentity();
    void fill(const T &value);
    inline void setValue(int row, int column, const T &value);
    T *data() {return *m_;}

    bool isIdentity() const;
    inline const T &at(int row, int column) const {return m_[row][column];}
    void copyDataTo(T *values) const;
    const T *data() const {return *m_;}
    const T *constData() const {return *m_;}
    KGenericMatrix<N, M, T> transposed() const;

    inline const T &operator()(int row, int column) const;
    inline T &operator()(int row, int column);
    KGenericMatrix<M, N, T> &operator+=(const KGenericMatrix<M, N, T> &other);
    KGenericMatrix<M, N, T> &operator-=(const KGenericMatrix<M, N, T> &other);
    KGenericMatrix<M, N, T> &operator*=(T factor);
    KGenericMatrix<M, N, T> &operator/=(T divisor);
    KGenericMatrix<M, N, T> &operator=(const KGenericMatrix<M, N, T> &other);
    bool operator==(const KGenericMatrix<M, N, T> &other) const;
    bool operator!=(const KGenericMatrix<M, N, T> &other) const;
    KGenericMatrix<M, N, T> operator+(const KGenericMatrix<M, N, T> &other) const;
    KGenericMatrix<M, N, T> operator-(const KGenericMatrix<M, N, T> &other) const;
    KGenericMatrix<M, N, T> operator*(T factor) const;
    KGenericMatrix<M, N, T> operator/(T divisor) const;
    KGenericVector<M, T> operator*(const KGenericVector<N, T> &vector) const;

    template<int MM, int NN, typename TT>
    friend KGenericMatrix<MM, NN, TT> operator-(
            const KGenericMatrix<MM, NN, TT> &matrix);

    template<int MM, int NN, typename TT>
    friend KGenericMatrix<MM, NN, TT> operator*(
            TT factor, const KGenericMatrix<MM, NN, TT> &matrix);

    template<int MM, int N1, int N2, typename TT>
    friend KGenericMatrix<MM, N2, TT> operator*(
            const KGenericMatrix<MM, N1, TT> &m1,
            const KGenericMatrix<N1, N2, TT> &m2);

private:
    T m_[M][N];
};

template<int M, int N, typename T>
KGenericMatrix<M, N, T>::KGenericMatrix()
{

}

template<int M, int N, typename T>
KGenericMatrix<M, N, T>::KGenericMatrix(const T &value)
{
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            m_[i][j] = value;
}

template<int M, int N, typename T>
KGenericMatrix<M, N, T>::KGenericMatrix(const T *values)
{
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            m_[i][j] = values[i * N + j];
}

template<int M, int N, typename T>
KGenericMatrix<M, N, T>::KGenericMatrix(const KGenericMatrix<M, N, T> &other)
{
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            m_[i][j] = other.m_[i][j];
}

template<int M, int N, typename T>
KGenericMatrix<M, N, T>::KGenericMatrix(const T m[M][N])
{
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            m_[i][j] = m[i][j];
}

template<int M, int N, typename T>
KGenericMatrix<M, N, T>::~KGenericMatrix()
{

}

template<int M, int N, typename T>
void KGenericMatrix<M, N, T>::setToIdentity()
{
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            m_[i][j] = 0;

    int min = kMin(M, N);
    for (int i = 0; i < min; ++i)
        m_[i][i] = 1;
}

template<int M, int N, typename T>
void KGenericMatrix<M, N, T>::fill(const T &value)
{
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            m_[i][j] = value;
}

template<int M, int N, typename T>
inline void KGenericMatrix<M, N, T>::setValue(int row, int column,
                                              const T &value)
{
    m_[row][column] = value;
}

template<int M, int N, typename T>
bool KGenericMatrix<M, N, T>::isIdentity() const
{
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i == j) {
                if (m_[i][j] != 1)
                    return false;
            } else {
                if (m_[i][j] != 0)
                    return false;
            }
        }
    }
    return true;
}

template<int M, int N, typename T>
void KGenericMatrix<M, N, T>::copyDataTo(T *values) const
{
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            values[i * N + j] = m_[i][j];
}

template<int M, int N, typename T>
KGenericMatrix<N, M, T> KGenericMatrix<M, N, T>::transposed() const
{
    KGenericMatrix<N, M, T> matrix;
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            matrix.m_[j][i] = m_[i][j];
    return matrix;
}

template<int M, int N, typename T>
inline const T &KGenericMatrix<M, N, T>::operator()(int row, int column) const
{
    return m_[row][column];
}

template<int M, int N, typename T>
inline T &KGenericMatrix<M, N, T>::operator()(int row, int column)
{
    return m_[row][column];
}

template<int M, int N, typename T>
KGenericMatrix<M, N, T> &KGenericMatrix<M, N, T>::operator+=(
        const KGenericMatrix<M, N, T> &other)
{
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            m_[i][j] += other.m_[i][j];
    return *this;
}

template<int M, int N, typename T>
KGenericMatrix<M, N, T> &KGenericMatrix<M, N, T>::operator-=(
        const KGenericMatrix<M, N, T> &other)
{
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            m_[i][j] -= other.m_[i][j];
    return *this;
}

template<int M, int N, typename T>
KGenericMatrix<M, N, T> &KGenericMatrix<M, N, T>::operator*=(T factor)
{
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            m_[i][j] *= factor;
    return *this;
}

template<int M, int N, typename T>
KGenericMatrix<M, N, T> &KGenericMatrix<M, N, T>::operator/=(T divisor)
{
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            m_[i][j] /= divisor;
    return *this;
}

template<int M, int N, typename T>
KGenericMatrix<M, N, T> &KGenericMatrix<M, N, T>::operator=(
        const KGenericMatrix<M, N, T> &other)
{
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            m_[i][j] = other.m_[i][j];
    return *this;
}

template<int M, int N, typename T>
bool KGenericMatrix<M, N, T>::operator==(const KGenericMatrix<M, N, T> &other)
const
{
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j) {
            if (m_[i][j] != other.m_[i][j])
                return false;
        }
    return true;
}

template<int M, int N, typename T>
bool KGenericMatrix<M, N, T>::operator!=(const KGenericMatrix<M, N, T> &other)
const
{
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j) {
            if (m_[i][j] != other.m_[i][j])
                return true;
        }
    return false;
}

template<int M, int N, typename T>
KGenericMatrix<M, N, T> KGenericMatrix<M, N, T>::operator+(
        const KGenericMatrix<M, N, T> &other) const
{
    KGenericMatrix<M, N, T> result;
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            result.m_[i][j] = m_[i][j] + other.m_[i][j];
    return result;
}

template<int M, int N, typename T>
KGenericMatrix<M, N, T> KGenericMatrix<M, N, T>::operator-(
        const KGenericMatrix<M, N, T> &other) const
{
    KGenericMatrix<M, N, T> result;
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            result.m_[i][j] = m_[i][j] - other.m_[i][j];
    return result;
}

template<int M, int N, typename T>
KGenericMatrix<M, N, T> KGenericMatrix<M, N, T>::operator*(T factor) const
{
    KGenericMatrix<M, N, T> result;
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            result.m_[i][j] = m_[i][j] * factor;
    return result;
}

template<int M, int N, typename T>
KGenericMatrix<M, N, T> KGenericMatrix<M, N, T>::operator/(T divisor) const
{
    KGenericMatrix<M, N, T> result;
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            result.m_[i][j] = m_[i][j] / divisor;
    return result;
}

template<int M, int N, typename T>
KGenericVector<M, T> KGenericMatrix<M, N, T>::operator*(
        const KGenericVector<N, T> &vector) const
{
    KGenericVector<M, T> result;
    for (int i = 0; i < M; ++i) {
        T sum = 0;
        for (int j = 0; j < N; ++j)
            sum += m_[i][j] * vector.at(j);
        result[i] = sum;
    }
    return result;
}

template<int MM, int NN, typename TT>
KING_EXPORT KGenericMatrix<MM, NN, TT> operator-(const KGenericMatrix<MM, NN, TT> &matrix)
{
    KGenericMatrix<MM, NN, TT> result;
    for (int i = 0; i < MM; ++i)
        for (int j = 0; j < NN; ++j)
            result.m_[i][j] = -matrix.m_[i][j];
    return result;
}

template<int MM, int NN, typename TT>
KING_EXPORT KGenericMatrix<MM, NN, TT> operator*(
        TT factor, const KGenericMatrix<MM, NN, TT> &matrix)
{
    KGenericMatrix<MM, NN, TT> result;
    for (int i = 0; i < MM; ++i)
        for (int j = 0; j < NN; ++j)
            result.m_[i][j] = factor * matrix.m_[i][j];
    return result;
}

template<int MM, int N1, int N2, typename TT>
KING_EXPORT KGenericMatrix<MM, N2, TT> operator*(const KGenericMatrix<MM, N1, TT> &m1,
                                     const KGenericMatrix<N1, N2, TT> &m2)
{
    KGenericMatrix<MM, N2, TT> result;
    for (int i = 0; i < MM; ++i) {
        for (int j = 0; j < N2; ++j) {
            TT sum = 0;
            for (int k = 0; k < N1; ++k)
                sum += m1.m_[i][k] * m2.m_[k][j];
            result.m_[i][j] = sum;
        }
    }
    return result;
}

#endif // KGENERICMATRIX_H
