#pragma once
#include "Node.h"

class GeneralTree {
	Node* root;
	Node** leaves;
	Node** innerNodes;
	unsigned int amountOfLeaves;
	unsigned int amountOfInnerNodes;
	char* input;
public:
	GeneralTree();
	~GeneralTree();
	Node** getLeaves();
	Node** getInnerNodes();
	unsigned int getAmountOfLeaves();
	unsigned int getAmountOfInnerNodes();
	void getInput();
	void parseInput();
	bool treeContains(Node* node, int value);
	void assignChildren();
};

