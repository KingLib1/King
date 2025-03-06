#ifndef KDynamicVector_H
#define KDynamicVector_H

#include "kmath.h"

// N维数，T类型
template<typename T>
class KING_EXPORT KDynamicVector
{
public:
    KDynamicVector();
    KDynamicVector(int size);
    KDynamicVector(int size, const T &value);
    KDynamicVector(const KDynamicVector<T> &other);
    ~KDynamicVector();

    void fill(const T &value);
    inline void setValue(int index, const T &value);
    inline void resize(int size);

    inline const T &at(int index) const;
    inline int size() const {return size_;}
    /**
     * @brief 范数
     */
    T norm(int p) const;
    T length() const;
    T lengthSquared() const;
    static T dotProduct(const KDynamicVector<T> &v1,
                        const KDynamicVector<T> &v2);

    inline T &operator[](int index);
    inline const T&operator[](int index) const;
    inline T &operator()(int index);
    inline const T &operator()(int index) const;
    KDynamicVector<T> &operator+=(const KDynamicVector<T> &other);
    KDynamicVector<T> &operator-=(const KDynamicVector<T> &other);
    KDynamicVector<T> &operator*=(T factor);
    KDynamicVector<T> &operator/=(T divisor);
    KDynamicVector<T> &operator=(const KDynamicVector<T> &other);
    KDynamicVector<T> operator+(const KDynamicVector<T> &other) const;
    KDynamicVector<T> operator-(const KDynamicVector<T> &other) const;
    KDynamicVector<T> operator*(T factor) const;
    KDynamicVector<T> operator/(T divisor) const;

    template<typename TT>
    friend KDynamicVector<TT> operator-(const KDynamicVector<TT> &vector);

    template<typename TT>
    friend KDynamicVector<TT> operator*(
            TT factor, const KDynamicVector<TT> &vector);

private:
    T *v_;
    int size_;
};

template<typename T>
KDynamicVector<T>::KDynamicVector() : v_(nullptr), size_(0)
{

}

template<typename T>
KDynamicVector<T>::KDynamicVector(int size) : v_(new T[size]), size_(size)
{

}

template<typename T>
KDynamicVector<T>::KDynamicVector(int size, const T &value) :
    v_(new T[size]), size_(size)
{
    for (int i = 0; i < size; ++i)
        v_[i] = value;
}

template<typename T>
KDynamicVector<T>::KDynamicVector(const KDynamicVector<T> &other) :
    v_(new T[other.size_]), size_(other.size_)
{
    for (int i = 0; i < size_; ++i)
        v_[i] = other.v_[i];
}

template<typename T>
KDynamicVector<T>::~KDynamicVector()
{
    if (v_)
        delete [] v_;
}

template<typename T>
void KDynamicVector<T>::fill(const T &value)
{
    for (int i = 0; i < size_; ++i)
        v_[i] = value;
}

template<typename T>
inline void KDynamicVector<T>::setValue(int index, const T &value)
{
    v_[index] = value;
}

template<typename T>
inline void KDynamicVector<T>::resize(int size)
{
    if (size_ != size) {
        if (v_)
            delete [] v_;
        size_ = size;
        if (size == 0) {
            v_ = nullptr;
        } else {
            v_ = new T[size];
        }
    }
}

template<typename T>
inline const T &KDynamicVector<T>::at(int index) const
{
    return v_[index];
}

template<typename T>
T KDynamicVector<T>::norm(int p) const
{
    if (p == 1) {
        T sum = 0;
        for (int i = 0; i < size_; ++i)
            sum += kFabs(v_[i]);
        return sum;
    }

    if (p == 2)
        return length();

    if (p == K_INT_MAX) {
        T max = 0;
        for (int i = 0; i < size_; ++i) {
            double f = kFabs(v_[i]);
            if (f > max)
                max = f;
        }
        return max;
    }

    if (p == K_INT_MIN) {
        T min = 0;
        for (int i = 0; i < size_; ++i) {
            double f = kFabs(v_[i]);
            if (f < min)
                min = f;
        }
        return min;
    }

    return 0;
}

