#pragma once
class Node {
	short value;
	Node* parent;
	Node* child;
	Node* sibling;
	Node** children;
	short amountOfChildren;
public:
	Node();
	~Node();
	short getValue() const;
	Node* getParent() const;
	Node* getChild() const;
	Node* getSibling() const;
	Node** getChildren() const;
	short getAmountOfChildren() const;
	void setValue(short v);
	void setParent(Node* p);
	void setChild(Node* c);
	void setSibling(Node* s);
	void setChildren(Node** ch);
	void incrementAmountOfChildren();
};

