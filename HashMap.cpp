#include "HashMap.h"
#include <stdio.h>
#include "HungarianAlgorithm.h"

unsigned int HashMap::getValueAt(unsigned int  a, unsigned int  b) {
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

unsigned int HashMap::maxOfThree(unsigned int a, unsigned int b, unsigned int c) {
    int max = a;
    if (max < b) max = b;
    if (max < c) max = c;
    return max;
}

unsigned int HashMap::compareChildrenWithNode1(Node* a, Node* b) {
    int max = 0;
    int value = 0;
    int i_a = 0;
    int j_b = 0;
    for (int i = 0; i < secondTreeSize; i++) {
        if (b == secondTreeValues[i]) {
            j_b = i; break;
        }
    }
    for (int i = 0; i < a->getAmountOfChildren(); i++) {
        Node* firstChild = a->getChildren()[i];
        for (int i = 0; i < firstTreeSize; i++) {
            if (firstChild == firstTreeValues[i]) {
                i_a = i; break;
            }
        }
        value = table[i_a][j_b];
        if (value > max) max = value;
    }
    return max;
}

unsigned int HashMap::compareChildrenWithNode2(Node* a, Node* b) {
    int max = 0;
    int value = 0;
    int i_a = 0;
    int j_b = 0;
    for (int i = 0; i < firstTreeSize; i++) {
        if (b == firstTreeValues[i]) {
            i_a = i; break;
        }
    }
    for (int i = 0; i < a->getAmountOfChildren(); i++) {
        Node* firstChild = a->getChildren()[i];
        for (int i = 0; i < secondTreeSize; i++) {
            if (firstChild == secondTreeValues[i]) {
                j_b = i; break;
            }
        }
        value = table[i_a][j_b];
        if (value > max) max = value;
    }
    return max;
}

unsigned int HashMap::compareChildren(Node* a, Node* b) {
    int** tmpTable = new int* [a->getAmountOfChildren()];
    for (int i = 0; i < a->getAmountOfChildren(); i++) {
        for (int j = 0; j < b->getAmountOfChildren(); j++) {
            tmpTable[i] = new int[b->getAmountOfChildren()];
        }
    }
    for (int i = 0; i < a->getAmountOfChildren(); i++) {
        for (int j = 0; j < b->getAmountOfChildren(); j++) {
            tmpTable[i][j] = getValueAt(a->getChildren()[i]->getValue(), b->getChildren()[j]->getValue());
        }
    }
    vector<vector<double>> costMatrix(a->getAmountOfChildren(), vector<double>(b->getAmountOfChildren()));
    for (int i = 0; i < a->getAmountOfChildren(); i++) {
        for (int j = 0; j < b->getAmountOfChildren(); j++) {
            costMatrix[i][j] = getValueAt(a->getChildren()[i]->getValue(), b->getChildren()[j]->getValue());
        }
    }
    for (int i = 0; i < a->getAmountOfChildren(); i++) {
        for (int j = 0; j < b->getAmountOfChildren(); j++) {
            costMatrix[i][j] *= -1;
        }
    }
    HungarianAlgorithm* h = new HungarianAlgorithm();
    vector<int> assignment;
    double cost = h->Solve(costMatrix, assignment);
    return (int) cost;
}

HashMap::HashMap(GeneralTree* firstTree, GeneralTree* secondTree) {
    this->firstTree = firstTree;
    this->secondTree = secondTree;
    this->firstTreeSize = this->firstTree->getAmountOfLeaves() + this->firstTree->getAmountOfInnerNodes();
    this->secondTreeSize = this->secondTree->getAmountOfLeaves() + this->secondTree->getAmountOfInnerNodes();
    this->table = new unsigned int* [this->firstTreeSize * sizeof(unsigned int)];
    for (int i = 0; i < this->firstTreeSize; i++) {
        this->table[i] = new unsigned int[this->secondTreeSize];
    }
    this->firstTreeValues = new Node * [this->firstTreeSize];
    this->secondTreeValues = new Node * [this->secondTreeSize];
    for (int i = 0; i < this->firstTreeSize; i++) {
        if (i < this->firstTree->getAmountOfLeaves()) firstTreeValues[i] = this->firstTree->getLeaves()[i];
        else firstTreeValues[i] = this->firstTree->getInnerNodes()[i - this->firstTree->getAmountOfLeaves()];
    }
    for (int i = 0; i < this->secondTreeSize; i++) {
        if (i < this->secondTree->getAmountOfLeaves()) secondTreeValues[i] = this->secondTree->getLeaves()[i];
        else secondTreeValues[i] = this->secondTree->getInnerNodes()[i - this->secondTree->getAmountOfLeaves()];
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

unsigned int HashMap::getSolution() {
    return this->firstTree->getAmountOfLeaves() - this->solution;
}

void HashMap::handleLeaves() {
    for (int i = 0; i < firstTreeSize; i++) {
        for (int j = 0; j < secondTreeSize; j++) {
            if (i < this->firstTree->getAmountOfLeaves() || j < this->secondTree->getAmountOfLeaves()) {
                if (j >= this->secondTree->getAmountOfLeaves()) {
                    this->table[i][j] = (this->secondTree->treeContains(this->secondTree->getInnerNodes()[j - this->secondTree->getAmountOfLeaves()]->getChild(), this->firstTree->getLeaves()[i]->getValue())) ? 1 : 0;
                }
                else if (i >= this->firstTree->getAmountOfLeaves()) {
                    this->table[i][j] = (this->firstTree->treeContains(this->firstTree->getInnerNodes()[i - this->firstTree->getAmountOfLeaves()]->getChild(), this->secondTree->getLeaves()[j]->getValue())) ? 1 : 0;
                }
                else {
                    this->table[i][j] = (this->firstTree->getLeaves()[i]->getValue() == this->secondTree->getLeaves()[j]->getValue()) ? 1 : 0;
                }
            }
        }
    }
}

void HashMap::handleInnerNodes() {
    for (int i = this->firstTreeSize - 1; i >= this->firstTree->getAmountOfLeaves(); i--) {
        for (int j = this->secondTreeSize - 1; j >= this->secondTree->getAmountOfLeaves(); j--) {
            int case1 = compareChildrenWithNode1(this->firstTreeValues[i], this->secondTreeValues[j]);
            int case2 = compareChildrenWithNode2(this->secondTreeValues[j], this->firstTreeValues[i]);
            int case3 = compareChildren(this->firstTreeValues[i], this->secondTreeValues[j]);
            case3 *= -1;
            this->table[i][j] = maxOfThree(case1, case2, case3);
            if (this->solution < this->table[i][j]) this->solution = this->table[i][j];
        }
    }
}

void HashMap::printTable() {
    printf("|");
    for (int i = 0; i < secondTreeSize; i++) {
        if (i < this->secondTree->getAmountOfLeaves()) printf("%d|", this->secondTree->getLeaves()[i]->getValue());
        else printf("%d|", this->secondTree->getInnerNodes()[i - firstTree->getAmountOfLeaves()]->getValue());
    }
    printf("\n");
    for (int i = 0; i <= secondTreeSize; i++) {
        printf("--");
    }
    printf("\n");
    for (int i = 0; i < this->firstTreeSize; i++) {
        if (i < this->firstTree->getAmountOfLeaves()) {
            if (this->firstTree->getLeaves()[i]->getValue() < 10) printf(" ");
            printf("%d|", this->firstTree->getLeaves()[i]->getValue());
        }
        else {
            if (this->firstTree->getInnerNodes()[i - firstTree->getAmountOfLeaves()]->getValue() < 10 && this->firstTree->getInnerNodes()[i - firstTree->getAmountOfLeaves()]->getValue() >= 0) printf(" ");
            printf("%d|", this->firstTree->getInnerNodes()[i - firstTree->getAmountOfLeaves()]->getValue());
        }
        for (int j = 0; j < this->secondTreeSize; j++) {
            printf("%d|", this->table[i][j]);
        }
        printf("\n");
    }
}
