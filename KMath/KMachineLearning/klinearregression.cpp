#include "klinearregression.h"

#include <QDebug>

// 辅助
void gradientDescent_1(const QVector<KPointF> &points,
                       double &k, double &b, double alpha)
{
    double dk = 0;
    double db = 0;

    for (int i = 0; i < points.size(); ++i) {
        double temp = k*points.at(i).x() + b - points.at(i).y();
        dk += temp * points.at(i).x();
        db += temp;
    }
    dk /= points.size();
    db /= points.size();

    k -= alpha * dk;
    b -= alpha * db;

    if (kFabs(dk) < EPS6 && kFabs(db) < EPS6)
        return;
    gradientDescent_1(points, k, b, alpha);
}

KLinear kLinearRegression(QVector<KPointF> points)
{
    int min = points.at(0).x();
    int max = points.at(0).x();
    for (int i = 1; i < points.size(); ++i) {
        if (points.at(i).x() < min)
            min = points.at(i).x();
        else if (points.at(i).x() > max)
            max = points.at(i).x();
    }

    double s = max - min;
    for (int i = 0; i < points.size(); ++i) {
        points[i].setX((points.at(i).x() - min) / s);
    }

    double k = 0;
    double b = 0;
    double alpha = 1;

    gradientDescent_1(points, k, b, alpha);
    k /= s;
    b -= k * min;
    return KLinear(k, b);
}

// 辅助
void LogisticRegression_1(QVector<KPointF> points, const QVector<int> &labels,
                          double alpha, double &a, double &b, double &c)
{
    double da = 0;
    double db = 0;
    double dc = 0;
    for (int i = 0; i < points.size(); ++i) {
        double z = a * points.at(i).x() + b * points.at(i).y() + c;
        double ez = kExp(z);
        double f = labels.at(i) == 1 ? 1.0 / (1 + ez) : -ez / kSquare(1 + ez);
        da += f * points.at(i).x();
        db += f * points.at(i).y();
        dc += f;
    }

    da /= points.size();
    db /= points.size();
    dc /= points.size();

    a += alpha * da;
    b += alpha * db;
    c += alpha * dc;

    if (kFabs(da) < EPS6 && kFabs(db) < EPS6 && kFabs(dc) < EPS6)
        return;
}

void LogisticRegression(QVector<KPointF> points, const QVector<int> &labels,
                        double &a, double &b, double &c)
{
    int minx = points.at(0).x();
    int maxx = points.at(0).x();
    int miny = points.at(0).y();
    int maxy = points.at(0).y();
    for (int i = 1; i < points.size(); ++i) {
        if (points.at(i).x() < minx)
            minx = points.at(i).x();
        else if (points.at(i).x() > maxx)
            maxx = points.at(i).x();
        if (points.at(i).y() < miny)
            miny = points.at(i).y();
        else if (points.at(i).y() > maxy)
            maxy = points.at(i).y();
    }

    double sx = maxx - minx;
    double sy = maxy - miny;
    for (int i = 0; i < points.size(); ++i) {
        points[i].setXY((points.at(i).x() - minx) / sx,
                        (points.at(i).y() - miny) / sy);
    }

    a = 1;
    b = 1;
    c = 0;
    double alpha = 1;

    LogisticRegression_1(points, labels, alpha, a, b, c);
    a /= sx;
    b /= sy;
    c -= a * minx + b * miny;
}
