#ifndef TEST_AUXILIARES_H_
#define TEST_AUXILIARES_H_

#include <vector>
#include "../edge.h"

typedef std::vector<std::vector<Edge>> Graph;

void RunAllAuxTests();
void print_graph(Graph& graph);

void graph_with_two_equal_edges_is_not_pruned();
void graph_with_single_edge();
void graph_with_two_edges_with_one_way_bigger_is_pruned();
void graph_with_six_nodes_with_one_inconsistent_edge_is_pruned();
void graph_with_two_edges_with_one_way_bigger();
void collecting_weights_for_a_leaf_should_return_nothing();
void collect_tree_height_3();
void collect_with_two_leaves();
void collect_with_limited_depth();
void in_a_graph_with_two_edges_the_shortest_should_be_consistent();
void standard_deviation_with_empty_population();
void standard_deviation_with_one_population();
void standard_deviation_with_five_population();
void edge_is_inconsistent_with_five_edges_where_one_is_inconsistent();
#endif
