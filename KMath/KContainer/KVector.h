//#ifndef KVECTOR_H
//#define KVECTOR_H

//#include <QDebug>
//#include <QVector>

//#include "KMath_global.h"

//template<typename T>
//class KTypeInfo
//{
//public:
//    bool trivial_ = std::is_trivial<T>::value;
//};

//template<typename T>
//class KTypeInfo<T*>
//{
//public:
//    bool trivial_ = true;
//};

//template<typename T>
//class KMATH_EXPORT KVector
//{
//public:
//    KVector();
//    KVector(const KVector<T> &other);
//    ~KVector();
//    inline int capacity() const {return capacity_;}
//    void append(const T &value);
//    void append(const KVector<T> &value);
//    void reserve(int size);
//    inline const T &at(int i) const {return data_[i];}
//    void clear();
//    inline const T *constData() const {return data_;}
//    inline const T &constFirst() const {return data_[0];}
//    inline const T &constLast() const {return data_[size_ - 1];}
//    bool contains(const T &value) const;
//    int count(const T &value) const;
//    inline int size() const {return size_;}
//    inline T *data() const {return data_;}
//    inline bool isEmpty() const {return size_ == 0;}
//    inline T &first() {return data_[0];}
//    inline const T &first() const {return data_[0];}
//    inline T &last() {return data_[size_ - 1];}
//    inline const T &last() const {return data_[size_ - 1];}
//    int indexOf(const T &value, int from = 0) const;
//    int lastIndexOf(const T &value, int from = -1) const;
//    inline void insert(int i, const T &value);
//    void insert(int i, int count, const T &value);
//    inline void prepend(const T &value);
//    KVector mid(int pos, int length = -1) const;
//    inline void remove(int i);
//    void remove(int i, int count);
//    int removeAll(const T &value);
//    void removeFirst();
//    void removeLast();
//    void replace(int i, const T &value);
//    void swap(KVector<T> &other);
//    inline T takeAt(int i);
//    inline T takeFirst();
//    inline T takeLast();
//    inline T &operator[](int i) const;
//    bool operator==(const KVector<T> &other) const;
//    inline bool operator!=(const KVector<T> &other) const;
//    inline KVector<T> &operator<<(const T &value);
//    inline KVector<T> &operator<<(const KVector<T> &other);
//    inline KVector<T> &operator+=(const T &value);
//    inline KVector<T> &operator+=(const KVector<T> &other);
//    inline KVector<T> operator+(const KVector<T> &other);
//    KVector<T> &operator=(const KVector<T> &other);

//private:
//    void capacityExpansion();

//    T *data_;
//    int size_ = 0;
//    int capacity_;
//    float expansion_multiple_ = 1.5;
//    const bool trivial_ = KTypeInfo<T>().trivial_;
//};

//template<typename T>
//KVector<T>::KVector() : capacity_(10), data_(new T[10])
//{

//}

//template<typename T>
//KVector<T>::KVector(const KVector<T> &other) : size_(other.size_),
//    capacity_(other.capacity_), data_(new T[other.capacity_])
//{
//    for (int i = 0; i < size_; ++i)
//        data_[i] = other.data_[i];
//}

//template<typename T>
//KVector<T>::~KVector()
//{
//    delete [] data_;
//}

//template<typename T>
//void KVector<T>::append(const T &value)
//{
//    if (size_ == capacity_) {
//        capacity_ *= expansion_multiple_;
//        capacityExpansion();
//    }
//    data_[size_++] = value;
//}

//template<typename T>
//void KVector<T>::append(const KVector<T> &value)
//{
//    int min_size = size_ + value.size_;
//    if (min_size > capacity_) {
//        do {
//            capacity_ *= expansion_multiple_;
//        } while (min_size > capacity_);
//        capacityExpansion();
//    }
//    for (int i = 0; i < value.size_; ++i) {
//        data_[size_++] = value.data_[i];
//    }
//}

//template<typename T>
//void KVector<T>::reserve(int size)
//{
//    if (size <= capacity_)
//        return;
//    capacity_ = size;
//    capacityExpansion();
//}

//template<typename T>
//void KVector<T>::clear()
//{
//    if (!trivial_) {
//        for (int i = 0; i < size_; ++i) {
//            data_[i].~T();
//        }
//    }
//    size_ = 0;
//}

//template<typename T>
//bool KVector<T>::contains(const T &value) const
//{
//    for (int i = 0; i < size_; ++i) {
//        if (data_[i] == value)
//            return true;
//    }
//    return false;
//}

