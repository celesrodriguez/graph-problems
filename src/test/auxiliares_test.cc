#include "auxiliares_test.h"

#define EXPLORE_ALL 99
#define SIGMA 3
#define F 2
#define EPSILON 0.00001

#include <cmath>
#include "test_utils.h"
#include "../auxiliares.h"
#include "stdio.h"
#include <string>

void RunAllAuxTests(){
	// Llamar a los otros tests
	graph_with_single_edge();
	graph_with_two_equal_edges_is_not_pruned();
	graph_with_two_edges_with_one_way_bigger_is_pruned();
	graph_with_six_nodes_with_one_inconsistent_edge_is_pruned();

 	graph_with_two_edges_with_one_way_bigger();
	collecting_weights_for_a_leaf_should_return_nothing();
	collect_tree_height_3();
	collect_with_two_leaves();
	collect_with_limited_depth();
	in_a_graph_with_two_edges_the_shortest_should_be_consistent();
	standard_deviation_with_empty_population();
	standard_deviation_with_one_population();
	standard_deviation_with_five_population();
	edge_is_inconsistent_with_five_edges_where_one_is_inconsistent();
}

void print_graph(Graph& graph){
	std::cout << std::endl;

	for(unsigned int i = 0; i < graph.size(); i++){
		std::cout << "[" << i << "] = ";
		for(unsigned int k = 0; k < graph[i].size(); k++){
			Edge e = graph[i][k];
			std::cout << "(" << std::to_string(e.v) << ", " << std::to_string(e.u) << ", " << std::to_string(e.distance) << ")" << ", ";
		}

		std::cout << std::endl;
	}	
}

void graph_with_single_edge() {
	TEST

	given("A graph with just one edge")
		Graph graph(2);
		Edge edge = Edge(0, 1, 10.0);
		graph[0].push_back(edge);
		graph[1].push_back(edge);

	when("It's pruned")
		aux::prune_edges(graph, SIGMA, F, EXPLORE_ALL);

	then("It should remain the same")
		assert( graph[0][0] == edge );
		assert( graph[1][0] == edge );

	END_TEST
}


void graph_with_two_equal_edges_is_not_pruned(){
	TEST

	given("A graph with two edges of the same length")
		Graph graph(3);
		graph[0].push_back(Edge(0, 1, 10.0));
		graph[1].push_back(Edge(0, 1, 10.0));
		graph[1].push_back(Edge(2, 1, 10.0));
		graph[2].push_back(Edge(2, 1, 10.0));
		Graph expected = graph;

	when("Pruning edges with a small tolerance")
		aux::prune_edges(graph, 1, 1, EXPLORE_ALL);

	then("No edges should be removed")
		assert( expected == graph );

	END_TEST
}

void graph_with_two_edges_with_one_way_bigger_is_pruned(){
	TEST
	
	given("A graph with two edges, one way bigger than the other")
		Graph graph(3);
		Edge inconsistent_edge = Edge(1, 2, 100.0);
		Edge consistent_edge = Edge(0, 1, 1.0);
		graph[0].push_back(consistent_edge);
		graph[1].push_back(consistent_edge);
		graph[1].push_back(inconsistent_edge);
		graph[2].push_back(inconsistent_edge);

	when("It's pruned")
		aux::prune_edges(graph, SIGMA, F, EXPLORE_ALL);

	then("The longest edge should be pruned but not the shortest")
		Graph expected(3);
		expected[0].push_back(consistent_edge);
		expected[1].push_back(consistent_edge);
		assert( expected == graph );

	END_TEST
}

void graph_with_six_nodes_with_one_inconsistent_edge_is_pruned(){
	TEST
	
	given("A graph with six nodes forming two clusters")
		Edge a = Edge(0, 1, 4);
		Edge b = Edge(1, 2, 5);
		Edge c = Edge(0, 3, 3);
		Edge d = Edge(3, 4, 3000000);
		Edge e = Edge(4, 5, 3);

		Graph tree(6);
		tree[0].push_back(a);
		tree[0].push_back(c);
		tree[1].push_back(a);
		tree[1].push_back(b);
		tree[2].push_back(b);
		tree[3].push_back(c);
		tree[3].push_back(d);
		tree[4].push_back(e);
		tree[4].push_back(d);
		tree[5].push_back(e);
		Graph expected = tree;

	when("It's pruned")
		aux::prune_edges(tree, SIGMA, F, EXPLORE_ALL);

	then("The longest edge should be pruned but not the shortest")
		expected[3].pop_back();
		expected[4].pop_back();
		assert(expected == tree);
		
	END_TEST
}

