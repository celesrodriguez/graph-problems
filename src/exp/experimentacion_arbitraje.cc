#include "exp/experimentacion_arbitraje.h"
#define ITER 10
#define CANT_EXP_CICLOS 5
#define CANT_EXP 5
#define NO_ARBITRAGE 5
#define BELL true
#define FLOYD false
using namespace std;

double MeasureAlgorithm(bool bellman, int n, int inicial, vector<vector<float> > &matriz){
	using namespace std;
	vector<double> total;
	total.reserve(ITER);
	if (bellman){
		for (int i = 0; i < ITER; i++){
			vector<Edge> aristas = {};
			for (int i = 0; i < n; i++){
				for (int j = 0; j < n; j++){
				aristas.push_back(Edge(i,j,matriz[i][j]));
				}
			}
			auto start = chrono::steady_clock::now();
			Arbitrage(aristas, n, inicial);
			auto end = chrono::steady_clock::now();
			auto dif = end - start;
			
			total.push_back(chrono::duration <double, milli> (end - start).count());
		}
	}else{
		vector<vector<float> > matrix(n, vector<float>(n, 0));
		for (int i = 0; i < ITER; i++){
			for (int i = 0; i < n; i++){
				for (int j = 0; j < n; j++){
					matrix[i][j] = matriz[i][j];
				}
			}	
			
			auto start = chrono::steady_clock::now();
			Arbitrage(matrix, n);
			auto end = chrono::steady_clock::now();
			auto dif = end - start;
			
			total.push_back(chrono::duration <double, milli> (end - start).count());
		}
	}
	
	return getMedian(total);
}

void crearInstanciaCiclos(int n, int longitud, string archivo){
	using namespace std;
	ofstream output("resources/" + archivo);
	/* Inicializa la matriz con un valor muy cercano a cero */
    vector<vector<float> > matriz(n, vector<float>(n, 1));
    crearCiclo(n, longitud, n, matriz);
    /* Guarda la instancia en el archivo */
    output << n << endl;
    for (int i = 0; i < n; i++){
    	for (int j = 0; j < n; j++){
    		output << matriz[i][j] << endl;
    	}
    }
    output.close();
}
void crearCiclo(int n, int longitud, int hasta, vector<vector<float> > &matriz){
	using namespace std;
	//float casiCero = pow(10, -33);
	float casiCero = 0.1;
	/* Inicializa la matriz con un valor muy cercano a cero */
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matriz[i][j] = casiCero;

	/* Pone la diagonal con peso = 1 */
	for (int i = 0; i < n; i++) matriz[i][i] = 1;

	/* Crea un ciclo con ganancia de tamaño longitud de indices random */
    vector<int> ciclo;
    int i,j,inicial;
    inicial = rand() % (hasta);
    i = inicial;
    longitud-=2;
    ciclo.push_back(inicial);
    do{
    	j = rand() % (hasta);
   		while (find(ciclo.begin(), ciclo.end(), j) != ciclo.end()){
    			j = rand() % (hasta);
    	}
    	matriz[i][j] = 1.00000000001;
    	i = j;
    	ciclo.push_back(j);
    	longitud--;
    } while (longitud > 0);
    matriz[j][inicial] = 2.0;
}

void experimentoCiclos(vector<int> cantNodos, vector<int> longCiclos, string output){
	using namespace std;
	ofstream resultados;
	resultados.open("out/" + output);
	resultados << "longCiclo";
	for (unsigned int i = 0; i < cantNodos.size(); i++){
		resultados << "," << "n = " << cantNodos[i] << " (B)" << "," << "n = " << cantNodos[i] << " (F)";
	}
	resultados << endl;

	for (unsigned int i = 0; i < longCiclos.size(); i++){
		
		resultados << longCiclos[i];

		for (unsigned int j = 0; j < cantNodos.size(); j++){
			if (cantNodos[j] + 1 >= longCiclos[i]){
				vector<double> tiemposB, tiemposF;
				tiemposB.reserve(CANT_EXP_CICLOS);
				tiemposF.reserve(CANT_EXP_CICLOS);

				vector<vector<float> > matriz(cantNodos[j], vector<float>(cantNodos[j], 0));
				for (int it = 0; it < CANT_EXP_CICLOS; it++){
				/* Prepara instancias para la experimentacion */
					crearCiclo(cantNodos[j], longCiclos[i], cantNodos[j], matriz);	

				/* Mide tiempos para Bellman y Floyd */
					tiemposB.push_back(MeasureAlgorithm(BELL, cantNodos[j], 0, matriz));
					tiemposF.push_back(MeasureAlgorithm(FLOYD, cantNodos[j], 0, matriz));
				}

				resultados << ",";
				resultados << getMedian(tiemposB);
				resultados << ",";
				resultados << getMedian(tiemposF);	
			}else{
				resultados << ",";
				resultados << 0;
				resultados << ",";
				resultados << 0;	
			}
		}
		resultados << endl;
	}
	resultados.close();
}


