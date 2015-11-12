#include <iostream>
#include "hash.h"

using namespace std;

int main(void)
{
	Lhash lhash;

	lhash.insert(12);
	lhash.insert(14);
	lhash.insert(145);
	lhash.insert(11);
	lhash.insert(14 + 46);
	lhash.insert(14 + 23);

	cout << "the hash size: " << lhash.size() << endl;
	lhash.print();
	cout << endl;

	lhash.remove(14 + 23);
	lhash.remove(14 + 46);
	lhash.remove(14);
	cout << "the hash size: " << lhash.size() << endl;
	lhash.print();
	cout << endl;

	if (lhash.find(14 + 23))
		cout << "find it" << endl;
	else
		cout << "not find it" << endl;

	return 0;
}
