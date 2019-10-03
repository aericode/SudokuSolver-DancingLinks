#ifndef LINKEDMESHH
#define LINKEDMESHH

#include "node.h"
#include <vector>

// implementado com base em https://bit.ly/2oHRcon

class LinkedMesh{
public:
	Node *header;
	//é uma node matrix
	Node **Matrix;
	std::vector<Node*> solutions; 

	int nRow;
	int nCol;

	int getRight(int); 
	int getLeft(int);
	int getUp(int);
	int getDown(int);

	LinkedMesh();
	LinkedMesh(bool**);

	void initialize(bool**);
	void cover(Node *targetNode);
	void uncover(Node *targetNode);
	Node *getMinColumn();

	void printSolutions();
	void search(int);
};

#endif