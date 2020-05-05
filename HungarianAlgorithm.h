#pragma once

class HungarianAlgorithm {
public:
	HungarianAlgorithm();
	~HungarianAlgorithm();
	int Solve(int** matrix, int rows, int cols, bool max);

private:
	void optimalAssignment(int* assignment, int* cost, int* distMatrixIn, int nOfRows, int nOfColumns);
	static void buildAssignment(int* assignment, bool* starMatrix, int nOfRows, int nOfColumns);
	static void computeAssignment(int* assignment, int* cost, int* distMatrix, int nOfRows);
	void step2a(int* assignment, int* distMatrix, bool* starMatrix, bool* newStarMatrix, bool* primeMatrix, bool* coveredColumns, bool* coveredRows, int nOfRows, int nOfColumns, int minDim);
	void step2b(int* assignment, int* distMatrix, bool* starMatrix, bool* newStarMatrix, bool* primeMatrix, bool* coveredColumns, bool* coveredRows, int nOfRows, int nOfColumns, int minDim);
	void step3(int* assignment, int* distMatrix, bool* starMatrix, bool* newStarMatrix, bool* primeMatrix, bool* coveredColumns, bool* coveredRows, int nOfRows, int nOfColumns, int minDim);
	void step4(int* assignment, int* distMatrix, bool* starMatrix, bool* newStarMatrix, bool* primeMatrix, bool* coveredColumns, bool* coveredRows, int nOfRows, int nOfColumns, int minDim, int row, int col);
	void step5(int* assignment, int* distMatrix, bool* starMatrix, bool* newStarMatrix, bool* primeMatrix, bool* coveredColumns, bool* coveredRows, int nOfRows, int nOfColumns, int minDim);
};