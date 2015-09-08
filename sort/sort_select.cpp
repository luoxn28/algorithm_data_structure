#include <iostream>
#include <algorithm>
using namespace std;

void select_sort(int a[], int length);

int main(void)
{
	int a[5] = {-1, 6, 2, 0, 12};

	select_sort(a, 5);
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
void select_sort(int a[], int length)
{
	for (int i = 0; i < length; i++)
	{
		int min = i;
		for (int j = i + 1; j < length; j++)
		{
			if (a[j] < a[min])
				min = j;
		}
		if (min != i)
			swap(a[min], a[i]);
	}
}
