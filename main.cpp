#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include "Hungarian.h"

#pragma warning(disable : 4996)

#define OPENING_BRACKET '('
#define CLOSING_BRACKET ')'
#define COMMA ','

class Node {
    int value;
    Node* parent;
    Node* child;
    Node* sibling;
    Node** children;
    int amountOfChildren;
public:
    Node() {
        this->value = 0;
        this->parent = nullptr;
        this->child = nullptr;
        this->sibling = nullptr;
        this->amountOfChildren = 0;
    }
    ~Node() {
        delete this->parent;
        delete this->child;
        delete this->sibling;
    }
    int getValue() {
        return this->value;
    }
    Node* getParent() {
        return this->parent;
    }
    Node* getChild() {
        return this->child;
    }
    Node* getSibling() {
        return this->sibling;
    }
    Node** getChildren() {
        return this->children;
    }
    int getAmountOfChildren() {
        return this->amountOfChildren;
    }
    void setValue(int value) {
        this->value = value;
    }
    void setParent(Node* parent) {
        this->parent = parent;
    }
    void setChild(Node* child) {
        this->child = child;
    }
    void setSibling(Node* sibling) {
        this->sibling = sibling;
    }
    void incrementAmountOfChildren() {
        this->amountOfChildren += 1;
    }
    void setChildren(Node** children) {
        this->children = children;
    }
    void printNode() {
        printf("Node[%X]\n\tvalue\t=> %2d\n\tparent\t=> [%X]\n\tchild\t=> [%X]\n\tsibling\t=> [%X]\n", this, this->value, this->parent, this->child, this->sibling);
    }
};

