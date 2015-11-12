#include <iostream>
#include "rbtree.h"

using namespace std;

int main(void)
{
	Rbtree tree;

	tree.insert(200);
	tree.insert(1);
	tree.insert(12);
	
	tree.insert(10);
	tree.insert(23);
	
	tree.insert(14);
	tree.insert(39);
	tree.insert(59);
	
	tree.insert(69);
	tree.insert(30);
	tree.insert(25);

	cout << "size: " << tree.size() << endl;
	tree.print();
	cout << endl;

	tree.remove(25);
	tree.remove(69);
	tree.remove(30);
	tree.remove(23);
	cout << "size: " << tree.size() << endl;
	tree.print();
	cout << endl;

	return 0;
}