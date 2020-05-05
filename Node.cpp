#include "Node.h"

Node::Node() {
	this->value = 0;
	this->parent = nullptr;
	this->child = nullptr;
	this->sibling = nullptr;
	this->children = nullptr;
	this->amountOfChildren = 0;
}

Node::~Node() {
	delete this->parent;
	delete this->child;
	delete this->sibling;
	delete[] this->children;
}

int Node::getValue() const {
	return this->value;
}

Node* Node::getParent() const {
	return this->parent;
}

Node* Node::getChild() const {
	return this->child;
}

Node* Node::getSibling() const {
	return this->sibling;
}

Node** Node::getChildren() const {
	return this->children;
}

int Node::getAmountOfChildren() const {
	return this->amountOfChildren;
}

void Node::setValue(int v) {
	this->value = v;
}

void Node::setParent(Node* p) {
	this->parent = p;
}

void Node::setChild(Node* c) {
	this->child = c;
}

void Node::setSibling(Node* s) {
	this->sibling = s;
}

void Node::setChildren(Node** ch) {
	this->children = ch;
}

void Node::incrementAmountOfChildren() {
	this->amountOfChildren += 1;
}