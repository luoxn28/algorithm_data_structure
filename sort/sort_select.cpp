#include <iostream>
#include <algorithm>
using namespace std;

void select_sort(int a[], int length);

#define N 100
int main(void)
{
	int left = 0;
	int right = 100;
	int arr[N];

	srand(time(NULL));

	for (int i = 0; i < N; i++)
	{
		int x = rand() % (right - left) + left;
		arr[i] = x;
	}

	select_sort(arr, N);

	for (int i = 0; i < N; i++)
		cout << arr[i] << " ";
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
