#include <iostream>
#include "hash.h"

Lhash::Lhash(int _capacity) : sizes(0)
{
	if (_capacity <= CAPACITY_INIT)
		capacity = _capacity;
	else
		capacity = nextPrime(_capacity + 1);

	array = new LhashNode[capacity];
	for (int i = 0; i < capacity; i++)
	{
		array[i].data = 0;
		array[i].next = NULL;
	}
}

Lhash::~Lhash()
{
	for (int i = 0; i < capacity; i++)
	{
		if (array[i].next)
			removeList(array[i].next);
	}
	delete []array;
}

void Lhash::insert(DataType data)
{
	int index = hash(data);
	LhashNode *phead = array[index].next;

	LhashNode *pnode = new LhashNode;
	pnode->data = data;
	pnode->next = NULL;

	if (!phead) // 此时对应的为空链表
	{
		array[index].next = pnode;
		array[index].data++; // 该链表中元素个数
		sizes++; // hash表中元素个数
	}
	else
	{
		LhashNode *pprev = &array[index]; // pprev为phead的前一个节点
		while (phead && phead->data < data)
		{
			pprev = phead;
			phead = phead->next;
		}

		// phead为NULL时pnode应插入到链表结尾，phead->data != data表示pnode应该插入phead前面
		if (!phead || phead->data != data)
		{
			pnode->next = phead;
			pprev->next = pnode;
			array[index].data++;
			sizes++;
		}
	}
}

void Lhash::remove(DataType data)
{
	bool found = find(data);

	if (found)
	{
		int index = hash(data);
		LhashNode *pnode = &array[index];
		while (pnode->next && pnode->next->data != data)
			pnode = pnode->next;

		LhashNode *ptmp = pnode->next;
		pnode->next = ptmp->next;
		delete ptmp;

		array[index].data--;
		sizes--;
	}
}

bool Lhash::find(DataType data)
{
	int index = hash(data);

	LhashNode *pnode = array[index].next;
	while (pnode)
	{
		if (pnode->data == data)
			return true;
		else if (pnode->data > data) // 链表中元素按从小到大顺序排列
			return false;
		pnode = pnode->next;
	}

	return false;
}

void Lhash::print() const
{
	for (int i = 0; i < capacity; i++)
	{
		std::cout << i << ": ";
		printList(array[i].next);
	}
}

void Lhash::removeList(LhashNode *phead)
{
	LhashNode *pnode = phead;

	while (pnode)
	{
		LhashNode *ptmp = pnode->next;
		delete pnode;
		pnode = ptmp;
	}
}

void Lhash::printList(LhashNode *pnode) const
{
	while (pnode)
	{
		std::cout << pnode->data << " ";
		pnode = pnode->next;
	}
	std::cout << std::endl;
}

int Lhash::nextPrime(int n) const
{
	while (n)
	{
		bool isprime = true;
		for (int i = 2; i <= n/2; i++)
		{
			if (n % i == 0)
			{
				isprime = false;
				break;
			}
		}
		if (isprime)
			break;

		n++;
	}
	return n;
}