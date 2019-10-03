#include <iostream>
#include <vector>
#include "node.h"
#include "linkedMesh.h"


int main(){
	std::cout<<"inicializando Binário\n"<<std::endl;

	//UMA DAS LINHAS É PARA OS HEADERS, NÃO TEM SIGNIFICADO NA INSTANCIA
	int nRow = 7;//linhas no problema
	int nCol = 7;//colunas (opções)

	

	bool binSim[100][50];



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

    binSim[1][0] = true; binSim[1][3] = true; 
    binSim[1][6] = true; binSim[2][0] = true; 
    binSim[2][3] = true; binSim[3][3] = true; 
    binSim[3][4] = true; binSim[3][6] = true; 
    binSim[4][2] = true; binSim[4][4] = true; 
    binSim[4][5] = true; binSim[5][1] = true; 
    binSim[5][2] = true; binSim[5][5] = true; 
    binSim[5][6] = true; binSim[6][1] = true; 
    binSim[6][6] = true; binSim[7][0] = true; 
    binSim[7][3] = true; 



	LinkedMesh test(binSim);


	//test.search(0);

	char a;
	std::cin>>a;
	//std::cout<<binSim[0][0];
}