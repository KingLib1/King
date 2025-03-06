#ifndef KALGORITHM_H
#define KALGORITHM_H

#include <QVector>
#include <QDebug>

#include "kmath.h"
#include "kindex2d.h"
#include "kvector3d.h"

/**
 * @brief 根据二分方向取值
 */
KING_EXPORT inline double binary(double low, double high)
{
    return (low + high) / 2;
}

// 搜索
// 二分搜索
template<typename T>
KING_EXPORT int binarySearch(T item, T list[], int size)
{
    int low = 0;
    int high = size - 1;
    int mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (list[mid] > item) {
            high = mid - 1;
        } else if (list[mid] < item) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}

// 二分搜索第一个大于等于给定元素的元素下标
template<typename T>
KING_EXPORT int binarySearchFirstLargerOrEqual(T item, T list[], int size)
{
    int low = 0;
    int high = size - 1;
    int mid;

    while (low <= high) {
        mid = (low + high) / 2;
        if (list[mid] < item)
            low = mid + 1;
        else if (list[mid] > item)
            high = mid - 1;
        else
            return mid;
    }

    if (low == size)
        return -1;
    return low;
}

// 排序
// 选择排序
template<typename T>
KING_EXPORT void selectionSort(T list[], int size, bool ascend = true)
{
    if (ascend) {
        int smallest_index;
        T temp;
        int times = size - 1;
        for (int i = 0; i < times; ++i) {
            smallest_index = i;
            for (int j = i + 1; j < size; ++j)
                if (list[j] < list[smallest_index])
                    smallest_index = j;
            temp = list[i];
            list[i] = list[smallest_index];
            list[smallest_index] = temp;
        }
    } else {
        int biggest_index;
        T temp;
        int times = size - 1;
        for (int i = 0; i < times; ++i) {
            biggest_index = i;
            for (int j = i + 1; j < size; ++j)
                if (list[j] > list[biggest_index])
                    biggest_index = j;
            temp = list[i];
            list[i] = list[biggest_index];
            list[biggest_index] = temp;
        }
    }
}

template<typename T>
KING_EXPORT void quickSortAscend(T list[], int low, int high)
{
    if (low >= high)
        return;
    int low1 = low;
    int high1 = high;
    int middle = (low + high) / 2;
    T base = list[middle];
    list[middle] = list[high];
    list[high] = base;
    do {
        while (low < high) {
            if (list[low] <= base) {
                ++low;
            } else {
                list[high] = list[low];
                --high;
                break;
            }
        }
        while (low < high) {
            if (list[high] >= base) {
                --high;
            } else {
                list[low] = list[high];
                ++low;
                break;
            }
        }
    } while (low != high);
    list[low] = base;
    quickSortAscend(list, low1, low - 1);
    quickSortAscend(list, low + 1, high1);
}

template<typename T>
KING_EXPORT void quickSortDescend(T list[], int low, int high)
{
    if (low >= high)
        return;
    int low1 = low;
    int high1 = high;
    int middle = (low + high) / 2;
    T base = list[middle];
    list[middle] = list[high];
    list[high] = base;
    do {
        while (low < high) {
            if (list[low] >= base) {
                ++low;
            } else {
                list[high] = list[low];
                --high;
                break;
            }
        }
        while (low < high) {
            if (list[high] <= base) {
                --high;
            } else {
                list[low] = list[high];
                ++low;
                break;
            }
        }
    } while (low != high);
    list[low] = base;
    quickSortDescend(list, low1, low - 1);
    quickSortDescend(list, low + 1, high1);
}

// 快速排序
template<typename T>
KING_EXPORT void kQuickSort(T list[], int size, bool ascend = true)
{
    int low = 0;
    int high = size - 1;
    if (ascend) {
        quickSortAscend(list, low, high);
    } else {
        quickSortDescend(list, low, high);
    }
}

template<typename T>
void heapAdjustAscend(T *list, int i, int j)
{
    T temp = list[i];
    for (int i1 = 2 * i; i1 <= j; i1 *= 2) {
        if (i1 < j && list[i1] < list[i1 + 1])
            ++i1;
        if (temp >= list[i1])
            break;
        list[i] = list[i1];
        i = i1;
    }
    list[i] = temp;
}

template<typename T>
KING_EXPORT void heapAdjustDescend(T *list, int i, int j)
{
    T temp = list[i];
    for (int i1 = 2 * i; i1 <= j; i1 *= 2) {
        if (i1 < j && list[i1] > list[i1 + 1])
            ++i1;
        if (temp <= list[i1])
            break;
        list[i] = list[i1];
        i = i1;
    }
    list[i] = temp;
}

