#include <iostream>
#include <algorithm>
#include <time.h>
#include <stdio.h>
using namespace std;

void insert_sort(int a[], int length);
void insert2_sort(int a[], int length);

int main(void)
{
	const int N = 10;
	int left = 0;
	int right = 100;
	int arr[N];

	srand(time(NULL));
	for (int i = 0; i < N; i++)
	{
		int tmp = rand() % (right - left) + left;
		arr[i] = tmp;
	}

	insert_sort(arr, N);

	for (int i = 0; i < N; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;

	return 0;
}

/**
 * @brief insert sort
 * @param [in] arr: the array be sorted
 *		  [in] length: the array size
 * @return void
 * @note time complexity O(n^2)
*/
void insert_sort(int arr[], int length)
{
	for (int i = 0; i < length; i++)
	{
		for (int j = i; j > 0 && arr[j-1] > arr[j]; j--)
			swap(arr[j], arr[j-1]);
	}
}

void insert2_sort(int arr[], int length)
{
	for (int i = 0; i < length; i++)
	{
		int x = arr[i], j;
		for (j = i; j > 0 && arr[j-1] > x; j--)
			arr[j] = arr[j-1];
		arr[j] = x;
	}
}
