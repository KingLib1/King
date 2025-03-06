#include "ksample.h"

#include "kmath.h"

KSample::KSample()
{

}

KSample::KSample(const QVector<double> &data) : data_(data)
{

}

double KSample::E() const
{
    if (data_.isEmpty())
        return 0;

    double sum = 0;
    for (int i = 0; i < data_.size(); ++i)
        sum += data_.at(i);
    return sum / data_.size();
}

double KSample::D() const
{
    return secondOrderOriginMoment() - kSquare(E());
}

double KSample::S() const
{
    return D() * data_.size() / (data_.size() - 1);
}

double KSample::secondOrderOriginMoment() const
{
    if (data_.isEmpty())
        return 0;

    double sum = 0;
    for (int i = 0; i < data_.size(); ++i)
        sum += kSquare(data_.at(i));
    return sum / data_.size();
}
