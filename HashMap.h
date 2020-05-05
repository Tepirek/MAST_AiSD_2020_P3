#pragma once
#include "GeneralTree.h"

class HashMap {
	int** table;
	GeneralTree* firstTree;
	GeneralTree* secondTree;
	int firstTreeSize;
	int secondTreeSize;
	Node** firstTreeValues;
	Node** secondTreeValues;
	int solution;
	int getValueAt(int a, int b) const;
	static int maxOfThree(int a, int b, int c);
	int compareChildrenWithNode1(Node* a, Node* b) const;
	int compareChildrenWithNode2(Node* a, Node* b) const;
	int compareChildren(Node* a, Node* b) const;
public:
	HashMap(GeneralTree* firstTree, GeneralTree* secondTree);
	~HashMap();
	int getSolution() const;
	void handleLeaves() const;
	void handleInnerNodes();
};