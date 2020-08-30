#ifndef PRIM_H_
#define PRIM_H_

#include "algorithm.h"
#include "vector"
#include "point.h"
#include "edge.h"
#include "compare.h"

#include <queue>
#include <vector>
#include <functional>

typedef std::vector<std::vector<Edge>> Graph;

class Prim : public Algorithm {
	public:
		std::vector<int> Clusterize(std::vector<Point> &points, std::vector<Edge> &edges);

private:
	std::priority_queue<std::pair<int, float>, std::vector<std::pair<int, float>>, CompareDistance> _minHeap;
	std::vector<bool> _visited;
	std::vector<float> _distance;
	std::vector<int> _parents;

	void init(int pointsSize);

    void treatNode(int startNode, int endNode, float distance);

	void refreshMinDistances(unsigned int nodeId, std::vector<Edge> &edges);

    std::vector<Edge> GetEdgesMST(std::vector<Point> &points);

	std::vector<Edge> FindMinimumSpanningTree(std::vector<Point> &points, std::vector<Edge> &edges);

	std::vector<Edge> PruneEdges(std::vector<Edge> &edges, int total_nodes, int depth, int sigma);

	std::vector<int> FindClusters(int qtyPoints, std::vector<Edge> &pruned_edges, std::vector<Point> &points);

	Graph edges_to_graph(std::vector<Edge> &edges, int total_nodes);

	std::vector<Edge> graph_to_edges(Graph &graph);

	bool parentConnectionExists(int node, int parent, std::vector<Edge> &pruned_edges);

	int findParent(int i, std::vector<Edge> &pruned_edges);

	void showNode(std::vector<Edge> &edges, int node);
};

#endif