//template<typename T>
//int KVector<T>::count(const T &value) const
//{
//    int num = 0;
//    for (int i = 0; i < size_; ++i) {
//        if (data_[i] == value)
//            ++num;
//    }
//    return num;
//}

//template<typename T>
//int KVector<T>::indexOf(const T &value, int from) const
//{
//    for (int i = from; i < size_; ++i) {
//        if (data_[i] == value)
//            return i;
//    }
//    return -1;
//}

//template<typename T>
//int KVector<T>::lastIndexOf(const T &value, int from) const
//{
//    if (from == -1)
//        from = size_ - 1;
//    for (int i = from; i >= 0; --i) {
//        if (data_[i] == value)
//            return i;
//    }
//    return -1;
//}

//template<typename T>
//inline void KVector<T>::insert(int i, const T &value)
//{
//    insert(i, 1, value);
//}

//template<typename T>
//void KVector<T>::insert(int i, int count, const T &value)
//{
//    if (i < 0 || i > size_ || count <= 0)
//        return;
//    int min_size = count + size_;
//    if (min_size > capacity_) {
//        do {
//            capacity_ *= expansion_multiple_;
//        } while (min_size > capacity_);
//        T *new_data = new T[capacity_];
//        if (size_ == 0) {
//            delete [] data_;
//            data_ = new_data;
//            size_ = count;
//            for (int j = 0; j < size_; ++j) {
//                data_[j] = value;
//            }
//            return;
//        }
//        for (int j = 0; j < i; ++j)
//            new_data[j] = data_[j];

//        for (int j = size_ - 1; j >= i; --j)
//            new_data[j + count] = data_[j];

//        int behind_start = i + count;
//        for (int j = i; j < behind_start; ++j)
//            new_data[j] = value;

//        delete [] data_;
//        data_ = new_data;
//        size_ = min_size;
//        return;
//    }

//    if (trivial_) {
//        for (int j = size_ - 1; j >= i; --j) {
//            data_[j + count] = data_[j];
//        }
//    } else {
//        for (int j = size_ - 1; j >= i; --j) {
//            data_[j + count] = data_[j];
//            data_[j].~T();
//        }
//    }
//    int behind_start = i + count;
//    for (int j = i; j < behind_start; ++j)-
//        data_[j] = value;

//    size_ = min_size;
//}

//template<typename T>
//void KVector<T>::prepend(const T &value)
//{
//    insert(0, 1, value);
//}

//template<typename T>
//KVector<T> KVector<T>::mid(int pos, int length) const
//{
//    KVector<T> child;
//    int remain = size_ - pos;
//    if (length == -1 || length > remain)
//        length = remain;
//    child.reserve(length);
//    for (int i = 0; i < length; ++i) {
//        child.data_[i] = data_[pos + i];
//    }
//    return child;
//}

//template<typename T>
//inline void KVector<T>::remove(int i)
//{
//    return remove(i, 1);
//}

//template<typename T>
//void KVector<T>::remove(int i, int count)
//{
//    if (i < 0 || i >= size_ || count < -1)
//        return;
//    int remain = size_ - i;
//    int last;
//    if (count == -1 || count > remain) {
//        last = size_ - 1;
//        count = remain;
//    } else {
//        last = i + count - 1;
//    }
//    if (trivial_) {
//        for (int j = last + 1; j < size_; ++j) {
//            data_[j - count] = data_[j];
//        }
//    } else {
//        for (int j = last + 1; j < size_; ++j) {
//            data_[j - count].~T();
//            data_[j - count] = data_[j];
//        }
//        for (int j = size_ - count; j < size_; ++j) {
//            data_[j].~T();
//        }
//    }
//    size_ -= count;
//}

//template<typename T>
//int KVector<T>::removeAll(const T &value)
//{
//    int num = 0;
//    for (int i = size_ - 1; i >= 0; --i) {
//        if (data_[i] == value) {
//            ++num;
//            remove(i, 1);
//        }
//    }
//    return num;
//}

//template<typename T>
//void KVector<T>::removeFirst()
//{
//    if (trivial_) {
//        for (int i = 1; i < size_; ++i) {
//            data_[i - 1] = data_[i];
//        }
//    } else {
//        int last = size_ - 1;
//        for (int i = 0; i < last; ++i) {
//            data_[i].~T();
//            data_[i] = data_[i + 1];
//        }
//        data_[last].~T();
//    }
//    --size_;
//}

//template<typename T>
//void KVector<T>::removeLast()
//{
//    if (!trivial_)
//        data_[size_ - 1].~T();
//    --size_;
//}

//template<typename T>
//void KVector<T>::replace(int i, const T &value)
//{
//    if (!trivial_)
//        data_[i].~T();
//    data_[i] = value;
//}