void graph_with_two_edges_with_one_way_bigger(){
	TEST
	
	given("A graph with two edges, one way bigger than the other")
		Graph graph(3);
		Edge inconsistent_edge = Edge(1, 2, 100.0);
		Edge consistent_edge = Edge(0, 1, 10.0);
		graph[0].push_back(consistent_edge);
		graph[1].push_back(consistent_edge);
		graph[1].push_back(inconsistent_edge);
		graph[2].push_back(inconsistent_edge);
		Graph expected = graph;

	then("The longest edge should be pruned but not the shortest")
		assert( aux::edge_is_inconsistent(graph, inconsistent_edge, SIGMA, F, EXPLORE_ALL) == true );
		assert( aux::edge_is_inconsistent(graph, consistent_edge, SIGMA, F, EXPLORE_ALL) == false );

	END_TEST
}


void collecting_weights_for_a_leaf_should_return_nothing(){
	TEST

	given("A leaf")
		Graph graph(2);
		graph[0].push_back(Edge(0, 1, 10.0));
		graph[1].push_back(Edge(0, 1, 10.0));

	when("Collecting its weights")
		auto weights = aux::collect_edge_weights(graph, 1, 0, 3);

	then("No weights should be returned")
		assert( weights == std::vector<float>() );

	END_TEST
}

void collect_tree_height_3(){
	TEST
	
	given("A tree of height 3")
		Graph graph(3);
		graph[0].push_back(Edge(0, 1, 10.0));
		graph[1].push_back(Edge(0, 1, 10.0));
		graph[1].push_back(Edge(1, 2, 100.0));
		graph[2].push_back(Edge(2, 1, 100.0));

	when("Collecting its weights")
		auto weights = aux::collect_edge_weights(graph, 1, 0, 3);

	then("Weight for the 1-2 edge should be returned")
		std::vector<float> expected(1);
		expected[0] = 100.0;
		assert( weights == expected );

	END_TEST
}

void collect_with_two_leaves(){
	TEST

	given("A graph of height 3, with two leafs")
		Graph graph(4);
		graph[0].push_back(Edge(0, 1, 10.0));
		graph[1].push_back(Edge(1, 0, 10.0));
		graph[1].push_back(Edge(1, 2, 100.0));
		graph[1].push_back(Edge(1, 3, 200.0));
		graph[2].push_back(Edge(2, 1, 100.0));
		graph[3].push_back(Edge(3, 1, 200.0));

	when("Collecting its weights")
		auto weights = aux::collect_edge_weights(graph, 1, 0, 3);

	then("Weight for the edges 1-2,1-3 should be returned")
		std::vector<float> expected(2);
		expected[0] = 100.0;
		expected[1] = 200.0;
		assert( weights == expected );


	END_TEST
}

void collect_with_limited_depth(){
	TEST

	given("A graph of height 4")
		Graph graph(4);
		graph[0].push_back(Edge(0, 1, 10.0));
		graph[1].push_back(Edge(1, 0, 10.0));
		graph[1].push_back(Edge(1, 2, 100.0));
		graph[2].push_back(Edge(2, 1, 100.0));
		graph[2].push_back(Edge(2, 3, 200.0));
		graph[3].push_back(Edge(3, 2, 200.0));

	when("Collecting its weights, up to a depth of 1")
		auto weights = aux::collect_edge_weights(graph, 1, 0, 1);

	then("Weight for the edge 1-2 should be returned")
		std::vector<float> expected(1);
		expected[0] = 100.0;
		assert( weights == expected );

	END_TEST
}

