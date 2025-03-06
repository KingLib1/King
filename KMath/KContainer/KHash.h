#ifndef KHASH_H
#define KHASH_H

#include <QString>
#include <QDebug>

#include "kvector3d.h"
#include "klinkedlist.h"
#include "KAlgorithm.h"

inline unsigned kHash(unsigned key)
{
    return key;
}

inline unsigned kHash(int key)
{
    return unsigned(key);
}

inline unsigned kHash(float key)
{
    return *(unsigned*)(&key);
}

inline unsigned kHash(long long key)
{
    return unsigned(key ^ (key >> 32));
}

inline unsigned kHash(double key)
{
    long long hash = *(long long*)&key;
    return unsigned(hash ^ (hash >> 32));
}

inline unsigned kHash(bool key)
{
    return key ? 1231 : 1237;
}

unsigned kHash(QString key)
{
    long long hash = 0;
    for (int i = 0; i < key.size(); ++i)
        hash = (hash << 5) - hash  + key.at(i).toLatin1();
    return kHash(hash);
}

inline unsigned kHash(const KPointF &key)
{
    double x = key.x();
    double y = key.y();
    long long hash = *(long long*)&x;
    hash = (hash << 5) - hash + *(long long*)&y;
    return kHash((hash << 5) - hash);
}

inline unsigned kHash(const KVector3D &key)
{
    double x = key.x();
    double y = key.y();
    double z = key.z();
    long long hash = *(long long*)&x;
    hash = (hash << 5) - hash + *(long long*)&y;
    hash = (hash << 5) - hash + *(long long*)&z;
    return kHash((hash << 5) - hash);
}

template<typename T>
inline unsigned kHash(const T *key)
{
    return *(unsigned*)key;
}

template<typename K, typename T>
struct KHashNode
{
    KHashNode(){}
    KHashNode(const K &key, const T &value) : k(key), t(value) {}
    K k;
    T t;
};

template<typename K, typename T>
class KING_EXPORT KHash
{
public:
    KHash();
    /**
     * @brief 根据估算的元素数量构造哈希表
     */
    KHash(unsigned estimatedSize);
    ~KHash();

    void insert(const K &key, const T &value);
    void clear();
    bool remove(const K &key);

    const T value(const K &key) const;
    const K key(const T &value) const;
    inline bool isEmpty() const;
    inline double size() const;
    inline int capacity() const;
    bool contains(const K &key) const;

private:
    void capacityExpansion();

    const unsigned prime_list[26] =
    {
        53, 97, 193, 389, 769,
        1543, 3079, 6151, 12289, 24593,
        49157, 98317, 196613, 393241, 786433,
        1572869, 3145739, 6291469, 12582917, 25165843,
        50331653, 100663319, 201326611, 402653189, 805306457,
        1610612741
    };

    int capacity_index_ = 0;
    int size_ = 0;
    QVector<KLinkedList<KHashNode<K, T>>> table_;
};

template<typename K, typename T>
KHash<K, T>::KHash()
{
    table_.resize(prime_list[capacity_index_]);
}

template<typename K, typename T>
KHash<K, T>::KHash(unsigned estimatedSize)
{
    capacity_index_ = binarySearchFirstLargerOrEqual(estimatedSize, prime_list, 26);
    table_.resize(prime_list[capacity_index_]);
}

template<typename K, typename T>
KHash<K, T>::~KHash()
{
    clear();
}

template<typename K, typename T>
void KHash<K, T>::insert(const K &key, const T &value)
{
    if (1.0 * (size_ + 1) / prime_list[capacity_index_] > 0.7)
        capacityExpansion();

    unsigned index = kHash(key) % capacity();
    const KLinkedList<KHashNode<K, T>> &list = table_.at(index);
    typename KLinkedList<KHashNode<K, T>>::iterator it = list.begin();
    typename KLinkedList<KHashNode<K, T>>::iterator end = list.end();
    for (; it != end; ++it) {
        if (it->k == key) {
            it->t = value;
            return;
        }
    }
    ++size_;
    KHashNode<K, T> node(key, value);
    table_[index].append(node);
}

template<typename K, typename T>
void KHash<K, T>::clear()
{
    size_ = 0;
    int cap = capacity();
    for (int i = 0; i < cap; ++i) {
        table_[i].clear();
    }
}

template<typename K, typename T>
bool KHash<K, T>::remove(const K &key)
{
    unsigned index = kHash(key) % capacity();
    typename KLinkedList<KHashNode<K, T>>::iterator it = table_.at(index).begin();
    typename KLinkedList<KHashNode<K, T>>::iterator end = table_.at(index).end();
    for (; it != end; ++it) {
        if (it->k == key) {
            table_[index].erase(it);
            return true;
        }
    }
    return false;
}

template<typename K, typename T>
const T KHash<K, T>::value(const K &key) const
{
    unsigned index = kHash(key) % capacity();
    const KLinkedList<KHashNode<K, T>> &list = table_.at(index);
    typename KLinkedList<KHashNode<K, T>>::iterator it = list.begin();
    typename KLinkedList<KHashNode<K, T>>::iterator end = list.end();
    for (; it != end; ++it) {
        if (it->k == key)
            return it->t;
    }
    return T();
}

template<typename K, typename T>
const K KHash<K, T>::key(const T &value) const
{
    for (int i = 0; i < table_.size(); ++i) {
        const KLinkedList<KHashNode<K, T>> &list = table_.at(i);
        typename KLinkedList<KHashNode<K, T>>::iterator it = list.begin();
        typename KLinkedList<KHashNode<K, T>>::iterator end = list.end();
        for (; it != end; ++it) {
            if (it->t == value)
                return it->k;
        }
    }
    return T();
}

template<typename K, typename T>
inline bool KHash<K, T>::isEmpty() const
{
    return size_ == 0;
}

template<typename K, typename T>
inline double KHash<K, T>::size() const
{
    return size_;
}

template<typename K, typename T>
inline int KHash<K, T>::capacity() const
{
    return prime_list[capacity_index_];
}

template<typename K, typename T>
bool KHash<K, T>::contains(const K &key) const
{
    unsigned index = kHash(key) % capacity();
    const KLinkedList<KHashNode<K, T>> &list = table_.at(index);
    typename KLinkedList<KHashNode<K, T>>::iterator it = list.begin();
    typename KLinkedList<KHashNode<K, T>>::iterator end = list.end();
    for (; it != end; ++it) {
        if (it->k == key)
            return true;
    }
    return false;
}

template<typename K, typename T>
void KHash<K, T>::capacityExpansion()
{
    if (capacity_index_ == 25)
        return;
    int cap = prime_list[capacity_index_];
    int new_cap = prime_list[++capacity_index_];
    QVector<KLinkedList<KHashNode<K, T>>> table1(new_cap);
    table_.swap(table1);

    typename KLinkedList<KHashNode<K, T>>::iterator it;
    typename KLinkedList<KHashNode<K, T>>::iterator end;
    unsigned index;
    for (int i = 0; i < cap; ++i) {
        end = table1.at(i).end();
        for (it = table1.at(i).begin(); it != end; ++it) {
            KHashNode<K, T> node(it->k, it->t);
            index = kHash(node.k) % new_cap;
            table_[index].append(node);
        }
    }
}

#endif // KHASH_H