//template<typename T>
//void KVector<T>::swap(KVector<T> &other)
//{
//    T *temp_data = data_;
//    int temp_size = size_;
//    int temp_capacity = capacity_;
//    data_ = other.data_;
//    size_ = other.size_;
//    capacity_ = other.capacity_;
//    other.data_ = temp_data;
//    other.size_ = temp_size;
//    other.capacity_ = temp_capacity;
//}

//template<typename T>
//inline T KVector<T>::takeAt(int i)
//{
//    T t = data_[i];
//    remove(i);
//    return t;
//}

//template<typename T>
//inline T KVector<T>::takeFirst()
//{
//    T t = data_[0];
//    removeFirst();
//    return t;
//}

//template<typename T>
//inline T KVector<T>::takeLast()
//{
//    T t = data_[size_ - 1];
//    removeLast();
//    return t;
//}

//template<typename T>
//inline T &KVector<T>::operator[](int i) const
//{
//    return data_[i];
//}

//template<typename T>
//bool KVector<T>::operator==(const KVector<T> &other) const
//{
//    if (size_ != other.size_)
//        return false;
//    for (int i = 0; i < size_; ++i) {
//        if (data_[i] != other.data_[i])
//            return false;
//    }
//    return true;
//}

//template<typename T>
//inline bool KVector<T>::operator!=(const KVector<T> &other) const
//{
//    return !(*this == other);
//}

//template<typename T>
//inline KVector<T> &KVector<T>::operator<<(const T &value)
//{
//    append(value);
//    return *this;
//}

//template<typename T>
//inline KVector<T> &KVector<T>::operator<<(const KVector<T> &other)
//{
//    append(other);
//    return *this;
//}

//template<typename T>
//inline KVector<T> &KVector<T>::operator+=(const T &value)
//{
//    append(value);
//    return *this;
//}

//template<typename T>
//inline KVector<T> &KVector<T>::operator+=(const KVector<T> &other)
//{
//    append(other);
//    return *this;
//}

//template<typename T>
//KVector<T> KVector<T>::operator+(const KVector<T> &other)
//{
//    KVector<T> v;
//    v.size_ = size_ + other.size_;
//    if (v.size_ > v.capacity_) {
//        v.capacity_ = v.size_;
//        v.capacityExpansion();
//    }
//    for (int i = 0; i < size_; ++i)
//        v.data_[i] = data_[i];
//    for (int i = 0; i < other.size_; ++i)
//        v.data_[i + size_] = other.data_[i];
//    return v;
//}

//template<typename T>
//KVector<T> &KVector<T>::operator=(const KVector<T> &other)
//{
//    if (other.size_ > capacity_) {
//        capacity_ = other.size_ * expansion_multiple_;
//        delete [] data_;
//        data_ = new T[capacity_];
//        size_ = other.size_;
//        for (int i = 0; i < size_; ++i)
//            data_[i] = other.data_[i];
//        return *this;
//    }
//    if (!trivial_)
//        for (int i = 0; i < size_; ++i)
//            data_[i].~T();
//    size_ = other.size_;
//    for (int i = 0; i < size_; ++i)
//        data_[i] = other.data_[i];
//    return *this;
//}

//template<typename T>
//void KVector<T>::capacityExpansion()
//{
//    T *new_data = new T[capacity_];
//    for (int i = 0; i < size_; ++i) {
//        new_data[i] = data_[i];
//    }
//    delete [] data_;
//    data_ = new_data;
//}

//#endif // KVECTOR_H































#ifndef KVECTOR_H
#define KVECTOR_H

#include <QDebug>

#include "King_global.h"

