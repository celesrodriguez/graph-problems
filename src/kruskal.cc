#include <algorithm>
#include "kruskal.h"
#include "auxiliares.h"

#define C_DEPTH 5
#define C_SIGMA 5
#define C_F 5

#define DEPTH 5
#define SIGMA 5
#define F 5

Kruskal::Kruskal(bool _path_compression_enabled): path_compression_enabled(_path_compression_enabled){};

std::vector<int> Kruskal::Clusterize(std::vector<Point> &points, std::vector<Edge> &edges){
	int total_nodes = points.size();
	std::vector<Edge> min_spanning_tree = FindMinimumSpanningTree(total_nodes, edges);
	std::vector<Edge> pruned_edges_by_constant = PruneEdges(min_spanning_tree, total_nodes, C_DEPTH, C_SIGMA, C_F);
	std::vector<Edge> pruned_edges = PruneEdges(pruned_edges_by_constant, total_nodes,  DEPTH, SIGMA, F);
	return FindClusters(points.size(), pruned_edges);
}

std::vector<Edge> Kruskal::FindMinimumSpanningTree(int points, std::vector<Edge> &edges){
	DisjointSetUnion agm_dsu = DisjointSetUnion(points, path_compression_enabled);

	std::vector<Edge> min_spanning_tree;
	std::sort(edges.begin(), edges.end());

	for(Edge &e : edges){
		if(not AddingEdgeMakesCycle(agm_dsu, e)){
			min_spanning_tree.push_back(e);
			agm_dsu.Union(e.v, e.u);
		}
	}

	return min_spanning_tree;
}

std::vector<Edge> Kruskal::PruneEdges(std::vector<Edge> &edges, int total_nodes, int depth, int sigma, int f){
	Graph graph = edges_to_graph(edges, total_nodes);
	aux::prune_edges(graph, sigma, f, depth);
	return graph_to_edges(graph);
}

std::vector<int> Kruskal::FindClusters(int points, std::vector<Edge> &pruned_edges){	
	DisjointSetUnion cluster_dsu = DisjointSetUnion(points, path_compression_enabled);

	for(Edge &e : pruned_edges){
		cluster_dsu.Union(e.v, e.u);
	}

	std::vector<int> clusters;
	for(int i = 0; i < points; i++){
		clusters.push_back(cluster_dsu.Find(i));
	}

	return clusters;
}

std::vector<Edge> Kruskal::graph_to_edges(Graph &graph){
	std::vector<Edge> edges;
	for( unsigned int node = 0; node < graph.size(); node++ ){
		for( unsigned int edge = 0; edge < graph[node].size(); edge++ ){
			if( graph[node][edge].u >= node and graph[node][edge].v >= node) // Avoid repeating edges
				edges.push_back(graph[node][edge]);
		}
	}
	return edges;
}

Graph Kruskal::edges_to_graph(std::vector<Edge> &edges, int total_nodes){
	Graph graph(total_nodes);

	for(Edge e : edges){
		graph[e.u].push_back(e);
		graph[e.v].push_back(e);
	}

	return graph;
}

bool Kruskal::AddingEdgeMakesCycle(DisjointSetUnion &dsu, Edge &e){
	return dsu.Find(e.v) == dsu.Find(e.u);
}
