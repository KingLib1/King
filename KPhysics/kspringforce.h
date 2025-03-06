#ifndef KSPRINGFORCE_H
#define KSPRINGFORCE_H

class KSpringForce
{
public:
    KSpringForce();
    /**
     * @brief KSpringForce
     * @param k 弹簧常数
     * @param rest 静止长度
     * @param current 当前长度
     */
    KSpringForce(double k, double rest, double current);
    KSpringForce(const KSpringForce &spr);
    ~KSpringForce();

    inline void setSpringConstant(double k);
    inline void setRestLength(double rest);
    inline void setCurrentLength(double current);

    inline double springConstant() const;
    inline double restLength() const;
    inline double currentLength() const;
    inline double springForce() const;

    inline KSpringForce &operator=(const KSpringForce &spr);

private:
    double k_; // 弹簧常数
    double rest_; // 静止长度
    double current_; // 当前长度
};

inline void KSpringForce::setSpringConstant(double k)
{
    k_ = k;
}

inline void KSpringForce::setRestLength(double rest)
{
    rest_ = rest;
}

inline void KSpringForce::setCurrentLength(double current)
{
    current_ = current;
}

inline double KSpringForce::springConstant() const
{
    return k_;
}

inline double KSpringForce::restLength() const
{
    return rest_;
}

inline double KSpringForce::currentLength() const
{
    return current_;
}

inline double KSpringForce::springForce() const
{
    return k_ * (rest_ - current_);
}

inline KSpringForce &KSpringForce::operator=(const KSpringForce &spr)
{
    k_ = spr.k_;
    rest_ = spr.rest_;
    current_ = spr.current_;
    return *this;
}

#endif // KSPRINGFORCE_H
