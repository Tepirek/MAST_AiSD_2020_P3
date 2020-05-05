#pragma once
#include "Node.h"

class GeneralTree {
	Node* root;
	Node** leaves;
	Node** innerNodes;
	short amountOfLeaves;
	short amountOfInnerNodes;
	char* input;
public:
	GeneralTree();
	~GeneralTree();
	Node** getLeaves() const;
	Node** getInnerNodes() const;
	short get_amount_of_leaves() const;
	short getAmountOfInnerNodes() const;
	void getInput();
	void parseInput();
	bool treeContains(Node* node, short value);
	void assignChildren() const;
};

