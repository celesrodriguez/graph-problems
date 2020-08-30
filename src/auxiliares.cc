#include "auxiliares.h"

#include <iostream>
#include <cmath>
#include <assert.h> 

namespace aux { 

	void prune_edges(std::vector<std::vector<Edge>> &graph, float sigma, float f, int depth){
		for(int node = graph.size() - 1; node >= 0; node--){
			for(int edge = graph[node].size() - 1; edge >= 0; edge--){
				int current_depth = 0;
				Edge e = graph[node][edge];
				if ( edge_is_inconsistent(graph, e, sigma, f, depth) ){
					delete_edge(graph[e.u], e);
					delete_edge(graph[e.v], e);
				}
			}
		}
	}

	void delete_edge(std::vector<Edge> &edge_list, Edge e){
		int node = -1;
		for( unsigned int i = 0; i < edge_list.size(); i++ ) {
			if ( edge_list[i] == e )
				node = i;
		}
		assert( node != -1 );
		edge_list.erase(edge_list.begin() + node);
	}

	bool edge_is_inconsistent(const std::vector<std::vector<Edge>> &graph, const Edge &edge, float sigma, float f, int depth){
		auto v_weights = collect_edge_weights(graph, edge.v, edge.u, depth);
		auto u_weights = collect_edge_weights(graph, edge.u, edge.v, depth);		

		float v_mean = calculate_mean(v_weights);
		float u_mean = calculate_mean(u_weights);

		float v_stdev = calculate_stdev(v_weights);
		float u_stdev = calculate_stdev(u_weights);

		bool u_is_consistent = not u_weights.empty() and edge.distance <= u_mean + sigma * u_stdev and
			edge.distance <= u_mean * f;

		bool v_is_consistent = not v_weights.empty() and edge.distance <= v_mean + sigma * v_stdev and
			edge.distance <= v_mean * f;

		if ( u_weights.empty() and v_weights.empty() )
			return false;
		
		return not(u_is_consistent or v_is_consistent);
	}

	float calculate_mean(std::vector<float> samples){
		if ( samples.empty() )
			return 0.0;

		float mean = 0.0;

		for(unsigned int i = 0; i < samples.size(); i++){
			mean += samples[i];
		}
		
		mean /= samples.size();

		return mean;
	}

	float calculate_stdev(std::vector<float> weights){
		int n = weights.size();

		if(n == 0) return 0.0;

		float mean = calculate_mean(weights);
		float variance = 0.0;

		for(int i = 0; i < n; i++){
			variance += pow(weights[i] - mean, 2);
		}

		variance /= n;

		return sqrt(variance);
	}

	std::vector<float> collect_edge_weights(const std::vector<std::vector<Edge>> &graph, Node node, Node parent, int depth){
		if( graph[node].size() == 1 ) { // Solo esta conectado al padre => es una hoja
			return std::vector<float>();
		}

		// Consigo los pesos de los hijos
		std::vector<float> weights;
		for(unsigned int child = 0; child < graph[node].size(); child++){
			Edge edge = graph[node][child];
			if( edge.u != parent && edge.v != parent ) {
				weights.push_back(edge.distance);

				if( depth != 1 ) { // Sigo explorando los hijos
					Node next_node = node == edge.u ? edge.v : edge.u;

					auto child_weights = collect_edge_weights(graph, next_node, node, depth - 1);
					weights.insert(weights.end(), child_weights.begin(), child_weights.end());
				}
			}
		}

		return weights;
	}
	
	void print_vector(const std::vector<float> &S){
		std::cout << '\n' << "{ ";
		for(unsigned int i = 0; i < S.size(); i++) {
			std::cout << S[i];
			if (i != S.size() - 1) {
				std::cout << ", ";
			}
		}
		std::cout << " }";
	}

	void print_edges(const std::vector<Edge> &S){
		std::cout << '\n' << "{ ";
		for(unsigned int i = 0; i < S.size(); i++) {
			std::cout << "(" << S[i].u << ", " << S[i].v << ", " << S[i].distance << ")";
			if (i != S.size() - 1) {
				std::cout << ", ";
			}
		}
		std::cout << " }";
	}
}
