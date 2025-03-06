#ifndef KMATRIXGRAPH_H
#define KMATRIXGRAPH_H

#include <QDebug>
#include <QVector>

#include "KGenericMatrix.h"
#include "KLinkedQueue.h"
#include "kindex2d.h"

template<typename W>
struct Edge
{
    Edge() {}
    Edge(const Edge &edge) : begin(edge.begin), end(edge.end),
        weight(edge.weight) {}
    int begin;
    int end;
    W weight;

    inline Edge &operator=(const Edge &edge)
    {
        begin = edge.begin;
        end = edge.end;
        weight = edge.weight;
        return *this;
    }
};

// N节点, W权值（边）, M最大节点数
template<typename N, typename W, int M>
class KING_EXPORT KMatrixGraph
{
public:
    KMatrixGraph();
    ~KMatrixGraph();

    inline void addVertex(const N &vertex);
    void addArc(const N &vertex1, const N &vertex2, const W &edge);
    inline void addArc(int index1, int index2, const W &edge, int);
    inline void fillMatrix(const W &weight);
    /**
     * @brief 指定邻接矩阵的无效值
     */
    inline void setNullWeight(const W &w);
    /**
     * @brief 把邻接矩阵的元素设为无效值
     */
    inline void invalidateMatrix();
    inline void setMatrix(const KGenericMatrix<M, M, W> &matrix);

    inline int indexOf(const N &vertex, int from = 0) const;
    bool containArc(const N &vertex1, const N &vertex2) const;
    inline bool containArc(int index1, int index2, int) const;
    inline int vertexesCount() const;
    inline const N &vertex(int index) const {return vertexes_.at(index);}
    inline const W &arc(int index1, int index2, int) const
    { return matrix_(index1, index2); }

    /**
     * @brief 深度优先遍历
     */
    void DFS() const;
    /**
     * @brief 广度优先遍历
     */
    void BFS() const;

    /**
     * @brief 最小生成树Prim算法, 返回节点连接的下标顺序
     */
    QVector<KIndex2D> prim() const;
    /**
     * @brief 最小生成树Kruskal算法, 返回节点连接的下标顺序
     */
    QVector<KIndex2D> kruskal() const;
    /**
     * @brief Dijkstra最短路径,返回经过路径的下标和路径长度
     */
    QVector<int> shortestPathDijkstra(int start, int end, W &length) const;
    /**
     * @brief Floyd最短路径算法
     * @param dis 返回最短距离矩阵
     * @param path 返回路径矩阵
     */
    void shortestPathFloyd(KGenericMatrix<M, M, W> &dis,
                           KGenericMatrix<M, M, W> &path) const;
    /**
     * @brief 调用了同名函数后返回的路径矩阵传入此函数，返回最短路径
     */
    QVector<int> shortestPathFloyd(const KGenericMatrix<M, M, W> &path,
                                   int start, int end) const;

private:
    void DFS(int index, QVector<bool> &visited) const;

    // 用于kruskal算法
    QVector<Edge<W>> toEdges() const;
    void edgesSort(QVector<Edge<W>> &edges) const;
    void swapEdges(QVector<Edge<W>> &edges, int i, int j) const;
    int findEnd(const QVector<int> &parent, int i) const;

    QVector<N> vertexes_;
    KGenericMatrix<M, M, W> matrix_;
    W null_;
};

template<typename N, typename W, int M>
KMatrixGraph<N, W, M>::KMatrixGraph()
{

}

template<typename N, typename W, int M>
KMatrixGraph<N, W, M>::~KMatrixGraph()
{

}

template<typename N, typename W, int M>
inline void KMatrixGraph<N, W, M>::addVertex(const N &vertex)
{
    vertexes_ << vertex;
}

template<typename N, typename W, int M>
void KMatrixGraph<N, W, M>::addArc(const N &vertex1, const N &vertex2, const W &edge)
{
    int index1 = indexOf(vertex1);
    if (index1 == -1) {
        addVertex(vertex1);
        index1 = vertexes_.size() - 1;
    }

    int index2 = indexOf(vertex2);
    if (index2 == -1) {
        addVertex(vertex2);
        index2 = vertexes_.size() - 1;
    }

    addArc(index1, index2, edge, 0);
}

template<typename N, typename W, int M>
inline void KMatrixGraph<N, W, M>::addArc(int index1, int index2, const W &edge, int)
{
    if (containArc(index1, index2, 0))
        return;
    matrix_(index1, index2) = edge;
    matrix_(index2, index1) = edge;
}

