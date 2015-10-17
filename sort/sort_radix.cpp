#include <iostream>
#include <algorithm>
//#include <ctime>
#include <stdio.h>
#include <string.h>

using namespace std;

// low和high表示元素区间，前开后闭，[low, high)
int low = 0;
int high = 100;
#define N 100

void radix_sort(int arr[], int length);

int main(void)
{
	int arr[N];
	srand(time(NULL));

	for (int i = 0; i < N; i++)
	{
		int x = rand() % (high - low) + low;
		arr[i] = x;
	}

	radix_sort(arr, N);

	for (int i = 0; i < N; i++)
		cout << arr[i] << " ";
	cout << endl;

	return 0;
}

/**
 * @brief 基数排序
 * @parm [in] arr:待排序的数组
 *	  		  length:待排序数组大小
 * @return void
 * @note 基数排序不是基于比较的排序算法
*/
void radix_sort(int arr[], int length)
{
	int sectionSize = high - low;
	int *aux = new int[length];
	int *cnt = new int[sectionSize];

	memset(cnt, 0, sizeof(int) * sectionSize);

	for (int i = 0; i < length; i++)		// 计算出现频率
		cnt[arr[i] + 1]++;
	for (int i = 1; i < sectionSize; i++)	// 频率转化为索引
		cnt[i] += cnt[i - 1];
	for (int i = 0; i < length; i++)		// 将元素分类
		aux[cnt[arr[i]]++] = arr[i];
	for (int i = 0; i < length; i++)		// 回写
		arr[i] = aux[i];

	delete []cnt;
	delete []aux;
}
