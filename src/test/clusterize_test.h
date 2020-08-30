#ifndef TEST_CLUSTERIZE_TEST_H_
#define TEST_CLUSTERIZE_TEST_H_

#include <vector>
#include "test_utils.h"
#include "../point.h"
#include "../edge.h"
#include "../algorithm.h"

void RunAllTestsFor(Algorithm* a);


void no_edges_should_be_built_for_empty_points();
void no_edges_should_be_built_for_a_single_node();
void one_edge_should_be_built_between_two_points();
void three_edges_should_be_built_between_three_points();

void two_cluters_test_and_eight_points_test();

#endif
