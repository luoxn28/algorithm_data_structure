/**
	低位优先的字符串排序
*/

#include <iostream>
#include <string>
#include <string.h>

using namespace std;

void string_lsd(string a[], int length);

int main(void)
{
	string arr[5] = {"name", "main", "null", "turn", "head"};

	for (int i = 0; i < 5; i++)
		cout << arr[i] << " ";
	cout << endl;

	string_lsd(arr, 5);

	for (int i = 0; i < 5; i++)
		cout << arr[i] << " ";
	cout << endl;

	return 0;
}

const int N = 256; // 字母表的范围
/**
 * @brief 低位优先的字符串排序
 * @param [in] a:待排序的string数组
 *		  [out] length:string数组中的元素个数
 * @return void
 * @note 数组中string元素的长度要一样
*/
void string_lsd(string a[], int length)
{
	string *aux = new string[length];
	int *count = new int[N + 1];

	for (int k = length - 1; k >= 0; k--)
	{
		memset(count, 0, sizeof(int)* (N + 1));

		for (int i = 0; i < length; i++)  //计算出现频率
			count[(int)a[i][k] + 1]++;
		for (int i = 1; i < N + 1; i++)   //将频率转换为索引
			count[i] += count[i - 1];
		for (int i = 0; i < length; i++)  //将元素分类
			aux[count[(int)a[i][k]]++] = a[i];
		for (int i = 0; i < length; i++)  //回写
			a[i] = aux[i];
	}

	delete []count;
	delete []aux;
}
