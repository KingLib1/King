#ifndef KFRICTION_H
#define KFRICTION_H

class KFriction
{
public:
    KFriction();
    /**
     * @brief KFriction
     * @param us 静摩擦系数
     * @param uk 动摩擦系数
     * @param n 法向力
     */
    KFriction(double us, double uk, double n);
    KFriction(const KFriction &fri);
    ~KFriction();

    inline void setStaticFrictionCoefficient(double us);
    inline void setKineticFrictionCoefficient(double uk);
    inline void setNormalForce(double n);

    inline double staticFrictionCoefficient() const;
    inline double kineticFrictionCoefficient() const;
    inline double normalForce() const;
    inline double staticFriction() const;
    inline double kineticFriction() const;

    inline KFriction &operator=(const KFriction &fri);

private:
    double us_; // 静摩擦系数
    double uk_; // 动摩擦系数
    double n_; // 法向力
};

inline void KFriction::setStaticFrictionCoefficient(double us)
{
    us_ = us;
}

inline void KFriction::setKineticFrictionCoefficient(double uk)
{
    uk_ = uk;
}

inline void KFriction::setNormalForce(double n)
{
    n_ = n;
}

inline double KFriction::staticFrictionCoefficient() const
{
    return us_;
}

inline double KFriction::kineticFrictionCoefficient() const
{
    return uk_;
}

inline double KFriction::normalForce() const
{
    return n_;
}

inline double KFriction::staticFriction() const
{
    return us_ * n_;
}

inline double KFriction::kineticFriction() const
{
    return uk_ * n_;
}

inline KFriction &KFriction::operator=(const KFriction &fri)
{
    us_ = fri.us_;
    uk_ = fri.uk_;
    n_ = fri.n_;
    return *this;
}

#endif // KFRICTION_H
