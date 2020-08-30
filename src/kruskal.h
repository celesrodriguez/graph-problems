#ifndef KRUSKAL_H_
#define KRUSKAL_H_

#include <vector>

#include "edge.h"
#include "point.h"
#include "algorithm.h"
#include "disjoint_set_union.h"

typedef std::vector<std::vector<Edge>> Graph;

class Kruskal : public Algorithm {
	private:
		bool path_compression_enabled;

	public:
		Kruskal(bool _path_compression_enabled);
		
		std::vector<int> Clusterize(std::vector<Point> &points, std::vector<Edge> &edges);

		std::vector<Edge> FindMinimumSpanningTree(int points, std::vector<Edge> &edges);

		std::vector<Edge> PruneEdges(std::vector<Edge> &edges, int total_nodes, int depth, int sigma, int f);

		std::vector<int> FindClusters(int points, std::vector<Edge> &pruned_edges);

		bool AddingEdgeMakesCycle(DisjointSetUnion &dsu, Edge &e);

		Graph edges_to_graph(std::vector<Edge> &edges, int total_nodes);
		
		std::vector<Edge> graph_to_edges(Graph &graph);
};
#endif
