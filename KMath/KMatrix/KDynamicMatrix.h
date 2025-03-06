#ifndef KDynamicMatrix_H
#define KDynamicMatrix_H

#include "KDynamicVector.h"

// M行数，N列数，T类型
template<typename T>
class KING_EXPORT KDynamicMatrix
{
public:
    KDynamicMatrix();
    KDynamicMatrix(int row, int column);
    KDynamicMatrix(int row, int column, const T &value);
    KDynamicMatrix(const KDynamicMatrix<T> &other);
    KDynamicMatrix(const T *m[], int row, int column);
    /**
     * @brief n维向量构造n x 1矩阵
     */
    KDynamicMatrix(const KDynamicVector<T> &vector);
    ~KDynamicMatrix();

    void setToIdentity();
    void fill(const T &value);
    inline void setValue(int row, int column, const T &value);
    void resize(int row, int column);
    /**
     * @brief 交换两行,从from_column列开始到最后一列
     */
    void swapRow(int row1, int row2, int from_column = 0);
    /**
     * @brief 某行乘times, 从from_column列开始到最后一列
     */
    void rowTimes(T times, int row, int from_column = 0);
    /**
     * @brief row1行的times倍加到row2行, 从from_column列开始到最后一列
     */
    void addTimesToAnotherRow(T times, int row1, int row2, int from_column = 0);

    inline int row() const {return row_;}
    inline int column() const {return column_;}
    KDynamicVector<T> diagonal() const;
    bool isIdentity() const;
    inline const T &at(int row, int column) const {return m_[row][column];}
    /**
     * @brief 行列式
     */
    T determinant() const;
    /**
     * @brief 余子式(Mij)
     */
    T cofactor(int row, int column) const;
    /**
     * @brief 代数余子式(Aij)
     */
    inline T algebraicCofactor(int row, int column) const;
    /**
     * @brief 伴随矩阵
     */
    KDynamicMatrix<T> adjoint() const;
    KDynamicMatrix<T> transposed() const;
    KDynamicMatrix<T> inverted(bool *success = nullptr) const;
    /**
     * @brief 行最简形
     * @param rank返回矩阵的秩,
     * @param pivotElement_columnIndex返回主元列下标
     */
    KDynamicMatrix<T> reducedRowEchelonForm(int *rank = nullptr, KDynamicVector<int> *pivotElement_columnIndex = nullptr) const;

    inline const T &operator()(int row, int column) const;
    inline T &operator()(int row, int column);
    KDynamicMatrix<T> &operator+=(const KDynamicMatrix<T> &other);
    KDynamicMatrix<T> &operator-=(const KDynamicMatrix<T> &other);
    KDynamicMatrix<T> &operator*=(T factor);
    KDynamicMatrix<T> &operator/=(T divisor);
    KDynamicMatrix<T> &operator=(const KDynamicMatrix<T> &other);
    bool operator==(const KDynamicMatrix<T> &other) const;
    bool operator!=(const KDynamicMatrix<T> &other) const;
    KDynamicMatrix<T> operator+(const KDynamicMatrix<T> &other) const;
    KDynamicMatrix<T> operator-(const KDynamicMatrix<T> &other) const;
    KDynamicMatrix<T> operator*(T factor) const;
    KDynamicMatrix<T> operator/(T divisor) const;
    KDynamicVector<T> operator*(const KDynamicVector<T> &vector) const;

    template<typename TT>
    friend KDynamicMatrix<TT> operator-(
            const KDynamicMatrix<TT> &matrix);

    template<typename TT>
    friend KDynamicMatrix<TT> operator*(
            TT factor, const KDynamicMatrix<TT> &matrix);

    template<typename TT>
    friend KDynamicMatrix<TT> operator*(
            const KDynamicMatrix<TT> &m1,
            const KDynamicMatrix<TT> &m2);

private:
    void free();

    T **m_;
    int row_;
    int column_;
};

template<typename T>
KDynamicMatrix<T>::KDynamicMatrix() : m_(nullptr), row_(0), column_(0)
{

}

