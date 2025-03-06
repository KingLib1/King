#ifndef CONNECTINGROD6_H
#define CONNECTINGROD6_H

class ConnectingRod6
{
public:
    ConnectingRod6();
    ConnectingRod6(double l1x, double l1y, double l1z, double l2, double l3,
                  double l4, double l5);
    ConnectingRod6(const ConnectingRod6 &other);
    ~ConnectingRod6();

    inline void setL1x(double l1x) {l1x_ = l1x;}
    inline void setL1y(double l1y) {l1y_ = l1y;}
    inline void setL1z(double l1z) {l1z_ = l1z;}
    inline void setL2(double l2) {l2_ = l2;}
    inline void setL3(double l3) {l3_ = l3;}
    inline void setL4(double l4) {l4_ = l4;}
    inline void setL5(double l5) {l5_ = l5;}

    inline double l1x() const {return l1x_;}
    inline double l1y() const {return l1y_;}
    inline double l1z() const {return l1z_;}
    inline double l2() const {return l2_;}
    inline double l3() const {return l3_;}
    inline double l4() const {return l4_;}
    inline double l5() const {return l5_;}

    inline ConnectingRod6 &operator=(const ConnectingRod6 &other);

private:
    double l1x_;
    double l1y_;
    double l1z_;
    double l2_;
    double l3_;
    double l4_;
    double l5_;
};

inline ConnectingRod6 &ConnectingRod6::operator=(const ConnectingRod6 &other)
{
    l1x_ = other.l1x_;
    l1y_ = other.l1y_;
    l1z_ = other.l1z_;
    l2_ = other.l2_;
    l3_ = other.l3_;
    l4_ = other.l4_;
    l5_ = other.l5_;
    return *this;
}

#endif // CONNECTINGROD6_H
