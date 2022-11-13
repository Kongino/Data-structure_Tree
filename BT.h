#pragma once
#include <iostream>
using namespace std;


class LinkedBinaryTree
{
protected:
	struct Node   // a node in the tree
	{
		int element;
		Node* parent;
		Node* left;
		Node* right;
		Node() :element(0), parent(NULL), left(NULL), right(NULL) {}
		bool operator==(const Node* v) const { return (this->element == v->element&&this->parent == v->parent&&this->left == v->left&&this->right == v->right); }
	};
	typedef Node* NodePtr;

public:

	class Position
	{
	private:
		Node * v;
	public:
		Position(Node* _v = NULL) :v(_v) {}
		int elem() const { return v->element; }
		void setelem(int x) { v->element = x; }
		Position left() const { return Position(v->left); }
		Position right() const { return Position(v->right); }
		Position parent() const { return Position(v->parent); }
		bool isRoot() const { return v->parent == NULL; }
		bool isExternal() const { return v->left == NULL && v->right == NULL; }
		bool isInternal() const { return !isExternal(); }
		bool operator==(const Position& p) const { return this->v == p.v; }
		friend LinkedBinaryTree;
	};
	LinkedBinaryTree();
	int size() const;
	bool empty() const;
	Position root() const;
	void addRoot();
	void expandExternal(const Position& p);
	Position removeAboveExternal(const Position& p);

private:
	Node * _root;            //pointer to the root
	int n;
};
LinkedBinaryTree::LinkedBinaryTree()
	:_root(NULL), n(0) {}
int LinkedBinaryTree::size() const { return n; }
bool LinkedBinaryTree::empty() const { return size() == 0; }
LinkedBinaryTree::Position LinkedBinaryTree::root() const { return Position(_root); }
void LinkedBinaryTree::addRoot()
{
	_root = new Node;
	n = 1;
}
void LinkedBinaryTree::expandExternal(const Position& p)
{
	Node* v = p.v;
	v->left = new Node;
	v->left->parent = v;
	v->right = new Node;
	v->right->parent = v;
	n += 2;
}
LinkedBinaryTree::Position LinkedBinaryTree::removeAboveExternal(const Position& p)
{
	Node* w = p.v;
	Node* v = w->parent;
	Node* sib = (w == v->left ? v->right : v->left);
	if (v == _root)
	{
		_root = sib;
		sib->parent = NULL;
	}
	else
	{
		Node* gpar = v->parent;
		if (v == gpar->left)
			gpar->left = sib;
		else
			gpar->right = sib;
		sib->parent = gpar;
	}
	delete w;
	delete v;
	n -= 2;
	return Position(sib);
}
