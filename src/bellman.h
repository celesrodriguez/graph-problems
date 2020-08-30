#ifndef BELLMAN_H_
#define BELLMAN_H_

#include <vector>
#include <iostream>
#include <math.h>
#include "edge.h"

std::vector<int> Arbitrage(std::vector<Edge> &edges, int n, int inicial);
std::vector<int> ArbitrageLogs(std::vector<Edge> &edges, int n, int inicial, int log);

std::vector<int> BellmanFord(std::vector<Edge> &edges, int n, int inicial);
std::vector<int> BellmanFordOptimizado(std::vector<Edge> &edges, int n, int inicial);

void UpdateWeights(std::vector<Edge> &edges);
void UpdateWeights2(std::vector<Edge> &edges);
void UpdateWeightsE(std::vector<Edge> &edges);

std::vector<int>::iterator isRepeated(std::vector<int> &res);

#endif