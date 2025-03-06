#include "KEquation.h"

#include "kquadratic.h"

#define K_1_E 0.36787944117144232159552377 // e^-1
#define K_1_E_2 0.18393972058572116079776 // (e^-1) / 2

KVector2D solveHomogeneousLinearEquations2x2(
        const KVector2D &v1, const KVector2D &v2, const KVector2D &v3)
{
    double D = v1.x() * v2.y() - v1.y() * v2.x();
    double D1 = v3.x() * v2.y() - v3.y() * v2.x();
    double D2 = v1.x() * v3.y() - v1.y() * v3.x();
    return KVector2D(D1 / D, D2 / D);
}

KVector2D solveHomogeneousLinearEquations3x2(
        const KVector3D &v1, const KVector3D &v2, const KVector3D &v3)
{
    double D = v1.x() * v2.y() - v1.y() * v2.x();
    double D1, D2;
    if (!isZero(D)) {
        D1 = v3.x() * v2.y() - v3.y() * v2.x();
        D2 = v1.x() * v3.y() - v1.y() * v3.x();
    } else {
        D = v1.x() * v2.z() - v1.z() * v2.x();
        if (!isZero(D)) {
            D1 = v3.x() * v2.z() - v3.z() * v2.x();
            D2 = v1.x() * v3.z() - v1.z() * v3.x();
        } else {
            D = v1.y() * v2.z() - v1.z() * v2.y();
            D1 = v3.y() * v2.z() - v3.z() * v2.y();
            D2 = v1.y() * v3.z() - v1.z() * v3.y();
        }
    }
    return KVector2D(D1 / D, D2 / D);
}

KVector3D solveHomogeneousLinearEquations3x3(
        const KVector3D &v1, const KVector3D &v2,
        const KVector3D &v3, const KVector3D &v4)
{
    double D = v1.x()*v2.y()*v3.z() + v2.x()*v3.y()*v1.z() + v3.x()*v1.y()*v2.z() -
            v3.x()*v2.y()*v1.z() - v2.x()*v1.y()*v3.z() - v1.x()*v3.y()*v2.z();
    double D1 = v4.x()*v2.y()*v3.z() + v2.x()*v3.y()*v4.z() + v3.x()*v4.y()*v2.z() -
            v3.x()*v2.y()*v4.z() - v2.x()*v4.y()*v3.z() - v4.x()*v3.y()*v2.z();
    double D2 = v1.x()*v4.y()*v3.z() + v4.x()*v3.y()*v1.z() + v3.x()*v1.y()*v4.z() -
            v3.x()*v4.y()*v1.z() - v4.x()*v1.y()*v3.z() - v1.x()*v3.y()*v4.z();
    double D3 = v1.x()*v2.y()*v4.z() + v2.x()*v4.y()*v1.z() + v4.x()*v1.y()*v2.z() -
            v4.x()*v2.y()*v1.z() - v2.x()*v1.y()*v4.z() - v1.x()*v4.y()*v2.z();
    return KVector3D(D1 / D, D2 / D, D3 / D);
}

KDynamicMatrix<double> solveHomogeneousLinearEquations(
        const KDynamicMatrix<double> &coefficient_matrix)
{
    int rank;
    KDynamicVector<int> indexes;
    KDynamicMatrix<double> m = coefficient_matrix.reducedRowEchelonForm(&rank, &indexes);

    int col = m.column();

    if (rank == col) {
        KDynamicMatrix<double> solve(col, 1);
        solve.fill(0);
        return solve;
    }

    bool *is_solve = new bool[col];
    for (int i = 0; i < col; ++i) {
        is_solve[i] = true;
    }

    for (int i = 0; i < indexes.size(); ++i) {
        is_solve[indexes[i]] = false;
    }

    int solve_count = col - rank;
    int *solve_index = new int[solve_count];
    int idx = 0;
    for (int i = 0; i < solve_count; ++i) {
        while (!is_solve[idx])
            ++idx;
        solve_index[i] = idx;
        ++idx;
    }

    KDynamicMatrix<double> solve(col, solve_count);
    for (int i = 0; i < solve_count; ++i) {
        for (int j = 0; j < solve_count; ++j) {
            solve(solve_index[j], i) = 0;
        }
        solve(solve_index[i], i) = 1;
    }

    for (int i = 0; i < solve_count; ++i) {
        for (int j = 0; j < rank; ++j) {
            solve(indexes[j], i) = -m(j, solve_index[i]);
        }
    }

    delete[] is_solve;
    delete[] solve_index;

    return solve;
}

