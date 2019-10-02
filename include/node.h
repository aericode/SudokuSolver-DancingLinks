#ifndef NODEH
#define NODEH

class Node{
public:
	Node *left; 
    Node *right; 
    Node *up; 
    Node *down; 
    Node *column; 
    int rowID; 
    int colID; 
    int nodeCount;

    Node();
};


#endif