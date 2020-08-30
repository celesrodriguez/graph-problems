#ifndef AUXILIARES_H_ 
#define AUXILIARES_H_

#include <iostream> 
#include <fstream> 
#include <vector>
#include "string"

#include "edge.h"
#include "point.h"

typedef std::vector<std::vector<Edge>> Graph;

namespace aux {
	typedef unsigned int Node;

	template <typename T>
	void print_vector(const std::vector<T> &S, std::ostream &output, std::string separator){
		for(unsigned int i = 0; i < S.size(); i++) {
			output << S[i];
			if (i != S.size() - 1) {
				output << separator;
			}
		}
	}

	template <typename T>
	void print_vector(const std::vector<T> &S){
		std::cout << "\n{ ";
		print_vector(S, std::cout, ", ");
		std::cout << " }";
	}

	void print_edges(const std::vector<Edge> &S);

	void prune_edges(Graph &graph, float sigma, float f, int depth);

	void delete_edge(std::vector<Edge> &edge_list, Edge e);
	
	std::vector<float> collect_edge_weights(const Graph &graph, Node node, Node parent, int depth);
	
	bool edge_is_inconsistent(const Graph &graph, const Edge &edge, float sigma, float f, int depth);

	float calculate_stdev(std::vector<float> weights);

	float calculate_mean(std::vector<float> samples);

	std::vector<Edge> build_edges(std::vector<Point> &points);
}

#endif
