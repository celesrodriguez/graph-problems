CFLAGS = -Wall -std=c++11 -Wextra -Wno-unused -O1

OBJS = prim.cc kruskal.cc bellman.cc floyd.cc auxiliares.cc disjoint_set_union.cc algorithm.cc test/arbitraje_test.cc exp/experimentacion_arbitraje.cc
TESTS = test/clusterize_test.cc test/auxiliares_test.cc 

.PHONY: all build test clean dirs

all: dirs build test

build: dirs main.cc lib/tiempo.h point.h $(OBJS)
	g++ $(CFLAGS) -o build/main main.cc $(OBJS) -I.

test: dirs point.h test/test_runner.cc $(TESTS)
	g++ $(CFLAGS) -o build/tests test/test_runner.cc $(OBJS) $(TESTS) -I.

clean:
	rm -f build/* out/*

dirs:
	mkdir -p build out resources
