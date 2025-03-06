#ifndef KHUFFMANTREE_H
#define KHUFFMANTREE_H

#include "KBinaryTree.h"
#include "KAlgorithm.h"

template <typename T>
class KHuffmanTree : public KBinaryTree<T>
{
    typedef KBinaryTreeNode<T> Node;
public:
    KHuffmanTree(const QVector<T> &datas);

};

template<typename T>
KHuffmanTree<T>::KHuffmanTree(const QVector<T> &datas)
{
    if (datas.isEmpty())
        return;
    if (datas.size() == 1) {
        this->root_ = new Node(datas.first());
        this->root_->left_ = new Node(datas.first());
        return;
    }

    QVector<T> ds = datas;
    kQuickSort(ds.data(), ds.size(), false);
    QVector<Node*> nodes;
    for (int i = 0; i < ds.size(); ++i)
        nodes << new Node(ds.at(i));
    while (nodes.size() > 1) {
        Node *n1 = nodes.takeLast();
        Node *n2 = nodes.last();
        Node *n = new Node(n1->data_ + n2->data_, n1, n2);
        int j = nodes.size() - 2;
        for (; j >= 0; --j) {
            if (n->data_ < nodes.at(j)->data_)
                break;
        }
        for (int k = nodes.size() - 2; k > j; --k)
            nodes[k + 1] = nodes[k];
        nodes[j + 1] = n;
    }
    this->root_ = nodes.first();
}

#endif // KHUFFMANTREE_H
