#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#define OPENING_BRACKET '('
#define CLOSING_BRACKET ')'
#define COMMA ','

class Node {
    int value;
    Node* parent;
    Node* child;
    Node* sibling;
public:
    Node() {
        this->value = 0;
        this->parent = nullptr;
        this->child = nullptr;
        this->sibling = nullptr;
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
        this->leaves = new Node*[10];
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
        while((c = getchar()) != '\n') {
            if(c == OPENING_BRACKET) this->amountOfInnerNodes++;
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
        if(node == nullptr) return false;
        if(node->getValue() == value) return true;
        return false;
    }
    bool treeContains(Node* node, int value) {
        if(node == nullptr) return false;
        if(node->getValue() == value) return true;
        return (treeContains(node->getChild(), value) || treeContains(node->getSibling(), value));
    }
    void printInput() {
        int position = 0;
        while(this->input[position] != ';') {
            printf("%c", this->input[position]);
            position++;
        }
        printf("\n");
    }
    void parseInput() {
        this->innerNodes = new Node*[this->amountOfInnerNodes];
        int position = 0;
        int innerNodeFlag = 0;
        int counter = 0;
        char c = this->input[position];
        Node* currentNode = this->root;
        while(c != ';') {
            if(c == OPENING_BRACKET) {
                // printf("Adding a child\n");
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
            else if(c == COMMA) {
                // printf("Adding a sibling\n");
                Node* n = new Node();
                n->setParent(currentNode->getParent());
                currentNode->setSibling(n);
                currentNode = n;
                position++;
                c = this->input[position];
            }
            else if(c == CLOSING_BRACKET) {
                // printf("Returning to parent node\n");
                currentNode = currentNode->getParent();
                position++;
                c = this->input[position];
            }
            else {
                // printf("Adding value ");
                int length = 0;
                char* number = new char[8];
                int intNumber;
                while(c != OPENING_BRACKET && c != COMMA && c != CLOSING_BRACKET) {
                    number[length] = c;
                    length++;
                    position++;
                    c = this->input[position];
                }
                sscanf(number, "%d", &intNumber);
                currentNode->setValue(intNumber);
                this->leaves[amountOfLeaves] = currentNode;
                this->amountOfLeaves++;
                // printf("%d\n", intNumber);
            }
        }
        /* printf("Empty = %d | Full = %d\n", this->amountOfInnerNodes, this->amountOfLeaves);
        for(int i = 0; i < this->amountOfInnerNodes; i++) {
            printf("%d ", this->innerNodes[i]->getValue());
        }
        printf("\n");
        for(int i = 0; i < this->amountOfLeaves; i++) {
            printf("%d ", this->leaves[i]->getValue());
        }
        printf("\n"); */
    }
};

class hashMap {
    int** table;
    GeneralTree* first;
    GeneralTree* second;
    int firstSize;
    int secondSize;
    int* firstValues;
    int* secondValues;
public:
    hashMap(GeneralTree* first, GeneralTree* second) {
        this->first = first;
        this->second = second;
        this->firstSize = first->getAmountOfLeaves() + first->getAmountOfInnerNodes();
        this->secondSize = second->getAmountOfLeaves() + second->getAmountOfInnerNodes();
        this->table = new int*[this->firstSize];
        for(int i = 0; i < this->secondSize; i++) {
            this->table[i] = new int[this->secondSize];
        }
        /* this->firstValues = new int[this->firstSize];
        this->secondValues = new int[this->secondSize];
        for(int i = 0; i < this->firstSize; i++) {
            if(i < this->first->getAmountOfLeaves()) firstValues[i] == this->first->getLeaves()[i];
            else firstValues[i] == this->first->getLeaves()[i];
        } */
    }
    ~hashMap() {

    }
    void prepareTable() {
        for(int i = 0; i < this->firstSize; i++) {
            for(int j = 0; j < this->secondSize; j++) {
                this->table[i][j] = 0;
            }
        }
    }
    void handleLeaves() {
        for(int i = 0; i < firstSize; i++) {
            for(int j = 0; j < secondSize; j++) {
                if(i < this->first->getAmountOfLeaves() || j < this->second->getAmountOfLeaves()) {
                    if(j >= this->second->getAmountOfLeaves()) {
                        this->table[i][j] = 2;
                        this->table[i][j] = (this->second->treeContains(this->second->getInnerNodes()[j - this->second->getAmountOfLeaves()], this->first->getLeaves()[i]->getValue())) ? 1 : 0;
                    }
                    else if(i >= this->first->getAmountOfLeaves()) {
                        this->table[i][j] = 3;
                    }
                    else {
                        // this->table[i][j] = 1;
                        this->table[i][j] = (this->first->currentContains(this->first->getLeaves()[i], this->second->getLeaves()[j]->getValue())) ? 1 : 0;
                    }
                }
                else {
                        this->table[i][j] = 4;
                }
            }
        }
    }
    void handleInnerNodes() {
        for(int i = this->first->getAmountOfLeaves(); i < this->firstSize; i++) {
            for(int j = this->second->getAmountOfLeaves(); j < this->secondSize; j++) {
                
            }
        }
    }
    void printTable() {
        printf("\t|");
        for(int i = 0; i < secondSize; i++) {
            if(i < this->second->getAmountOfLeaves()) printf("%d\t|", this->second->getLeaves()[i]->getValue());
            else printf("%d\t|", this->second->getInnerNodes()[i - first->getAmountOfLeaves()]->getValue()); 
        }
        printf("\n-");
        for(int i = 0; i <= secondSize; i++) {
            printf("--------");
        }
        printf("\n");
        for(int i = 0; i < this->firstSize; i++) {
            if(i < this->first->getAmountOfLeaves()) printf("%d\t|", this->first->getLeaves()[i]->getValue());
            else printf("%d\t|", this->first->getInnerNodes()[i - first->getAmountOfLeaves()]->getValue()); 
            for(int j = 0; j < this->secondSize; j++) {
                printf("%d\t|", this->table[i][j]);
            }
            printf("\n");
        }
    }
};

int main(void) {

    int numberOfTrees = 0;
    scanf("%d ", &numberOfTrees);
    GeneralTree** trees = new GeneralTree*[numberOfTrees];
    for(int i = 0; i < numberOfTrees; i++) {
        GeneralTree* gt = new GeneralTree();
        gt->getInput();
        gt->parseInput();
        trees[i] = gt;
    }
    for(int i = 0; i < numberOfTrees; i++) {
        for(int j = i; j < numberOfTrees; j++) {
            if(i == j) continue;
            hashMap* h = new hashMap(trees[i], trees[j]);
            h->prepareTable();
            // h->printTable();
            // printf("\n");
            h->handleLeaves();
            h->handleInnerNodes();
            h->printTable();
        }
    }
    return 0;
}