template<typename T>
KDynamicMatrix<T>::KDynamicMatrix(int row, int column) :
    m_(new T*[row]), row_(row), column_(column)
{
    for (int i = 0; i < row; ++i)
        m_[i] = new T[column];
}

template<typename T>
KDynamicMatrix<T>::KDynamicMatrix(int row, int column, const T &value) :
    m_(new T*[row]), row_(row), column_(column)
{
    for (int i = 0; i < row; ++i) {
        m_[i] = new T[column];
        for (int j = 0; j < column; ++j)
            m_[i][j] = value;
    }
}

template<typename T>
KDynamicMatrix<T>::KDynamicMatrix(const KDynamicMatrix<T> &other) :
    m_(new T*[other.row_]), row_(other.row_), column_(other.column_)
{
    for (int i = 0; i < row_; ++i) {
        m_[i] = new T[column_];
        for (int j = 0; j < column_; ++j)
            m_[i][j] = other.m_[i][j];
    }
}

template<typename T>
KDynamicMatrix<T>::KDynamicMatrix(const T *m[], int row, int column) :
    m_(new T*[row]), row_(row), column_(column)
{
    for (int i = 0; i < row; ++i) {
        m_[i] = new T[column];
        for (int j = 0; j < column; ++j)
            m_[i][j] = m[i][j];
    }
}

template<typename T>
KDynamicMatrix<T>::KDynamicMatrix(const KDynamicVector<T> &vector) :
    m_(new T*[vector.size()]), row_(vector.size()), column_(1)
{
    for (int i = 0; i < row_; ++i) {
        m_[i] = new T[1];
        m_[i][0] = vector.at(i);
    }
}

template<typename T>
KDynamicMatrix<T>::~KDynamicMatrix()
{
    free();
}

template<typename T>
void KDynamicMatrix<T>::setToIdentity()
{
    for (int i = 0; i < row_; ++i)
        for (int j = 0; j < column_; ++j)
            m_[i][j] = 0;

    int min = kMin(row_, column_);
    for (int i = 0; i < min; ++i)
        m_[i][i] = 1;
}

template<typename T>
void KDynamicMatrix<T>::fill(const T &value)
{
    for (int i = 0; i < row_; ++i)
        for (int j = 0; j < column_; ++j)
            m_[i][j] = value;
}

template<typename T>
inline void KDynamicMatrix<T>::setValue(int row, int column, const T &value)
{
    m_[row][column] = value;
}

template<typename T>
void KDynamicMatrix<T>::resize(int row, int column)
{
    if (row_ != row || column_ != column) {
        free();
        row_ = row;
        column_ = column;
        m_ = new T*[row];
        for (int i = 0; i < row; ++i)
            m_[i] = new T[column];
    }
}

template<typename T>
void KDynamicMatrix<T>::swapRow(int row1, int row2, int from_column)
{
    double temp;
    for (int i = from_column; i < column_; ++i) {
        temp = m_[row2][i];
        m_[row2][i] = m_[row1][i];
        m_[row1][i] = temp;
    }
}

template<typename T>
void KDynamicMatrix<T>::rowTimes(T times, int row, int from_column)
{
    for (int i = from_column; i < column_; ++i)
        m_[row][i] *= times;
}

template<typename T>
void KDynamicMatrix<T>::addTimesToAnotherRow(T times, int row1, int row2,
                                             int from_column)
{
    for (int i = from_column; i < column_; ++i)
        m_[row2][i] += m_[row1][i] * times;
}

template<typename T>
KDynamicVector<T> KDynamicMatrix<T>::diagonal() const
{
    int n = kMin(row_, column_);
    KDynamicVector<T> v(n);
    for (int i = 0; i < n; ++i)
        v[i] = m_[i][i];
    return v;
}