void in_a_graph_with_two_edges_the_shortest_should_be_consistent(){
	TEST
	
	given("A graph with two edges, one way bigger than the other")
		Graph graph(3);
		Edge edge = Edge(0, 1, 10.0);
		graph[0].push_back(edge);
		graph[1].push_back(edge);
		graph[1].push_back(Edge(2, 1, 100.0));
		graph[2].push_back(Edge(2, 1, 100.0));

	then("The short edge should not be inconsistent")
		assert( aux::edge_is_inconsistent(graph, edge, SIGMA, F, EXPLORE_ALL) == false );

	END_TEST
}

void standard_deviation_with_empty_population(){
	TEST

	given("An empty population list")
		std::vector<float> population;

	when("Calculating it's standard deviation")
		float result = aux::calculate_stdev(population);

	then("Zero should be returned")
		float expected = 0.0;
		assert(expected == result);

	END_TEST
}

void standard_deviation_with_one_population(){
	TEST

	given("A list with one floating point population")
		std::vector<float> population;
		population.push_back(20.0);

	when("Calculating it's standard deviation")
		float result = aux::calculate_stdev(population);

	then("The result should be equal or almost equal to the expected value")
		float expected = 0.0;
		bool result_is_like_expected = abs(expected - result) < EPSILON;
		assert(result_is_like_expected);

	END_TEST
}

void standard_deviation_with_five_population(){
	TEST

	given("A list with five floating point population")
		std::vector<float> population;
		population.push_back(1.0);
		population.push_back(2.0);
		population.push_back(3.0);
		population.push_back(4.0);
		population.push_back(5.0);

	when("Calculating it's standard deviation")
		float result = aux::calculate_stdev(population);

	then("The result should be equal or almost equal to the expected value")
		float expected = 1.4142135623731;
		bool result_is_like_expected = abs(expected - result) < EPSILON;
		assert(result_is_like_expected);

	END_TEST
}

void edge_is_inconsistent_with_five_edges_where_one_is_inconsistent(){
	TEST

	given("A 5 node connected graph with 4 light weight edges (consistents) and a heavy one (inconsistent)")
		Graph graph(6);
		Edge light_edge_0_1 = Edge(0, 1, 40.0);
		Edge light_edge_0_2 = Edge(0, 2, 41.0);
		Edge light_edge_3_4 = Edge(3, 4, 42.0);
		Edge light_edge_3_5 = Edge(3, 5, 43.0);
		Edge heavy_edge_0_3 = Edge(0, 3, 9999.0);
		graph[0].push_back(light_edge_0_1);
		graph[0].push_back(light_edge_0_2);
		graph[0].push_back(heavy_edge_0_3);
		graph[1].push_back(light_edge_0_1);
		graph[2].push_back(light_edge_0_2);
		graph[3].push_back(light_edge_3_4);
		graph[3].push_back(heavy_edge_0_3);
		graph[3].push_back(light_edge_3_5);
		graph[4].push_back(light_edge_3_4);
		graph[5].push_back(light_edge_3_5);

	when("Calling edge_is_inconsistent with defined parameters")
		bool is_light_edge_0_1_inconsistent = aux::edge_is_inconsistent(graph, light_edge_0_1, SIGMA, F, EXPLORE_ALL);
		bool is_light_edge_0_2_inconsistent = aux::edge_is_inconsistent(graph, light_edge_0_2, SIGMA, F, EXPLORE_ALL);
		bool is_light_edge_3_4_inconsistent = aux::edge_is_inconsistent(graph, light_edge_3_4, SIGMA, F, EXPLORE_ALL);
		bool is_light_edge_3_5_inconsistent = aux::edge_is_inconsistent(graph, light_edge_3_5, SIGMA, F, EXPLORE_ALL);
		bool is_heavy_edge_0_3_inconsistent = aux::edge_is_inconsistent(graph, heavy_edge_0_3, SIGMA, F, EXPLORE_ALL);

	then("The light weights edges are consistent and the heavy edge is inconsistent")
		assert(not is_light_edge_0_1_inconsistent);
		assert(not is_light_edge_0_2_inconsistent);
		assert(not is_light_edge_3_4_inconsistent);
		assert(not is_light_edge_3_5_inconsistent);
		assert(is_heavy_edge_0_3_inconsistent);

	END_TEST	
}
