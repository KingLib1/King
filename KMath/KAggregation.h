#ifndef KAGGREGATION_H
#define KAGGREGATION_H

#include <QVector>

#include "King_global.h"

template<typename T>
class KING_EXPORT KAggregation
{
public:
    KAggregation();
    KAggregation(const QVector<T> &data);
    KAggregation(const KAggregation &other);
    ~KAggregation();

    inline void addData(const T &data);
    inline void removeData(const T &data);
    inline void setData(const QVector<T> &data);
    void removeMax();
    void removeMin();

    T averageValue() const;
    inline const QVector<T> &data() const;
    T max() const;
    T min() const;

    inline KAggregation &operator=(const KAggregation &other);

private:
    QVector<T> data_;
};

template<typename T>
KAggregation<T>::KAggregation()
{

}

template<typename T>
KAggregation<T>::KAggregation(const QVector<T> &data)
{
    data_ = data;
}

template<typename T>
KAggregation<T>::KAggregation(const KAggregation &other)
{
    data_ = other.data_;
}

template<typename T>
KAggregation<T>::~KAggregation()
{

}

template<typename T>
inline void KAggregation<T>::addData(const T &data)
{
    data_ << data;
}

template<typename T>
inline void KAggregation<T>::removeData(const T &data)
{
    data_.removeOne(data);
}

template<typename T>
inline void KAggregation<T>::setData(const QVector<T> &data)
{
    data_ = data;
}

template<typename T>
void KAggregation<T>::removeMax()
{
    if (data_.isEmpty())
        return;
    T max = data_.at(0);
    int idx = 0;
    for (int i = 1; i < data_.size(); ++i) {
        if (data_.at(i) > max) {
            max = data_.at(i);
            idx = i;
        }
    }
    data_.remove(idx);
}

template<typename T>
void KAggregation<T>::removeMin()
{
    if (data_.isEmpty())
        return;
    T min = data_.at(0);
    int idx = 0;
    for (int i = 1; i < data_.size(); ++i) {
        if (data_.at(i) < min) {
            min = data_.at(i);
            idx = i;
        }
    }
    data_.remove(idx);
}

template<typename T>
T KAggregation<T>::averageValue() const
{
    if (data_.isEmpty())
        return T();
    T av = data_.at(0);
    for (int i = 1; i < data_.size(); ++i)
        av += data_.at(i);
    return av;
}

template<typename T>
inline const QVector<T> &KAggregation<T>::data() const
{
    return data_;
}

template<typename T>
T KAggregation<T>::max() const
{
    if (data_.isEmpty())
        return T();
    T max = data_.at(0);
    for (int i = 1; i < data_.size(); ++i) {
        if (data_.at(i) > max)
            max = data_.at(i);
    }
    return max;
}

template<typename T>
T KAggregation<T>::min() const
{
    if (data_.isEmpty())
        return T();
    T min = data_.at(0);
    for (int i = 1; i < data_.size(); ++i) {
        if (data_.at(i) < min)
            min = data_.at(i);
    }
    return min;
}

template<typename T>
KAggregation<T> &KAggregation<T>::operator=(const KAggregation &other)
{
    data_ = other.data_;
}

#endif // KAGGREGATION_H
