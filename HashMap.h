#pragma once
#include "GeneralTree.h"

class HashMap {
	short** table;
	GeneralTree* firstTree;
	GeneralTree* secondTree;
	short firstTreeSize;
	short secondTreeSize;
	Node** firstTreeValues;
	Node** secondTreeValues;
	short solution;
	short getValueAt(short a, short b) const;
	static short maxOfThree(short a, short b, short c);
	short compareChildrenWithNode1(Node* a, Node* b) const;
	short compareChildrenWithNode2(Node* a, Node* b) const;
	short compareChildren(Node* a, Node* b) const;
public:
	HashMap(GeneralTree* firstTree, GeneralTree* secondTree);
	~HashMap();
	short getSolution() const;
	void handleLeaves() const;
	void handleInnerNodes();
};