template<typename N, typename W, int M>
inline void KMatrixGraph<N, W, M>::fillMatrix(const W &weight)
{
    matrix_.fill(weight);
}

template<typename N, typename W, int M>
inline void KMatrixGraph<N, W, M>::setNullWeight(const W &w)
{
    null_ = w;
}

template<typename N, typename W, int M>
inline void KMatrixGraph<N, W, M>::invalidateMatrix()
{
    matrix_.fill(null_);
}

template<typename N, typename W, int M>
inline void KMatrixGraph<N, W, M>::setMatrix(
        const KGenericMatrix<M, M, W> &matrix)
{
    vertexes_.resize(M);
    matrix_ = matrix;
}

template<typename N, typename W, int M>
inline int KMatrixGraph<N, W, M>::indexOf(const N &vertex, int from) const
{
    return vertexes_.indexOf(vertex, from);
}

template<typename N, typename W, int M>
bool KMatrixGraph<N, W, M>::containArc(const N &vertex1, const N &vertex2) const
{
    int index1 = indexOf(vertex1);
    if (index1 == -1)
        return false;

    int index2 = indexOf(vertex2);
    if (index2 == -1)
        return false;

    return containArc(index1, index2, 0);
}

template<typename N, typename W, int M>
inline bool KMatrixGraph<N, W, M>::containArc(int index1, int index2, int) const
{
    return matrix_(index1, index2) != null_;
}

template<typename N, typename W, int M>
inline int KMatrixGraph<N, W, M>::vertexesCount() const
{
    return vertexes_.size();
}

template<typename N, typename W, int M>
void KMatrixGraph<N, W, M>::DFS() const
{
    QVector<bool> visited(vertexes_.size(), false);
    for (int i = 0; i < vertexes_.size(); ++i)
        if (!visited.at(i))
            DFS(i, visited);
}

template<typename N, typename W, int M>
void KMatrixGraph<N, W, M>::BFS() const
{
    QVector<bool> visited(vertexes_.size(), false);
    KLinkedQueue<int> queue;
    for (int i = 0; i < vertexes_.size(); ++i) {
        if (visited.at(i))
            continue;
        queue.enqueue(i);

        while (!queue.isEmpty()) {
            int index = queue.dequeue();
            if (visited.at(index))
                continue;
            qDebug() << index;
            visited.replace(index, true);
            for (int j = 0; j < vertexes_.size(); ++j)
                if (!visited.at(j) && containArc(index, j, 0))
                    queue.enqueue(j);
        }
    }
}

template<typename N, typename W, int M>
QVector<KIndex2D> KMatrixGraph<N, W, M>::prim() const
{
    QVector<KIndex2D> tree;
    if (vertexes_.isEmpty())
        return tree;
    QVector<bool> visited(vertexes_.size(), false);
    visited.replace(0, true);
    QVector<W> lowcost(vertexes_.size());
    QVector<int> adj(vertexes_.size(), 0);
    for (int i = 1; i < vertexes_.size(); ++i) {
        lowcost.replace(i, matrix_(0, i));
    }
    int min_index = -1, j;
    for (int i = 1; i < vertexes_.size(); ++i) {
        j = 1;
        for (; j < vertexes_.size(); ++j) {
            if (visited.at(j)) {
                continue;
            } else {
                min_index = j;
                break;
            }
        }
        for (++j; j < vertexes_.size(); ++j)
            if (!visited.at(j) && lowcost.at(j) < lowcost.at(min_index))
                min_index = j;
        tree << KIndex2D(adj.at(min_index), min_index);
        visited.replace(min_index, true);
        for (int k = 1; k < vertexes_.size(); ++k) {
            if (!visited.at(k) && matrix_(min_index, k) < lowcost.at(k)) {
                lowcost.replace(k, matrix_(min_index, k));
                adj.replace(k, min_index);
            }
        }
    }
    return tree;
}

template<typename N, typename W, int M>
QVector<KIndex2D> KMatrixGraph<N, W, M>::kruskal() const
{
    QVector<KIndex2D> indexes;
    QVector<Edge<W>> edges = toEdges();
    edgesSort(edges);
    QVector<int> parent(vertexes_.size(), 0);
    for (int i = 0; i < edges.size(); ++i) {
        int n = findEnd(parent, edges.at(i).begin);
        int m = findEnd(parent, edges.at(i).end);
        if (n == m)
            continue;
        parent.replace(n, m);
        indexes << KIndex2D(edges.at(i).begin, edges.at(i).end);
    }
    return indexes;
}