KDynamicMatrix<double> solveNonhomogeneousLinearEquations(
        const KDynamicMatrix<double> &augmented_matrix, bool &solution)
{
    int rank;
    KDynamicVector<int> indexes;
    KDynamicMatrix<double> m = augmented_matrix.reducedRowEchelonForm(&rank, &indexes);

    int col = m.column();
    int xcount = col - 1;
    if (indexes[rank - 1] == xcount) { // 无解
        solution = false;
        return KDynamicMatrix<double>();
    }

    solution = true;

    if (rank == xcount) {
        KDynamicMatrix<double> solve(xcount, 1);
        for (int i = 0; i < xcount; ++i) {
            solve(i, 0) = m(i, xcount);
        }
        return solve;
    }

    bool *is_solve = new bool[xcount];
    for (int i = 0; i < xcount; ++i) {
        is_solve[i] = true;
    }

    for (int i = 0; i < indexes.size(); ++i) {
        is_solve[indexes[i]] = false;
    }

    int solve_count = xcount - rank;
    int *solve_index = new int[solve_count];
    int idx = 0;
    for (int i = 0; i < solve_count; ++i) {
        while (!is_solve[idx])
            ++idx;
        solve_index[i] = idx;
        ++idx;
    }

    KDynamicMatrix<double> solve(xcount, solve_count + 1);
    for (int i = 0; i <= solve_count; ++i) {
        for (int j = 0; j < solve_count; ++j) {
            solve(solve_index[j], i) = 0;
        }

        if (i < solve_count)
            solve(solve_index[i], i) = 1;
    }

    for (int i = 0; i < solve_count; ++i) {
        for (int j = 0; j < rank; ++j) {
            solve(indexes[j], i) = -m(j, solve_index[i]);
        }
    }

    for (int i = 0; i < rank; ++i) {
        solve(indexes[i], solve_count) = m(i, xcount);
    }

    delete[] is_solve;
    delete[] solve_index;

    return solve;
}

KPair<double, double> solution1_1(double y, int &count)
{
    if (y < -K_1_E) {
        count = 0;
        return KPair<double, double>(0, 0);
    }

    if (y <= -K_1_E + EPS6) {
        count = 1;
        return KPair<double, double>(-K_1_E, -K_1_E);
    }

    KPair<double, double> pair;
    double x = y + 1;
    double last;
    do {
        last = x;
        x = (y + x) / (kLog(x) + 1);
    } while (!isEqual(last, x, EPS9));
    pair.second = x;

    if (y < 0) {
        count = 2;
        x = -y / 2;
        do {
            last = x;
            x = (y + x) / (kLog(x) + 1);
        } while (!isEqual(last, x, EPS9));
        pair.first = x;
        return pair;
    }

    count = 1;
    pair.first = pair.second;
    return pair;
}

KPair<double, double> solution1_2(double y, int &count)
{
    if (y < 1) {
        count = 0;
        return KPair<double, double>(0, 0);
    }

    if (y <= 1 + EPS6) {
        count = 1;
        return KPair<double, double>(1, 1);
    }

    count = 2;
    KPair<double, double> pair;
    double x = EPS6;
    double last;

    if (y > 14)
        pair.first = 0;
    else {
        do {
            last = x;
            x = (y + kLog(x) - 1) * x / (x - 1);
        } while (!isEqual(last, x, EPS9));
        pair.first = x;
    }

    x = 2;
    do {
        last = x;
        x = (y + kLog(x) - 1) * x / (x - 1);
    } while (!isEqual(last, x, EPS9));
    pair.second = x;

    return pair;
}

KPair<KPointF, KPointF> solution2_1(double r2, double a, double b, double c,
                                    int &count)
{
    double a2 = a * a;
    double b2 = b * b;
    double c2 = c * c;

    KPair<KPointF, KPointF> pair;
    double faba = kFabs(a);
    double fabb = kFabs(b);
    if (faba > fabb && !isZero(a)) {
        KQuadratic qua(a2 + b2, -2 * b * c, c2 - a2 * r2);
        KPair<double, double> y = qua.root(&count);
        if (count == 0) {
            return pair;
        }

        pair.first.setXY((c - b * y.first) / a, y.first);
        pair.second.setXY((c - b * y.second) / a, y.second);
        return pair;
    }

    if (fabb > faba && !isZero(b)) {
        KQuadratic qua(a2 + b2, -2 * a * c, c2 - b2 * r2);
        KPair<double, double> x = qua.root(&count);
        if (count == 0) {
            return pair;
        }

        pair.first.setXY(x.first, (c - a * x.first) / b);
        pair.second.setXY(x.second, (c - a * x.second) / b);
        return pair;
    }

    count = 0;
    return pair;
}
