#include "clusterize_test.h"

#include <math.h>

Algorithm* algorithm;

void RunAllTestsFor(Algorithm* a){
	algorithm = a;

	no_edges_should_be_built_for_empty_points();
	no_edges_should_be_built_for_a_single_node();
	one_edge_should_be_built_between_two_points();
	three_edges_should_be_built_between_three_points();
	two_cluters_test_and_eight_points_test();
}

void no_edges_should_be_built_for_empty_points(){
	TEST

	given("An empty set of points")
		std::vector<Point> points;

	when("Building their edges")
		auto edges = algorithm->BuildEdges(points);

	then("No edges should be found")
		assert( edges.empty() );

	END_TEST
}

void no_edges_should_be_built_for_a_single_node(){
	TEST  

	given("A set containing a single point")
		std::vector<Point> points;
		points.push_back(Point(0,0));

	when("Building its edges")
		auto edges = algorithm->BuildEdges(points);

	then("No edges should be found")
		assert( edges.empty() );

	END_TEST
}

void one_edge_should_be_built_between_two_points(){
	TEST SUPRESS_STDOUT

	given("A set containing two points")
		std::vector<Point> points;
		points.push_back(Point(0,0));
		points.push_back(Point(1,1));

	when("Building its edges")
		auto edges = algorithm->BuildEdges(points);

	then("One edge should be found")
		assert( edges.size() == 1 );
	And("The points in the edge should be the same")
		assert( edges[0].v == 0 );
		assert( edges[0].u == 1 );

	ENABLE_STDOUT END_TEST
}

void three_edges_should_be_built_between_three_points(){
	TEST SUPRESS_STDOUT

	given("A set containing three points")
		std::vector<Point> points;
		points.push_back(Point(0,0));
		points.push_back(Point(1,1));
		points.push_back(Point(2,2));

	when("Building its edges")
		auto edges = algorithm->BuildEdges(points);

	then("Three edges should be found")
		assert( edges.size() == 3 );
	And("The points in the edge should be the same")
		assert( edges[0].v == 0 );
		assert( edges[0].u == 1 );
		assert( edges[1].v == 0 );
		assert( edges[1].u == 2 );
		assert( edges[2].v == 1 );
		assert( edges[2].u == 2 );

	ENABLE_STDOUT END_TEST
}

void edge_weight_should_be_distance_between_points(){
	TEST SUPRESS_STDOUT

	given("A set containing three points")
		std::vector<Point> points;
		points.push_back(Point(0,0));
		points.push_back(Point(1,1));
		points.push_back(Point(-1,-1));

	when("Building its edges")
		auto edges = algorithm->BuildEdges(points);

	then("Edge weight should be distance between points")
		assert( edges[0].distance == sqrt(2) );
		assert( edges[1].distance == sqrt(2) );
		assert( edges[2].distance == 2 );

	ENABLE_STDOUT END_TEST
}

void two_cluters_test_and_eight_points_test(){
	TEST  SUPRESS_STDOUT

	given("Ocho puntos")
		std::vector<Point> vertex;
		vertex.push_back(Point(3, 11));
		vertex.push_back(Point(4, 10));
		vertex.push_back(Point(5, 11));
		vertex.push_back(Point(5, 13));
		vertex.push_back(Point(9, 6));
		vertex.push_back(Point(12, 6));
		vertex.push_back(Point(10, 8));
		vertex.push_back(Point(3, 12));

	when("Los clusterizo")
		algorithm->Clusterize(vertex);

	then("Deberian resolverse dos clusters en total")
		// assert(true)

	ENABLE_STDOUT  END_TEST
}
