#include <stdlib.h>
#include <cfloat>
#include <cmath>
#include "HungarianAlgorithm.h"

HungarianAlgorithm::HungarianAlgorithm() {

}

HungarianAlgorithm::~HungarianAlgorithm() {

}

int HungarianAlgorithm::Solve(int** matrix, int rows, int cols, bool max) {
	unsigned int nRows = rows;
	unsigned int nCols = cols;

	int* distMatrixIn = new int[nRows * nCols];
	int* assignment = new int[nRows];
	int cost = 0;

	for (unsigned int i = 0; i < nRows; i++) {
		for (unsigned int j = 0; j < nCols; j++) {
			distMatrixIn[i + nRows * j] = matrix[i][j];
			if (max) distMatrixIn[i + nRows * j] *= -1;
		}
	}
	
	optimalAssignment(assignment, &cost, distMatrixIn, nRows, nCols);

	delete[] distMatrixIn;
	delete[] assignment;
	if (max) cost *= -1;
	return cost;
}

void HungarianAlgorithm::optimalAssignment(int* assignment, int* cost, int* distMatrixIn, int nOfRows, int nOfColumns) {
	int* distMatrixTemp, value, minValue;
	int minDim, row, col;

	*cost = 0;
	for (row = 0; row < nOfRows; row++)
		assignment[row] = -1;

	int nOfElements = nOfRows * nOfColumns;
	int* distMatrix = (int*)malloc(nOfElements * sizeof(int));
	int* distMatrixEnd = distMatrix + nOfElements;

	for (row = 0; row < nOfElements; row++) {
		value = distMatrixIn[row];
		distMatrix[row] = value;
	}
	
	bool* coveredColumns = (bool*)calloc(nOfColumns, sizeof(bool));
	bool* coveredRows = (bool*)calloc(nOfRows, sizeof(bool));
	bool* starMatrix = (bool*)calloc(nOfElements, sizeof(bool));
	bool* primeMatrix = (bool*)calloc(nOfElements, sizeof(bool));
	bool* newStarMatrix = (bool*)calloc(nOfElements, sizeof(bool));

	if (nOfRows <= nOfColumns) {
		minDim = nOfRows;

		for (row = 0; row < nOfRows; row++) {
			distMatrixTemp = distMatrix + row;
			minValue = *distMatrixTemp;
			distMatrixTemp += nOfRows;
			while (distMatrixTemp < distMatrixEnd) {
				value = *distMatrixTemp;
				if (value < minValue)
					minValue = value;
				distMatrixTemp += nOfRows;
			}

			distMatrixTemp = distMatrix + row;
			while (distMatrixTemp < distMatrixEnd) {
				*distMatrixTemp -= minValue;
				distMatrixTemp += nOfRows;
			}
		}

		for (row = 0; row < nOfRows; row++)
			for (col = 0; col < nOfColumns; col++)
				if (fabs(distMatrix[row + nOfRows * col]) < DBL_EPSILON)
					if (!coveredColumns[col]) {
						starMatrix[row + nOfRows * col] = true;
						coveredColumns[col] = true;
						break;
					}
	}
	else {
		minDim = nOfColumns;

		for (col = 0; col < nOfColumns; col++) {
			distMatrixTemp = distMatrix + nOfRows * col;
			int* columnEnd = distMatrixTemp + nOfRows;

			minValue = *distMatrixTemp++;
			while (distMatrixTemp < columnEnd) {
				value = *distMatrixTemp++;
				if (value < minValue)
					minValue = value;
			}
			distMatrixTemp = distMatrix + nOfRows * col;
			while (distMatrixTemp < columnEnd)
				*distMatrixTemp++ -= minValue;
		}

		for (col = 0; col < nOfColumns; col++)
			for (row = 0; row < nOfRows; row++)
				if (fabs(distMatrix[row + nOfRows * col]) < DBL_EPSILON)
					if (!coveredRows[row]) {
						starMatrix[row + nOfRows * col] = true;
						coveredColumns[col] = true;
						coveredRows[row] = true;
						break;
					}
		for (row = 0; row < nOfRows; row++)
			coveredRows[row] = false;
	}

	step2b(assignment, distMatrix, starMatrix, newStarMatrix, primeMatrix, coveredColumns, coveredRows, nOfRows, nOfColumns, minDim);

	computeAssignment(assignment, cost, distMatrixIn, nOfRows);

	free(distMatrix);
	free(coveredColumns);
	free(coveredRows);
	free(starMatrix);
	free(primeMatrix);
	free(newStarMatrix);
	return;
}

void HungarianAlgorithm::buildAssignment(int* assignment, bool* starMatrix, int nOfRows, int nOfColumns) {
	for (int row = 0; row < nOfRows; row++)
		for (int col = 0; col < nOfColumns; col++)
			if (starMatrix[row + nOfRows * col]) {
#ifdef ONE_INDEXING
				assignment[row] = col + 1;
#else
				assignment[row] = col;
#endif
				break;
			}
}

void HungarianAlgorithm::computeAssignment(int* assignment, int* cost, int* distMatrix, int nOfRows) {
	for (int row = 0; row < nOfRows; row++) {
		int col = assignment[row];
		if (col >= 0)
			*cost += distMatrix[row + nOfRows * col];
	}
}

