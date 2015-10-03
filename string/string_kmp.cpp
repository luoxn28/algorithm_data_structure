#include <iostream>
#include <string.h>
using namespace std;

int KmpSearch(char *s, char *p);

int main(void)
{
	char pstr[] = "BBC ABCDAB ABCDABCDABDE";
	char pfind[] = "ABCDABD";

	int index = KmpSearch(pstr, pfind);
	if (index == -1)
		cout << "not find" << endl;
	else
		cout << (char *)&pstr[index] << endl;

	return 0;
}

// 通过代码递推计算求得的next数组
void GetNext(char *p, int next[])
{
	if (!p || !next)
		return;
	
	int length = strlen(p);
	int j = 0;
	int k = -1;

	next[0] = -1;
	while (j < length - 1) // 根据next[j]的值来求next[j+1]的值，所以j != length-1
	{
		// p[k]表示前缀，p[j]表示后缀
		if (k == -1 || p[j] == p[k])
		{
			k++;
			j++;
			next[j] = k;
		}
		else
		{
			k = next[k];
		}
	}
}

/// KMP搜索
int KmpSearch(char *s, char *p)
{
	int lengthS = strlen(s);
	int lengthP = strlen(p);
	int i = 0, j = 0;

	int *next = new int[lengthP];

	GetNext(p, next);
	while (i < lengthS && j < lengthP)
	{
		if (j == -1 || s[i] == p[j])
		{
			i++;
			j++;
		}
		else
		{
			j = next[j];
		}
	}

	delete next;
	if (j == lengthP)
		return i - j;
	else
		return -1;
}


/// 暴力搜索1
int Search1(const char *pstr, const char *pfind)
{
    int n = strlen(pstr);
    int m = strlen(pfind);

    for (int i = 0; i <= n - m; i++)
    {
        int j;
        for (j = 0; j < m; j++)
        {
            if (pstr[i + j] != pfind[j])
                break;
        }

        if (j == m)
            return i;
    }

    return n;
}

/// 暴力搜索2
int Search2(const char *pstr, const char *pfind)
{
    int n = strlen(pstr);
    int m = strlen(pfind);
    int i, j;

    for (i = j = 0; i < n && j < m; i++)
    {
        if (pstr[i] == pfind[j])
            j++;
        else
        {
            i -= j;
            j = 0;
        }
    }

    if (j == m)
        return i - m;
    else
        return n;
}
