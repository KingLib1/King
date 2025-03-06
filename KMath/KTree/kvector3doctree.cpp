#include "kvector3doctree.h"

#include <QDebug>

KVector3DOctreeNodeData::KVector3DOctreeNodeData()
{

}

KVector3DOctreeNodeData::KVector3DOctreeNodeData(const QVector<KVector3D> &points)
    : boundingVolume(points)
{
    for (int i = 0; i < points.size(); ++i)
        indexes << i;
}

KVector3DOctree::KVector3DOctree(const QVector<KVector3D> &points) :
    points_(points)
{
    KVector3DOctreeNodeData data(points);
    root_ = new Node(data);
}

KVector3DOctree::~KVector3DOctree()
{
    delete root_;
}

void KVector3DOctree::divideRecursivelyUntilBelow(int size, double range)
{
    const KBoundingVolume &v = root_->data_.boundingVolume;
    if (root_->data_.indexes.size() > size &&
            (v.dx()>range || v.dy()>range || v.dz()>range))
        pDivide(root_, size, range);
}

KVector3DOctreeNodeData KVector3DOctree::findDeepestNodeDataContain(
        const KVector3D &p) const
{
    if (!root_->data_.boundingVolume.contains(p))
        return KVector3DOctreeNodeData();

    Node *node = pFindDeepest(root_, p);
    return node->data_;
}

void KVector3DOctree::pDivide(Node *node, int size, double range)
{
    QVector<KBoundingVolume> volumes = node->data_.boundingVolume.divideIntoEight();
    KVector3D mid = volumes.at(0).min;
    QVector<int> firstIndexes;
    QVector<int> secondIndexes;
    QVector<int> thirdIndexes;
    QVector<int> fourthIndexes;
    QVector<int> fifthIndexes;
    QVector<int> sixthIndexes;
    QVector<int> seventhIndexes;
    QVector<int> eighthIndexes;

    const QVector<int> &indexes = node->data_.indexes;
    for(int i = 0; i < indexes.size(); ++i) {
        const KVector3D &p = points_.at(indexes.at(i));
        if (p.x() >= mid.x()) {
            if (p.y() >= mid.y()) {
                if (p.z() >= mid.z()) firstIndexes << indexes.at(i);
                else fifthIndexes << indexes.at(i);
            } else {
                if (p.z() >= mid.z()) fourthIndexes << indexes.at(i);
                else eighthIndexes << indexes.at(i);
            }
        } else {
            if (p.y() >= mid.y()) {
                if (p.z() >= mid.z()) secondIndexes << indexes.at(i);
                else sixthIndexes << indexes.at(i);
            } else {
                if (p.z() >= mid.z()) thirdIndexes << indexes.at(i);
                else seventhIndexes << indexes.at(i);
            }
        }
    }

    double dx = volumes.at(0).dx();
    double dy = volumes.at(0).dy();
    double dz = volumes.at(0).dz();
    bool overrange = dx > range || dy > range || dz > range;
    if (!firstIndexes.isEmpty()) {
        node->newFirst();
        node->first->data_.indexes = firstIndexes;
        node->first->data_.boundingVolume = volumes.at(0);
        if (firstIndexes.size() > size && overrange)
            pDivide(node->first, size, range);
    }
    if (!secondIndexes.isEmpty()) {
        node->newSecond();
        node->second->data_.indexes = secondIndexes;
        node->second->data_.boundingVolume = volumes.at(1);
        if (secondIndexes.size() > size && overrange)
            pDivide(node->second, size, range);
    }
    if (!thirdIndexes.isEmpty()) {
        node->newThird();
        node->third->data_.indexes = thirdIndexes;
        node->third->data_.boundingVolume = volumes.at(2);
        if (thirdIndexes.size() > size && overrange)
            pDivide(node->third, size, range);
    }
    if (!fourthIndexes.isEmpty()) {
        node->newfourth();
        node->fourth->data_.indexes = fourthIndexes;
        node->fourth->data_.boundingVolume = volumes.at(3);
        if (fourthIndexes.size() > size && overrange)
            pDivide(node->fourth, size, range);
    }
    if (!fifthIndexes.isEmpty()) {
        node->newFifth();
        node->fifth->data_.indexes = fifthIndexes;
        node->fifth->data_.boundingVolume = volumes.at(4);
        if (fifthIndexes.size() > size && overrange)
            pDivide(node->fifth, size, range);
    }
    if (!sixthIndexes.isEmpty()) {
        node->newSixth();
        node->sixth->data_.indexes = sixthIndexes;
        node->sixth->data_.boundingVolume = volumes.at(5);
        if (sixthIndexes.size() > size && overrange)
            pDivide(node->sixth, size, range);
    }
    if (!seventhIndexes.isEmpty()) {
        node->newSeventh();
        node->seventh->data_.indexes = seventhIndexes;
        node->seventh->data_.boundingVolume = volumes.at(6);
        if (seventhIndexes.size() > size && overrange)
            pDivide(node->seventh, size, range);
    }
    if (!eighthIndexes.isEmpty()) {
        node->newEighth();
        node->eighth->data_.indexes = eighthIndexes;
        node->eighth->data_.boundingVolume = volumes.at(7);
        if (eighthIndexes.size() > size && overrange)
            pDivide(node->eighth, size, range);
    }
}

KVector3DOctree::Node *KVector3DOctree::pFindDeepest(Node *node, const KVector3D &p)
const
{
    const KBoundingVolume &vol = node->data_.boundingVolume;
    KVector3D mid = vol.mid();
    if (p.x() >= mid.x()) {
        if (p.y() >= mid.y()) {
            if (p.z() >= mid.z()) {
                if (node->first)
                    return pFindDeepest(node->first, p);
                return node;
            }
            if (node->fifth)
                return pFindDeepest(node->fifth, p);
            return node;
        }
        if (p.z() >= mid.z()) {
            if (node->fourth)
                return pFindDeepest(node->fourth, p);
            return node;
        }
        if (node->eighth)
            return pFindDeepest(node->eighth, p);
        return node;
    }
    if (p.y() >= mid.y()) {
        if (p.z() >= mid.z()) {
            if (node->second)
                return pFindDeepest(node->second, p);
            return node;
        }
        if (node->sixth)
            return pFindDeepest(node->sixth, p);
        return node;
    }
    if (p.z() >= mid.z()) {
        if (node->third)
            return pFindDeepest(node->third, p);
        return node;
    }
    if (node->seventh)
        return pFindDeepest(node->seventh, p);
    return node;
}
