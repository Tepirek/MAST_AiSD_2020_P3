#pragma once
class Node {
	unsigned int value;
	Node* parent;
	Node* child;
	Node* sibling;
	Node** children;
	unsigned int amountOfChildren;
public:
	Node();
	~Node();
	unsigned int getValue();
	Node* getParent();
	Node* getChild();
	Node* getSibling();
	Node** getChildren();
	unsigned int getAmountOfChildren();
	void setValue(int value);
	void setParent(Node* parent);
	void setChild(Node* child);
	void setSibling(Node* sibling);
	void setChildren(Node** children);
	void incrementAmountOfChildren();
};

