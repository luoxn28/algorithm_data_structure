#include <iostream>
#include <algorithm>
using namespace std;

int binary_search(int a[], int length, int key);

int main(void)
{
	int a[6] = { 1, 2, 3, 4, 5, 6};

	int index = binary_search(a, 6, 4);
	if (index != -1)
		cout << "find it, index = " << index << endl;
	else
		cout << "not find it" << endl;

	return 0;
}

/**
 * @brief 二分查找
 * @param [in] key:待查找的键
 *		  [in] a:查找数组
 *		  [in] length:数组长度
 * @return 找到为该键在数组中的下标，否则为-1
 * @note while (low <= high)不能改为<，否则的话条件判断不完整，比如：
 *		a[3] = {1, 3, 5};待查找的键为5，此时在(low < high)条件下就会找不到
 *		因为low和high相等时，指向元素5，但是此时条件不成立，没有进入while()中
*/
int binary_search(int a[], int length, int key)
{
	int left = 0;
	int right = length - 1;

	while (left <= right)
	{
		int mid = left + ((right - left) >> 1);
		if (key == a[mid])
			return mid;
		else if (key < a[mid])
			right = mid - 1;
		else
			left = mid + 1;
	}

	return -1;
}