// 堆排序
template<typename T>
KING_EXPORT void kHeapSort(QVector<T> &list, bool ascend = true)
{
    const int size = list.size();
    T array[size + 1];
    for (int i = 0; i < list.size(); ++i)
        array[i + 1] = list.at(i);

    if (ascend) {
        for (int i = size / 2; i > 0; --i) {
            heapAdjustAscend(array, i, size);
        }

        int last = size;
        while (last > 1) {
            kSwap(array[1], array[last]);
            --last;
            heapAdjustAscend(array, 1, last);
        }
    } else {
        for (int i = size / 2; i > 0; --i) {
            heapAdjustDescend(array, i, size);
        }

        int last = size;
        while (last > 1) {
            kSwap(array[1], array[last]);
            --last;
            heapAdjustDescend(array, 1, last);
        }
    }

    for (int i = 0; i < list.size(); ++i)
        list[i] = array[i + 1];
}

// 冒泡排序
template<typename T>
KING_EXPORT void kBubbleSort(QVector<T> &v, bool ascend = true)
{
    bool change = true;
    int last = v.size() - 1;
    int j_1;
    if (ascend) {
        for (int i = 1; i < v.size() && change; ++i) {
            change = false;
            for (int j = last; j >= i; j = j_1) {
                j_1 = j - 1;
                if (v.at(j) < v.at(j_1)) {
                    T temp = v.at(j);
                    v[j] = v.at(j_1);
                    v[j_1] = temp;
                    change = true;
                }
            }
        }
    } else {
        for (int i = 1; i < v.size() && change; ++i) {
            change = false;
            for (int j = last; j >= i; j = j_1) {
                j_1 = j - 1;
                if (v.at(j) > v.at(j_1)) {
                    T temp = v.at(j);
                    v[j] = v.at(j_1);
                    v[j_1] = temp;
                    change = true;
                }
            }
        }
    }
}

// 插入排序
template<typename T>
KING_EXPORT void kInsertSort(QVector<T> &v, bool ascend = true)
{
    if (ascend) {
        for (int i = 1; i < v.size(); ++i) {
            if (v.at(i) < v.at(i - 1)) {
                T temp = v.at(i);
                int j;
                for (j = i - 1; j >= 0 && v.at(j) > temp; --j)
                    v[j + 1] = v.at(j);
                v[j + 1] = temp;
            }
        }
    } else {
        for (int i = 1; i < v.size(); ++i) {
            if (v.at(i) > v.at(i - 1)) {
                T temp = v.at(i);
                int j;
                for (j = i - 1; j >= 0 && v.at(j) < temp; --j)
                    v[j + 1] = v.at(j);
                v[j + 1] = temp;
            }
        }
    }
}

// 希尔排序
template<typename T>
KING_EXPORT void kShellSort(QVector<T> &v, bool ascend = true)
{
    int increment = v.size();
    if (ascend) {
        while (increment > 1) {
            increment = int(kSqrt(double(increment)));
            for (int i = increment; i < v.size(); ++i) {
                if (v.at(i) < v.at(i - increment)) {
                    T temp = v.at(i);
                    int j;
                    for (j = i - increment; j >= 0 && v.at(j) > temp; j-= increment)
                        v[j + increment] = v.at(j);
                    v[j + increment] = temp;
                }
            }
        }
    } else {
        while (increment > 1) {
            increment = int(kSqrt(double(increment)));
            for (int i = increment; i < v.size(); ++i) {
                if (v.at(i) > v.at(i - increment)) {
                    T temp = v.at(i);
                    int j;
                    for (j = i - increment; j >= 0 && v.at(j) < temp; j -= increment)
                        v[j + increment] = v.at(j);
                    v[j + increment] = temp;
                }
            }
        }
    }
}

template<typename T>
KING_EXPORT void mergeAscend(QVector<T> &v, int i1, int j1, int i2, int j2)
{
    T temp[j2 - i1 + 1];
    int index = 0, start = i1;
    while (i1 <= j1 && i2 <= j2) {
        if (v.at(i1) <= v.at(i2))
            temp[index++] = v.at(i1++);
        else
            temp[index++] = v.at(i2++);
    }

    while (i1 <= j1)
        temp[index++] = v.at(i1++);
    while (i2 <= j2)
        temp[index++] = v.at(i2++);

    index = 0;
    while (start <= j2)
        v[start++] = temp[index++];
}

