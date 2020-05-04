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

unsigned int Node::getValue() {
	return this->value;
}

Node* Node::getParent() {
	return this->parent;
}

Node* Node::getChild() {
	return this->child;
}

Node* Node::getSibling() {
	return this->sibling;
}

Node** Node::getChildren() {
	return this->children;
}

unsigned int Node::getAmountOfChildren() {
	return this->amountOfChildren;
}

void Node::setValue(int value) {
	this->value = value;
}

void Node::setParent(Node* parent) {
	this->parent = parent;
}

void Node::setChild(Node* child) {
	this->child = child;
}

void Node::setSibling(Node* sibling) {
	this->sibling = sibling;
}

void Node::setChildren(Node** children) {
	this->children = children;
}

void Node::incrementAmountOfChildren() {
	this->amountOfChildren += 1;
}