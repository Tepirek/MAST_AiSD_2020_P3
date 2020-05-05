#include "AdditionalAlgorithm.h"

bool AdditionalAlgorithm::handleCombinations(int index, int terminator) {
    int move = 1;
    bool finished = true;
    for (int i = 0; i <= index; i++) {
        if (this->takenPosition[i] == this->takenPosition[index] + move) {
            move++;
            i = -1;
        }
    }
    this->takenPosition[index] = this->takenPosition[index] + move;
    if (this->takenPosition[index] >= terminator) {
        if (index - 1 < 0) {
            finished = false;
        }
        else {
            finished = handleCombinations(index - 1, terminator);
            if (finished) {
                move = 0;
                for (int i = 0; i < index; i++) {
                    if (this->takenPosition[i] == move) {
                        move++;
                        i = -1;
                    }
                }
                this->takenPosition[index] = move;
            	if(this->option) {
                    this->valuesToAdd[index] = this->table[index][this->takenPosition[index]];
            	}
				else {
                    this->valuesToAdd[index] = this->table[this->takenPosition[index]][index];
                }
            }
        }
    }
    else {
        if (option) {
            this->valuesToAdd[index] = this->table[index][this->takenPosition[index]];
        }
        else {
            this->valuesToAdd[index] = this->table[this->takenPosition[index]][index];
        }
    }
    return finished;
}

int AdditionalAlgorithm::sumValues() {
    int sum = 0;
    for (int i = 0; i < this->smaller; i++) sum += this->valuesToAdd[i];
    return sum;
}

AdditionalAlgorithm::AdditionalAlgorithm(Node* a, Node* b, int** table) {
    this->sum = 0;
    this->maxSum = 0;
    this->rows = a->getAmountOfChildren();
    this->columns = b->getAmountOfChildren();
    this->table = table;
    this->smaller = (this->rows > this->columns) ? this->columns : this->rows;
    this->option = (this->columns > this->rows) ? 1 : 0;
    this->valuesToAdd = new int[this->smaller];
    this->takenPosition = new int[this->smaller];
    for (int i = 0; i < this->smaller; i++) {
        this->valuesToAdd[i] = this->table[i][i];
        this->takenPosition[i] = i;
    }
}

AdditionalAlgorithm::~AdditionalAlgorithm() {
	for(int i = 0; i < this->rows; i++) {
        delete[] this->table[i];
	}
    delete[] this->table;
    delete[] this->valuesToAdd;
    delete[] this->takenPosition;
}

int AdditionalAlgorithm::findMaxSum() {
    bool result = true;
    while (true) {
        if (result == false) return this->maxSum;
        this->sum = sumValues();
        if (this->sum > this->maxSum) this->maxSum = this->sum;
        if (this->option) {
            result = handleCombinations(this->rows - 1, this->columns);
        }
        else {
            result = handleCombinations(this->columns - 1, this->rows);
        }
    }
}