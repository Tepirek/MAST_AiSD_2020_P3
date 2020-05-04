#pragma once
#include "GeneralTree.h"

class HashMap {
	unsigned int** table;
	GeneralTree* firstTree;
	GeneralTree* secondTree;
	unsigned int firstTreeSize;
	unsigned int secondTreeSize;
	Node** firstTreeValues;
	Node** secondTreeValues;
	unsigned int solution;
	unsigned int getValueAt(unsigned int a, unsigned int b);
	unsigned int maxOfThree(unsigned int a, unsigned int b, unsigned int c);
	unsigned int compareChildrenWithNode1(Node* a, Node* b);
	unsigned int compareChildrenWithNode2(Node* a, Node* b);
	unsigned int compareChildren(Node* a, Node* b);
public:
	HashMap(GeneralTree* firstTree, GeneralTree* secondTree);
	~HashMap();
	unsigned int getSolution();
	void handleLeaves();
	void handleInnerNodes();
	void printTable();
};