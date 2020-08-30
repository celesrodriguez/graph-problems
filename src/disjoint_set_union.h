#ifndef DISJOIN_SET_UNION
#define DISJOIN_SET_UNION

#include <vector>

class DisjointSetUnion {
private:
	std::vector<int> height;
	std::vector<int> parent;
	bool enable_path_compression;
	
public:
	DisjointSetUnion(int n, bool enable_path_compression);

	int Find(int x);

	void Union(int x, int y);

	void Print();

	std::vector<int> GetClusters();
};

#endif