void experimentoFloydvsBellman(int n, string output){
	ofstream resultados;
	resultados.open("out/" + output);
	resultados << "n" << "," << "Bellman"  << "," << "Floyd" << endl;

	for (int i = 10; i <= n; i+=5){
		resultados << i;
		vector<vector<float> > matriz(i, vector<float>(i, 1));
		
		/* Crea instancias de i nodos con un ciclo de i/4 nodos con los primeros i/4 nodos*/
		crearCiclo(i, i/4, i/4, matriz);
			/* Mide tiempos para Bellman y Floyd */
		float bell_tiempo = MeasureAlgorithm(BELL, i, 0, matriz);
		float floyd_tiempo = MeasureAlgorithm(FLOYD, i, 0, matriz);
		
		resultados << ",";
		resultados << bell_tiempo;
		resultados << ",";
		resultados << floyd_tiempo;	
		
		resultados << endl;
	}
	resultados.close();
}

void experimentoSinArbitraje(int n, string output){
	ofstream resultados;
	resultados.open("out/" + output);
	resultados << "n" << "," << "Bellman"  << "," << "Floyd" << endl;

	for (int i = 10; i < n; i+=5){
		resultados << i;
		vector<double> tiemposB, tiemposF;
		tiemposB.reserve(NO_ARBITRAGE);
		tiemposF.reserve(NO_ARBITRAGE);
		vector<vector<float> > matriz(i, vector<float>(i, 1));
		for (int it = 0; it < NO_ARBITRAGE; it++){
			/* Crea instancias de i nodos con pesos en las aristas entre 0.3 y 1.0, por lo tanto, no hay arbitraje*/
			float currency;
			for (int f = 0; f < i; f++){
				for (int c = 0; c < i; c++){
					if (f != c){
						currency = 0.3 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(0.7)));
						matriz[f][c] = currency; 
					}			
				}
			}	
			/* Mide tiempos para Bellman y Floyd */
			tiemposB.push_back(MeasureAlgorithm(BELL, i, 0, matriz));
			tiemposF.push_back(MeasureAlgorithm(FLOYD, i, 0, matriz));
		}
		resultados << ",";
		resultados << getMedian(tiemposB);
		resultados << ",";
		resultados << getMedian(tiemposF);	
		
		resultados << endl;
	}
	resultados.close();

}


void experimentoGenerico(int n, string output){
	ofstream resultados;
	resultados.open("out/" + output);
	resultados << "n" << "," << "Bellman"  << "," << "Floyd" << endl;

	for (int i = 10; i <= n; i+=5){
		resultados << i;
		vector<double> tiemposB, tiemposF;
		tiemposB.reserve(CANT_EXP + CANT_EXP_CICLOS + NO_ARBITRAGE);
		tiemposF.reserve(CANT_EXP + CANT_EXP_CICLOS + NO_ARBITRAGE);

		vector<vector<float> > matriz(i, vector<float>(i, 1));

		for (int it = 0; it < NO_ARBITRAGE; it++){
			/* Mide tiempos para Bellman y Floyd en instancias donde no hay arbitraje*/
			tiemposB.push_back(MeasureAlgorithm(BELL, i, 0, matriz));
			tiemposF.push_back(MeasureAlgorithm(FLOYD, i, 0, matriz));
		}

		for (int it = 0; it < CANT_EXP_CICLOS; it++){
			/* Crea instancias de i nodos con ciclos random de tamano 3 hasta tamano i-3 */
			crearCiclo(i, (rand() % (i-2))+3, i, matriz);	
			/* Mide tiempos para Bellman y Floyd */
			tiemposB.push_back(MeasureAlgorithm(BELL, i, 0, matriz));
			tiemposF.push_back(MeasureAlgorithm(FLOYD, i, 0, matriz));
		}

		for (int it = 0; it < CANT_EXP; it++){
			/* Crea instancias de i nodos con pesos en las aristas entre 0.08 y 1.08, puede haber arbitraje o no*/
			float currency;
			for (int f = 0; f < i; f++){
				for (int c = 0; c < i; c++){
					if (f != c){
						currency = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
						matriz[f][c] = currency+0.07; 
					}			
				}
			}	
			/* Mide tiempos para Bellman y Floyd */
			tiemposB.push_back(MeasureAlgorithm(BELL, i, 0, matriz));
			tiemposF.push_back(MeasureAlgorithm(FLOYD, i, 0, matriz));
		}

		resultados << ",";
		resultados << getMedian(tiemposB);
		resultados << ",";
		resultados << getMedian(tiemposF);	
		
		resultados << endl;
	}
	resultados.close();
}

