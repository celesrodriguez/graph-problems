#include "floyd.h"
using namespace std;

vector<int> Arbitrage(vector<vector<float> > &matrix, int n){
	vector<int> res;
	vector<vector<float> > distance(n, vector<float>(n, 0));
	vector<vector<int> > next(n, vector<int>(n, 0));

	/* Inicializo la matriz de siguientes, como el grafo es completo, siempre es j*/
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			next[i][j] = j;
		}
	}

	/* Inicializo la matriz de distancias con los pesos actualizados*/
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			distance[i][j] = -log10f(matrix[i][j]);
		}
	}

	for(int k = 0; k < n; k++){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){

				if (distance[i][j] > distance[i][k] + distance[k][j]){
					distance[i][j] = distance[i][k] + distance[k][j];
					next[i][j] = next[i][k];
				}

			}
			if (distance[i][i] < 0 ){
				/* Encontre ciclo negativo, empieza y termina en i */

				int k = next[i][i];
				res.push_back(i);
				
				while (k != i){
					res.push_back(k);
					k = next[k][i];
				}
				res.push_back(i);
				
				return res;

			}
		}
	}

	return res;
}








