#include "algorithm.h"

std::vector<int> Algorithm::Clusterize(std::vector<Point> &points){
	std::vector<Edge> edges = BuildEdges(points);
	return Clusterize(points, edges);
}

std::vector<Edge> Algorithm::BuildEdges(std::vector<Point> &points){
	std::vector<Edge> edges;

	int vertex_count = points.size();

	for(int v = 0; v < vertex_count - 1; v++){
		for(int u = v + 1; u < vertex_count; u++){
			Point point_v = points[v];
			Point point_u = points[u];
			float distance = point_v.DistanceTo(point_u);

/*			std::cout << "agregada arista (" << v << ", " << u << "), ";
			std::cout << "v=(" << point_v.x << ", " << point_v.y << "), ";
			std::cout << "u=(" << point_u.x << ", " << point_u.y << ") ";
			std::cout << "con distancia " << distance << std::endl;
*/			
			edges.push_back(Edge(v, u, distance));
		}
	}

	return edges;
}
