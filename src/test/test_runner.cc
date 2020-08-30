#include "iostream"

#include "test_utils.h"
#include "clusterize_test.h"
#include "auxiliares_test.h"

#include "../prim.h"
#include "../kruskal.h"

#define PATH_COMPRESSION_ENABLED true
#define PATH_COMPRESSION_DISABLED false

int main (){
	std::cout << "\nRunning common functions tests\n";
	std::cout << "================================\n";
	RunAllAuxTests();

	std::cout << "\nRunning Prim tests\n";
	std::cout << "====================\n";
	RunAllTestsFor(new Prim());

	std::cout << "\nRunning Kruskal tests\n";
	std::cout << "=======================\n";
	RunAllTestsFor(new Kruskal(PATH_COMPRESSION_ENABLED));

	std::cout << "\nRunning Kruskal w/ path compression tests\n";
	std::cout << "===========================================\n";
	RunAllTestsFor(new Kruskal(PATH_COMPRESSION_DISABLED));

	std::cout << "\n";
	return 0;
}
