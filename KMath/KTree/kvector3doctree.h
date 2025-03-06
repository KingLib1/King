#ifndef KVECTOR3DOCTREE_H
#define KVECTOR3DOCTREE_H

#include <QVector>

#include "KOctree.h"
#include "kvector3d.h"
#include "kboundingvolume.h"

class KING_EXPORT KVector3DOctreeNodeData
{
public:
    KVector3DOctreeNodeData();
    KVector3DOctreeNodeData(const QVector<KVector3D> &points);
    QVector<int> indexes;
    KBoundingVolume boundingVolume;
};

class KING_EXPORT KVector3DOctree
{
    typedef KOctreeNode<KVector3DOctreeNodeData> Node;
public:
    KVector3DOctree(const QVector<KVector3D> &points);
    ~KVector3DOctree();
    /**
     * @brief 递归地进行空间细分，直到点的数量<=size或者空间范围<=range
     *        只可调用一次。
     */
    void divideRecursivelyUntilBelow(int size, double range);
    /**
     * @brief 找到最深的包含p点的节点数据
     */
    KVector3DOctreeNodeData findDeepestNodeDataContain(const KVector3D &p) const;
    inline const QVector<KVector3D> &points() const;

private:
    void pDivide(Node *node, int size, double range);
    Node *pFindDeepest(Node *node, const KVector3D &p) const;

    QVector<KVector3D> points_;
    Node *root_;
};

inline const QVector<KVector3D> &KVector3DOctree::points() const
{
    return points_;
}

#endif // KVECTOR3DOCTREE_H
