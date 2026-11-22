#include <iostream>
#include <queue>  /* 和 Lab11 的层次遍历一样，使用 std::queue */

#include "graph.h"

/* 深度优先：沿用 Lab11 的先序遍历，先访问当前顶点，再递归访问邻接点。
 * 二叉树只有 lc/rc 两个孩子；图要用循环扫描这一行，寻找所有邻接点。 */
void dfs(const Graph& graph, int v, bool visited[]) {
    /* 已访问就直接返回（图有环，靠 visited 防止重复进入）；
     * 否则标记并输出 graph.vertices[v]，每个字符后输出一个空格。
     * 按 w = 0～numVertices-1 扫描第 v 行，遇到存在边且未访问的 w 时递归。
     * visited 传的是首地址，函数内不清空、不重置。 */
    if (visited[v]) {
        return;
    }

    visited[v] = true;
    std::cout << graph.vertices[v] << " ";

    for (int w = 0; w < graph.numVertices; ++w) {
        if (graph.edge[v][w] == 1 && !visited[w]) {
            dfs(graph, w, visited);
        }
    }
}

/* 一次搜索不一定覆盖全图：用外层循环补上尚未访问的部分。 */
void dfsAll(const Graph& graph) {
    /* bool visited[MAXV] = {}; 初始化 MAXV 个 false，只初始化这一次；
     * 按编号递增检查所有顶点，对未访问的顶点调用 dfs，
     * 外层用循环变量 v 而不是写死 0，否则其余连通分量与孤立点不会被访问。 */
    bool visited[MAXV] = {};
    for (int v = 0; v < graph.numVertices; ++v) {
        if (!visited[v]) {
            dfs(graph, v, visited);
        }
    }
}

/* 广度优先：沿用 Lab11 的层次遍历，先入队，再循环出队、访问、扩展。
 * 树的队列保存 Node*；本次队列保存顶点编号 int。 */
void bfs(const Graph& graph, int v, bool visited[]) {
    /* 已访问就直接返回；否则创建 std::queue<int>，
     * 先把起点标记为已访问再入队（入队即标记，避免同一顶点被多个前驱重复入队）。
     * 每轮取队首编号、出队、输出该顶点，再按编号递增扫描它的邻接点，
     * 存在边且未访问的邻接点先标记再入队。 */
    if (visited[v]) {
        return;
    }

    std::queue<int> q;
    visited[v] = true;
    q.push(v);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        std::cout << graph.vertices[u] << " ";

        for (int w = 0; w < graph.numVertices; ++w) {
            if (graph.edge[u][w] == 1 && !visited[w]) {
                visited[w] = true;
                q.push(w);
            }
        }
    }
}

void bfsAll(const Graph& graph) {
    /* bool visited[MAXV] = {}; 初始化 MAXV 个 false，只初始化这一次；
     * 按编号递增检查所有顶点，对未访问的顶点调用 bfs（continue 跳过
     * 已访问顶点，而不是 return，否则首个分量结束后函数整体退出）。 */
    bool visited[MAXV] = {};
    for (int v = 0; v < graph.numVertices; ++v) {
        if (!visited[v]) {
            bfs(graph, v, visited);
        }
    }
}
