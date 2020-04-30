#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#define OPENING_BRACKET '('
#define CLOSING_BRACKET ')'
#define COMMA ','

class Node {
    int id;
    int value;
    Node* parent;
    Node* child;
    Node* sibling;
public:
    Node() {
        this->id = 0;
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
    int getId() {
        return this->id;
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
    void setId(int id) {
        this->id = id;
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
        printf("Node[%X]\n\tid\t=> %2d\n\tvalue\t=> %2d\n\tparent\t=> [%X]\n\tchild\t=> [%X]\n\tsibling\t=> [%X]\n", this, this->id, this->value, this->parent, this->child, this->sibling);
    }
};

class GeneralTree {
    Node* root;
    char* input = new char[100];
    int amountOfEmptyNodes;
    int amountOfFullNodes;
public:
    GeneralTree() {
        this->root = new Node();
        this->amountOfEmptyNodes = 0;
        this->amountOfFullNodes = 0;
    }
    ~GeneralTree() {

    }
    void getInput() {
        char c;
        int position = 0;
        while((c = getchar()) != '\n') {
            this->input[position] = c;
            position++;
        }
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
        int position = 0;
        char c = this->input[position];
        Node* currentNode = this->root;
        while(c != ';') {
            if(c == OPENING_BRACKET) {
                // printf("Adding a child\n");
                Node* n = new Node();
                n->setParent(currentNode);
                currentNode->setChild(n);
                currentNode = n;
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
                // printf("%d\n", intNumber);
            }
        }
    }
};

void compareTrees(GeneralTree* first, GeneralTree* second);

int main(void) {

    int numberOfTrees = 0;
    scanf("%d ", &numberOfTrees);
    GeneralTree** trees = new GeneralTree*[numberOfTrees];
    for(int i = 0; i < numberOfTrees; i++) {
        GeneralTree* gt = new GeneralTree();
        gt->getInput();
        gt->parseInput();
    }
    for(int i = 0; i < numberOfTrees; i++) {
        for(int j = i; j < numberOfTrees; j++) {
            if(i == j) continue;
            compareTrees(trees[i], trees[j]);
        }
    }
    return 0;
}

void compareTrees(GeneralTree* first, GeneralTree* second) {

}
