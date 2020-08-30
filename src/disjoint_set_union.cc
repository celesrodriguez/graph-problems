#include <iostream>
#include "disjoint_set_union.h"

DisjointSetUnion::DisjointSetUnion(int n, bool _enable_path_compression){
	enable_path_compression = _enable_path_compression;

	for(int i = 0; i < n; i++){
		height.push_back(1);
		parent.push_back(i);
	}
}

int DisjointSetUnion::Find(int x){
	if(parent[x] != x){
		int p = Find(parent[x]);

		if(enable_path_compression){
			parent[x] = p;
		}else{
			return p;
		}
	}

	return parent[x];
}

void DisjointSetUnion::Union(int x, int y){
	x = Find(x);
	y = Find(y);

	if(height[x] < height[y])
		parent[x] = y;
	else
		parent[y] = x;
	

	if(height[x] == height[y])
		height[x] = height[x] + 1;
}

void DisjointSetUnion::Print(){
	for(unsigned int i = 0; i < parent.size(); i++){
		std::cout << "Vertex " << i << " belongs to cluster " << parent[i] << std::endl;
	}
}

std::vector<int> DisjointSetUnion::GetClusters(){
	return parent;
}