class GeneralTree {
    Node* root;
    char* input = new char[100];
    Node** leaves;
    Node** innerNodes;
    int amountOfInnerNodes;
    int amountOfLeaves;
public:
    GeneralTree() {
        this->root = new Node();
        this->leaves = new Node * [10];
        this->amountOfInnerNodes = 0;
        this->amountOfLeaves = 0;
    }
    ~GeneralTree() {

    }
    Node** getLeaves() {
        return this->leaves;
    }
    Node** getInnerNodes() {
        return this->innerNodes;
    }
    void getInput() {
        char c;
        int position = 0;
        while ((c = getchar()) != '\n') {
            if (c == OPENING_BRACKET) this->amountOfInnerNodes++;
            this->input[position] = c;
            position++;
        }
    }
    int getAmountOfInnerNodes() {
        return this->amountOfInnerNodes;
    }
    int getAmountOfLeaves() {
        return this->amountOfLeaves;
    }
    bool currentContains(Node* node, int value) {
        if (node == nullptr) return false;
        if (node->getValue() == value) return true;
        return false;
    }
    bool treeContains(Node* node, int value, bool flag) {
        if (node == nullptr) return false;
        // printf("Current node %d and value %d\n", node->getValue(), value);
        if (node->getValue() == value) {
            // printf("Found! %d == %d\n", node->getValue(), value);
            return true;
        }
        return (treeContains(node->getChild(), value, flag) || treeContains(node->getSibling(), value, flag));
    }
    bool hasParent(Node* node, int value) {
        while (node != nullptr) {
            if (node->getValue() == value) return true;
            else node = node->getParent();
        }
        return false;
    }
    void printInput() {
        int position = 0;
        while (this->input[position] != ';') {
            printf("%c", this->input[position]);
            position++;
        }
        printf("\n");
    }
    void parseInput() {
        this->innerNodes = new Node * [this->amountOfInnerNodes];
        int position = 0;
        int innerNodeFlag = 0;
        int counter = 0;
        char c = this->input[position];
        Node* currentNode = this->root;
        while (c != ';') {
            if (c == OPENING_BRACKET) {
                // printf("Adding a child\n");
                if (currentNode->getParent() != nullptr) currentNode->getParent()->incrementAmountOfChildren();
                Node* n = new Node();
                n->setParent(currentNode);
                currentNode->setChild(n);
                currentNode->setValue(innerNodeFlag);
                this->innerNodes[counter] = currentNode;
                // currentNode->printNode();
                currentNode = n;
                counter++;
                innerNodeFlag--;
                position++;
                c = this->input[position];
            }
            else if (c == COMMA) {
                // printf("Adding a sibling\n");
                Node* n = new Node();
                n->setParent(currentNode->getParent());
                currentNode->setSibling(n);
                // currentNode->printNode();
                currentNode = n;
                position++;
                c = this->input[position];
            }
            else if (c == CLOSING_BRACKET) {
                // printf("Returning to parent node\n");
                currentNode = currentNode->getParent();
                position++;
                c = this->input[position];
            }
            else {
                // printf("Adding value ");
                if (currentNode->getParent() != nullptr) currentNode->getParent()->incrementAmountOfChildren();
                int length = 0;
                char* number = new char[8];
                int intNumber;
                while (c != OPENING_BRACKET && c != COMMA && c != CLOSING_BRACKET) {
                    number[length] = c;
                    length++;
                    position++;
                    c = this->input[position];
                }
                sscanf(number, "%d", &intNumber);
                currentNode->setValue(intNumber);
                this->leaves[amountOfLeaves] = currentNode;
                this->amountOfLeaves++;
                // currentNode->printNode();
                // printf("%d\n", intNumber);
            }
        }
        /*
        printf("Empty = %d | Full = %d\n", this->amountOfInnerNodes, this->amountOfLeaves);
        for(int i = 0; i < this->amountOfInnerNodes; i++) {
            printf("%d ", this->innerNodes[i]->getValue());
        }
        printf("\n");
        for(int i = 0; i < this->amountOfLeaves; i++) {
            printf("%d ", this->leaves[i]->getValue());
        }
        printf("\n");
        for (int i = 0; i < this->amountOfInnerNodes; i++) {
            printf("Node %d has %d children\n", this->innerNodes[i]->getValue(), this->innerNodes[i]->getAmountOfChildren());
        }
        */
    }
    void assignChildren() {
        Node* node;
        for (int i = 0; i < this->amountOfInnerNodes; i++) {
            node = this->innerNodes[i];
            Node * *children = new Node * [node->getAmountOfChildren()];
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
    void printInnerNodesWithChildren() {
        for (int i = 0; i < this->amountOfInnerNodes; i++) {
            printf("Node %d\n", this->innerNodes[i]->getValue());
            for (int j = 0; j < this->innerNodes[i]->getAmountOfChildren(); j++) {
                printf("%d ", this->innerNodes[i]->getChildren()[j]->getValue());
            }
            printf("\n");
        }
    }
};

class HashMap {
    int** table;
    GeneralTree* first;
    GeneralTree* second;
    int firstSize;
    int secondSize;
    Node** firstValues;
    Node** secondValues;
public:
    HashMap(GeneralTree* first, GeneralTree* second) {
        this->first = first;
        this->second = second;
        this->firstSize = first->getAmountOfLeaves() + first->getAmountOfInnerNodes();
        this->secondSize = second->getAmountOfLeaves() + second->getAmountOfInnerNodes();
        this->table = new int* [this->firstSize];
        for (int i = 0; i < this->secondSize; i++) {
            this->table[i] = new int[this->secondSize];
        }
        this->firstValues = new Node*[this->firstSize];
        this->secondValues = new Node*[this->secondSize];
        for(int i = 0; i < this->firstSize; i++) {
            if(i < this->first->getAmountOfLeaves()) firstValues[i] = this->first->getLeaves()[i];
            else firstValues[i] = this->first->getInnerNodes()[i - this->first->getAmountOfLeaves()];
        }
        for (int i = 0; i < this->secondSize; i++) {
            if (i < this->second->getAmountOfLeaves()) secondValues[i] = this->second->getLeaves()[i];
            else secondValues[i] = this->second->getInnerNodes()[i - this->second->getAmountOfLeaves()];
        }
    }
    ~HashMap() {

    }
    void prepareTable() {
        for (int i = 0; i < this->firstSize; i++) {
            for (int j = 0; j < this->secondSize; j++) {
                this->table[i][j] = 0;
            }
        }
    }
    void handleLeaves() {
        for (int i = 0; i < firstSize; i++) {
            for (int j = 0; j < secondSize; j++) {
                if (i < this->first->getAmountOfLeaves() || j < this->second->getAmountOfLeaves()) {
                    if (j >= this->second->getAmountOfLeaves()) {
                        // this->table[i][j] = 2;
                        this->table[i][j] = (this->second->treeContains(this->second->getInnerNodes()[j - this->second->getAmountOfLeaves()]->getChild(), this->first->getLeaves()[i]->getValue(), true)) ? 1 : 0;
                    }
                    else if (i >= this->first->getAmountOfLeaves()) {
                        // this->table[i][j] = 3;
                        this->table[i][j] = (this->first->treeContains(this->first->getInnerNodes()[i - this->first->getAmountOfLeaves()]->getChild(), this->second->getLeaves()[j]->getValue(), true)) ? 1 : 0;
                    }
                    else {
                        // this->table[i][j] = 1;
                        this->table[i][j] = (this->first->getLeaves()[i]->getValue() == this->second->getLeaves()[j]->getValue()) ? 1 : 0;
                    }
                }
            }
        }
    }
    void handleInnerNodes() {
        for (int i = this->firstSize - 1; i >= this->first->getAmountOfLeaves(); i--) {
            for (int j = this->secondSize - 1; j >= this->second->getAmountOfLeaves(); j--) {
                // this->table[i][j] = 4;
                int case1 = compareChildrenWithNode(this->firstValues[i], this->secondValues[j]);
                int case2 = compareChildrenWithNode(this->secondValues[j], this->firstValues[i]);
                int case3 = compareChildren(this->firstValues[i], this->secondValues[j]);
                this->table[i][j] = maxOfThree(case1, case2, case3);
            }
        }
    }
    int compareChildrenWithNode(Node* a, Node* b) {
        int max = 0;
        int value = 0;
        for (int i = 0; i < a->getAmountOfChildren(); i++) {
            value = getValueAt(a->getChildren()[i]->getValue(), b->getValue());
            if (value > max) max = value;
        }
        return max;
    }
    int compareChildren(Node* a, Node* b) {
        int** tmpTable = new int* [a->getAmountOfChildren()];
        for (int i = 0; i < a->getAmountOfChildren(); i++) {
            for (int j = 0; j < b->getAmountOfChildren(); j++) {
                tmpTable[i] = new int[b->getAmountOfChildren()];
            }
        }
        for (int i = 0; i < a->getAmountOfChildren(); i++) {
            for (int j = 0; j < b->getAmountOfChildren(); j++) {
                // tmpTable[i][j] = getValueAt(a->getChildren[i]->getValue(), b->getChildren()[j]->getValue());
            }
        }

        return 0;
    }
    int maxOfThree(int a, int b, int c) {
        int max = a;
        if (max < b) max = b;
        if (max < c) max = c;
        return max;
    }
    int getValueAt(int a, int b) {
        int i_a = 0, j_b = 0;
        for (int i = 0; i < this->firstSize; i++) {
            if (this->firstValues[i]->getValue() == a) {
                i_a = i;
                break;
            }
        }
        for (int j = 0; j < this->secondSize; j++) {
            if (this->secondValues[j]->getValue() == b) {
                j_b = j;
                break;
            }
        }
        // printf("Value = %d\n", this->table[i_a][j_b]);
        return this->table[i_a][j_b];
    }
    void printTable() {
        printf("|");
        for (int i = 0; i < secondSize; i++) {
            if (i < this->second->getAmountOfLeaves()) printf("%d|", this->second->getLeaves()[i]->getValue());
            else printf("%d|", this->second->getInnerNodes()[i - first->getAmountOfLeaves()]->getValue());
        }
        printf("\n");
        for (int i = 0; i <= secondSize; i++) {
            printf("--");
        }
        printf("\n");
        for (int i = 0; i < this->firstSize; i++) {
            if (i < this->first->getAmountOfLeaves()) {
                if (this->first->getLeaves()[i]->getValue() < 10) printf(" ");
                printf("%d|", this->first->getLeaves()[i]->getValue());
            } 
            else {
                if (this->first->getInnerNodes()[i - first->getAmountOfLeaves()]->getValue() < 10 && this->first->getInnerNodes()[i - first->getAmountOfLeaves()]->getValue() >= 0) printf(" ");
                printf("%d|", this->first->getInnerNodes()[i - first->getAmountOfLeaves()]->getValue());
            } 
            for (int j = 0; j < this->secondSize; j++) {
                printf("%d|", this->table[i][j]);
            }
            printf("\n");
        }
    }
};

int main(void) {
    int numberOfTrees = 0;
    scanf("%d ", &numberOfTrees);
    GeneralTree** trees = new GeneralTree * [numberOfTrees];
    for (int i = 0; i < numberOfTrees; i++) {
        GeneralTree* gt = new GeneralTree();
        gt->getInput();
        gt->parseInput();
        gt->assignChildren();
        // gt->printInnerNodesWithChildren();
        trees[i] = gt;
    }
    for (int i = 0; i < numberOfTrees; i++) {
        for (int j = i; j < numberOfTrees; j++) {
            if (i == j) continue;
            HashMap* h = new HashMap(trees[i], trees[j]);
            h->prepareTable();
            // h->printTable();
            // printf("\n");
            h->handleLeaves();
            h->printTable();
            printf("\n");
            h->handleInnerNodes();
            h->printTable();
        }
    }

    return 0;
}

/*

(4,(8,1,(5,3)),(9,2,(10,(7,6))));
(10,(8,(9,(5,4)),(6,2,3)),(7,1));

*/
