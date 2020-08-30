#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include <iostream>
#include <vector>
#include "edge.h"
#include "point.h"

class Algorithm {
	public:
		virtual std::vector<int> Clusterize(std::vector<Point> &points, std::vector<Edge> &edges) = 0;

		std::vector<int> Clusterize(std::vector<Point> &points);

		std::vector<Edge> BuildEdges(std::vector<Point> &points);

	private:
};
#endif
