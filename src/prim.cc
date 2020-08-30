#include "prim.h"

#include <algorithm>
#include "auxiliares.h"

#define C_DEPTH 5
#define C_SIGMA 5
#define C_F 5

#define DEPTH 9
#define SIGMA 3
#define F 2

std::vector<Edge> Prim::GetEdgesMST(std::vector<Point> &points) {
    std::vector<Edge> result;
    for (int v = 0; v < _parents.size(); v++) {
        int u = _parents[v];
        float distance = points[u].DistanceTo(points[v]);
        if (u != v) {
            result.push_back(Edge(u, v, distance));
        }
    }
    return result;
}

void Prim::init(int pointsSize) {
    for (int i = 0; i < pointsSize; i++) {
        _visited.push_back(false);
        _distance.push_back(std::numeric_limits<float>::max());
        _parents.push_back(i);
    }
    _distance[0] = 0;
    _parents[0] = 0;
    _minHeap.push(std::pair<int, float>(0, _distance[0]));
}

void Prim::treatNode(int startNode, int endNode, float distance) {
    if (!_visited[endNode] && _distance[endNode] > distance) {
        _distance[endNode] = distance;
        _parents[endNode] = startNode;
        _minHeap.push(std::pair<int, float>(endNode, _distance[endNode]));
    }
}

void Prim::refreshMinDistances(unsigned int nodeId, std::vector<Edge> &edges) {
    for (unsigned int i = 0; i < edges.size(); i++) {
        Edge e = edges[i];
        if (e.u == nodeId) {
            treatNode(e.u, e.v, e.distance);
        } else if (e.v == nodeId) {
            treatNode(e.v, e.u, e.distance);
        }
    }
}

std::vector<Edge> Prim::FindMinimumSpanningTree(std::vector<Point> &points, std::vector<Edge> &edges) {
    init(points.size());
    while (!_minHeap.empty()) {
        std::pair<int, float> p = _minHeap.top();
        _minHeap.pop();
        int nodeId = p.first;
        if (_visited[nodeId]) {
            continue;
        } else {
            _visited[nodeId] = true;
            refreshMinDistances(nodeId, edges);
        }
    }
   return GetEdgesMST(points);
}

std::vector<Edge> Prim::PruneEdges(std::vector<Edge> &edges, int total_nodes, int depth, int sigma) {
    Graph graph = edges_to_graph(edges, total_nodes);
    aux::prune_edges(graph, sigma, 0, depth);
    return graph_to_edges(graph);
}

bool Prim::parentConnectionExists(int node, int parent, std::vector<Edge> &pruned_edges) {
    for (Edge e : pruned_edges) {
        if (node == e.u && parent == e.v) {
            return true;
        } else if (node == e.v && parent == e.u) {
            return true;
        }
    }
    return false;
}

int Prim::findParent(int i, std::vector<Edge> &pruned_edges) {
    if (_parents[i] == i) {
        return i;
    }
    if (parentConnectionExists(i, _parents[i], pruned_edges)) {
        return findParent(_parents[i], pruned_edges);
    }
    return i;
}

std::vector<int> Prim::FindClusters(int qtyPoints, std::vector<Edge> &pruned_edges, std::vector<Point> &points) {
    std::vector<int> clusters;
    for (int i = 0; i < qtyPoints; i++) {
        int par = findParent(i, pruned_edges);
        clusters.push_back(par);
    }
    return clusters;
}

std::vector<Edge> Prim::graph_to_edges(Graph &graph) {
    std::vector<Edge> edges;
    for (unsigned int node = 0; node < graph.size(); node++) {
        for (unsigned int edge = 0; edge < graph[node].size(); edge++) {
            if (graph[node][edge].u >= node and graph[node][edge].v >= node) // Avoid repeating edges
                edges.push_back(graph[node][edge]);
        }
    }
    return edges;
}

Graph Prim::edges_to_graph(std::vector<Edge> &edges, int total_nodes) {
    Graph graph(total_nodes);

    for (Edge e : edges) {
        graph[e.u].push_back(e);
        graph[e.v].push_back(e);
    }

    return graph;
}

std::vector<int> Prim::Clusterize(std::vector<Point> &points, std::vector<Edge> &edges) {
    int total_nodes = points.size();
    std::vector<Edge> min_spanning_tree = FindMinimumSpanningTree(points, edges);
    std::vector<Edge> pruned_edges_by_constant = PruneEdges(min_spanning_tree, total_nodes, DEPTH, SIGMA);
    return FindClusters(total_nodes, pruned_edges_by_constant, points);
}