#ifndef HASH_H
#define HASH_H

typedef int DataType;
struct LhashNode
{
	DataType data;
	LhashNode *next;
};

/// Lhash才用的是分离连接法，对应一个链表的顺序为从小到大排列
class Lhash
{
	static const int CAPACITY_INIT = 23; // 初始化数组大小，一个素数
public:
	Lhash(int _capacity = CAPACITY_INIT);
	~Lhash();

	void insert(DataType data);
	void remove(DataType data);
	// 存在data返回true，否则返回false
	bool find(DataType data);

	int size() const { return sizes; }
	void print() const;

private:
	// 哈希函数
	int hash(int n) const { return (n % capacity); }
	// 释放一个链表
	void removeList(LhashNode *phead);
	// 打印一个链表
	void printList(LhashNode *phead) const;
	// 返回大于等于n的第一个素数
	int nextPrime(int n) const;

	int sizes; // hash表中元素个数
	int capacity; // hash表的数组大小
	LhashNode *array; // hash表的数组
};

#endif