template<typename T>
KING_EXPORT void mergeDescend(QVector<T> &v, int i1, int j1, int i2, int j2)
{
    T temp[j2 - i1 + 1];
    int index = 0, start = i1;
    while (i1 <= j1 && i2 <= j2) {
        if (v.at(i1) >= v.at(i2))
            temp[index++] = v.at(i1++);
        else
            temp[index++] = v.at(i2++);
    }

    while (i1 <= j1)
        temp[index++] = v.at(i1++);
    while (i2 <= j2)
        temp[index++] = v.at(i2++);

    index = 0;
    while (start <= j2)
        v[start++] = temp[index++];
}

template<typename T>
KING_EXPORT void mergeSortAscend(QVector<T> &v, int i, int j)
{
    if (i == j)
        return;
    int mid = (i + j) / 2;
    mergeSortAscend(v, i, mid);
    mergeSortAscend(v, mid + 1, j);
    mergeAscend(v, i, mid, mid + 1, j);
}

template<typename T>
KING_EXPORT void mergeSortDescend(QVector<T> &v, int i, int j)
{
    if (i == j)
        return;
    int mid = (i + j) / 2;
    mergeSortDescend(v, i, mid);
    mergeSortDescend(v, mid + 1, j);
    mergeDescend(v, i, mid, mid + 1, j);
}

// 递归归并排序
template<typename T>
KING_EXPORT void kMergeSort(QVector<T> &v, bool ascend = true)
{
    if (v.size() < 2)
        return;
    if (ascend)
        mergeSortAscend(v, 0, v.size() - 1);
    else
        mergeSortDescend(v, 0, v.size() - 1);
}

// 非递归归并排序
template<typename T>
KING_EXPORT void kMergeSort2(QVector<T> &v, bool ascend = true)
{
    if (v.size() < 2)
        return;
    int space = 1;

    if (ascend) {
        do {
            int i1 = 0;
            int i2 = i1 + space;
            do {
                mergeAscend(v, i1, i2 - 1, i2, kMin(v.size() - 1, i2 + space - 1));
                i1 += 2 * space;
                i2 = i1 + space;
            } while (i2 < v.size());
            space *= 2;
        } while (space < v.size());
    } else {
        do {
            int i1 = 0;
            int i2 = i1 + space;
            do {
                mergeDescend(v, i1, i2 - 1, i2, kMin(v.size() - 1, i2 + space - 1));
                i1 += 2 * space;
                i2 = i1 + space;
            } while (i2 < v.size());
            space *= 2;
        } while (space < v.size());
    }
}

//两个数组合并排序，v1和v2必须是有序的且方向一致
template<typename T>
KING_EXPORT QVector<T> kMergeSort(const QVector<T> &v1, const QVector<T> &v2, bool ascend = true)
{
    QVector<T> v;
    if (v1.size() == 0) {
        int i2 = 0;
        while (i2 < v2.size())
            v << v2.at(i2++);
        return v;
    }
    if (v2.size() == 0) {
        int i1 = 0;
        while (i1 < v1.size())
            v << v1.at(i1++);
        return v;
    }

    int i1 = 0;
    int i2 = 0;
    if (ascend) {
        while (1) {
            if (v1.at(i1) < v2.at(i2)) {
                v << v1.at(i1);
                ++i1;
                if (i1 == v1.size()) {
                    while (i2 < v2.size())
                        v << v2.at(i2++);
                    return v;
                }
            } else {
                v << v2.at(i2);
                ++i2;
                if (i2 == v2.size()) {
                    while (i1 < v1.size())
                        v << v1.at(i1++);
                    return v;
                }
            }
        }
    } else {
        while (1) {
            if (v1.at(i1) > v2.at(i2)) {
                v << v1.at(i1);
                ++i1;
                if (i1 == v1.size()) {
                    while (i2 < v2.size())
                        v << v2.at(i2++);
                    return v;
                }
            } else {
                v << v2.at(i2);
                ++i2;
                if (i2 == v2.size()) {
                    while (i1 < v1.size())
                        v << v1.at(i1++);
                    return v;
                }
            }
        }
    }
}

template<typename T>
KING_EXPORT T min(const QVector<T> &v)
{
    if (v.size() == 0)
        return 0;
    T m = v.at(0);
    for (int i = 1; i < v.size(); ++i)
        if (v.at(i) < m)
            m = v.at(i);
    return m;
}

