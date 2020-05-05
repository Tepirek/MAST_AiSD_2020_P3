#pragma once
#include "Node.h"

class AdditionalAlgorithm {
	int sum;
	int maxSum;
	int rows;
	int columns;
	int** table;
	int smaller;
	int option;
	int* valuesToAdd;
	int* takenPosition;
	int sumValues();
	bool handleCombinations(int index, int terminator);
public:
	AdditionalAlgorithm(Node* a, Node* b, int** table);
	~AdditionalAlgorithm();
	int findMaxSum();
};