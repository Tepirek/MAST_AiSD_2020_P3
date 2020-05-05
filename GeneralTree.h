#pragma once
#include "Node.h"

class GeneralTree {
	Node* root;
	Node** leaves;
	Node** innerNodes;
	int amountOfLeaves;
	int amountOfInnerNodes;
	char* input;
public:
	GeneralTree();
	~GeneralTree();
	Node** getLeaves() const;
	Node** getInnerNodes() const;
	int get_amount_of_leaves() const;
	int getAmountOfInnerNodes() const;
	void getInput();
	void parseInput();
	bool treeContains(Node* node, int value);
	void assignChildren() const;
};

