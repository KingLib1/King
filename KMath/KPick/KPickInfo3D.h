#ifndef KPICKINFO3D_H
#define KPICKINFO3D_H

#include "kvector3d.h"

template<typename T>
class KING_EXPORT KPickInfo3D
{
public:
    KPickInfo3D();
    KPickInfo3D(const T &object, const KVector3D pick3d, int place,
                double distance = 0, int priority = 0);
    KPickInfo3D(const KPickInfo3D &other);
    ~KPickInfo3D();

    inline void setObject(const T &object);
    inline void setPos(const KVector3D &pickedPos3D);
    inline void setPlace(int place);
    inline void setDistance(double distance);
    inline void setPriority(double priority);

    inline T &object();
    inline const T &object() const;
    inline const KVector3D &pickedPos3D() const;
    inline int place() const;
    inline double distance() const;
    inline int priority() const;

    inline KPickInfo3D &operator=(const KPickInfo3D &other);

private:
    T object_;
    KVector3D pick3d_;
    int place_;
    double distance_;
    int priority_; // 优先级
};

template<typename T>
KPickInfo3D<T>::KPickInfo3D() : place_(0), distance_(0)
{

}

template<typename T>
KPickInfo3D<T>::KPickInfo3D(const T &object, const KVector3D pick3d, int place,
                            double distance, int priority) :
    object_(object), pick3d_(pick3d), place_(place), distance_(distance),
    priority_(priority)
{

}

template<typename T>
KPickInfo3D<T>::KPickInfo3D(const KPickInfo3D &other) :
    object_(other.object_), pick3d_(other.pick3d_), place_(other.place_),
    distance_(other.distance_), priority_(other.priority_)
{

}

template<typename T>
KPickInfo3D<T>::~KPickInfo3D()
{

}

template<typename T>
inline void KPickInfo3D<T>::setObject(const T &object)
{
    object_ = object;
}

template<typename T>
inline void KPickInfo3D<T>::setPos(const KVector3D &pos)
{
    pick3d_ = pos;
}

template<typename T>
inline void KPickInfo3D<T>::setPlace(int place)
{
    place_ = place;
}

template<typename T>
inline void KPickInfo3D<T>::setDistance(double distance)
{
    distance_ = distance;
}

template<typename T>
inline void KPickInfo3D<T>::setPriority(double priority)
{
    priority_ = priority;
}

template<typename T>
inline T &KPickInfo3D<T>::object()
{
    return object_;
}

template<typename T>
inline const T &KPickInfo3D<T>::object() const
{
    return object_;
}

template<typename T>
inline const KVector3D &KPickInfo3D<T>::pickedPos3D() const
{
    return pick3d_;
}

template<typename T>
inline int KPickInfo3D<T>::place() const
{
    return place_;
}

template<typename T>
inline double KPickInfo3D<T>::distance() const
{
    return distance_;
}

template<typename T>
inline int KPickInfo3D<T>::priority() const
{
    return priority_;
}

template<typename T>
inline KPickInfo3D<T> &KPickInfo3D<T>::operator=(const KPickInfo3D &other)
{
    object_ = other.object_;
    pick3d_ = other.pick3d_;
    place_ = other.place_;
    distance_ = other.distance_;
    priority_ = other.priority_;
    return *this;
}

#endif // KPICKINFO3D_H
