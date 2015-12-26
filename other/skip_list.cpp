#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stddef.h>
using namespace std;

// note: 因为我们分配内存使用的是malloc，所以key和value的类型不要是STL中的容器，
// 否则的话可能会出现问题(运行时错误)
typedef int KeyType;
typedef int ValueType;

typedef struct node
{
	KeyType key;            // key值
	ValueType value;        // value值
	struct node* next[1];   // 后继数组
} Node;

typedef struct skip_list
{
	int level;  // 层数
	Node **head; // 指向头结点
} SkipList;

#define MAX_LEVEL 6
#define new_node(n) \
	((Node*)malloc(sizeof(Node)+(n)* sizeof(Node*)))

static int RandomLevel()
{
	int level = 1;

	while (rand() % 2) {
		level++;
	}
	level = (level > MAX_LEVEL ? MAX_LEVEL : level);
	return level;
}

// 创建节点
static Node* CreateNode(int level, KeyType key, ValueType value)
{
	Node* node = (Node *)malloc(sizeof(Node) + sizeof(Node*) * level);
	if (!node) {
		return NULL;
	}

	node->key = key;
	node->value = value;
	return node;
}

// 创建跳表
SkipList* CreateSkipList()
{
	SkipList *list = (SkipList*)malloc(sizeof(SkipList));
	if (!list) {
		return NULL;
	}

	list->level = MAX_LEVEL;
	list->head = (Node **)malloc(sizeof(Node*) * MAX_LEVEL);
	if (!list->head) {
		free(list);
		return NULL;
	}
	// 将head的next数组初始化
	for (int i = 0; i < MAX_LEVEL; i++) {
		list->head[i] = NULL;
	}

	srand(time(NULL));
	return list;
}

// 跳表插入操作
// step1: 查找到在每层待插入位置，更新update数组
// step2: 产生一个随机层数
// step3: 从高层向下插入，与普通链表的插入完全相同
bool Insert(SkipList* list, KeyType key, ValueType value)
{
	
	// key需要插入在该跳表的第一个节点位置
	if (!list->head[0] || key < list->head[0]->key) {
		// level的大小不会超过 MAX_LEVEL
		int level = RandomLevel();
		Node *temp = CreateNode(level - 1, key, value);
		if (!temp) {
			return false;
		}

		for (int i = level - 1; i >= 0; i--) {
			temp->next[i] = list->head[i];
			list->head[i] = temp;
		}
		// 插入成功
		return true;
	}
	
	Node *update[MAX_LEVEL];
	Node *p, *q;
	int i;

	for (i = 0; i < MAX_LEVEL; i++) {
		update[i] =list->head[i];
	}

	i = list->level - 1;
	for (; i >= 0; i--) {
		p = q = update[i];
		while (p && p->key < key) {
			q = p;
			p = p->next[i];
		}
		update[i] = q;
	}
	if (p && p->key == key) {
		// 跳表中已存在该key
		p->value = value;
		return true;
	}

	// level的大小不会超过 MAX_LEVEL
	int level = RandomLevel();
	Node *temp = CreateNode(level - 1, key, value);
	if (!temp) {
		return false;
	}

	// 逐层更新节点的指针，和普通链表插入一样
	for (i = level - 1; i >= 0; i--) {
		if (update[i]) {
			temp->next[i] = update[i]->next[i];
			update[i]->next[i] = temp;
		}
		else {
			temp->next[i] = update[i];
		}
	}
	return true;
}

// 跳表销毁操作
void FreeSkipList(SkipList *list)
{
	Node *node = list->head[0], *remove;

	while (node) {
		remove = node;
		node = node->next[0];
		free(remove);
	}
	free(list->head);
	free(list);
}

#define SKIP_LIST_DEBUG
#ifdef SKIP_LIST_DEBUG
void PrintSkipList(const SkipList* list)
{
	Node *node = list->head[0];

	while (node) {
		std::cout << node->key << ": " << node->value << endl;
		node = node->next[0];
	}
}
#endif

int main(int argc, char** argv)
{
	SkipList *list = CreateSkipList();

	for (int i = 0; i < 100; i++) {
		Insert(list, 100 - i, i);
	}

	PrintSkipList(list);

	FreeSkipList(list);

	return 0;
}
