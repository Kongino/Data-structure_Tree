#pragma once
#include <iostream>
#include "23BT.h"
#include <string>
#include "exc.h"
using namespace std;

class THBST
{
private:
	LinkedBinaryTree T;
	int a;
public:
	THBST();
	typedef typename LinkedBinaryTree::Position TPos;
	void insert(const int& k);
	int getsize() { return T.size(); }
	int max(int a, int b, int c)
	{
		if (a >= b&&a >= c)
			return a;
		else if (b >= a&&b >= c)
			return b;
		else
			return c;
	}
	int rd(int a, int b, int c)
	{
		if (a >= b && a <= c || a <= b && a >= c)
			return a;
		else if (b >= a && b <= c || b <= a && b >= c)
			return b;
		else
			return c;
	}
	int min(int a, int b, int c)
	{
		if (a <= b && a <= c)
			return a;
		else if (b <= a && b <= c)
			return b;
		else
			return c;
	}
#define N 200
	int g[N];                 // 트리 형태 출력에 사용되는 배열
	void norder(TPos v);       // 트리를 배열 형태로 나타내는 함수
	void Treeprint();             // 트리 형태로 출력하는 함수
	int numnum(TPos v);       // Tree를 배열 형태로 나타낼 때 사용되는 함수



protected:
	TPos finder(const int& k, const TPos& p);
	TPos root() const;
	TPos inserter(const int& k);

	// 강의자료에 있는 코드를 바탕으로 작성한 BST
};

THBST::THBST() :T(), a(0)
{
	T.addRoot();
}
typename THBST::TPos THBST::root() const { return T.root(); }

typename THBST::TPos THBST::finder(const int& k, const TPos& p)
{
	if (p.isExternal()) return p;
	if (k < p.elem())
	{
		if (p.left().isInternal())
			return finder(k, p.left());
		else
			return p;
	}
	else if (p.elem() < k)
	{
		if (p.mid().isInternal())
			return finder(k, p.mid());
		else if (p.elem2() == 0)
			return p;
		else if (k < p.elem2())
		{
				return p;
		}
		else if (p.elem2() < k)
		{
			if (p.right().isInternal())
				return finder(k, p.right());
			else
				return p;
		}
	}
	else return p;
}
typename THBST::TPos THBST::inserter(const int& k)
{
	TPos v = finder(k, root());

	if (v.elem() == 0)
	{
		T.expandExternal(v);
		v.setelem(k);
	}
	else if (v.elem2() == 0)
	{
		if (v.elem() < k)
			v.setelem2(k);
		else
		{
			v.setelem2(v.elem());
			v.setelem(k);
		}
	}
	else
	{
		int one, two, thr;

		one = min(k, v.elem(), v.elem2());
		two = rd(k, v.elem(), v.elem2());
		thr = max(k, v.elem(), v.elem2());
		{
			if (v == v.parent().left())
			{
				TPos w = v.parent().mid();
				int b = v.parent().elem();
				v.parent().setelem(thr);
				v.setelem2(two);
				v.setelem(one);
				inserter(b);
			}
			else if (v == v.parent().mid())
			{
				TPos w = v.parent().right();
				int b = v.parent().elem2();
				v.parent().setelem2(thr);
				v.setelem2(two);
				v.setelem(one);
				inserter(b);
			}
			else
			{
				TPos w = v.parent().mid();
				int b = v.parent().elem2();
				v.parent().setelem2(one);
				v.setelem(two);
				v.setelem2(thr);
				inserter(b);
			}
		}
	}

	return v;
}

void THBST::insert(const int& k)
{
	inserter(k);
}


int THBST::numnum(TPos v)
{
	if (v.isRoot())
		return 1;
	else if (v == v.parent().left())
		return numnum(v.parent()) * 3 - 1;
	else if (v == v.parent().mid())
		return numnum(v.parent()) * 3;
	else
		return numnum(v.parent()) * 3 + 1;
}                                            // 트리를 배열 형태로 나타내기 위해 Rank를 할당한다.
void THBST::norder(TPos v)
{
	int x = numnum(v);
	g[x*2-1] = v.elem();
	g[x * 2] = v.elem2();
	if (v.isInternal())
	{
		norder(v.left());
		norder(v.mid());
		norder(v.right());
	}
	// 트리를 순회하면서 numnum(TPos v)함수의 규칙에 따라 트리를 배열로 표현한다.
}
void THBST::Treeprint()
{
	norder(root());
	
	cout << "                " << g[1] << "=" << g[2];
	cout << endl;
	
	cout << "    " << g[3] << "=" << g[4] << "---------" << g[5] << "=" << g[6] << "---------" << g[7] << "=" << g[8];
	cout << endl;

	for (int i = 2; i < 5; i++)
	{
		cout << g[(i * 3 - 1) * 2 - 1] << "=" << g[(i * 3 - 1) * 2] << "-" << g[(i * 3) * 2 - 1] << "=" << g[(i * 3) * 2] << "-" << g[(i * 3 + 1) * 2 - 1] << "=" << g[(i * 3 + 1) * 2] << " ";
	}
	cout << endl;
	// 트리 형태로 출력하는 함수이다. 최대 26개의 정수들(최대 4층)을 출력할 수 있다.
	// 한 노드 안에 들어있는 숫자들은 "="로 연결되고, 같은 부모를 가진 노드는 "-"로 연결되며 같은 부모를 가지지 않는 노드는 공백으로 띄어져 있다.
	// 기본적으로 insert되지 않은 부분은 0으로 출력된다. (0은 비어 있는 노드라는 뜻)
	// 한 층을 더 출력하고 싶다면 위 함수에서의 "-"와 "=", 그리고 공백의 갯수를 적절히 늘린 후마지막 for루프와 같은 방식으로 for루프를 사용하여 g[27]~g[78]을 출력해주면 된다.
	//(이 때, 에러를 막기 위해 배열 g[N]을 선언하는 부분에서 N이 마지막 External Node를 전부 포함할 수 있는 숫자가 되도록 늘려저ㅜ야 한다.

	// 출력하는 숫자가 두 자리 수만 되어도 모양이 조금 흐트러지지만 알아보기에 어렵지 않다.
	// 하지만 출력하는 숫자가 세 자리, 네 자리 수를 넘어간다면 모양이 많이 흐트러지는데, 그럴 때엔 <iomanip>에 setw(int n)을 사용하여 출력을 정렬해주면 된다.
	// setw(int n)을 사용할 때, 마찬가지로 위 함수 내부에 있는 공백, "-", "="의 갯수 역시 맞춰서 늘어나야 모양이 갖춰진다.

}


