#include <iostream>
#include <algorithm>
#include <time.h>
#include <stdio.h>
using namespace std;

void quick_sort(int arr[], int length);

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

	quick_sort(arr, N);
	
	for (int i = 0; i < N; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;

	return 0;
}

/**
 * 快速排序
 * 快速排序是一种分治的排序算法，它将一个数组分成两个子数组，将两部分独立地排序。 
 * 快速排序和归并排序是互补的：归并排序将数组分成两个子数组分别排序，并将有序的子数组归并以将整个数组排序；
 * 而快速排序的方式是当两个子数组有序时整个数组也就自然有序了。归并排序中，递归发生在处理整个数组之前，
 * 一个数组被分为两半；快速排序中，递归调用发生在处理整个数组之后，切分的位置取决于数组的内容。
 */
int partion(int arr[], int left, int right)
{
	int x = arr[right];
	int i, j;

	for (i = j = left; i < right; i++)
	{
		if (arr[i] <= x)
			swap(arr[i], arr[j++]);
	}
	swap(arr[j], arr[right]);

	return j;
}

void quick_sort(int arr[], int left, int right)
{
	if (left < right)
	{
		int mid = partion(arr, left, right);
		quick_sort(arr, left, mid - 1);
		quick_sort(arr, mid + 1, right);
	}
}

void quick_sort(int arr[], int length)
{
	if (!arr || length <= 1)
		return;
	
	quick_sort(arr, 0, length - 1);
}

// partion()的第二种写法
/**
 * @brief 把数组arr分为两部分，比选择数字小的移到数组的左边，大的移动到数组右边
 * @param [in] arr:待划分数组
 *		  [in] left:数组左边界
 *		  [in] right:数组右边界
 * @return 所选择数字最后所在位置下标值
*/
int partion2(int arr[], int left, int right)
{
	if (left < right)
	{
		int x = arr[left];
		while (left < right)
		{
			while (left < right && arr[right] >= x)
				right--;
			arr[left] = arr[right];

			while (left < right && arr[left] <= x)
				left++;
			arr[right] = arr[left];
		}
		arr[left] = x;
	}

	return left;
}
