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
	int g[N];                 // Ʈ�� ���� ��¿� ���Ǵ� �迭
	void norder(TPos v);       // Ʈ���� �迭 ���·� ��Ÿ���� �Լ�
	void Treeprint();             // Ʈ�� ���·� ����ϴ� �Լ�
	int numnum(TPos v);       // Tree�� �迭 ���·� ��Ÿ�� �� ���Ǵ� �Լ�



protected:
	TPos finder(const int& k, const TPos& p);
	TPos root() const;
	TPos inserter(const int& k);

	// �����ڷῡ �ִ� �ڵ带 �������� �ۼ��� BST
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
}                                            // Ʈ���� �迭 ���·� ��Ÿ���� ���� Rank�� �Ҵ��Ѵ�.
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
	// Ʈ���� ��ȸ�ϸ鼭 numnum(TPos v)�Լ��� ��Ģ�� ���� Ʈ���� �迭�� ǥ���Ѵ�.
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
	// Ʈ�� ���·� ����ϴ� �Լ��̴�. �ִ� 26���� ������(�ִ� 4��)�� ����� �� �ִ�.
	// �� ��� �ȿ� ����ִ� ���ڵ��� "="�� ����ǰ�, ���� �θ� ���� ���� "-"�� ����Ǹ� ���� �θ� ������ �ʴ� ���� �������� ����� �ִ�.
	// �⺻������ insert���� ���� �κ��� 0���� ��µȴ�. (0�� ��� �ִ� ����� ��)
	// �� ���� �� ����ϰ� �ʹٸ� �� �Լ������� "-"�� "=", �׸��� ������ ������ ������ �ø� �ĸ����� for������ ���� ������� for������ ����Ͽ� g[27]~g[78]�� ������ָ� �ȴ�.
	//(�� ��, ������ ���� ���� �迭 g[N]�� �����ϴ� �κп��� N�� ������ External Node�� ���� ������ �� �ִ� ���ڰ� �ǵ��� �÷����̾� �Ѵ�.

	// ����ϴ� ���ڰ� �� �ڸ� ���� �Ǿ ����� ���� ��Ʈ�������� �˾ƺ��⿡ ����� �ʴ�.
	// ������ ����ϴ� ���ڰ� �� �ڸ�, �� �ڸ� ���� �Ѿ�ٸ� ����� ���� ��Ʈ�����µ�, �׷� ���� <iomanip>�� setw(int n)�� ����Ͽ� ����� �������ָ� �ȴ�.
	// setw(int n)�� ����� ��, ���������� �� �Լ� ���ο� �ִ� ����, "-", "="�� ���� ���� ���缭 �þ�� ����� ��������.

}


