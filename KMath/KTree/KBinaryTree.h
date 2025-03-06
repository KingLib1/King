#ifndef KBINARYTREE_H
#define KBINARYTREE_H

#include <QDebug>

#include "KLinkedQueue.h"

template <typename T>
struct KBinaryTreeNode
{
    KBinaryTreeNode() : left_(0), right_(0) {}
    KBinaryTreeNode(const T &data) : data_(data), left_(0), right_(0) {}
    
    T data_;
    KBinaryTreeNode *left_;
    KBinaryTreeNode *right_;
};

template <typename T>
class KBinaryTree
{
    typedef KBinaryTreeNode<T> Node;
    
public:
    KBinaryTree();
    ~KBinaryTree();

    virtual void visit(Node *node) = 0;

    /**
     * @brief 创建二叉树
     * @param datas
     */
    inline void preorderCeateBinaryTree(const QVector<T> &datas, const T &empty);
    /**
     * @brief 前序遍历
     */
    inline void PreorderTraversal();
    /**
     * @brief 中序遍历
     */
    inline void inorderTraversal();
    /**
     * @brief 后序遍历
     */
    inline void postorderTraversal();
    /**
     * @brief 层序遍历
     */
    void levelTraversal();
    
    inline void clear();
    
protected:
    inline Node *root() const;
    void pPreorderCreateBinaryTree(
            Node **node_addr, const QVector<T> &datas, int &index, const T &empty);
    void pPreorderTraversal(Node *node);
    void pInorderTraversal(Node *node);
    void pPostorderTraversal(Node *node);
    void pClear(Node *node);

    Node *root_ = nullptr;
};

#endif // KBINARYTREE_H

template<typename T>
KBinaryTree<T>::KBinaryTree()
{
    
}

template<typename T>
KBinaryTree<T>::~KBinaryTree()
{
    clear();
}

template<typename T>
inline void KBinaryTree<T>::preorderCeateBinaryTree(const QVector<T> &datas,
                                             const T &empty)
{
    int index = 0;
    pPreorderCreateBinaryTree(&root_, datas, index, empty);
}

template<typename T>
inline void KBinaryTree<T>::PreorderTraversal()
{
    pPreorderTraversal(root_);
}

template<typename T>
inline void KBinaryTree<T>::inorderTraversal()
{
    pInorderTraversal(root_);
}

template<typename T>
inline void KBinaryTree<T>::postorderTraversal()
{
    pPostorderTraversal(root_);
}

template<typename T>
void KBinaryTree<T>::levelTraversal()
{
    KLinkedQueue<T> queue;
    if (!root_)
        return;
    queue.enqueue(root_);
    while (!queue.isEmpty()) {
        Node *node = queue.dequeue();
        visit(node);
        if (node->left_)
            queue.enqueue(node->left_);
        if (node->right_)
            queue.enqueue(node->right_);
    }
}

template<typename T>
inline void KBinaryTree<T>::clear()
{
    pClear(root_);
}

template<typename T>
inline typename KBinaryTree<T>::Node *KBinaryTree<T>::root() const
{
    return root_;
}

template<typename T>
void KBinaryTree<T>::pPreorderCreateBinaryTree(
        Node **node_addr, const QVector<T> &datas, int &index, const T &empty)
{
    if (index == datas.size())
        return;
    if (datas.at(index) == empty) {
        ++index;
        return;
    }
    *node_addr = new Node(datas.at(index++));
    pPreorderCreateBinaryTree(&(*node_addr)->left_, datas, index, empty);
    pPreorderCreateBinaryTree(&(*node_addr)->right_, datas, index, empty);
}

template<typename T>
void KBinaryTree<T>::pPreorderTraversal(Node *node)
{
    if (!node)
        return;
    visit(node);
    pPreorderTraversal(node->left_);
    pPreorderTraversal(node->right_);
}

template<typename T>
void KBinaryTree<T>::pInorderTraversal(KBinaryTree::Node *node)
{
    if (!node)
        return;
    pInorderTraversal(node->left_);
    visit(node);
    pInorderTraversal(node->right_);
}

template<typename T>
void KBinaryTree<T>::pPostorderTraversal(KBinaryTree::Node *node)
{
    if (!node)
        return;
    pPostorderTraversal(node->left_);
    pPostorderTraversal(node->right_);
    visit(node);
}

template<typename T>
void KBinaryTree<T>::pClear(KBinaryTree::Node *node)
{
    if (!node)
        return;
    Node *left = node->left_;
    Node *right = node->right_;
    delete node;
    pClear(left);
    pClear(right);
}
