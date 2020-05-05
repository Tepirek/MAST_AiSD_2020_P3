#include "GeneralTree.h"
#include <stdio.h>
#include <iostream>
constexpr auto OPENING_BRACKET = '(';
constexpr auto CLOSING_BRACKET = ')';
constexpr auto COMMA = ',';

GeneralTree::GeneralTree() {
    this->root = new Node();
    this->leaves = new Node * [10];
    this->innerNodes = nullptr;
    this->amountOfLeaves = 0;
    this->amountOfInnerNodes = 0;
    this->input = new char[100];
}

GeneralTree::~GeneralTree() {
    delete this->root;
    delete[] this->leaves;
    delete[] this->innerNodes;
    delete[] this->input;
}

Node** GeneralTree::getLeaves() const {
    return this->leaves;
}

Node** GeneralTree::getInnerNodes() const {
    return this->innerNodes;
}

int GeneralTree::get_amount_of_leaves() const {
    return this->amountOfLeaves;
}

int GeneralTree::getAmountOfInnerNodes() const {
    return this->amountOfInnerNodes;
}

/*
void GeneralTree::getInput() {
    char c;
    int position = 0;
    while ((c = getchar()) != '\n') {
        if (c == OPENING_BRACKET) this->amountOfInnerNodes++;
        this->input[position] = c;
        position++;
    }
}
*/

void GeneralTree::getInput() {
    char c;
    int position = 0;
    while ((c = getchar()) != ';') {
        if (c == OPENING_BRACKET) this->amountOfInnerNodes++;
        this->input[position] = c;
        position++;
    }
    this->input[position] = ';';
}

void GeneralTree::parseInput() {
    this->innerNodes = new Node * [this->amountOfInnerNodes * sizeof(Node*)];
    int position = 0;
    int innerNodeFlag = 0;
    int counter = 0;
    char c = this->input[position];
    Node* currentNode = this->root;
    while (c != ';') {
        if (c == OPENING_BRACKET) {
            if (currentNode->getParent() != nullptr) currentNode->getParent()->incrementAmountOfChildren();
            Node* n = new Node();
            n->setParent(currentNode);
            currentNode->setChild(n);
            currentNode->setValue(innerNodeFlag);
            this->innerNodes[counter] = currentNode;
            currentNode = n;
            counter++;
            innerNodeFlag--;
            position++;
            c = this->input[position];
        }
        else if (c == COMMA) {
            Node* n = new Node();
            n->setParent(currentNode->getParent());
            currentNode->setSibling(n);
            currentNode = n;
            position++;
            c = this->input[position];
        }
        else if (c == CLOSING_BRACKET) {
            currentNode = currentNode->getParent();
            position++;
            c = this->input[position];
        }
        else {
            if (currentNode->getParent() != nullptr) currentNode->getParent()->incrementAmountOfChildren();
            int length = 0;
            char* number = new char[10];
            int intNumber;
            while (c != OPENING_BRACKET && c != COMMA && c != CLOSING_BRACKET) {
                number[length] = c;
                length++;
                position++;
                c = this->input[position];
            }
            sscanf_s(number, "%hd", &intNumber);
            currentNode->setValue(intNumber);
            this->leaves[amountOfLeaves] = currentNode;
            this->amountOfLeaves++;
            delete[] number;
        }
    }
    delete[] this->input;
}

bool GeneralTree::treeContains(Node* node, int value) {
    if (node == nullptr) return false;
    if (node->getValue() == value) return true;
    return (treeContains(node->getChild(), value) || treeContains(node->getSibling(), value));
}

void GeneralTree::assignChildren() const {
    Node* node;
    for (int i = 0; i < this->amountOfInnerNodes; i++) {
        node = this->innerNodes[i];
        Node** children = new Node * [node->getAmountOfChildren() * sizeof(Node*)];
        if (node->getChild() == nullptr) return;
        children[0] = node->getChild();
        node = node->getChild();
        int counter = 1;
        while (node->getSibling() != nullptr) {
            children[counter] = node->getSibling();
            node = node->getSibling();
            counter++;
        }
        this->innerNodes[i]->setChildren(children);
    }
}