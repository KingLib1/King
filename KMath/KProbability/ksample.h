#ifndef KSAMPLE_H
#define KSAMPLE_H

#include <QVector>

// 样本
class KSample
{
public:
    KSample();
    KSample(const QVector<double> &data);

    inline void setData(const QVector<double> &data);
    inline const QVector<double> &data() const;
    /**
     * @brief 期望
     */
    double E() const;
    /**
     * @brief 总体方差
     */
    double D() const;
    /**
     * @brief 样本方差
     */
    double S() const;
    /**
     * @brief 二阶原点矩
     */
    double secondOrderOriginMoment() const;

private:
    QVector<double> data_;
};

inline void KSample::setData(const QVector<double> &data)
{
    data_ = data;
}

inline const QVector<double> &KSample::data() const
{
    return data_;
}

#endif // KSAMPLE_H
