#include <iostream>
#include <vector>
#include "node.h"
#include "linkedMesh.h"
#include <string>
#include <fstream>
#include <chrono>

//144 = 9x16 maior número de linhas que pode ser gerada por um sudoku 4x4 convertido
#define NROW 144
//explicado logo abaixo
#define NCOL 64

//Escolhe 4 locais entre 64 para representar, linha, coluna e valor (do sudoku original)
//De 0  a 15: 4xLinha  + Coluna = num. da celula
//De 16 a 31: 4xColuna + Valor  = "já tem esse valor na coluna"
//De 31 a 47: 4xLinha  + Valor  = "já tem esse valor na linha"
//De 47 a 63: 4xBloco  + Valor  = "já tem esse valor no bloco"
//Marca 1 em cada um desses intervalos, isso permite resolver por cover-set
//binPlace que vai carregar esses valores
void cellToBin(int row, int column, int value, int binPlace[]){
	//column = x row = y
	//assume value entre 0 e 3.

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

//Utiliza a função CellToBin para converter um sudoku em uma matriz binária
//Cada "dica" (espaço preenchido no puzzle original) gera uma linha
//Cada espaço em branco gera uma linha para cada valor que poderia assumir
//Se for um sudoku 4x4 gera 4 linhas, 9x9 gera 9, 16x16 gera 16, e assim por diante
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


//Traduz de volta a linha indicada por rowID para uma tripla (coluna - linha - valor)
//Usa-se essa função quando já tenho uma cobertura exata.
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

//O array Result contém as LINHAS da matriz binária que resultarão em um coverset
//Traduzindo elas e colocando todas em um array, temos a resposta do sudoku
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
		//convertendo int pra char
		stringified += (char)(finalResult[i]+'0');
	}

	return stringified;

}


//Pega puzzles e respostas do CSV na pasta input
void sampleFromFile
	(std::vector<std::string> &puzzle_list,
	 std::vector<std::string> &answer_list){

	std::string line;
	std::string puzzle;
	std::string answer;

	int i =0;

	std::ifstream file ("./input/sudoku.csv");
	
	while (file && getline(file, line)){

		puzzle = line.substr(0,16);
		answer = line.substr(17,16);


		puzzle_list.push_back(puzzle);
		answer_list.push_back(answer);

	}

}

int main(){
	//pega os puzzles e respostas de uma lista externa
	std::vector<std::string> puzzle_list;
	std::vector<std::string> answer_list;
	sampleFromFile(puzzle_list, answer_list);
	int puzzleCount = puzzle_list.size()-1;


	//quais listas da matriz binária contém a solução
	int solutionRows[16];

	//marcador para indicar que nenhuma solução foi achada
	solutionRows[15] = -1;

	//nRow indica o numero maximo de linhas em um puzzle
	//as operações são feitas usando o maximo +1, a linha 0 indexa headers
	bool binSim[NROW+1][NCOL];

	int chosenPuzzleID;
	//string na forma 3--2-1--23-4--41 contendo o sudoku 4x4 a ser resolvido
	std::string sudoku;

	//resposta do algoritmo
	std::string outputAnswer;

	std::cout << "selecione um puzzle (0-"<<puzzleCount<<')'<<std::endl;
	std::cin  >> chosenPuzzleID;

	if(chosenPuzzleID>puzzleCount){
		std::cout<<"não há puzzle com esse ID na lista"<<std::endl;
		return 0;
	}

	sudoku = puzzle_list.at(chosenPuzzleID);
	std::cout<<"puzzle:   " <<sudoku<<std::endl;

	//timers
	auto begin = std::chrono::high_resolution_clock::now();

	//traduz o sudoku para binário
	sudokuToBin(sudoku,binSim,NROW,NCOL);
	//transforma o binário em linkedlists
	LinkedMesh test(binSim);
	//aplica o algoritmo X de knuth nas linked lists
	test.search(solutionRows);

	//timers
	auto end = std::chrono::high_resolution_clock::now();    
	auto dur = end - begin;
	auto ms = std::chrono::duration_cast<std::chrono::microseconds >(dur).count();

	//checa se o puzzle foi resolvido antes de acessar os valores da lista
	if(solutionRows[15]!=-1){
		//traduz de volta para a forma de sudoku
		outputAnswer = stringifyResult(solutionRows, binSim);
		std::cout<<"resposta: "<<outputAnswer<<std::endl;

		if(outputAnswer==answer_list[chosenPuzzleID]){
			std::cout<<"a resposta proposta coincide com a do gabarito"<<std::endl;
		}else{
			std::cout<<"a resposta proposta não coincide com a do gabarito"<<std::endl;
			std::cout<<"resposta do gabarito: "<<answer_list.at(chosenPuzzleID);
		}
	}else{
		std::cout<<"não foram encontradas respostas para o puzzle"<<std::endl;
	}

	std::cout<<"tempo de resolução: "<<(int)ms<<" micro-segundos"<<std::endl;

	return 0;
}