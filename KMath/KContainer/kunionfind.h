#ifndef KUNIONFIND_H
#define KUNIONFIND_H

#include <QVector>

class KUnionFind
{
public:
    KUnionFind(int count);
    // 设置关联，有关联的元素都会放在同一个集合中
    void setUnion(int i, int j);
    // 判断元素是否在同一个集合中
    bool isUnion(int i, int j) const;

private:
    int findParent(int i) const;

    QVector<int> parent_;
};

#endif // KUNIONFIND_H
