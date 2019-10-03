#include "node.h"
#include "linkedMesh.h"
#include <vector>

//81x4 para sudokus padrão
#define SUDOKUWIDTH 324

//retornam a prox. linha/coluna lidando com a caracteristica circular
//lida também com a coluna extra dos headers

//col à direita
int LinkedMesh::getRight(int i){return (i+1) % nCol;}
//col à esquerda
int LinkedMesh::getLeft(int i){
	if(i-1 < 0){
		return nCol-1;
	}else{
		return i-1;
	}
}
//linha acima
int LinkedMesh::getUp(int i){
	if(i-1 < 0){
		//não desconta 1 pois existe uma linha a mais para headers
		return nRow;
	}else{
		return i-1;
	}
}   
//linha abaixo
int LinkedMesh::getDown(int i){return (i+1) % (nRow+1);} 

LinkedMesh::LinkedMesh(){}

LinkedMesh::LinkedMesh(std::vector<bool*> ProbMat){
	// One extra row for list header nodes 
    // for each column
    nRow = ProbMat.size();
	nCol = SUDOKUWIDTH;


    for(int i = 0; i <= nRow; i++) 
    { 
        for(int j = 0; j < nCol; j++) 
        { 
            //"há um 1 nessa etapa da matriz" 
            if(ProbMat[i][j]) 
            { 
                int a, b; 
  
                // Atualizar a contagem de elementos na coluna do header de coluna
                if(i!=0){
                	Matrix[0][j].nodeCount += 1; 
                }
  
                // Associa o header de coluna ao campo de coluna
                Matrix[i][j].column = &Matrix[0][j]; 
  
                // coloca id de linha e coluna 
                Matrix[i][j].rowID = i; 
                Matrix[i][j].colID = j; 
  
                // Liga com os '1's vizinhos (considerando a "circularidade" da lista)
  
                // Left pointer 
                a = i; b = j; 
                do{ b = getLeft(b); } while(!ProbMat[a][b] && b != j); 
                Matrix[i][j].left = &Matrix[i][b]; 
  
                // Right pointer 
                a = i; b = j; 
                do { b = getRight(b); } while(!ProbMat[a][b] && b != j); 
                Matrix[i][j].right = &Matrix[i][b]; 
  
                // Up pointer 
                a = i; b = j; 
                do { a = getUp(a); } while(!ProbMat[a][b] && a != i); 
                Matrix[i][j].up = &Matrix[a][j]; 
  
                // Down pointer 
                a = i; b = j; 
                do { a = getDown(a); } while(!ProbMat[a][b] && a != i); 
                Matrix[i][j].down = &Matrix[a][j]; 
            } 
        }
    }

    // link header right pointer to column  
    // header of first column  
    header->right = &Matrix[0][0]; 
  
    // link header left pointer to column  
    // header of last column  
    header->left = &Matrix[0][nCol-1]; 
  
    Matrix[0][0].left = header; 
    Matrix[0][nCol-1].right = header; 
}

//Tira um node da lista
void LinkedMesh::cover(Node *targetNode) 
{ 
    Node *row, *rightNode; 
   
   	//header da coluna do nó 
    Node *colNode = targetNode->column; 
  
    // desliga a coluna da lista dos indexados
    colNode->left->right = colNode->right; 
    colNode->right->left = colNode->left; 
  
    // Move para baixo e remove todos os nodes que tiverem conexão (indo para a direita)
    for(row = colNode->down; row != colNode; row = row->down) 
    { 
        for(rightNode = row->right; rightNode != row; 
            rightNode = rightNode->right) 
        { 
            rightNode->up->down = rightNode->down; 
            rightNode->down->up = rightNode->up; 
  
            // atualiza nodecount do header
            Matrix[0][rightNode->colID].nodeCount -= 1; 
        } 
    } 
}

void LinkedMesh::uncover(Node *targetNode) 
{ 
    Node *rowNode, *leftNode; 
  
    // get the pointer to the header of column 
    // to which this node belong  
    Node *colNode = targetNode->column; 
  
    // Move down the column and link back 
    // each row by traversing left 
    for(rowNode = colNode->up; rowNode != colNode; rowNode = rowNode->up) 
    { 
        for(leftNode = rowNode->left; leftNode != rowNode; 
            leftNode = leftNode->left) 
        { 
            leftNode->up->down = leftNode; 
            leftNode->down->up = leftNode; 
  
            // after linking row node, increment the 
            // node count in column header 
            Matrix[0][leftNode->colID].nodeCount += 1; 
        } 
    } 
  
    // link the column header from it's neighbors 
    colNode->left->right = colNode; 
    colNode->right->left = colNode; 
} 