#include "kunionfind.h"

KUnionFind::KUnionFind(int count)
{
    parent_.fill(-1, count);
}

void KUnionFind::setUnion(int i, int j)
{
    i = findParent(i);
    j = findParent(j);
    if (i != j) {
        parent_[i] = j;
    }
}

bool KUnionFind::isUnion(int i, int j) const
{
    return findParent(i) == findParent(j);
}

int KUnionFind::findParent(int i) const
{
    while (parent_.at(i) >= 0) {
        i = parent_.at(i);
    }
    return i;
}
