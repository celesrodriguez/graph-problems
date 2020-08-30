#include <iostream> 
#include <fstream> 

#include "vector"
#include "map"
#include "string"

#include "lib/tiempo.h"

#include "algorithm.h"
#include "point.h"
#include "edge.h"
#include "auxiliares.h"
#include "prim.h"
#include "kruskal.h"
#include "bellman.h"
#include "floyd.h"

#define PATH_COMPRESSION_ENABLED true
#define PATH_COMPRESSION_DISABLED false

using namespace std; 

void MeasureAlgorithm(string name, Algorithm* algorithm, string input, ofstream &output);

vector<Point> GetPoints(); 

void ArbitrageBellman();

void ArbitrageFloyd();


int main(int argc, char** argv) { 
	map<string, Algorithm*> algoritmos;
	algoritmos["prim"] = new Prim();
	algoritmos["kruskal"] = new Kruskal(PATH_COMPRESSION_DISABLED);
	algoritmos["kruskal-pc"] = new Kruskal(PATH_COMPRESSION_ENABLED);

	if ( argc == 1 ) {
		cout << "Se necesita pasar el algoritmo a usar como argumento.\nOpciones: prim, kruskal, kruskal-pc, bellman, floyd\n"; 
		return 1;
	} 
	string algoritmo = argv[1];

	if( algoritmo == "experimentos" ){ // Corro todos los algoritmos y mido el tiempo
		string input = argv[2];
		for(auto it = algoritmos.begin(); it != algoritmos.end(); ++it) {
			ofstream output("out/" + it->first + "_" + input);
			cout << "Running for: " << it->first << "...";
			MeasureAlgorithm(it->first, it->second, input, output);
			cout << " done\n";
			output.close();	
		}
	} else {
		if (algoritmo == "bellman"){
			cout << "\nIngrese los datos, siguiendo el formato planteado en el enunciado.\n";
			ArbitrageBellman();
		} else {
			if (algoritmo == "floyd"){
				cout << "\nIngrese los datos, siguiendo el formato planteado en el enunciado.\n";
				ArbitrageFloyd();
			} else {
				if ( algoritmos.count(algoritmo) == 0 ) {
					cout << "Algoritmo invalido.\nOpciones: prim, kruskal, kruskal-pc, bellman, floyd\n";
					return 1;
				}
				Algorithm* algorithm = algoritmos[algoritmo];
				cout << "\nIngrese los datos, siguiendo el formato planteado en el enunciado.\n";
				vector<Point> vertex = GetPoints();
				auto output = algorithm->Clusterize(vertex);
				aux::print_vector(output);
			}
		}	
	}
	return 0; 
} 

void MeasureAlgorithm(string name, Algorithm* algorithm, string input, ofstream &output){
	ifstream dataset("resources/" + input);	
	if( dataset.is_open() ){
		cin.rdbuf(dataset.rdbuf());
		while( dataset.peek() != EOF && !dataset.eof() ) {
			vector<Point> vertex = GetPoints();
			int n = vertex.size();
			unsigned long start, end;

			MEDIR_TIEMPO_START(start);
			auto sol = algorithm->Clusterize(vertex);
			MEDIR_TIEMPO_STOP(end);
			// Modificar esto para que haga output de algo util para los experimentos
			// output << name << "," << n << "," << sol.size()  << "," << (end-start) << "\n";
			aux::print_vector(sol, output, "\n");
		}
	}
	dataset.close();
}

void ArbitrageBellman(){
	int n;
    float currency;
    cin >> n; 
    vector<Edge> aristas;
    for (int i = 0; i < n; i++){
    	for (int j = 0; j < n; j++){
    		cin >> currency; 
    		aristas.push_back(Edge(i,j,currency));
    	}
    }
    auto output = Arbitrage(aristas, n, 0);
    aux::print_vector(output);
}

void ArbitrageFloyd(){
	int n;
    float currency;
    cin >> n; 
    vector<vector<float> > matriz(n, vector<float>(n, 0));

    for (int i = 0; i < n; i++){
    	for (int j = 0; j < n; j++){
    		cin >> currency; 
    		matriz[i][j] = currency;
    	}
    }

    auto output = Arbitrage(matriz, n);
    aux::print_vector(output);
}

vector<Point> GetPoints() {
	int size;
	cin >> size;

	vector<Point> points;
	for(int i = 0; i < size; ++i){
		float x, y;
		cin >> x;
		cin >> y;
		points.push_back(Point(x, y));
	}
	return points;
}
