#ifndef KBITHRTREE_H
#define KBITHRTREE_H

#include <QDebug>

#define KTHREAD true
#define KLINK false

template<typename T>
struct KBiThrTreeNode
{
    KBiThrTreeNode() : left_(0), right_(0) {}
    KBiThrTreeNode(const T &data) : data_(data), left_(0), right_(0) {}

    T data_;
    bool ltag_;
    bool rtag_;
    KBiThrTreeNode *left_;
    KBiThrTreeNode *right_;
};

template<typename T>
class KBiThrTree
{
    typedef KBiThrTreeNode<T> Node;
public:
    KBiThrTree();
    ~KBiThrTree();
    /**
     * @brief 中序线索化
     */
    void inThreading();

    void inorderTraverse();

private:
    void pInThreading(Node *node, Node *pre);

    Node *root_ = 0;
    Node *thread_ = 0;
};

#endif // KBITHRTREE_H

template<typename T>
KBiThrTree<T>::KBiThrTree()
{

}

template<typename T>
KBiThrTree<T>::~KBiThrTree()
{

}

template<typename T>
void KBiThrTree<T>::inThreading()
{
    if (!root_)
        return;
    
    thread_ = new Node;
    thread_->left_ = root_;
    thread_->ltag_ = KLINK;
    Node *pre = thread_;
    pInThreading(root_, pre);
    pre->right_ = thread_;
    thread_->right_ = pre;
    thread_->rtag_ = KTHREAD;
}

template<typename T>
void KBiThrTree<T>::inorderTraverse()
{
    if (!thread_)
        return;
    Node *p = thread_->left_;
    while (p != thread_) {
        while (p->ltag_ == KLINK)
            p = p->left_;
        qDebug() << p->data_;
        while (p->rtag_ == KTHREAD && p->right_ != thread_) {
            p = p->right_;
            qDebug() << p->data_;
        }
        p = p->right_;
    }
}

template<typename T>
void KBiThrTree<T>::pInThreading(Node *node, Node *pre)
{
    if (!node)
        return;
    pInThreading(node->left_);
    if (!node->left_) {
        node->ltag_ = KTHREAD;
        node->left_ = pre;
    } else {
        node->ltag_ = KLINK;
    }
    if (!pre->right_) {
        pre->rtag_ = KTHREAD;
        pre->right_ = node;
    } else {
        pre->rtag_ = KLINK;
    }
    pre = node;
    pInThreading(node->right_);
}
