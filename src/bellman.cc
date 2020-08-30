#include "bellman.h"
#define null 0

#include <algorithm>
using namespace std;
float INF = 0;

vector<int> Arbitrage(vector<Edge> &edges, int n, int inicial){
	INF = 0;
	/* Actualizo los pesos de los ejes para aplicar Bellman-ford */
	UpdateWeights(edges);

	/* Ejecuto Bellman-Ford buscando ciclos negativos */
	return BellmanFordOptimizado(edges, n, inicial);
}

vector<int> BellmanFord(vector<Edge> &edges, int n, int inicial){
	
	/* Inicializo los vectores de predecesores y distancias, distancia y pred el nodo 0 es 0 */
	vector<int> pred(n, null);
	vector<float> distance(n, INF);
	vector<int> res;
	res.reserve(n);

	distance[inicial] = 0;

	for (int i = 1; i < n; i++){

		for(Edge &e : edges){

			if(distance[e.u] > distance[e.v] + e.distance){
				distance[e.u] = distance[e.v] + e.distance;
				pred[e.u] = e.v;
			}

		}

	}

	for(Edge &e : edges){

			if(distance[e.u] > distance[e.v] + e.distance){
				/* Sigue mejorando, es decir, encontre un ciclo negativo */
				res.push_back(e.u);
				int v = e.v;
				vector<int>::iterator it; 

				do{
					res.push_back(v);
					it = isRepeated(res);
					v = pred[v];				
				} while (it == res.end());

				res.erase(res.begin(), it);
				reverse(res.begin(),res.end());

				return res;
			}

	}

	/* No encontre ciclo negativo, devuelvo vector vacio */
	return res;
}	

vector<int> BellmanFordOptimizado(vector<Edge> &edges, int n, int inicial){
	
	/* Inicializo los vectores de predecesores y distancias, distancia y pred el nodo 0 es 0 */
	vector<int> pred(n, null);
	vector<float> distance(n, INF);
	vector<int> res;
	res.reserve(n);
	distance[inicial] = 0;

	bool sigueMejorando = true;
	for (int i = 1; i < n && sigueMejorando; i++){
		sigueMejorando = false;
		for(Edge &e : edges){

			if(distance[e.u] > distance[e.v] + e.distance){
				distance[e.u] = distance[e.v] + e.distance;
				pred[e.u] = e.v;
				sigueMejorando = true;
			}
			
		}

	}

	if (!sigueMejorando)	return res;
	

	for(Edge &e : edges){
			
			if(distance[e.u] > distance[e.v] + e.distance){
				/* Sigue mejorando, es decir, encontre un ciclo negativo */
				res.push_back(e.u);
				int v = e.v;
				vector<int>::iterator it; 

				do{
					res.push_back(v);
					it = isRepeated(res);
					v = pred[v];				
				} while (it == res.end());

				res.erase(res.begin(), it);
				reverse(res.begin(),res.end());

				return res;
			}

	}
	
	/* No encontre ciclo negativo, devuelvo vector vacio */
	return res;
}	

void UpdateWeights(vector<Edge> &edges){

	for(Edge &e : edges){
		e.distance = -log10f(e.distance);
		if (e.distance > INF) INF = e.distance;
	}

}
void UpdateWeightsE(vector<Edge> &edges){

	for(Edge &e : edges){
		e.distance = -logf(e.distance);
		if (e.distance > INF) INF = e.distance;
	}
	
}
void UpdateWeights2(vector<Edge> &edges){

	for(Edge &e : edges){
		e.distance = -log2f(e.distance);
		if (e.distance > INF) INF = e.distance;
	}
	
}

vector<int> ArbitrageLogs(vector<Edge> &edges, int n, int inicial, int log){
	INF = 0;
	if (log == 10){
		UpdateWeights(edges);
	}else{
		if (log == 2){
			UpdateWeights2(edges);
		}else{
			UpdateWeightsE(edges);
		}
	}
	
	return BellmanFordOptimizado(edges,n,inicial);
}


vector<int>::iterator isRepeated(vector<int> &res){
	/* Chequea si el ultimo elemento ya habia sido previamente agregado */
	int last = res[res.size() - 1 ];
	for (vector<int>::iterator it = res.begin() ; it != res.end() - 1; ++it){
		if (*it == last) return it;
	}
	return res.end();
}






