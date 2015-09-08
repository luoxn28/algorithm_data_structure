#include <iostream>
#include <algorithm>
using namespace std;

void select_insert(int a[], int length);
void select_insert2(int a[], int length);

int main(void)
{
	int a[5] = {-1, 6, 2, 0, 12};

	select_insert(a, 5);
	for (int i = 0; i < 5; i++)
		cout << a[i] << " ";
	cout << endl;

	return 0;
}

/**
 * @brief select sort
 * @param [in] a: the array be sorted
 *		  [in] length: the array size
 * @return void
 * @note time complexity O(n^2)
*/
void select_insert(int a[], int length)
{
	for (int i = 0; i < length; i++)
	{
		for (int j = i; j > 0 && a[j-1] > a[j]; j--)
			swap(a[j], a[j-1]);
	}
}

void select_insert2(int a[], int length)
{
	for (int i = 0; i < length; i++)
	{
		int x = a[i], j;
		for (j = i; j > 0 && a[j-1] > x; j--)
			a[j] = a[j-1];
		a[j] = x;
	}
}
