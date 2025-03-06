#ifndef KBINARYSORTTREE_H
#define KBINARYSORTTREE_H

template<typename T>
struct KBinarySortTreeNode
{
    KBinarySortTreeNode(const T &data) : data_(data) {}
    T data_;
    int bf_; // 平衡因子
    KBinarySortTreeNode<T> *left_ = 0;
    KBinarySortTreeNode<T> *right_ = 0;
};

template<typename T>
class KBinarySortTree
{
    typedef KBinarySortTreeNode<T> Node;
public:
    KBinarySortTree();
    ~KBinarySortTree();

    inline bool insert(const T &key);
    inline bool remove(const T &key);
    inline void clear();

    inline bool search(const T &key) const;

private:
    bool pInsert(Node **node, const T &key);
    bool pRemove(Node **node, const T &key);
    bool pRemove(Node **node);
    void pClear(Node *node);
    void rightRotate(Node **node);
    void leftRotate(Node **node);

    bool pSearch(Node *node, const T &key) const;

    Node *root_ = nullptr;
};

template<typename T>
KBinarySortTree<T>::KBinarySortTree()
{

}

template<typename T>
KBinarySortTree<T>::~KBinarySortTree()
{
    clear();
}

template<typename T>
inline bool KBinarySortTree<T>::insert(const T &key)
{
    return pInsert(&root_, key);
}

template<typename T>
inline bool KBinarySortTree<T>::remove(const T &key)
{
    return pRemove(&root_, key);
}

template<typename T>
inline void KBinarySortTree<T>::clear()
{
    pClear(root_);
}

template<typename T>
inline bool KBinarySortTree<T>::search(const T &key) const
{
    return pSearch(root_, key);
}

template<typename T>
bool KBinarySortTree<T>::pInsert(KBinarySortTree::Node **node, const T &key)
{
    if (!(*node)) {
        *node = new Node(key);
        return true;
    }
    if (key < (*node)->data_)
        return pInsert(&(*node)->left_, key);
    else if (key > (*node)->data_)
        return pInsert(&(*node)->right_, key);
    else
        return false;
}

template<typename T>
bool KBinarySortTree<T>::pRemove(KBinarySortTree::Node **node, const T &key)
{
    if (!(*node))
        return false;
    if (key < (*node)->data_)
        return pRemove(&(*node)->left_, key);
    else if (key > (*node)->data_)
        return pRemove(&(*node)->right_, key);
    else
        return pRemove(node);
}

template<typename T>
bool KBinarySortTree<T>::pRemove(KBinarySortTree::Node **node)
{
    if (!((*node)->right_)) {
        Node *q = *node;
        *node = (*node)->left_;
        delete q;
    } else if (!((*node)->left)) {
        Node *q = *node;
        *node = (*node)->right_;
        delete q;
    } else {
        Node *q = *node;
        Node *s = (*node)->left_;
        while (s->right_) {
            q = s;
            s = s->right_;
        }
        (*node)->data_ = s->data_;
        if (q == (*node))
            q->left_ = s->left_;
        else
            q->right_ = s->left_;
        delete s;
    }
    return true;
}

template<typename T>
void KBinarySortTree<T>::pClear(KBinarySortTree::Node *node)
{
    if (!node)
        return;
    Node *left = node->left_;
    Node *right = node->right_;
    delete node;
    pClear(left);
    pClear(right);
}

template<typename T>
void KBinarySortTree<T>::rightRotate(KBinarySortTree::Node **node)
{
    Node *left = (*node)->left_;
    (*node)->left_ = left->right_;
    left->right_ = (*node);
    (*node) = left;
}

template<typename T>
void KBinarySortTree<T>::leftRotate(KBinarySortTree::Node **node)
{
    Node *right = (*node)->right_;
    (*node)->right_ = right->left_;
    right->left_ = (*node);
    (*node) = right;
}

template<typename T>
bool KBinarySortTree<T>::pSearch(KBinarySortTree::Node *node, const T &key) const
{
    if (!node)
        return false;
    if (key < node)
        return pSearch(node->left_, key);
    else if (key > node)
        return pSearch(node->right_, key);
    else
        return true;
}

#endif // KBINARYSORTTREE_H