template<typename T>
KING_EXPORT int minIndex(const QVector<T> &v)
{
    if (v.size() == 0)
        return -1;
    T m = v.at(0);
    int ind = 0;
    for (int i = 1; i < v.size(); ++i) {
        if (v.at(i) < m) {
            m = v.at(i);
            ind = i;
        }
    }
    return ind;
}

KING_EXPORT inline void findLCSElement(QVector<KIndex2D> &ind,
                                        const QVector<QVector<short>> &dp,
                                        int row, int column)
{
    if (dp[row][column] == 0)
        return;

    int r1 = row - 1;
    int c1 = column - 1;

    if (dp[row][column] == dp[r1][c1])
        return findLCSElement(ind, dp, r1, c1);

    if (dp[row][column] == dp[r1][column])
        return findLCSElement(ind, dp, r1, column);

    if (dp[row][column] == dp[row][c1])
        return findLCSElement(ind, dp, row, c1);

    ind << KIndex2D(r1, c1);
    return findLCSElement(ind, dp, r1, c1);
}

template<typename T>
/**
 * @brief 最长公共子序列
 * @param v1
 * @param v2
 * @param indexes 返回子序列的元素在v1和v2中的下标
 * @return
 */
KING_EXPORT QVector<T> LCS(const QVector<T> &v1, const QVector<T> &v2,
               QVector<KIndex2D> &indexes)
{
    QVector<T> v;
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
            if (v1.at(i1) == v2.at(j1))
                dp[i][j] = dp[i1][j1] + 1;
            else
                dp[i][j] = kMax(dp[i1][j], dp[i][j1]);
        }
    }

//    i1 = v1.size();
//    j1 = v2.size();
    findLCSElement(indexes, dp, v1.size(), v2.size());
    for (int i = indexes.size() - 1; i > -1; --i) {
        v << v1.at(indexes.at(i).i());
    }
    return v;
}

// 连续子序列最大和
inline int MaxSumCSubsequences(const QVector<int> &nums, int &i, int &j)
{
    if (nums.isEmpty())
        return 0;
    if (nums.size() == 1)
        return nums.at(0);

    int current_max = nums.at(0);
    int max = nums.at(0);
    int current_i = 0;
    i = 0;
    j = 0;
    for (int idx = 1; idx < nums.size(); ++idx) {
        int sum = current_max + nums.at(idx);
        if (nums.at(idx) > sum) {
            current_i = idx;
            current_max = nums.at(idx);
        } else {
            current_max = sum;
        }
        if (current_max > max) {
            max = current_max;
            j = idx;
            i = current_i;
        }
    }
    return max;
}

// 最长递增子序列
inline QVector<int> LIS(const QVector<int> &seq)
{
    if (seq.size() <= 1)
        return seq;

    QVector<int> dp(seq.size(), 1);
    QVector<int> pre_i(seq.size(), 0);
    pre_i[0] = -1;

    int max = 1;
    int max_i = 0;
    for (int i = 1; i < seq.size(); ++i) {
        dp[i] = 1;
        for (int j = 0; j < i; ++j) {
            if (seq.at(i) > seq.at(j)) {
                int num = dp[j] + 1;
                if (num > dp[i]) {
                    dp[i] = num;
                    pre_i[i] = j;
                }
            }
        }

        if (dp[i] > dp[max_i]) {
            max_i = i;
        }
    }

    QVector<int> son(dp[max_i]);
    int i = max_i;
    for (int j = dp[max_i] - 1; j >= 0; --j) {
        son[j] = seq.at(i);
        i = pre_i[i];
    }
    return son;
}

// rgb三种颜色涂到n个格子上，相邻颜色不同，首尾颜色不同，返回涂色方案个数
inline int RGB(int n)
{
    if (n == 1)
        return 3;
    if (n == 2 || n == 3)
        return 6;

    int s1 = 3;
    int s2 = 6;
    for (int i = 4; i <= n; ++i) {
        int s = s2 + s1 * 2;
        s1 = s2;
        s2 = s;
    }
    return s2;
}

// 朴素模式串匹配
KING_EXPORT inline int indexOf(const QString &s, const QString &c, int from = 0)
{
    if (s.isEmpty() || c.isEmpty() || from >= s.size())
        return -1;
    int i = from;
    int j = 0;
    while (i < s.size() && j < c.size()) {
        if (s[i] == c[j]) {
            ++i;
            ++j;
        } else {
            i = i - j + 1;
            j = 0;
        }
    }
    return j < c.size() ? -1 : i - j;
}

