#include <iostream>
#include <vector>
#include "node.h"
#include "linkedMesh.h"
#include <string>

//column = x row = y
void cellToBin(int row, int column, int value, int binPlace[]){
	//1 a 4 -> 0 a 3
	//facilitar as contas
	value=value-1;

	if(row>3||column>3||value>3){
		std::cout<<"invalid input in cell to binary conversion"<<std::endl;
		return;
	}

	/*
	xBlock = row/2;
	yBlock = column/2;

	Blockindex = 2*xBlock + yblock;
	*/

	int block = row + column/2;

	binPlace[0] =      (4*row    + column);
	binPlace[1] = 16 + (4*column + value);
	binPlace[2] = 32 + (4*row    + value);
	binPlace[3] = 48 + (4*block + value);

	return;
}

void sudokuToBin(std::string sudoku, bool problem[145][64]){
	int nRow = 144;//linhas no problema
	int nCol = 64;//colunas (opções)

	//locais da linha da matriz problema a serem marcados
	int binPlace[4];

	int currentRow = 1;

	int cellRow;
    int cellCol;
    int currentValue;

	if(sudoku.size()!=16){
		std::cout<<"invalid input size for 4x4 too short, 16 characters required"<<std::endl;
		return;
	}

	for(int i=0; i<=nRow; i++) 
    { 
        for(int j=0; j<nCol; j++) 
        { 
            if(i == 0){
            	problem[i][j] = true;
            }else{
            	problem[i][j] = false;
            }
        } 
    }

    for(int i = 0; i < sudoku.size();i++){
 	cellRow  = i/4;
    cellCol  = i%4;   	


    	if(sudoku[i] == '-'){
    		for(int j=0;j<4;j++){
    			currentValue = j;
    			cellToBin(cellRow,cellCol,currentValue,binPlace);

    			problem[currentRow][binPlace[0]]=true;
    			problem[currentRow][binPlace[1]]=true;
    			problem[currentRow][binPlace[2]]=true;
    			problem[currentRow][binPlace[3]]=true;

    			currentRow++;
    		}
    	}else{
    		currentValue = sudoku[i] - '0';
    		if(currentValue<1 || currentValue>4){
    			std::cout<<"valor fora do alcance (1-4)"<<std::endl;
    		}

			cellToBin(cellRow,cellCol,currentValue,binPlace);

			problem[currentRow][binPlace[0]]=true;
			problem[currentRow][binPlace[1]]=true;
			problem[currentRow][binPlace[2]]=true;
			problem[currentRow][binPlace[3]]=true;

			currentRow++;

    	}
    }

    


}

int main(){
	std::cout<<"inicializando Binário\n"<<std::endl;

	//UMA DAS LINHAS É PARA OS HEADERS, NÃO TEM SIGNIFICADO NA INSTANCIA
	int nRow = 144;//linhas no problema
	int nCol = 64;//colunas (opções)
	std::string sudoku;
	

	bool binSim[145][64];

	sudoku = "3-1--2-2-4-32-1-";

	int binPlace[4];

	cellToBin(0,0,2,binPlace);

	std::cout<<binPlace[0]<<' '<<binPlace[1]<<' '<<binPlace[2]<<' '<<binPlace[3]<<std::endl;

	/*
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
	*/

	/*
	for (int i=0;i<145;i++){
		for (int j=0;i<64;j++){
			if(binSim[i][j]){
				std::cout<<'1';
			}else{
				std::cout<<'0';
			}
		}
		std::cout<<std::endl;
	}
	*/

	/*
	sudokuToBin(sudoku,binSim);

    std::cout<<"inicializando linked mesh\n";

	LinkedMesh test(binSim);

	std::cout<<"linked mesh inicializada\n";

	test.search(0);
	*/
	
}