template<typename T>
bool KDynamicMatrix<T>::isIdentity() const
{
    for (int i = 0; i < row_; ++i) {
        for (int j = 0; j < column_; ++j) {
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

template<typename T>
T KDynamicMatrix<T>::determinant() const
{
    if (row_ != column_)
        return 0;

    KDynamicMatrix<T> A(*this);
    T k = 0;

    for (int turn = 0; turn < row_; ++turn) {
        int i;
        for (i = turn; i < row_; ++i)
            if (kFabs(A.m_[i][turn]) > EPS9)
                break;
        if (i == row_)
            return 0;

        if (i != turn) {
            A.swapRow(turn, i);
            k = -k;
        }

        double c = 1 / A.m_[turn][turn];
        A.rowTimes(c, turn);
        k /= c;

        for (int j = turn + 1; j < row_; ++j) {
            c = -A.m_[j][turn];
            A.addTimesToAnotherRow(c, turn, j);
        }
    }

    return k;
}

template<typename T>
T KDynamicMatrix<T>::cofactor(int row, int column) const
{
    if (row_ != column_)
        return 0;

    int r = 0, c = 0, row_1 = row_ - 1;
    KDynamicMatrix<T> m(row_1, row_1);
    for (int i = 0; i < row_1; ++i) {
        if (r == row)
            ++r;
        for (int j = 0; j < row_1; ++j) {
             if (c == column)
                 ++c;
             m[i][j] = m_[r][c];
             ++c;
        }
        ++r;
        c = 0;
    }

    return m.determinant();
}

template<typename T>
inline T KDynamicMatrix<T>::algebraicCofactor(int row, int column) const
{
    return (row + column) % 2 == 1 ?
                -cofactor(row, column) : cofactor(row, column);
}

template<typename T>
KDynamicMatrix<T> KDynamicMatrix<T>::adjoint() const
{
    KDynamicMatrix<T> adj(row_, column_);
    if (row_ != column_) {
        adj.fill(0);
        return adj;
    }

    for (int i = 0; i < row_; ++i)
        for (int j = 0; j < column_; ++j)
            adj[j][i] = algebraicCofactor(i, j);

    return adj;
}

template<typename T>
KDynamicMatrix<T> KDynamicMatrix<T>::transposed() const
{
    KDynamicMatrix<T> matrix(column_, row_);
    for (int i = 0; i < row_; ++i)
        for (int j = 0; j < column_; ++j)
            matrix.m_[j][i] = m_[i][j];
    return matrix;
}

template<typename T>
KDynamicMatrix<T> KDynamicMatrix<T>::inverted(bool *invertible) const
{
    if (row_ != column_) {
        if (invertible)
            *invertible = false;
        return KDynamicMatrix<T>();
    }
    KDynamicMatrix<T> A(*this);
    KDynamicMatrix<T> E(row_, column_);
    E.setToIdentity();

    for (int turn = 0; turn < row_; ++turn) {
        int i;
        for (i = turn; i < row_; ++i)
            if (kFabs(A.m_[i][turn]) > EPS9)
                break;
        if (i == row_) {
            if (invertible)
                *invertible = false;
            return KDynamicMatrix<T>();
        }

        if (i != turn) {
            A.swapRow(turn, i);
            E.swapRow(turn, i);
        }
        double c = 1 / A.m_[turn][turn];
        A.rowTimes(c, turn);
        E.rowTimes(c, turn);

        for (int j = turn + 1; j < row_; j++) {
            c = -A.m_[j][turn];
            A.addTimesToAnotherRow(c, turn, j);
            E.addTimesToAnotherRow(c, turn, j);
        }
    }

    for (int turn = row_ - 1; turn > 0; --turn) {
        for (int i = turn - 1; i >= 0; --i) {
            double c = -A.m_[i][turn];
            A.m_[i][turn] = 0;
            E.addTimesToAnotherRow(c, turn, i);
        }
    }

    if (invertible)
        *invertible = true;
    return E;
}

template<typename T>
KDynamicMatrix<T> KDynamicMatrix<T>::reducedRowEchelonForm(
        int *rank, KDynamicVector<int> *pivotElement_columnIndex) const
{
    KDynamicMatrix<T> A(*this);
    int cur_row = 0;

    for (int col = 0; col < column_; ++col) {
        int i;
        for (i = cur_row; i < row_; ++i)
            if (!isZero(A.m_[i][col]))
                break;

        if (i > cur_row) {
            if (i == row_) {
                continue;
            } else {
                A.swapRow(cur_row, i, col);
            }
        }

        double f = 1 / A.m_[cur_row][col];
        A.m_[cur_row][col] = 1;
        A.rowTimes(f, cur_row, col + 1);

        for (int j = cur_row + 1; j < row_; ++j) {
            f = -A.m_[j][col];
            A.m_[j][col] = 0;
            A.addTimesToAnotherRow(f, cur_row, j, col + 1);
        }
        ++cur_row;
        if (cur_row >= row_)
            break;
    }

    if (rank)
        *rank = cur_row;
    if (pivotElement_columnIndex) {
        pivotElement_columnIndex->resize(cur_row);
    }

    for (int r = cur_row - 1; r > 0; --r) {
        int col = 0;
        for (; col < column_; ++col) {
            if (!isZero(A.m_[r][col]))
                break;
        }

        if (pivotElement_columnIndex) {
            pivotElement_columnIndex->setValue(r, col);
        }

        for (int i = r - 1; i >= 0; --i) {
            double f = -A.m_[i][col];
            A.m_[i][col] = 0;
            A.addTimesToAnotherRow(f, r, i, col + 1);
        }
    }

    if (pivotElement_columnIndex) {
        for (int i = 0; i < column_; ++i) {
            if (!isZero(A.m_[0][i])) {
                pivotElement_columnIndex->setValue(0, i);
                break;
            }
        }
    }

    return A;
}

template<typename T>
inline const T &KDynamicMatrix<T>::operator()(int row, int column) const
{
    return m_[row][column];
}

template<typename T>
inline T &KDynamicMatrix<T>::operator()(int row, int column)
{
    return m_[row][column];
}

template<typename T>
KDynamicMatrix<T> &KDynamicMatrix<T>::operator+=(
        const KDynamicMatrix<T> &other)
{
    for (int i = 0; i < row_; ++i)
        for (int j = 0; j < column_; ++j)
            m_[i][j] += other.m_[i][j];
    return *this;
}

template<typename T>
KDynamicMatrix<T> &KDynamicMatrix<T>::operator-=(
        const KDynamicMatrix<T> &other)
{
    for (int i = 0; i < row_; ++i)
        for (int j = 0; j < column_; ++j)
            m_[i][j] -= other.m_[i][j];
    return *this;
}

template<typename T>
KDynamicMatrix<T> &KDynamicMatrix<T>::operator*=(T factor)
{
    for (int i = 0; i < row_; ++i)
        for (int j = 0; j < column_; ++j)
            m_[i][j] *= factor;
    return *this;
}

template<typename T>
KDynamicMatrix<T> &KDynamicMatrix<T>::operator/=(T divisor)
{
    for (int i = 0; i < row_; ++i)
        for (int j = 0; j < column_; ++j)
            m_[i][j] /= divisor;
    return *this;
}

template<typename T>
KDynamicMatrix<T> &KDynamicMatrix<T>::operator=(
        const KDynamicMatrix<T> &other)
{
    if (row_ != other.row_ || column_ != other.column_) {
        free();
        row_ = other.row_;
        column_ = other.column_;
        m_ = new T*[row_];
        for (int i = 0; i < row_; ++i) {
            m_[i] = new T[column_];
            for (int j = 0; j < column_; ++j)
                m_[i][j] = other.m_[i][j];
        }
    } else {
        for (int i = 0; i < row_; ++i)
            for (int j = 0; j < column_; ++j)
                m_[i][j] = other.m_[i][j];
    }

    return *this;
}

template<typename T>
bool KDynamicMatrix<T>::operator==(const KDynamicMatrix<T> &other) const
{
    for (int i = 0; i < row_; ++i)
        for (int j = 0; j < column_; ++j) {
            if (m_[i][j] != other.m_[i][j])
                return false;
        }
    return true;
}

template<typename T>
bool KDynamicMatrix<T>::operator!=(const KDynamicMatrix<T> &other) const
{
    for (int i = 0; i < row_; ++i)
        for (int j = 0; j <column_; ++j) {
            if (m_[i][j] != other.m_[i][j])
                return true;
        }
    return false;
}

template<typename T>
KDynamicMatrix<T> KDynamicMatrix<T>::operator+(
        const KDynamicMatrix<T> &other) const
{
    KDynamicMatrix<T> result(row_, column_);
    for (int i = 0; i < row_; ++i)
        for (int j = 0; j < column_; ++j)
            result.m_[i][j] = m_[i][j] + other.m_[i][j];
    return result;
}

template<typename T>
KDynamicMatrix<T> KDynamicMatrix<T>::operator-(
        const KDynamicMatrix<T> &other) const
{
    KDynamicMatrix<T> result(row_, column_);
    for (int i = 0; i < row_; ++i)
        for (int j = 0; j < column_; ++j)
            result.m_[i][j] = m_[i][j] - other.m_[i][j];
    return result;
}

template<typename T>
KDynamicMatrix<T> KDynamicMatrix<T>::operator*(T factor) const
{
    KDynamicMatrix<T> result;
    for (int i = 0; i < row_; ++i)
        for (int j = 0; j < column_; ++j)
            result.m_[i][j] = m_[i][j] * factor;
    return result;
}

template<typename T>
KDynamicMatrix<T> KDynamicMatrix<T>::operator/(T divisor) const
{
    KDynamicMatrix<T> result(row_, column_);
    for (int i = 0; i < row_; ++i)
        for (int j = 0; j < column_; ++j)
            result.m_[i][j] = m_[i][j] / divisor;
    return result;
}

template<typename T>
KDynamicVector<T> KDynamicMatrix<T>::operator*(
        const KDynamicVector<T> &vector) const
{
    KDynamicVector<T> result(row_);
    for (int i = 0; i < row_; ++i) {
        T sum = 0;
        for (int j = 0; j < column_; ++j)
            sum += m_[i][j] * vector.at(j);
        result[i] = sum;
    }
    return result;
}

template<typename T>
void KDynamicMatrix<T>::free()
{
    for (int i = 0; i < row_; ++i)
        delete [] m_[i];
    delete [] m_;
}

template<typename TT>
KING_EXPORT KDynamicMatrix<TT> operator-(const KDynamicMatrix<TT> &matrix)
{
    KDynamicMatrix<TT> result(matrix.row_, matrix.column_);
    for (int i = 0; i < matrix.row_; ++i)
        for (int j = 0; j < matrix.column_; ++j)
            result.m_[i][j] = -matrix.m_[i][j];
    return result;
}

template<typename TT>
KING_EXPORT KDynamicMatrix<TT> operator*(TT factor, const KDynamicMatrix<TT> &matrix)
{
    KDynamicMatrix<TT> result(matrix.row_, matrix.column_);
    for (int i = 0; i < matrix.row_; ++i)
        for (int j = 0; j < matrix.column_; ++j)
            result.m_[i][j] = factor * matrix.m_[i][j];
    return result;
}

template<typename TT>
KING_EXPORT KDynamicMatrix<TT> operator*(const KDynamicMatrix<TT> &m1,
                             const KDynamicMatrix<TT> &m2)
{
    KDynamicMatrix<TT> result(m1.row_, m2.column_);
    for (int i = 0; i < m1.row_; ++i) {
        for (int j = 0; j < m2.column_; ++j) {
            TT sum = 0;
            for (int k = 0; k < m1.column_; ++k)
                sum += m1.m_[i][k] * m2.m_[k][j];
            result.m_[i][j] = sum;
        }
    }

    return result;
}

#endif // KDynamicMatrix2_H
