#pragma once
#include <iostream>
#include "BT.h"
#include <string>
#include "exc.h"
using namespace std;

class BST
{
private:
	LinkedBinaryTree T;
	int a;
public:
	BST();
	typedef typename LinkedBinaryTree::Position TPos;
	TPos find(const int& k);
	void insert(const int& k) { inserter(k); }
	void remove(const int& k) throw(NonexistentElement);
	void preorder(TPos v);
	void preorderR();
	void postorder(TPos v);
	void postorderR();
	void inorder(TPos v);
	void inorderR();
	int getsize() { return T.size(); }
#define N 200
	int g[N];                 // Ʈ�� ���� ��¿� ���Ǵ� �迭
	void norder(TPos v);       // Ʈ���� �迭 ���·� ��Ÿ���� �Լ�
	void Treeprint();             // Ʈ�� ���·� ����ϴ� �Լ�
	int numnum(TPos v);       // Tree�� �迭 ���·� ��Ÿ�� �� ���Ǵ� �Լ�



protected:
	TPos finder(const int& k, const TPos& p);
	TPos root() const;
	TPos inserter(const int& k);
	TPos remover(TPos& v);

	                                         // �����ڷῡ �ִ� �ڵ带 �������� �ۼ��� BST
};

BST::BST() :T(), a(0)
{
	T.addRoot();
}
typename BST::TPos BST::root() const { return T.root(); }

typename BST::TPos BST::finder(const int& k, const TPos& p)
{
	if (p.isExternal()) return p;
	if (k < p.elem()) return finder(k, p.left());
	else if (p.elem() < k) return finder(k, p.right());
	else return p;
}
typename BST::TPos BST::find(const int& k)
{
	TPos l=NULL;
	TPos v = finder(k, root());
	if (v.isInternal()) return v;
	else return l;
}
typename BST::TPos BST::inserter(const int& k)
{
	TPos v = finder(k, root());
	while (v.isInternal())
		v = finder(k, v.right());
	T.expandExternal(v);
	v.setelem(k);
	return v;
}
typename BST::TPos BST::remover(TPos& v)
{
	TPos w;
	if (v.left().isExternal())
		w = v.left();
	else if (v.right().isExternal())
		w = v.right();
	else
	{
		w = v.right();
		do
			w = w.left();
		while (w.isInternal());
		TPos u = w.parent();
		u.setelem(w.elem());
	}
	return T.removeAboveExternal(w);
}
void BST::remove(const int& k) throw(NonexistentElement)
{
	TPos v = finder(k, root());
	if (v.isExternal())
		throw NonexistentElement("Erase of nonexistent");
	remover(v);
}
void BST::preorder(TPos v)
{
	if (v.elem()!=0)                                // �����Ͱ� ä���� ���� ���� External Node�� elem���� 0�̱� ������ �װ��� �����ϰ� ����Ѵ�.
		cout << v.elem() << " ";
	if (v.isInternal())
	{
		preorder(v.left());
		preorder(v.right());
	}
}
void BST::preorderR() { preorder(root()); }
void BST::postorder(TPos v)
{
	if (v.isInternal())
	{
		postorder(v.left());
		postorder(v.right());
	}
	if (v.elem() != 0)                     // �����Ͱ� ä���� ���� ���� External Node�� elem���� 0�̱� ������ �װ��� �����ϰ� ����Ѵ�.
		cout << v.elem() << " ";
}
void BST::postorderR() { postorder(root()); }
void BST::inorder(TPos v)
{
	if (v.isInternal())
		inorder(v.left());
	if (v.elem() != 0)                      // �����Ͱ� ä���� ���� ���� External Node�� elem���� 0�̱� ������ �װ��� �����ϰ� ����Ѵ�.
		cout << v.elem() << " ";
	if (v.isInternal())
		inorder(v.right());
}
void BST::inorderR() { inorder(root()); }

int BST::numnum(TPos v)
{
	if (v.isRoot())
		return 1;
	else if (v == v.parent().left())
		return numnum(v.parent()) * 2;
	else
		return numnum(v.parent()) * 2 + 1;
}                                            // Ʈ���� �迭 ���·� ��Ÿ���� ���� Rank�� �Ҵ��Ѵ�.
void BST::norder(TPos v)
{
	int x = numnum(v);
	g[x] = v.elem();
	if (v.isInternal())
	{
		norder(v.left());
		norder(v.right());
	}
	// Ʈ���� ��ȸ�ϸ鼭 numnum(TPos v)�Լ��� ��Ģ�� ���� Ʈ���� �迭�� ǥ���Ѵ�.
}
void BST::Treeprint()
{
	norder(root());
	cout << "                               " << g[1] << endl;
	cout << "               " << g[2] << "-------------------------------" << g[3] << endl;
	cout << "       " << g[4] << "---------------" << g[5] << "               " << g[6] << "---------------" << g[7] << endl;

	cout << "   ";
	for (int i = 4; i < 8; i++)
		cout << g[i * 2] << "-------" << g[i * 2 + 1] << "       ";
	cout << endl;
	cout<<" ";
	for (int i = 8; i < 16; i++)
		cout << g[i * 2] << "---" << g[i * 2 + 1] << "   ";
	cout << endl;
	for (int i = 16; i < 32; i++)
		cout << g[i * 2] << "-" << g[i * 2 + 1] << " ";
	cout << endl;
	  // Ʈ�� ���·� ����ϴ� �Լ��̴�. �ִ� 63���� ������(�ִ� 6��)�� ����� �� �ִ�.
	// ���� �θ� ���� ���� "-"�� ����Ǹ� ���� �θ� ������ �ʴ� ���� �������� ����� �ִ�.
	// �⺻������ insert���� ���� �κ��� 0���� ��µȴ�. (0�� ��� �ִ� ����� ��)
	// �� ���� �� ����ϰ� �ʹٸ� �� �Լ������� "-"�� ������ ������ ������ �ø� ��(root�� ���� ���� ���̰� ���� x�̶�� �ϸ�, ù��° ������ 2^x-1���̰�
	// �� �� ����� "-"�� ������ 2^(x+1)-1�� �ǵ��� �����ָ� �ȴ�) ������ for������ ���� ������� for������ ����Ͽ� g[64]~g[127]�� ������ָ� �ȴ�.
	//(�� ��, ������ ���� ���� �迭 g[N]�� �����ϴ� �κп��� N�� 2^(x+1)�̻��� �ǵ��� �������־�� �Ѵ�.

	// ����ϴ� ���ڰ� �� �ڸ� ���� �Ǿ ����� ���� ��Ʈ�������� �˾ƺ��⿡ ����� �ʴ�.
	// ������ ����ϴ� ���ڰ� �� �ڸ�, �� �ڸ� ���� �Ѿ�ٸ� ����� ���� ��Ʈ�����µ�, �׷� ���� <iomanip>�� setw(int n)�� ����Ͽ� ����� �������ָ� �ȴ�.
	// setw(int n)�� ����� ��, ���������� �� �Լ� ���ο� �ִ� ����� "-"�� ���� ���� ���缭 �þ�� ����� ��������.

}