template<typename T>
class KING_EXPORT KVector
{
public:
    KVector();
    KVector(const KVector<T> &other);
    ~KVector();
    inline int capacity() const {return capacity_;}
    void append(const T &value);
    void append(const KVector<T> &value);
    void reserve(int size);
    inline const T &at(int i) const {return data_[i];}
    void clear();
    inline const T *constData() const {return data_;}
    inline const T &constFirst() const {return data_[0];}
    inline const T &constLast() const {return data_[size_ - 1];}
    bool contains(const T &value) const;
    int count(const T &value) const;
    inline int size() const {return size_;}
    inline T *data() const {return data_;}
    inline bool isEmpty() const {return size_ == 0;}
    inline T &first() {return data_[0];}
    inline const T &first() const {return data_[0];}
    inline T &last() {return data_[size_ - 1];}
    inline const T &last() const {return data_[size_ - 1];}
    int indexOf(const T &value, int from = 0) const;
    int lastIndexOf(const T &value, int from = -1) const;
    inline void insert(int i, const T &value);
    void insert(int i, int count, const T &value);
    inline void prepend(const T &value);
    KVector mid(int pos, int length = -1) const;
    inline void remove(int i);
    void remove(int i, int count);
    int removeAll(const T &value);
    void removeFirst();
    void removeLast();
    void replace(int i, const T &value);
    void swap(KVector<T> &other);
    inline T takeAt(int i);
    inline T takeFirst();
    inline T takeLast();
    inline T &operator[](int i) const;
    bool operator==(const KVector<T> &other) const;
    inline bool operator!=(const KVector<T> &other) const;
    inline KVector<T> &operator<<(const T &value);
    inline KVector<T> &operator<<(const KVector<T> &other);
    inline KVector<T> &operator+=(const T &value);
    inline KVector<T> &operator+=(const KVector<T> &other);
    inline KVector<T> operator+(const KVector<T> &other);
    KVector<T> &operator=(const KVector<T> &other);

private:
    void capacityExpansion();

    T *data_;
    int size_ = 0;
    int capacity_;
    float expansion_multiple_ = 1.5;
};

template<typename T>
KVector<T>::KVector() : capacity_(10), data_(new T[10])
{

}

template<typename T>
KVector<T>::KVector(const KVector<T> &other) : size_(other.size_),
    capacity_(other.capacity_), data_(new T[other.capacity_])
{
    for (int i = 0; i < size_; ++i)
        data_[i] = other.data_[i];
}

template<typename T>
KVector<T>::~KVector()
{
    delete [] data_;
}

template<typename T>
void KVector<T>::append(const T &value)
{
    if (size_ == capacity_) {
        capacity_ *= expansion_multiple_;
        capacityExpansion();
    }
    data_[size_++] = value;
}

template<typename T>
void KVector<T>::append(const KVector<T> &value)
{
    int min_size = size_ + value.size_;
    if (min_size > capacity_) {
        do {
            capacity_ *= expansion_multiple_;
        } while (min_size > capacity_);
        capacityExpansion();
    }
    for (int i = 0; i < value.size_; ++i) {
        data_[size_++] = value.data_[i];
    }
}

template<typename T>
void KVector<T>::reserve(int size)
{
    if (size <= capacity_)
        return;
    capacity_ = size;
    capacityExpansion();
}

template<typename T>
void KVector<T>::clear()
{
    size_ = 0;
}

template<typename T>
bool KVector<T>::contains(const T &value) const
{
    for (int i = 0; i < size_; ++i) {
        if (data_[i] == value)
            return true;
    }
    return false;
}

template<typename T>
int KVector<T>::count(const T &value) const
{
    int num = 0;
    for (int i = 0; i < size_; ++i) {
        if (data_[i] == value)
            ++num;
    }
    return num;
}

template<typename T>
int KVector<T>::indexOf(const T &value, int from) const
{
    for (int i = from; i < size_; ++i) {
        if (data_[i] == value)
            return i;
    }
    return -1;
}

template<typename T>
int KVector<T>::lastIndexOf(const T &value, int from) const
{
    if (from == -1)
        from = size_ - 1;
    for (int i = from; i >= 0; --i) {
        if (data_[i] == value)
            return i;
    }
    return -1;
}

template<typename T>
inline void KVector<T>::insert(int i, const T &value)
{
    insert(i, 1, value);
}

template<typename T>
void KVector<T>::insert(int i, int count, const T &value)
{
    if (i < 0 || i > size_ || count <= 0)
        return;
    int min_size = count + size_;
    if (min_size > capacity_) {
        capacity_ = min_size * expansion_multiple_;
        T *new_data = new T[capacity_];
        if (size_ == 0) {
            delete [] data_;
            data_ = new_data;
            size_ = count;
            for (int j = 0; j < size_; ++j)
                data_[j] = value;
            return;
        }
        for (int j = 0; j < i; ++j)
            new_data[j] = data_[j];

        for (int j = size_ - 1; j >= i; --j)
            new_data[j + count] = data_[j];

        int behind_start = i + count;
        for (int j = i; j < behind_start; ++j)
            new_data[j] = value;

        delete [] data_;
        data_ = new_data;
        size_ = min_size;
        return;
    }

    for (int j = size_ - 1; j >= i; --j)
        data_[j + count] = data_[j];

    int behind_start = i + count;
    for (int j = i; j < behind_start; ++j)
        data_[j] = value;

    size_ = min_size;
}

template<typename T>
void KVector<T>::prepend(const T &value)
{
    insert(0, 1, value);
}

