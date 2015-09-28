#include <iostream>
#include <algorithm>
using namespace std;

void select_shell(int a[], int length);

int main(void)
{
	int a[5] = {-1, 6, 2, 0, 12};

	select_shell(a, 5);
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
 *		 希尔排序类似于插入排序，只是插入排序只会交换相邻的元素，而希尔排序
 *		 会交换不相邻的元素以对数组进行局部排序
*/
void select_shell(int a[], int length)
{
	for (int inc = length / 2; inc > 0; inc /= 2)
	{
		for (int i = inc; i < length; i++)
		{
			for (int j = i; j >= inc && a[j-inc] > a[j]; j -= inc)
				swap(a[j], a[j-inc]);
		}
	}
}