template<typename N, typename W, int M>
QVector<int> KMatrixGraph<N, W, M>::shortestPathDijkstra(
        int start, int end, W &length) const
{
    W weight[vertexes_.size()];
    bool visited[vertexes_.size()];
    int adj[vertexes_.size()];
    for (int i = 0; i < vertexes_.size(); ++i) {
        weight[i] = matrix_(start, i);
        visited[i] = false;
        adj[i] = start;
    }
    visited[start] = true;
    W min;
    int min_index = start;
    for (int i = 1; i < vertexes_.size(); ++i) {
        min = null_;
        for (int j = 0; j < vertexes_.size(); ++j) {
            if (!visited[j] && weight[j] < min) {
                min = weight[j];
                min_index = j;
            }
        }
        visited[min_index] = true;
        for (int j = 0; j < vertexes_.size(); ++j) {
            if (!visited[j]) {
                W sum = matrix_(min_index, j) + min;
                if (sum < weight[j]) {
                    weight[j] = sum;
                    adj[j] = min_index;
                }
            }
        }
    }

    length = weight[end];
    QVector<int> path;
    path << end;
    while (end != start) {
        end = adj[end];
        path << end;
    }
    return path;
}

template<typename N, typename W, int M>
void KMatrixGraph<N, W, M>::shortestPathFloyd(
        KGenericMatrix<M, M, W> &dis, KGenericMatrix<M, M, W> &path) const
{
    for (int i = 0; i < vertexes_.size(); ++i) {
        for (int j = 0; j < vertexes_.size(); ++j) {
            dis(i, j) = matrix_(i, j);
            path(i, j) = j;
        }
    }

    for (int i = 0; i < vertexes_.size(); ++i) {
        for (int j = 0; j < vertexes_.size(); ++j) {
            for (int k = 0; k < vertexes_.size(); ++k) {
                if (dis(j, i) + dis(i, k) < dis(j, k)) {
                    dis(j, k) = dis(j, i) + dis(i, k);
                    path(j, k) = path(j, i);
                }
            }
        }
    }
}

template<typename N, typename W, int M>
void KMatrixGraph<N, W, M>::DFS(int index, QVector<bool> &visited) const
{
    qDebug() << index;
    visited.replace(index, true);
    for (int i = 0; i < vertexes_.size(); ++i)
        if (!visited.at(i) && matrix_(index, i) != null_)
            DFS(i, visited);
}

template<typename N, typename W, int M>
QVector<Edge<W>> KMatrixGraph<N, W, M>::toEdges() const
{
    QVector<Edge<W>> edges;
    Edge<W> edge;
    int last = vertexes_.size() - 1;
    for (int i = 0; i < last; ++i) {
        for (int j = i + 1; j < vertexes_.size(); ++j) {
            if (matrix_(i, j) < null_) {
                edge.begin = i;
                edge.end = j;
                edge.weight = matrix_(i, j);
                edges << edge;
            }
        }
    }
    return edges;
}

template<typename N, typename W, int M>
void KMatrixGraph<N, W, M>::edgesSort(QVector<Edge<W>> &edges) const
{
    int last = edges.size() - 1;
    for (int i = 0; i < last; ++i) {
        for (int j = i + 1; j < edges.size(); ++j) {
            if (edges.at(i).weight > edges.at(j).weight)
                swapEdges(edges, i, j);
        }
    }
}

template<typename N, typename W, int M>
void KMatrixGraph<N, W, M>::swapEdges(QVector<Edge<W>> &edges, int i, int j)
const
{
    Edge<W> edge(edges.at(i));
    edges.replace(i, edges.at(j));
    edges.replace(j, edge);
}

template<typename N, typename W, int M>
int KMatrixGraph<N, W, M>::findEnd(const QVector<int> &parent, int i) const
{
    while (parent.at(i) > 0)
        i = parent.at(i);
    return i;
}

template<typename N, typename W, int M>
QVector<int> KMatrixGraph<N, W, M>::shortestPathFloyd(
        const KGenericMatrix<M, M, W> &path, int start, int end) const
{
    QVector<int> path1;
    path1 << start;
    start = path(start, end);
    while (start != end) {
        path1 << start;
        start = path(start, end);
    }
    path1 << end;
    return path1;
}

#endif // KMATRIXGRAPH_H
