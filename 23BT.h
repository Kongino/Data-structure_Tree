#pragma once
#include <iostream>
using namespace std;


class LinkedBinaryTree
{
protected:
	struct Node   // a node in the tree
	{
		int element;
		int element2;
		Node* parent;
		Node* left;
		Node* mid;
		Node* right;
		Node() :element(0), element2(0), parent(NULL), left(NULL), mid(NULL), right(NULL) {}
		bool operator==(const Node* v) const
		{ return (this->element == v->element&&this->element2==v->element2&&this->parent == v->parent&&this->left == v->left&&this->mid==v->mid&&this->right == v->right); }
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
		int elem2() const { return v->element2; }
		void setelem(int x) { v->element = x; }
		void setelem2(int x) { v->element2 = x; }
		Position left() const { return Position(v->left); }
		Position mid() const { return Position(v->mid); }
		Position right() const { return Position(v->right); }
		Position parent() const { return Position(v->parent); }
		bool isRoot() const { return v->parent == NULL; }
		bool isExternal() const { return v->left == NULL && v->mid == NULL && v->right == NULL; }
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
	v->mid = new Node;
	v->mid->parent = v;
	v->right = new Node;
	v->right->parent = v;
	n += 3;
}
