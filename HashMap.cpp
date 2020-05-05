#include "HashMap.h"
#include "HungarianAlgorithm.h"
// #include "AdditionalAlgorithm.h"

int HashMap::getValueAt(int a, int b) const {
    int i_a = 0;
    int j_b = 0;
    for (int i = 0; i < this->firstTreeSize; i++) {
        if (a == this->firstTreeValues[i]->getValue()) {
            i_a = i;
            break;
        }
    }
    for (int i = 0; i < this->secondTreeSize; i++) {
        if (b == this->secondTreeValues[i]->getValue()) {
            j_b = i;
            break;
        }
    }
    return this->table[i_a][j_b];
}

int HashMap::maxOfThree(int a, int b, int c) {
    int max = a;
    if (max < b) max = b;
    if (max < c) max = c;
    return max;
}

int HashMap::compareChildrenWithNode1(Node* a, Node* b) const {
    int max = 0;
    int i_a = 0;
    int j_b = 0;
    for (int i = 0; i < secondTreeSize; i++) {
        if (b == secondTreeValues[i]) {
            j_b = i; break;
        }
    }
    for (int i = 0; i < a->getAmountOfChildren(); i++) {
        int value = 0;
        Node* firstChild = a->getChildren()[i];
        for (int j = 0; j < firstTreeSize; j++) {
            if (firstChild == firstTreeValues[j]) {
                i_a = j; break;
            }
        }
        value = table[i_a][j_b];
        if (value > max) max = value;
    }
    return max;
}

int HashMap::compareChildrenWithNode2(Node* a, Node* b) const {
    int max = 0;
    int i_a = 0;
    int j_b = 0;
    for (int i = 0; i < firstTreeSize; i++) {
        if (b == firstTreeValues[i]) {
            i_a = i;
            break;
        }
    }
    for (int i = 0; i < a->getAmountOfChildren(); i++) {
        int value = 0;
        Node* firstChild = a->getChildren()[i];
        for (int j = 0; j < secondTreeSize; j++) {
            if (firstChild == secondTreeValues[j]) {
                j_b = j;
                break;
            }
        }
        value = table[i_a][j_b];
        if (value > max) max = value;
    }
    return max;
}

int HashMap::compareChildren(Node* a, Node* b) const {
    int** tmpTable = new int * [a->getAmountOfChildren()];
	for(int i = 0; i < a->getAmountOfChildren(); i++) {
        tmpTable[i] = new int[b->getAmountOfChildren()];
	}
    for (int i = 0; i < a->getAmountOfChildren(); i++) {
        for (int j = 0; j < b->getAmountOfChildren(); j++) {
            tmpTable[i][j] = getValueAt(a->getChildren()[i]->getValue(), b->getChildren()[j]->getValue());
        }
    }
    HungarianAlgorithm* h = new HungarianAlgorithm();
    int result = h->Solve(tmpTable, a->getAmountOfChildren(), b->getAmountOfChildren(), true);
    return result;
	/*
    int rows = a->getAmountOfChildren();
    int columns = b->getAmountOfChildren();
    int** tmpTable = new int* [rows];
	for(int i = 0; i < rows; i++) {
        tmpTable[i] = new int[columns];
	}
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < columns; j++) {
            tmpTable[i][j] = getValueAt(a->getChildren()[i]->getValue(), b->getChildren()[j]->getValue());
		}
	}
    AdditionalAlgorithm* ad = new AdditionalAlgorithm(a, b, tmpTable);
    int result = ad->findMaxSum();
    return result;
    */
}

HashMap::HashMap(GeneralTree* firstTree, GeneralTree* secondTree) {
    this->firstTree = firstTree;
    this->secondTree = secondTree;
    this->firstTreeSize = this->firstTree->get_amount_of_leaves() + this->firstTree->getAmountOfInnerNodes();
    this->secondTreeSize = this->secondTree->get_amount_of_leaves() + this->secondTree->getAmountOfInnerNodes();
    this->table = new int* [this->firstTreeSize * sizeof(int)];
    for (int i = 0; i < this->firstTreeSize; i++) {
        this->table[i] = new int[this->secondTreeSize];
    }
    this->firstTreeValues = new Node * [this->firstTreeSize];
    this->secondTreeValues = new Node * [this->secondTreeSize];
    for (int i = 0; i < this->firstTreeSize; i++) {
        if (i < this->firstTree->get_amount_of_leaves()) firstTreeValues[i] = this->firstTree->getLeaves()[i];
        else firstTreeValues[i] = this->firstTree->getInnerNodes()[i - this->firstTree->get_amount_of_leaves()];
    }
    for (int i = 0; i < this->secondTreeSize; i++) {
        if (i < this->secondTree->get_amount_of_leaves()) secondTreeValues[i] = this->secondTree->getLeaves()[i];
        else secondTreeValues[i] = this->secondTree->getInnerNodes()[i - this->secondTree->get_amount_of_leaves()];
    }
    this->solution = 0;
}

HashMap::~HashMap() {
    for (int i = 0; i < this->firstTreeSize; i++) {
        delete[] this->table[i];
    }
    delete[] this->table;
    delete this->firstTree;
    delete this->secondTree;
    delete[] this->firstTreeValues;
    delete[] this->secondTreeValues;
}

int HashMap::getSolution() const {
    return this->firstTree->get_amount_of_leaves() - this->solution;
}

void HashMap::handleLeaves() const {
    for (int i = 0; i < firstTreeSize; i++) {
        for (int j = 0; j < secondTreeSize; j++) {
            if (i < this->firstTree->get_amount_of_leaves() || j < this->secondTree->get_amount_of_leaves()) {
                if (j >= this->secondTree->get_amount_of_leaves()) {
                    this->table[i][j] = (this->secondTree->treeContains(this->secondTree->getInnerNodes()[j - this->secondTree->get_amount_of_leaves()]->getChild(), this->firstTree->getLeaves()[i]->getValue())) ? 1 : 0;
                }
                else if (i >= this->firstTree->get_amount_of_leaves()) {
                    this->table[i][j] = (this->firstTree->treeContains(this->firstTree->getInnerNodes()[i - this->firstTree->get_amount_of_leaves()]->getChild(), this->secondTree->getLeaves()[j]->getValue())) ? 1 : 0;
                }
                else {
                    this->table[i][j] = (this->firstTree->getLeaves()[i]->getValue() == this->secondTree->getLeaves()[j]->getValue()) ? 1 : 0;
                }
            }
        }
    }
}

void HashMap::handleInnerNodes() {
    for (int i = this->firstTreeSize - 1; i >= this->firstTree->get_amount_of_leaves(); i--) {
        for (int j = this->secondTreeSize - 1; j >= this->secondTree->get_amount_of_leaves(); j--) {
	        const int case1 = compareChildrenWithNode1(this->firstTreeValues[i], this->secondTreeValues[j]);
	        const int case2 = compareChildrenWithNode2(this->secondTreeValues[j], this->firstTreeValues[i]);
            int case3 = compareChildren(this->firstTreeValues[i], this->secondTreeValues[j]);
            this->table[i][j] = maxOfThree(case1, case2, case3);
            if (this->solution < this->table[i][j]) this->solution = this->table[i][j];
        }
    }
}