template<typename T>
KVector<T> KVector<T>::mid(int pos, int length) const
{
    KVector<T> child;
    int remain = size_ - pos;
    if (length == -1 || length > remain)
        length = remain;
    child.reserve(length);
    for (int i = 0; i < length; ++i) {
        child.data_[i] = data_[pos + i];
    }
    return child;
}

template<typename T>
inline void KVector<T>::remove(int i)
{
    return remove(i, 1);
}

template<typename T>
void KVector<T>::remove(int i, int count)
{
    if (i < 0 || i >= size_ || count < -1)
        return;
    int remain = size_ - i;
    int last;
    if (count == -1 || count > remain) {
        last = size_ - 1;
        count = remain;
    } else {
        last = i + count - 1;
    }

    for (int j = last + 1; j < size_; ++j)
        data_[j - count] = data_[j];

    size_ -= count;
}

template<typename T>
int KVector<T>::removeAll(const T &value)
{
    int num = 0;
    for (int i = size_ - 1; i >= 0; --i) {
        if (data_[i] == value) {
            ++num;
            remove(i, 1);
        }
    }
    return num;
}

template<typename T>
void KVector<T>::removeFirst()
{
    if (size_ == 0)
        return;

    for (int i = 1; i < size_; ++i)
        data_[i - 1] = data_[i];

    --size_;
}

template<typename T>
void KVector<T>::removeLast()
{
    if (size_ == 0)
        return;

    --size_;
}

template<typename T>
void KVector<T>::replace(int i, const T &value)
{
    data_[i] = value;
}

template<typename T>
void KVector<T>::swap(KVector<T> &other)
{
    T *temp_data = data_;
    int temp_size = size_;
    int temp_capacity = capacity_;
    data_ = other.data_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    other.data_ = temp_data;
    other.size_ = temp_size;
    other.capacity_ = temp_capacity;
}

template<typename T>
inline T KVector<T>::takeAt(int i)
{
    T t = data_[i];
    remove(i);
    return t;
}

template<typename T>
inline T KVector<T>::takeFirst()
{
    T t = data_[0];
    removeFirst();
    return t;
}

template<typename T>
inline T KVector<T>::takeLast()
{
    T t = data_[size_ - 1];
    removeLast();
    return t;
}

template<typename T>
inline T &KVector<T>::operator[](int i) const
{
    return data_[i];
}

template<typename T>
bool KVector<T>::operator==(const KVector<T> &other) const
{
    if (size_ != other.size_)
        return false;
    for (int i = 0; i < size_; ++i) {
        if (data_[i] != other.data_[i])
            return false;
    }
    return true;
}

template<typename T>
inline bool KVector<T>::operator!=(const KVector<T> &other) const
{
    return !(*this == other);
}

template<typename T>
inline KVector<T> &KVector<T>::operator<<(const T &value)
{
    append(value);
    return *this;
}

template<typename T>
inline KVector<T> &KVector<T>::operator<<(const KVector<T> &other)
{
    append(other);
    return *this;
}

template<typename T>
inline KVector<T> &KVector<T>::operator+=(const T &value)
{
    append(value);
    return *this;
}

template<typename T>
inline KVector<T> &KVector<T>::operator+=(const KVector<T> &other)
{
    append(other);
    return *this;
}

template<typename T>
KVector<T> KVector<T>::operator+(const KVector<T> &other)
{
    KVector<T> v;
    v.size_ = size_ + other.size_;
    if (v.size_ > v.capacity_) {
        v.capacity_ = v.size_;
        v.capacityExpansion();
    }
    for (int i = 0; i < size_; ++i)
        v.data_[i] = data_[i];
    for (int i = 0; i < other.size_; ++i)
        v.data_[i + size_] = other.data_[i];
    return v;
}

template<typename T>
KVector<T> &KVector<T>::operator=(const KVector<T> &other)
{
    if (other.size_ > capacity_) {
        capacity_ = other.size_ * expansion_multiple_;
        delete [] data_;
        data_ = new T[capacity_];
        size_ = other.size_;
        for (int i = 0; i < size_; ++i)
            data_[i] = other.data_[i];
        return *this;
    }

    size_ = other.size_;
    for (int i = 0; i < size_; ++i)
        data_[i] = other.data_[i];
    return *this;
}

template<typename T>
void KVector<T>::capacityExpansion()
{
    T *new_data = new T[capacity_];
    for (int i = 0; i < size_; ++i) {
        new_data[i] = data_[i];
    }
    delete [] data_;
    data_ = new_data;
}

#endif // KVECTOR_H
