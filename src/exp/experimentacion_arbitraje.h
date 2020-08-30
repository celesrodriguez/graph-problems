#ifndef EXP_ARBITRAJE_H_
#define EXP_ARBITRAJE_H_

#include <iostream> 
#include <fstream> 

#include "vector"
#include "string"
#include "lib/tiempo.h"
#include <math.h>
#include "edge.h"
#include "auxiliares.h"
#include "bellman.h"
#include "floyd.h"

double MeasureAlgorithm(bool bellman, int n, int inicial, std::vector<std::vector<float> > &matriz);
void crearInstanciaCiclos(int n, int longitud, std::string archivo);
void experimentoCiclos(std::vector<int> cantNodos, std::vector<int> longCiclos, std::string output);
void experimentoGenerico(int n, std::string output);
void experimentoSinArbitraje(int n, std::string output);
void experimentoFloydvsBellman(int n, std::string output);
void experimentoLogs2(int n, std::string output);
double getMedian(std::vector<double> &vec);
void crearCiclo(int n, int longitud, int hasta, std::vector<std::vector<float> > &matriz);
std::vector<int> ArbitrageLogs(std::vector<Edge> &edges, int n, int inicial, int log);
void experimentoLogs(int n, std::string output);
double MeasureAlgorithm(int n, int inicial, std::vector<std::vector<float> > &matriz, int log);

#endif
