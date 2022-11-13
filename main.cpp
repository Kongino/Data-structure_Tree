#include <iostream>
#include "BT.h"
#include "BST.h"
#include "exc.h"
using namespace std;

int main()
{
	try {

		BST a;

#define B 27
		int ar[B] = { 16,7,5,8,2,6,1,3,9,11,5,5,25,22,17,18,29, 27, 30,33,23, 19, 10, 13, 32, 34, 24};

		for (int i = 0; i < B; i++)
			a.insert(ar[i]);

		cout << "»ðÀÔ ¼ø¼­ : ";
		for (int i = 0; i < B; i++)
			cout << ar[i] << " ";

		
		cout << endl << endl;
		cout << "preorder" << endl;
		a.preorderR();
		cout << endl << endl;

		cout << "postorder" << endl;
		a.postorderR();
		cout << endl << endl;
		
		cout << "inorder" << endl;
		a.inorderR();


		cout << endl << endl << endl;

		a.Treeprint();
	}
	catch (NonexistentElement& ex)
	{
		cout << "error" << endl;
	}

}