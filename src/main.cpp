#include <iostream>
#include <vector>
#include "node.h"
#include "linkedMesh.h"
#include <string>

//column = x row = y
void cellToBin(int row, int column, int value, int binPlace[]){
	//1 a 4 -> 0 a 3
	//facilitar as contas

	if(row>3||column>3||value>3){
		std::cout<<"invalid input in cell to binary conversion"<<std::endl;
		return;
	}

	//usando divisão inteira para dar "floor" no row
	int block = ((row/2)*2 + column/2);


	binPlace[0] =      (4*row    + column);
	binPlace[1] = 16 + (4*column + value);
	binPlace[2] = 32 + (4*row    + value);
	binPlace[3] = 48 + (4*block  + value);

	return;
}

void sudokuToBin(std::string sudoku, bool problem[145][64], int nRow, int nCol){



	//locais da linha da matriz problema a serem marcados
	int binPlace[4];

	int currentRow = 1;

	int cellRow;
    int cellCol;
    int currentValue;

	if(sudoku.size()!=16){
		std::cout<<"invalid input size for 4x4 too short, 16 characters required"<<std::endl;
		std::cout<<"current size: "<<sudoku.size()<<std::endl;

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
    		//reduzindo o range de (1-4) para (0-3)
    		currentValue = currentValue - 1;
			cellToBin(cellRow,cellCol,currentValue,binPlace);

			problem[currentRow][binPlace[0]]=true;
			problem[currentRow][binPlace[1]]=true;
			problem[currentRow][binPlace[2]]=true;
			problem[currentRow][binPlace[3]]=true;

			currentRow++;

    	}
    }

    


}

void testfill(bool problem[145][64]){
	for(int i=0;i<3;i++){
		problem[0][i]= true;
	}


}

void dummyFill(bool problem[145][64]){
	for(int i=0;i<64;i++){
		if(i%2==0)problem[1][i]= true;
	}

	for(int i=0;i<64;i++){
		if(i%2==1)problem[2][i]= true;
	}	
}

int* binaryToSudoku(int rowID, bool problem[145][64]){
	int* fillInfo =  new int[3];

	int rawCoord;
	int coordX;
	int coordY;
	int value;

	for(int i=0;i<16;i++){
		if(problem[rowID][i]){
			rawCoord = i;
			break;
		}
	}

	coordX = rawCoord%4;
	coordY = rawCoord/4;

	int rawValue;

	for(int i = 16;i<32;i++){
		if(problem[rowID][i]){
			rawValue = i;
			break;
		}
	}

	value = rawValue%4;

	fillInfo[0] = coordX;
	fillInfo[1] = coordY;
	fillInfo[2] = value;

	return fillInfo;
}

std::string stringifyResult(int result[16], bool problem[145][64]){
	std::string stringified;
	int* locvalue = new int(3);
	int finalResult[16];
	int solutionIndex;
	int placeValue;


	for(int i=0;i<16;i++){
		locvalue = binaryToSudoku(result[i],problem);

		//converte de x/y para uma linha reta
		solutionIndex = locvalue[1]*4 + locvalue[0];

		//volta o range de 0-3 para 1-4
		placeValue = locvalue[2] + 1;
			
		finalResult[solutionIndex] =  placeValue;

	}

	for(int i=0;i<16;i++){
		stringified += (char)(finalResult[i]+'0');
	}

	return stringified;

}



int main(){
	int solutionRows[16];
	solutionRows[15] = -1;
	int binPlace[4];

	//UMA DAS LINHAS É PARA OS HEADERS, NÃO TEM SIGNIFICADO NA INSTANCIA
	int nRow = 144;//linhas no problema
	int nCol = 64;//colunas (opções)
	std::string sudoku;

	bool binSim[145][64];

	sudoku = "---3-1-442311342";
	std::cout<<"puzzle:   " <<sudoku<<std::endl;


	sudokuToBin(sudoku,binSim,144,64);

	LinkedMesh test(binSim);

	test.search(0,solutionRows);

	if(solutionRows[15]!=-1){
		std::cout<<"resposta: ";
		std::cout<<stringifyResult(solutionRows, binSim)<<std::endl;
	}else{
		std::cout<<"não foram encontradas respostas para o puzzle"<<std::endl;
	}

	
}