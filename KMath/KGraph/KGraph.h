#ifndef KGRAPH_H
#define KGRAPH_H

#include <QVector>
#include <QDebug>
#include <QHash>

#include "KLinkedQueue.h"

template<typename W>
struct KEdgeNode
{
    int id;
    W weight;
};

template<typename T, typename W>
struct KVertexNode
{
    T data;
    KLinkedList<KEdgeNode<W>> edgelist;
};

template<typename T, typename W>
class KING_EXPORT KGraph
{
    typedef KVertexNode<T, W> Node;
public:
    KGraph();
    ~KGraph();

    void addVertex(const T &data);
    void removeOneVertex(const T &data);
    void removeVertex(int id, int);
    void addArc(const T &node1, const T &node2, const W &edge);
    void addArc(int id1, int id2, const W &edge, int);
    void removeArc(const T &node1, const T &node2);
    void removeArc(int id1, int id2, int);

    inline QList<int> id() const;
    int idOf(const T &data) const;
    bool containArc(const T &data1, const T &data2);
    bool containArc(int id1, int id2, int) const;
    inline int vertexCount() const;
    inline const T &vertex(int id) const;
    const W arc(int id1, int id2) const;
    /**
     * @brief 节点的度
     */
    inline int degree(int id) const;

//    QVector<QVector<int>> closedSequence() const;

    void DFS() const;
    QVector<int> DFSStartAt(int id) const;
    QVector<int> closedDFS() const;
    QVector<int> stripDFS() const;

    void BFS() const;

private:
    void DFS(int id, QVector<int> &visited) const;
    bool closedDFS(int id, QVector<int> &close, QVector<int> &visited) const;
    void stripDFS(int id, QVector<int> &strip) const;

    QHash<int, Node*> adj_list1_;
    int new_id_ = 0;
};

template<typename T, typename W>
KGraph<T,W>::KGraph()
{

}

template<typename T, typename W>
KGraph<T, W>::~KGraph()
{
//    for (int i = 0; i < adj_list_.size(); ++i)
//        delete adj_list_[i];

    QList<Node*> vs = adj_list1_.values();
    for (int i = 0; i < vs.size(); ++i)
        delete vs[i];
}

template<typename T, typename W>
void KGraph<T, W>::addVertex(const T &data)
{
//    Node *node = new Node;
//    node->data = data;
//    adj_list_ << node;

    Node *node = new Node;
    node->data = data;
    adj_list1_.insert(new_id_++, node);
}

template<typename T, typename W>
void KGraph<T, W>::removeOneVertex(const T &data)
{
    int id = idOf(data);
    if (id == -1)
        return;
    removeVertex(id, 0);
}

template<typename T, typename W>
void KGraph<T, W>::removeVertex(int id, int)
{
    Node *node = adj_list1_.value(id);
    typename KLinkedList<KEdgeNode<W>>::iterator it = node->edgelist.begin();
    typename KLinkedList<KEdgeNode<W>>::iterator end = node->edgelist.end();
    for (; it != end; ++it) {
        Node *node1 = adj_list1_.value(it->id);
        typename KLinkedList<KEdgeNode<W>>::iterator it1 =
                node1->edgelist.begin();
        typename KLinkedList<KEdgeNode<W>>::iterator end1 =
                node1->edgelist.end();
        for (; it1 != end1; ++it1) {
            if (id == it1->id) {
                adj_list1_.value(it1->id)->edgelist.erase(it1);
                break;
            }
        }
    }
    delete node;
    adj_list1_.remove(id);
}

template<typename T, typename W>
void KGraph<T, W>::addArc(const T &node1, const T &node2, const W &edge)
{
    int id1 = idOf(node1);
    if (id1 == -1) {
        id1 = new_id_;
        addVertex(node1);
    }

    int id2 = idOf(node2);
    if (id2 == -1) {
        id2 = new_id_;
        addVertex(node2);
    }

    addArc(id1, id2, edge, 0);
}

template<typename T, typename W>
void KGraph<T, W>::addArc(int id1, int id2, const W &edge, int)
{
    if (containArc(id1, id2, 0))
        return;

    KEdgeNode<W> edge_node;
    edge_node.id = id2;
    edge_node.weight = edge;
    Node *node1 = adj_list1_.value(id1);
    node1->edgelist.append(edge_node);

    Node *node2 = adj_list1_.value(id2);
    edge_node.id = id1;
    node2->edgelist.append(edge_node);
}

template<typename T, typename W>
void KGraph<T, W>::removeArc(const T &node1, const T &node2)
{
    int id1 = idOf(node1);
    if (id1 == -1)
        return;

    int id2 = idOf(node2);
    if (id2 == -1)
        return;

    removeArc(id1, id2, 0);
}

template<typename T, typename W>
void KGraph<T, W>::removeArc(int id1, int id2, int)
{
    Node *node1 = adj_list1_.value(id1);
    typename KLinkedList<KEdgeNode<W>>::iterator it =
            node1->edgelist.begin();
    typename KLinkedList<KEdgeNode<W>>::iterator end =
            node1->edgelist.end();
    for (; it != end; ++it) {
        if (id2 == it->id) {
            node1->edgelist.erase(it);
            Node *node2 = adj_list1_.value(id2);
            typename KLinkedList<KEdgeNode<W>>::iterator it1 =
                    node2->edgelist.begin();
            typename KLinkedList<KEdgeNode<W>>::iterator end1 =
                    node2->edgelist.end();
            for (; it1 != end1; ++it1) {
                if (id1 == it1->id) {
                    node2->edgelist.erase(it1);
                    return;
                }
            }
        }
    }
}

template<typename T, typename W>
inline QList<int> KGraph<T, W>::id() const
{
    return adj_list1_.keys();
}