void HungarianAlgorithm::step2a(int* assignment, int* distMatrix, bool* starMatrix, bool* newStarMatrix, bool* primeMatrix, bool* coveredColumns, bool* coveredRows, int nOfRows, int nOfColumns, int minDim) {
	for (int col = 0; col < nOfColumns; col++) {
		bool* starMatrixTemp = starMatrix + nOfRows * col;
		bool* columnEnd = starMatrixTemp + nOfRows;
		while (starMatrixTemp < columnEnd) {
			if (*starMatrixTemp++) {
				coveredColumns[col] = true;
				break;
			}
		}
	}

	step2b(assignment, distMatrix, starMatrix, newStarMatrix, primeMatrix, coveredColumns, coveredRows, nOfRows, nOfColumns, minDim);
}

void HungarianAlgorithm::step2b(int* assignment, int* distMatrix, bool* starMatrix, bool* newStarMatrix, bool* primeMatrix, bool* coveredColumns, bool* coveredRows, int nOfRows, int nOfColumns, int minDim) {
	int nOfCoveredColumns = 0;
	for (int col = 0; col < nOfColumns; col++)
		if (coveredColumns[col])
			nOfCoveredColumns++;

	if (nOfCoveredColumns == minDim) {
		buildAssignment(assignment, starMatrix, nOfRows, nOfColumns);
	}
	else {
		step3(assignment, distMatrix, starMatrix, newStarMatrix, primeMatrix, coveredColumns, coveredRows, nOfRows, nOfColumns, minDim);
	}

}

void HungarianAlgorithm::step3(int* assignment, int* distMatrix, bool* starMatrix, bool* newStarMatrix, bool* primeMatrix, bool* coveredColumns, bool* coveredRows, int nOfRows, int nOfColumns, int minDim) {
	int starCol;

	bool zerosFound = true;
	while (zerosFound) {
		zerosFound = false;
		for (int col = 0; col < nOfColumns; col++)
			if (!coveredColumns[col])
				for (int row = 0; row < nOfRows; row++)
					if ((!coveredRows[row]) && (fabs(distMatrix[row + nOfRows * col]) < DBL_EPSILON)) {
						primeMatrix[row + nOfRows * col] = true;

						for (starCol = 0; starCol < nOfColumns; starCol++)
							if (starMatrix[row + nOfRows * starCol])
								break;

						if (starCol == nOfColumns) {
							step4(assignment, distMatrix, starMatrix, newStarMatrix, primeMatrix, coveredColumns, coveredRows, nOfRows, nOfColumns, minDim, row, col);
							return;
						}
						else {
							coveredRows[row] = true;
							coveredColumns[starCol] = false;
							zerosFound = true;
							break;
						}
					}
	}
	step5(assignment, distMatrix, starMatrix, newStarMatrix, primeMatrix, coveredColumns, coveredRows, nOfRows, nOfColumns, minDim);
}

void HungarianAlgorithm::step4(int* assignment, int* distMatrix, bool* starMatrix, bool* newStarMatrix, bool* primeMatrix, bool* coveredColumns, bool* coveredRows, int nOfRows, int nOfColumns, int minDim, int row, int col) {
	int n, starRow, primeCol;
	int nOfElements = nOfRows * nOfColumns;

	for (n = 0; n < nOfElements; n++)
		newStarMatrix[n] = starMatrix[n];

	newStarMatrix[row + nOfRows * col] = true;

	int starCol = col;
	for (starRow = 0; starRow < nOfRows; starRow++)
		if (starMatrix[starRow + nOfRows * starCol])
			break;

	while (starRow < nOfRows) {
		newStarMatrix[starRow + nOfRows * starCol] = false;

		int primeRow = starRow;
		for (primeCol = 0; primeCol < nOfColumns; primeCol++)
			if (primeMatrix[primeRow + nOfRows * primeCol])
				break;

		newStarMatrix[primeRow + nOfRows * primeCol] = true;

		starCol = primeCol;
		for (starRow = 0; starRow < nOfRows; starRow++)
			if (starMatrix[starRow + nOfRows * starCol])
				break;
	}

	for (n = 0; n < nOfElements; n++) {
		primeMatrix[n] = false;
		starMatrix[n] = newStarMatrix[n];
	}
	for (n = 0; n < nOfRows; n++)
		coveredRows[n] = false;

	step2a(assignment, distMatrix, starMatrix, newStarMatrix, primeMatrix, coveredColumns, coveredRows, nOfRows, nOfColumns, minDim);
}

void HungarianAlgorithm::step5(int* assignment, int* distMatrix, bool* starMatrix, bool* newStarMatrix, bool* primeMatrix, bool* coveredColumns, bool* coveredRows, int nOfRows, int nOfColumns, int minDim) {
	int row, col;

	int h = INT_MAX;
	for (row = 0; row < nOfRows; row++)
		if (!coveredRows[row])
			for (col = 0; col < nOfColumns; col++)
				if (!coveredColumns[col]) {
					int value = distMatrix[row + nOfRows * col];
					if (value < h)
						h = value;
				}

	for (row = 0; row < nOfRows; row++)
		if (coveredRows[row])
			for (col = 0; col < nOfColumns; col++)
				distMatrix[row + nOfRows * col] += h;

	for (col = 0; col < nOfColumns; col++)
		if (!coveredColumns[col])
			for (row = 0; row < nOfRows; row++)
				distMatrix[row + nOfRows * col] -= h;

	step3(assignment, distMatrix, starMatrix, newStarMatrix, primeMatrix, coveredColumns, coveredRows, nOfRows, nOfColumns, minDim);
}