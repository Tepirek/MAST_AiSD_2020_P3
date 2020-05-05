#include "HashMap.h"
#include <stdio.h>
#include "HungarianAlgorithm.h"

short HashMap::getValueAt(short a, short b) const {
    short i_a = 0;
    short j_b = 0;
    for (short i = 0; i < this->firstTreeSize; i++) {
        if (a == this->firstTreeValues[i]->getValue()) {
            i_a = i;
            break;
        }
    }
    for (short i = 0; i < this->secondTreeSize; i++) {
        if (b == this->secondTreeValues[i]->getValue()) {
            j_b = i;
            break;
        }
    }
    return this->table[i_a][j_b];
}

short HashMap::maxOfThree(short a, short b, short c) {
    short max = a;
    if (max < b) max = b;
    if (max < c) max = c;
    return max;
}

short HashMap::compareChildrenWithNode1(Node* a, Node* b) const {
    short max = 0;
    short i_a = 0;
    short j_b = 0;
    for (short i = 0; i < secondTreeSize; i++) {
        if (b == secondTreeValues[i]) {
            j_b = i; break;
        }
    }
    for (short i = 0; i < a->getAmountOfChildren(); i++) {
        short value = 0;
        Node* firstChild = a->getChildren()[i];
        for (short j = 0; j < firstTreeSize; j++) {
            if (firstChild == firstTreeValues[j]) {
                i_a = j; break;
            }
        }
        value = table[i_a][j_b];
        if (value > max) max = value;
    }
    return max;
}

short HashMap::compareChildrenWithNode2(Node* a, Node* b) const {
	short max = 0;
	short i_a = 0;
	short j_b = 0;
	for (short i = 0; i < firstTreeSize; i++) {
		if (b == firstTreeValues[i]) {
			i_a = i;
			break;
		}
	}
	for (short i = 0; i < a->getAmountOfChildren(); i++) {
        short value = 0;
		Node* firstChild = a->getChildren()[i];
		for (short j = 0; j < secondTreeSize; j++) {
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

short HashMap::compareChildren(Node* a, Node* b) const {
	/*
    short** tmpTable = new short* [a->getAmountOfChildren()];
    for (short i = 0; i < a->getAmountOfChildren(); i++) {
        for (short j = 0; j < b->getAmountOfChildren(); j++) {
            tmpTable[i] = new short[b->getAmountOfChildren()];
        }
    }
    for (short i = 0; i < a->getAmountOfChildren(); i++) {
        for (short j = 0; j < b->getAmountOfChildren(); j++) {
            tmpTable[i][j] = getValueAt(a->getChildren()[i]->getValue(), b->getChildren()[j]->getValue());
        }
    }
    */
    vector<vector<double>> costMatrix(a->getAmountOfChildren(), vector<double>(b->getAmountOfChildren()));
    for (short i = 0; i < a->getAmountOfChildren(); i++) {
        for (short j = 0; j < b->getAmountOfChildren(); j++) {
            costMatrix[i][j] = getValueAt(a->getChildren()[i]->getValue(), b->getChildren()[j]->getValue());
        }
    }
    for (short i = 0; i < a->getAmountOfChildren(); i++) {
        for (short j = 0; j < b->getAmountOfChildren(); j++) {
            costMatrix[i][j] *= -1;
        }
    }
    HungarianAlgorithm* h = new HungarianAlgorithm();
    vector<int> assignment;
    double cost = h->Solve(costMatrix, assignment);
    return static_cast<short>(cost);
}

HashMap::HashMap(GeneralTree* firstTree, GeneralTree* secondTree) {
    this->firstTree = firstTree;
    this->secondTree = secondTree;
    this->firstTreeSize = this->firstTree->get_amount_of_leaves() + this->firstTree->getAmountOfInnerNodes();
    this->secondTreeSize = this->secondTree->get_amount_of_leaves() + this->secondTree->getAmountOfInnerNodes();
    this->table = new short* [this->firstTreeSize * sizeof(short)];
    for (short i = 0; i < this->firstTreeSize; i++) {
        this->table[i] = new short[this->secondTreeSize];
    }
    this->firstTreeValues = new Node * [this->firstTreeSize];
    this->secondTreeValues = new Node * [this->secondTreeSize];
    for (short i = 0; i < this->firstTreeSize; i++) {
        if (i < this->firstTree->get_amount_of_leaves()) firstTreeValues[i] = this->firstTree->getLeaves()[i];
        else firstTreeValues[i] = this->firstTree->getInnerNodes()[i - this->firstTree->get_amount_of_leaves()];
    }
    for (short i = 0; i < this->secondTreeSize; i++) {
        if (i < this->secondTree->get_amount_of_leaves()) secondTreeValues[i] = this->secondTree->getLeaves()[i];
        else secondTreeValues[i] = this->secondTree->getInnerNodes()[i - this->secondTree->get_amount_of_leaves()];
    }
    this->solution = 0;
}

HashMap::~HashMap() {
    for (short i = 0; i < this->firstTreeSize; i++) {
        delete[] this->table[i];
    }
    delete[] this->table;
    delete this->firstTree;
    delete this->secondTree;
    delete[] this->firstTreeValues;
    delete[] this->secondTreeValues;
}

short HashMap::getSolution() const {
    return this->firstTree->get_amount_of_leaves() - this->solution;
}

void HashMap::handleLeaves() const {
    for (short i = 0; i < firstTreeSize; i++) {
        for (short j = 0; j < secondTreeSize; j++) {
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
    for (short i = this->firstTreeSize - 1; i >= this->firstTree->get_amount_of_leaves(); i--) {
        for (short j = this->secondTreeSize - 1; j >= this->secondTree->get_amount_of_leaves(); j--) {
	        const short case1 = compareChildrenWithNode1(this->firstTreeValues[i], this->secondTreeValues[j]);
	        const short case2 = compareChildrenWithNode2(this->secondTreeValues[j], this->firstTreeValues[i]);
            short case3 = compareChildren(this->firstTreeValues[i], this->secondTreeValues[j]);
            case3 *= -1;
            this->table[i][j] = maxOfThree(case1, case2, case3);
            if (this->solution < this->table[i][j]) this->solution = this->table[i][j];
        }
    }
}