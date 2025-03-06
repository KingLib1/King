#include "kpathcompare.h"

#include "kspliter.h"
#include "KAlgorithm.h"
#include "kcompatibly.h"

KPathCompare::KPathCompare(const QVector<KVector3D> &path1,
                           const QVector<KVector3D> &path2) :
    path1_(path1), path2_(path2)
{

}

void KPathCompare::compare()
{
    duplicationRemoval(path1_);
    duplicationRemoval(path2_);

    double mindis1;
    QVector<double> dis1 = calculateDistance(path1_, mindis1);
    double mindis2;
    QVector<double> dis2 = calculateDistance(path2_, mindis2);

    mindis1 = kMin(delta_, mindis1);
//    qDebug() << "delta_" << delta_ << mindis1 << del;
    QVector<KVector3D> path1 = interpolation(path1_, dis1, mindis1, mindis1);
    QVector<KVector3D> path2 = interpolation(path2_, dis2, mindis1, mindis1);
    QVector<KIndex2D> indexes;
    QVector<KVector3D> lcs = LCS(path2, path1, indexes);
    match_ratio1_ = double(lcs.size()) / double(path1.size());

//    qDebug() << "pathssize" << path1.size();
//    qDebug() << "indexes" << indexes.size();
//    qDebug() << "lcssize" << lcs.size();
//    for (int i = 0; i < indexes.size(); ++i){
//        qDebug() << "index" << indexes.at(i).i() << indexes.at(i).j() << path2.at(indexes.at(i).i()) << path1.at(indexes.at(i).j());
//    }

    indexes.clear();
    mindis2 = kMin(delta_, mindis2);
//    qDebug() << "delta_" << delta_ << mindis2 <<del;
    path2 = interpolation(path2_, dis2, mindis2, mindis2);
    path1 = interpolation(path1_, dis1, mindis2, mindis2);
    lcs = LCS(path1, path2, indexes);
    match_ratio2_ = double(lcs.size()) / double(path2.size());

//    qDebug() << "pathssize" << path2.size();
//    qDebug() << "indexes" << indexes.size();
//    for (int i = 0; i < indexes.size(); ++i){
//        qDebug() << "index" << indexes.at(i).i() << indexes.at(i).j() << path1.at(indexes.at(i).i()) << path2.at(indexes.at(i).j());
//    }
}

QVector<KVector3D> KPathCompare::interpolation(const QVector<KVector3D> &path,
    const QVector<double> &dis, double delta, double &mindis) const
{
    mindis = K_DBL_MAX;
    QVector<KVector3D> tpath;
    KSpliter spliter;
    for (int i = 1; i < path.size(); ++i) {
        double d = dis.at(i - 1);
        if (d <= delta) {
            tpath << path.at(i - 1);
            continue;
        }
        int slices = d / delta + 1;
        d /= slices;
        if (d < mindis)
            mindis = d;
        tpath << spliter.split(path.at(i - 1), path.at(i), slices, true, false);
    }
    tpath << path.last();

    return tpath;
}

QVector<KVector3D> KPathCompare::LCS(const QVector<KVector3D> &v1,
                                     const QVector<KVector3D> &v2,
                                     QVector<KIndex2D> &indexes)
{
    QVector<KVector3D> v;
    if (v1.isEmpty() || v2.isEmpty())
        return v;

    const int row = v1.size() + 1;
    const int column = v2.size() + 1;
    QVector<QVector<short>> dp(row, QVector<short>(column));

    for (int i = 0; i < row; ++i)
        dp[i][0] = 0;
    for (int i = 0; i < column; ++i)
        dp[0][i] = 0;

    int i1, j1;
    for (int i = 1; i < row; ++i) {
        i1 = i - 1;
        for (int j = 1; j < column; ++j) {
            j1 = j - 1;
            if (v1.at(i1).isEqualWith(v2.at(j1), delta_))
                dp[i][j] = dp[i1][j1] + 1;
            else
                dp[i][j] = kMax(dp[i1][j], dp[i][j1]);
        }
    }

    findLCSElement(indexes, dp, v1.size(), v2.size());

//    qDebug() << "index";
//    for (int i = 0; i < indexes.size(); ++i) {
//        qDebug() << indexes.at(i).i() << indexes.at(i).j();
//    }

    for (int i = indexes.size() - 1; i > -1; --i) {
        v << v1.at(indexes.at(i).i());
    }
    return v;
}

QVector<double> KPathCompare::calculateDistance(const QVector<KVector3D> &v1,
                                                double &mindis) const
{
    QVector<double> result;
    mindis = K_DBL_MAX;
    for (int i = 1; i < v1.size(); ++i) {
        double dis = v1.at(i).distanceToPoint(v1.at(i - 1));
        if (dis < mindis)
            mindis = dis;
        result << dis;
    }
    return result;
}

void KPathCompare::duplicationRemoval(QVector<KVector3D> &ring)
{
    for (int i = ring.size() - 1; i > 0; --i)
        if (ring.at(i - 1) == ring.at(i))
            ring.removeAt(i);

    int last = ring.size() - 1;
    for (int i = last - 1; i > 0; --i) {
        KLineSegment3D line(ring.at(i - 1), ring.at(i + 1));
        if (line.contains(ring.at(i)))
            ring.removeAt(i);
    }
}