inline QVector<int> createNextArray(const QString &s)
{
    QVector<int> next;
    if (s.isEmpty())
        return next;

    int i = 0;
    int j = 1;
    next << 0 << 0;
    int last = s.size() - 1;
    while (j < last) {
        if (s[i] == s[j]) {
            ++i;
            ++j;
            if (s[j] == s[i]) {
                next << next[i];
            } else {
                next << i;
            }
        } else {
            if (i == 0) {
                next << i;
                ++j;
            } else {
                i = next[i];
            }
        }
    }
    return next;
    // ababaaaba
}

// KMP模式匹配
KING_EXPORT inline int indexOf_KMP(const QString &s, const QString &c, int from = 0)
{
    if (s.isEmpty() || c.isEmpty() || from >= s.size())
        return -1;
    QVector<int> next = createNextArray(c);
    int i = from;
    int j = 0;
    while (i < s.size() && j < c.size()) {
        if (s[i] == c[j]) {
            ++i;
            ++j;
        } else {
            if (j == 0) {
                ++i;
            } else {
                j = next[j];
            }
        }
    }
    if (j < c.size())
        return -1;
    return i - j;
}

KING_EXPORT inline int previousIndex(int i, int size)
{
    return i == 0 ? size - 1 : i - 1;
}

KING_EXPORT inline int nextIndex(int i, int size)
{
    return i == size - 1 ? 0 : i + 1;
}

// 下标 from 到 to 之间是否包含 i
KING_EXPORT inline bool containsIndex(int i, int from, int to)
{
    if (from <= to)
        return i >= from && i <= to;
    return i >= from || i <= to;
}

template<typename T>
KING_EXPORT inline int minSizeIndex(const QVector<QVector<T>> &v)
{
    if (v.isEmpty())
        return -1;

    int index = 0;
    for (int i = 1; i < v.size(); ++i)
        if (v.at(i).size() < v.at(index).size())
            index = i;

    return index;
}

template<typename T>
KING_EXPORT inline int maxSizeIndex(const QVector<QVector<T>> &v)
{
    if (v.isEmpty())
        return -1;

    int index = 0;
    for (int i = 1; i < v.size(); ++i)
        if (v.at(i).size() > v.at(index).size())
            index = i;

    return index;
}

KING_EXPORT inline int nearestIndex(const QVector<KVector3D> &points,
                                    const KVector3D &p)
{
    if (points.size() == 0)
        return -1;

    int nind = 0;
    double ndis = points.at(0).distanceSquaredToPoint(p);
    for (int i = 1; i < points.size(); ++i) {
        double dis = points.at(i).distanceSquaredToPoint(p);
        if (dis < ndis) {
            ndis = dis;
            nind = i;
        }
    }
    return nind;
}

// 数组反转
template<typename T>
KING_EXPORT inline void reverse(QVector<T> &v)
{
    int i = 0;
    int j = v.size() - 1;
    while (i < j) {
        kSwap(v[i], v[j]);
        ++i;
        --j;
    }
}

// 数组每个元素变为相反数
template<typename T>
KING_EXPORT inline void opposite(QVector<T> &v)
{
    for (int i = 0; i < v.size(); ++i)
        v[i] = -v.at(i);
}

// 数组循环左移shift位
template<typename T>
KING_EXPORT inline void loopLeftShift(QVector<T> &v, int shift)
{
    shift %= v.size();
    int i = 0;
    int j = shift - 1;

    while (i < j) {
        kSwap(v[i], v[j]);
        ++i;
        --j;
    }

    i = shift;
    j = v.size() - 1;
    while (i < j) {
        kSwap(v[i], v[j]);
        ++i;
        --j;
    }

    i = 0;
    j = v.size() - 1;
    while (i < j) {
        kSwap(v[i], v[j]);
        ++i;
        --j;
    }
}

// 数组循环右移shift位
template<typename T>
KING_EXPORT inline void loopRightShift(QVector<T> &v, int shift)
{
    shift %= v.size();

    int i = 0;
    int j = v.size() - shift - 1;
    while (i < j) {
        kSwap(v[i], v[j]);
        ++i;
        --j;
    }

    i = v.size() - shift;
    j = v.size() - 1;
    while (i < j) {
        kSwap(v[i], v[j]);
        ++i;
        --j;
    }

    i = 0;
    j = v.size() - 1;
    while (i < j) {
        kSwap(v[i], v[j]);
        ++i;
        --j;
    }
}

#endif // KALGORITHM_H
