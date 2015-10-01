#include <iostream>
#include <algorithm>
#include <time.h>
#include <stdio.h>
using namespace std;


void heap_sort(int arr[], int length);

int main(void)
{
	const int N = 10 + 1;
	int left = 0;
	int right = 100;
	int arr[N];

	srand(time(NULL));
	for (int i = 1; i <= N; i++)
	{
		int tmp = rand() % (right - left) + left;
		arr[i] = tmp;
	}

	heap_sort(arr, N + 1);
	
	for (int i = 1; i <= N; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;

	return 0;
}

/**
 * 堆排序
 * 堆排序是用堆来实现的一种排序算法，堆排序分为两个阶段，在堆的构造阶段中，我们将原始数据重新组织安排
 * 进一个堆中；然后在下沉排序阶段，我们从堆中按照递减顺序取出所有元素并得到排序算法
 */
void sink(int arr[], int k, int high)
{
	while (2 * k <= high)
	{
		int child = 2 * k;
		if (child < high && arr[child] < arr[child + 1])
			child++;

		if (arr[k] < arr[child])
			swap(arr[k], arr[child]);
		else
			break;

		k = child;
	}
}

void heap_sort(int arr[], int length)
{
	int high = length - 1;

	/* 这个需要注意i >= 1，如果是i > 1，则建堆不完全 */
	for (int i = high / 2; i >= 1; i--)
		sink(arr, i, high);
	
	while (high > 1)
	{
		swap(arr[1], arr[high--]);
		sink(arr, 1, high);
	}
}
