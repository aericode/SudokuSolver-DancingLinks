#include <iostream>
#include <vector>
#include "node.h"
#include "linkedMesh.h"


int main(){
	std::cout<<"inicializando Binário\n"<<std::endl;

	//UMA DAS LINHAS É PARA OS HEADERS, NÃO TEM SIGNIFICADO NA INSTANCIA
	int nRow = 7;//linhas no problema
	int nCol = 7;//colunas (opções)

	

	bool** binSim;

	binSim = new bool*[50];

	//NROW DEVE SER UM PONTO MAIOR DO QUE N (i<N)
	for (int i=0;i<50;i++){//linhas na matriz
		binSim[i]=new bool[50];
	}


	std::cout<<"Marcando headers\n"<<std::endl;
	for(int i=0; i<=nRow; i++) 
    { 
        for(int j=0; j<nCol; j++) 
        { 
            if(i == 0){
            	binSim[i][j] = true;
            }else{
            	binSim[i][j] = false;
            }
        } 
    } 



	LinkedMesh test(binSim);

	//LinkedMesh test(binSim);

	//test.search(0);
	//std::cout<<binSim[0][0];
}