template<typename T, typename W>
int KGraph<T, W>::idOf(const T &data) const
{
    QList<int> keys = adj_list1_.keys();
    for (int i = 0; i < keys.size(); ++i) {
        Node *value = adj_list1_.value(keys.at(i));
        if (value->data == data)
            return keys.at(i);
    }
    return -1;
}

template<typename T, typename W>
bool KGraph<T, W>::containArc(const T &data1, const T &data2)
{
    int id1 = idOf(data1);
    if (id1 == -1)
        return false;

    int id2 = idOf(data2);
    if (id2 == -1)
        return false;

    return containArc(id1, id2, 0);
}

template<typename T, typename W>
bool KGraph<T, W>::containArc(int id1, int id2, int) const
{
    Node *node = adj_list1_.value(id1);
    typename KLinkedList<KEdgeNode<W>>::iterator it =
            node->edgelist.begin();
    typename KLinkedList<KEdgeNode<W>>::iterator end =
            node->edgelist.end();
    for (; it != end; ++it) {
        if (id2 == it->id)
            return true;
    }
    return false;
}

template<typename T, typename W>
inline int KGraph<T, W>::vertexCount() const
{
    return adj_list1_.size();
}

template<typename T, typename W>
inline const T &KGraph<T, W>::vertex(int id) const
{
    return adj_list1_.value(id)->data;
}

template<typename T, typename W>
const W KGraph<T, W>::arc(int id1, int id2) const
{
    Node *node = adj_list1_.value(id1);
    typename KLinkedList<KEdgeNode<W>>::iterator it = node->edgelist.begin();
    typename KLinkedList<KEdgeNode<W>>::iterator end = node->edgelist.end();
    for (; it != end; ++it) {
        if (id2 == it->id)
            return it->weight;
    }

    return W();
}

template<typename T, typename W>
inline int KGraph<T, W>::degree(int id) const
{
    Node *node = adj_list1_.value(id);
    return node->edgelist.size();
}

template<typename T, typename W>
void KGraph<T, W>::DFS() const
{
    QList<int> keys = adj_list1_.keys();
    QVector<int> visited;
    for (int i = 0; i < keys.size(); ++i) {
        if (!visited.contains(keys.at(i)))
            DFS(keys.at(i), visited);
    }
}

template<typename T, typename W>
QVector<int> KGraph<T, W>::DFSStartAt(int id) const
{
    QVector<int> visited;
    DFS(id, visited);
    return visited;
}

template<typename T, typename W>
void KGraph<T, W>::DFS(int id, QVector<int> &visited) const
{
//    qDebug() << id;
    visited << id;
    Node *node = adj_list1_.value(id);
    typename KLinkedList<KEdgeNode<W>>::iterator it =
            node->edgelist.begin();
    typename KLinkedList<KEdgeNode<W>>::iterator end =
            node->edgelist.end();
    for (; it != end; ++it) {
        if (!visited.contains(it->id))
            DFS(it->id, visited);
    }
}

template<typename T, typename W>
QVector<int> KGraph<T, W>::closedDFS() const
{
    QVector<int> visited;
    QList<int> keys = adj_list1_.keys();
    for (int i = 0; i < keys.size(); ++i) {
        QVector<int> close;
        if (closedDFS(keys.at(i), close, visited))
            return close;
    }
    QVector<int> close1;
    return close1;
}

template<typename T, typename W>
QVector<int> KGraph<T, W>::stripDFS() const
{
    QVector<int> stip;
    if (!adj_list1_.isEmpty())
        stripDFS(adj_list1_.keys().at(0), stip);
    return stip;
}

template<typename T, typename W>
void KGraph<T, W>::BFS() const
{
    KLinkedQueue<int> queue;
    QVector<int> visited;
    QList<int> keys = adj_list1_.keys();
    for (int i = 0; i < keys.size(); ++i) {
        if (visited.contains(keys.at(i)))
            continue;
        queue.enqueue(keys.at(i));

        while (!queue.isEmpty()) {
            int id = queue.dequeue();
            if (visited.contains(id))
                continue;
            qDebug() << id;
            visited << id;

            Node *node = adj_list1_.value(id);
            typename KLinkedList<KEdgeNode<W>>::iterator it =
                    node->edgelist.begin();
            typename KLinkedList<KEdgeNode<W>>::iterator end =
                    node->edgelist.end();
            for (; it != end; ++it) {
                if (!visited.contains(it->id))
                    queue.enqueue(it->id);
            }
        }
    }
}

template<typename T, typename W>
bool KGraph<T, W>::closedDFS(int id, QVector<int> &close, QVector<int> &visited)
const
{
    visited << id;
    close << id;
    Node *node = adj_list1_.value(id);
    typename KLinkedList<KEdgeNode<W>>::iterator it =
            node->edgelist.begin();
    typename KLinkedList<KEdgeNode<W>>::iterator end =
            node->edgelist.end();
    for (; it != end; ++it) {
        if (close.size() >= 3 && it->id == close.first())
            return true;
        if (!visited.contains(it->id)) {
            bool isclosed = closedDFS(it->id, close, visited);
            if (isclosed)
                return true;
        }
    }
    close.removeLast();
    return false;
}

template<typename T, typename W>
void KGraph<T, W>::stripDFS(int id, QVector<int> &strip) const
{
    strip << id;
    Node *node = adj_list1_.value(id);
    typename KLinkedList<KEdgeNode<W>>::iterator it =
            node->edgelist.begin();
    typename KLinkedList<KEdgeNode<W>>::iterator end =
            node->edgelist.end();
    if (it != end)
        stripDFS(it->id, strip);
}

#endif // KGRAPH_H
