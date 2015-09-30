#include <iostream>
#include <algorithm>
#include <time.h>
#include <stdio.h>
using namespace std;

void merge_sort(int a[], int length);

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

	merge_sort(arr, N);
	
	for (int i = 0; i < N; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;

	return 0;
}

void merge(int a[], int aux[], int left, int mid, int right)
{
	int i = left;
	int j = mid + 1;
	int k = left;

	while (i <= mid && j <= right)
	{
		if (a[j] < a[i])
			aux[k++] = a[j++];
		else
			aux[k++] = a[i++];
	}
	while (i <= mid)
		aux[k++] = a[i++];
	while (j <= right)
		aux[k++] = a[j++];
	
	for (i = left; i <= right; i++)
		a[i] = aux[i];
}

void merge_sort(int a[], int aux[], int left, int right)
{
	if (left < right)
	{
		int mid = left + ((right - left) >> 1);
		merge_sort(a, aux, left, mid);
		merge_sort(a, aux, mid + 1, right);
		merge(a, aux, left, mid, right);
	}
}

/// 自顶向下的归并排序
void merge_sort(int a[], int length)
{
	int *aux = new int[length];

	merge_sort(a, aux, 0, length - 1);

	delete aux;
}