void experimentoLogs2(int n, string output){
	ofstream resultados;
	resultados.open("out/" + output);
	resultados << "n" << "," << "Bellman log2"  << "," << "Bellman log10" << "," << "Bellman loge" << endl;

	for (int i = 10; i <= n; i+=5){
		resultados << i;
		vector<vector<float> > matriz(i, vector<float>(i, 1));
		/* Mide tiempos para Bellman*/
		float tiempo2 = MeasureAlgorithm(i, 0, matriz, 2);
		float tiempo10 = MeasureAlgorithm(i, 0, matriz, 10);
		float tiempoE = MeasureAlgorithm(i, 0, matriz, 0);
		
		resultados << ",";
		resultados << tiempo2;
		resultados << ",";
		resultados << tiempo10;	
		resultados << ",";
		resultados << tiempoE;	
		
		resultados << endl;
	}
	resultados.close();
}

void experimentoLogs(int n, string output){
	ofstream resultados;
	resultados.open("out/" + output);
	resultados << "n" << "," << "Bellman log2"  << "," << "Bellman log10" << "," << "Bellman loge" << endl;

	for (int i = 10; i <= n; i+=5){
		resultados << i;
		vector<double> tiempos2, tiempos10, tiemposE;
		tiempos2.reserve(CANT_EXP_CICLOS+CANT_EXP);
		tiempos10.reserve(CANT_EXP_CICLOS+CANT_EXP);
		tiemposE.reserve(CANT_EXP_CICLOS+CANT_EXP);

		vector<vector<float> > matriz(i, vector<float>(i, 1));
		for (int it = 0; it < CANT_EXP_CICLOS; it++){
			/* Crea instancias de i nodos con ciclos random de tamano 3 hasta tamano i-3 */
			crearCiclo(i, (rand() % (i-2))+3, i, matriz);	
			/* Mide tiempos para Bellman y Floyd */
			tiempos2.push_back(MeasureAlgorithm(i, 0, matriz, 2));
			tiempos10.push_back(MeasureAlgorithm(i, 0, matriz, 10));
			tiemposE.push_back(MeasureAlgorithm(i, 0, matriz, 0));
			
		}
	
		for (int it = 0; it < CANT_EXP; it++){
			/* Crea instancias de i nodos con pesos en las aristas entre 0.08 y 1.08, puede haber arbitraje o no*/
			float currency;
			for (int f = 0; f < i; f++){
				for (int c = 0; c < i; c++){
					if (f != c){
						currency = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
						matriz[f][c] = currency+0.07; 
					}			
				}
			}	
			/* Mide tiempos para Bellman y Floyd */
			tiempos2.push_back(MeasureAlgorithm(i, 0, matriz, 2));
			tiempos10.push_back(MeasureAlgorithm(i, 0, matriz, 10));
			tiemposE.push_back(MeasureAlgorithm(i, 0, matriz, 0));
		}

		resultados << ",";
		resultados << getMedian(tiempos2);
		resultados << ",";
		resultados << getMedian(tiempos10);	
		resultados << ",";
		resultados << getMedian(tiemposE);	
		
		resultados << endl;
	}
	resultados.close();
}

double MeasureAlgorithm(int n, int inicial, vector<vector<float> > &matriz, int log){
	vector<double> total;
	total.reserve(ITER);
	for (int i = 0; i < ITER; i++){
		vector<Edge> aristas = {};
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				aristas.push_back(Edge(i,j,matriz[i][j]));
			}
		}
		auto start = chrono::steady_clock::now();
		ArbitrageLogs(aristas, n, inicial, log);
		auto end = chrono::steady_clock::now();
		auto dif = end - start;
		total.push_back(chrono::duration <double, milli> (end - start).count());
	}
	
	return getMedian(total);
}


double getMedian(vector<double> &vec){
	sort(vec.begin(), vec.end());

	if (vec.size() % 2 == 0){
		return (vec[vec.size() / 2 - 1] + vec[vec.size() / 2])/2;
	}else{
		return vec[vec.size() / 2];
	}

}






