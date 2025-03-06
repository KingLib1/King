#ifndef KGENERICVECTOR_H
#define KGENERICVECTOR_H

#include "kmath.h"

// N维数，T类型
template<int N, typename T>
class KING_EXPORT KGenericVector
{
public:
    KGenericVector();
    KGenericVector(const T &value);
    KGenericVector(const KGenericVector<N, T> &other);
    ~KGenericVector();

    void fill(const T &value);
    inline void setValue(int index, const T &value);

    inline const T &at(int index) const;
    T length() const;
    T lengthSquared() const;
    static T dotProduct(const KGenericVector<N, T> &v1,
                        const KGenericVector<N, T> &v2);

    inline T &operator[](int index);
    inline const T&operator[](int index) const;
    inline T &operator()(int index);
    inline const T &operator()(int index) const;
    KGenericVector<N, T> &operator+=(const KGenericVector<N, T> &other);
    KGenericVector<N, T> &operator-=(const KGenericVector<N, T> &other);
    KGenericVector<N, T> &operator*=(T factor);
    KGenericVector<N, T> &operator/=(T divisor);
    KGenericVector<N, T> &operator=(const KGenericVector<N, T> &other);
    KGenericVector<N, T> operator+(const KGenericVector<N, T> &other) const;
    KGenericVector<N, T> operator-(const KGenericVector<N, T> &other) const;
    KGenericVector<N, T> operator*(T factor) const;
    KGenericVector<N, T> operator/(T divisor) const;

    template<int NN, typename TT>
    friend KGenericVector<NN, TT> operator-(
            const KGenericVector<NN, TT> &vector);

    template<int NN, typename TT>
    friend KGenericVector<NN, TT> operator*(
            TT factor, const KGenericVector<NN, TT> &vector);

private:
    T v_[N];
};

template<int N, typename T>
KGenericVector<N, T>::KGenericVector()
{

}

template<int N, typename T>
KGenericVector<N, T>::KGenericVector(const T &value)
{
    for (int i = 0; i < N; ++i)
        v_[i] = value;
}

template<int N, typename T>
KGenericVector<N, T>::KGenericVector(const KGenericVector<N, T> &other)
{
    for (int i = 0; i < N; ++i)
        v_[i] = other.v_[i];
}

template<int N, typename T>
KGenericVector<N, T>::~KGenericVector()
{

}

template<int N, typename T>
void KGenericVector<N, T>::fill(const T &value)
{
    for (int i = 0; i < N; ++i)
        v_[i] = value;
}

template<int N, typename T>
inline void KGenericVector<N, T>::setValue(int index, const T &value)
{
    v_[index] = value;
}

template<int N, typename T>
inline const T &KGenericVector<N, T>::at(int index) const
{
    return v_[index];
}

template<int N, typename T>
T KGenericVector<N, T>::length() const
{
    return kSqrt(lengthSquared());
}

template<int N, typename T>
T KGenericVector<N, T>::lengthSquared() const
{
    T sum = 0;
    for (int i = 0; i < N; ++i)
        sum += kSquare(v_[i]);
    return sum;
}

template<int N, typename T>
T KGenericVector<N, T>::dotProduct(const KGenericVector<N, T> &v1,
                                   const KGenericVector<N, T> &v2)
{
    T sum = 0;
    for (int i = 0; i < N; ++i)
        sum += v1.v_[i] * v2.v_[i];
    return sum;
}

template<int N, typename T>
inline T &KGenericVector<N, T>::operator[](int index)
{
    return v_[index];
}

template<int N, typename T>
inline const T &KGenericVector<N, T>::operator[](int index) const
{
    return v_[index];
}

template<int N, typename T>
inline T &KGenericVector<N, T>::operator()(int index)
{
    return v_[index];
}

template<int N, typename T>
inline const T &KGenericVector<N, T>::operator()(int index) const
{
    return v_[index];
}

template<int N, typename T>
KGenericVector<N, T> &KGenericVector<N, T>::operator+=(
        const KGenericVector<N, T> &other)
{
    for (int i = 0; i < N; ++i)
        v_[i] += other.v_[i];
    return *this;
}

template<int N, typename T>
KGenericVector<N, T> &KGenericVector<N, T>::operator-=(
        const KGenericVector<N, T> &other)
{
    for (int i = 0; i < N; ++i)
        v_[i] -= other.v_[i];
    return *this;
}

template<int N, typename T>
KGenericVector<N, T> &KGenericVector<N, T>::operator*=(T factor)
{
    for (int i = 0; i < N; ++i)
        v_[i] *= factor;
    return *this;
}

template<int N, typename T>
KGenericVector<N, T> &KGenericVector<N, T>::operator/=(T divisor)
{
    for (int i = 0; i < N; ++i)
        v_[i] /= divisor;
    return *this;
}

template<int N, typename T>
KGenericVector<N, T> &KGenericVector<N, T>::operator=(
        const KGenericVector<N, T> &other)
{
    for (int i = 0; i < N; ++i)
        v_[i] = other.v_[i];
    return *this;
}

template<int N, typename T>
KGenericVector<N, T> KGenericVector<N, T>::operator+(
        const KGenericVector<N, T> &other) const
{
    KGenericVector<N, T> v;
    for (int i = 0; i < N; ++i)
        v.v_[i] = v_[i] + other.v_[i];
    return v;
}

template<int N, typename T>
KGenericVector<N, T> KGenericVector<N, T>::operator-(
        const KGenericVector<N, T> &other) const
{
    KGenericVector<N, T> v;
    for (int i = 0; i < N; ++i)
        v.v_[i] = v_[i] - other.v_[i];
    return v;
}

template<int N, typename T>
KGenericVector<N, T> KGenericVector<N, T>::operator*(T factor) const
{
    KGenericVector<N, T> v;
    for (int i = 0; i < N; ++i)
        v.v_[i] = v_[i] * factor;
    return v;
}

template<int N, typename T>
KGenericVector<N, T> KGenericVector<N, T>::operator/(T divisor) const
{
    KGenericVector<N, T> v;
    for (int i = 0; i < N; ++i)
        v.v_[i] = v_[i] / divisor;
    return v;
}

template<int NN, typename TT>
KING_EXPORT KGenericVector<NN, TT> operator-(const KGenericVector<NN, TT> &vector)
{
    KGenericVector<NN, TT> v;
    for (int i = 0; i < NN; ++i)
        v.v_[i] = -vector.v_[i];
    return v;
}

template<int NN, typename TT>
KING_EXPORT KGenericVector<NN, TT> operator*(
        TT factor, const KGenericVector<NN, TT> &vector)
{
    KGenericVector<NN, TT> v;
    for (int i = 0; i < NN; ++i)
        v.v_[i] = vector.v_[i] * factor;
    return v;
}

#endif // KGENERICVECTOR_H
