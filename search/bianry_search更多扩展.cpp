// 以下是二分查找的各种变种
// 查找第一个与key相等的值、最后一个与key相等的值、第一个等于或大于key的值、
// 第一个大于key的值、最后一个小于或等于key的值、最后一个小于key的值
// 参考链接：http://blog.chinaunix.net/uid-1844931-id-3337784.html

#include <iostream>
using namespace std;

int FindFirstEqual(int a[], int length, int key);
int FindLastEqual(int a[], int length, int key);
int FindFirstEqualLarger(int a[], int length, int key);
int FindFirstLarger(int a[], int length, int key);
int FindLastEqualSmaller(int a[], int length, int key);
int FindLastSmaller(int a[], int length, int key);

int main(void)
{
	int a1[5] = { 1, 2, 2, 3, 4 };
	int a2[5] = { 2, 2, 3, 4, 5 };
	int a3[5] = { 1, 2, 3, 4, 4 };

	cout << FindLastSmaller(a1, 5, 2) << endl;
	cout << FindLastSmaller(a2, 5, 2) << endl;
	cout << FindLastSmaller(a3, 5, 4) << endl;
	cout << FindLastSmaller(a1, 5, -3) << endl;
	cout << FindLastSmaller(a1, 5, 12) << endl;

	return 0;
}

/// 查找第一个与key相等的值
int FindFirstEqual(int a[], int length, int key)
{
	int left = 0;
	int right = length - 1;

	while (left <= right)
	{
		int mid = left + ((right - left) >> 1);
		if (key <= a[mid])
			right = mid - 1;
		else
			left = mid + 1;
	}

	if (left < length && a[left] == key)
		return left;

	return -1;
}

/// 查找最后一个与key相等的值
int FindLastEqual(int a[], int length, int key)
{
	int left = 0;
	int right = length - 1;

	while (left <= right)
	{
		int mid = left + ((right - left) >> 1);
		if (key >= a[mid])
			left = mid + 1;
		else
			right = mid - 1;
	}

	if (right >= 0 && a[right] == key)
		return right;

	return -1;
}

/// 查找第一个等于或大于key的值
int FindFirstEqualLarger(int a[], int length, int key)
{
	int left = 0;
	int right = length - 1;

	while (left <= right)
	{
		int mid = left + ((right - left) >> 1);
		if (key <= a[mid])
			right = mid - 1;
		else
			left = mid + 1;
	}

	return left;
}

/// 查找第一个大于key的值
int FindFirstLarger(int a[], int length, int key)
{
	int left = 0;
	int right = length - 1;

	while (left <= right)
	{
		int mid = left + ((right - left) >> 1);
		if (key >= a[mid])
			left = mid + 1;
		else
			right = mid - 1;
	}

	return left;
}

/// 查找最后一个等于或小于key的值
int FindLastEqualSmaller(int a[], int length, int key)
{
	int left = 0;
	int right = length - 1;

	while (left <= right)
	{
		int mid = left + ((right - left) >> 1);
		if (key >= a[mid])
			left = mid + 1;
		else
			right = mid - 1;
	}

	return right;
}

/// 查找最后一个小于key的值
int FindLastSmaller(int a[], int length, int key)
{
	int left = 0;
	int right = length - 1;

	while (left <= right)
	{
		int mid = left + ((right - left) >> 1);
		if (key > a[mid])
			left = mid + 1;
		else
			right = mid - 1;
	}

	return right;
}