template<typename T>
T KDynamicVector<T>::length() const
{
    return kSqrt(lengthSquared());
}

template<typename T>
T KDynamicVector<T>::lengthSquared() const
{
    T sum = 0;
    for (int i = 0; i < size_; ++i)
        sum += kSquare(v_[i]);
    return sum;
}

template<typename T>
T KDynamicVector<T>::dotProduct(const KDynamicVector<T> &v1,
                                 const KDynamicVector<T> &v2)
{
    T sum = 0;
    for (int i = 0; i < v1.size_; ++i)
        sum += v1.v_[i] * v2.v_[i];
    return sum;
}

template<typename T>
inline T &KDynamicVector<T>::operator[](int index)
{
    return v_[index];
}

template<typename T>
inline const T &KDynamicVector<T>::operator[](int index) const
{
    return v_[index];
}

template<typename T>
inline T &KDynamicVector<T>::operator()(int index)
{
    return v_[index];
}

template<typename T>
inline const T &KDynamicVector<T>::operator()(int index) const
{
    return v_[index];
}

template<typename T>
KDynamicVector<T> &KDynamicVector<T>::operator+=(
        const KDynamicVector<T> &other)
{
    for (int i = 0; i < size_; ++i)
        v_[i] += other.v_[i];
    return *this;
}

template<typename T>
KDynamicVector<T> &KDynamicVector<T>::operator-=(
        const KDynamicVector<T> &other)
{
    for (int i = 0; i < size_; ++i)
        v_[i] -= other.v_[i];
    return *this;
}

template<typename T>
KDynamicVector<T> &KDynamicVector<T>::operator*=(T factor)
{
    for (int i = 0; i < size_; ++i)
        v_[i] *= factor;
    return *this;
}

template<typename T>
KDynamicVector<T> &KDynamicVector<T>::operator/=(T divisor)
{
    for (int i = 0; i < size_; ++i)
        v_[i] /= divisor;
    return *this;
}

template<typename T>
KDynamicVector<T> &KDynamicVector<T>::operator=(
        const KDynamicVector<T> &other)
{
    resize(other.size_);
    for (int i = 0; i < size_; ++i)
        v_[i] = other.v_[i];
    return *this;
}

template<typename T>
KDynamicVector<T> KDynamicVector<T>::operator+(
        const KDynamicVector<T> &other) const
{
    KDynamicVector<T> v(size_);
    for (int i = 0; i < size_; ++i)
        v.v_[i] = v_[i] + other.v_[i];
    return v;
}

template<typename T>
KDynamicVector<T> KDynamicVector<T>::operator-(
        const KDynamicVector<T> &other) const
{
    KDynamicVector<T> v(size_);
    for (int i = 0; i < size_; ++i)
        v.v_[i] = v_[i] - other.v_[i];
    return v;
}

template<typename T>
KDynamicVector<T> KDynamicVector<T>::operator*(T factor) const
{
    KDynamicVector<T> v(size_);
    for (int i = 0; i < size_; ++i)
        v.v_[i] = v_[i] * factor;
    return v;
}

template<typename T>
KDynamicVector<T> KDynamicVector<T>::operator/(T divisor) const
{
    KDynamicVector<T> v(size_);
    for (int i = 0; i < size_; ++i)
        v.v_[i] = v_[i] / divisor;
    return v;
}

template<typename TT>
KING_EXPORT KDynamicVector<TT> operator-(const KDynamicVector<TT> &vector)
{
    KDynamicVector<TT> v(vector.size_);
    for (int i = 0; i < vector.size_; ++i)
        v.v_[i] = -vector.v_[i];
    return v;
}

template<typename TT>
KING_EXPORT KDynamicVector<TT> operator*(
        TT factor, const KDynamicVector<TT> &vector)
{
    KDynamicVector<TT> v(vector.size_);
    for (int i = 0; i < vector.size_; ++i)
        v.v_[i] = vector.v_[i] * factor;
    return v;
}

#endif // KDynamicVector_H
