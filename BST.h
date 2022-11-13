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
	int g[N];                 // 트리 형태 출력에 사용되는 배열
	void norder(TPos v);       // 트리를 배열 형태로 나타내는 함수
	void Treeprint();             // 트리 형태로 출력하는 함수
	int numnum(TPos v);       // Tree를 배열 형태로 나타낼 때 사용되는 함수



protected:
	TPos finder(const int& k, const TPos& p);
	TPos root() const;
	TPos inserter(const int& k);
	TPos remover(TPos& v);

	                                         // 강의자료에 있는 코드를 바탕으로 작성한 BST
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
	if (v.elem()!=0)                                // 데이터가 채워져 있지 않은 External Node의 elem값이 0이기 때문에 그것을 제외하고 출력한다.
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
	if (v.elem() != 0)                     // 데이터가 채워져 있지 않은 External Node의 elem값이 0이기 때문에 그것을 제외하고 출력한다.
		cout << v.elem() << " ";
}
void BST::postorderR() { postorder(root()); }
void BST::inorder(TPos v)
{
	if (v.isInternal())
		inorder(v.left());
	if (v.elem() != 0)                      // 데이터가 채워져 있지 않은 External Node의 elem값이 0이기 때문에 그것을 제외하고 출력한다.
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
}                                            // 트리를 배열 형태로 나타내기 위해 Rank를 할당한다.
void BST::norder(TPos v)
{
	int x = numnum(v);
	g[x] = v.elem();
	if (v.isInternal())
	{
		norder(v.left());
		norder(v.right());
	}
	// 트리를 순회하면서 numnum(TPos v)함수의 규칙에 따라 트리를 배열로 표현한다.
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
	  // 트리 형태로 출력하는 함수이다. 최대 63개의 정수들(최대 6층)을 출력할 수 있다.
	// 같은 부모를 가진 노드는 "-"로 연결되며 같은 부모를 가지지 않는 노드는 공백으로 띄어져 있다.
	// 기본적으로 insert되지 않은 부분은 0으로 출력된다. (0은 비어 있는 노드라는 뜻)
	// 한 층을 더 출력하고 싶다면 위 함수에서의 "-"와 공백의 갯수를 적절히 늘린 후(root가 가장 높은 층이고 층을 x이라고 하면, 첫번째 공백은 2^x-1개이고
	// 그 뒤 공백과 "-"의 갯수는 2^(x+1)-1이 되도록 맞춰주면 된다) 마지막 for루프와 같은 방식으로 for루프를 사용하여 g[64]~g[127]을 출력해주면 된다.
	//(이 때, 에러를 막기 위해 배열 g[N]을 선언하는 부분에서 N이 2^(x+1)이상이 되도록 설정해주어야 한다.

	// 출력하는 숫자가 두 자리 수만 되어도 모양이 조금 흐트러지지만 알아보기에 어렵지 않다.
	// 하지만 출력하는 숫자가 세 자리, 네 자리 수를 넘어간다면 모양이 많이 흐트러지는데, 그럴 때엔 <iomanip>에 setw(int n)을 사용하여 출력을 정렬해주면 된다.
	// setw(int n)을 사용할 때, 마찬가지로 위 함수 내부에 있는 공백과 "-"의 갯수 역시 맞춰서 늘어나야 모양이 갖춰진다.

}
