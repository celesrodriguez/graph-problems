#include "test/arbitraje_test.h"

void hayArbitraje(std::string input, std::vector<int> ciclo){
	if (ciclo.size() != 0){
		std::ifstream dataset("resources/" + input);
		float dinero = 1;
		int n;
		dataset >> n;
		std::vector<std::vector<float> > matriz(n, std::vector<float>(n, 0));
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				dataset >> matriz[i][j];
			}
		}
		for (unsigned int i = 0; i < ciclo.size()-1; i++){
			dinero*= matriz[ciclo[i]][ciclo[i+1]];
		}
		if (dinero > 1){
			std::cout << "El ciclo es valido" << std::endl;
		}else{
			std::cout << "El ciclo NO es valido" << std::endl;
		} 
		dataset.close();		
	}
	
}