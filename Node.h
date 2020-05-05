#pragma once
class Node {
	int value;
	Node* parent;
	Node* child;
	Node* sibling;
	Node** children;
	int amountOfChildren;
public:
	Node();
	~Node();
	int getValue() const;
	Node* getParent() const;
	Node* getChild() const;
	Node* getSibling() const;
	Node** getChildren() const;
	int getAmountOfChildren() const;
	void setValue(int v);
	void setParent(Node* p);
	void setChild(Node* c);
	void setSibling(Node* s);
	void setChildren(Node** ch);
	void incrementAmountOfChildren();
};

