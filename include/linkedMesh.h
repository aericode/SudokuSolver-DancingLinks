#ifndef LINKEDMESHH
#define LINKEDMESHH

#include "node.h"
#include <vector>

// implementado com base em https://bit.ly/2oHRcon

class LinkedMesh{
public:
	Node *header;
	//é uma node matrix
	Node Matrix[100][100];
	std::vector<Node*> solutions; 

	int nRow;
	int nCol;

	int getRight(int); 
	int getLeft(int);
	int getUp(int);
	int getDown(int);

	LinkedMesh();
	LinkedMesh(bool probMatrix[100][100]);

	void initialize(bool probMatrix[100][100]);
	void cover(Node *targetNode);
	void uncover(Node *targetNode);
	Node *getMinColumn();

	void printSolutions();
	void search(int);
};

#endif