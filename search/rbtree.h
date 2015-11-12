#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>

typedef int DataType;
enum Color { RED, BLACK };

class TreeNode
{
public:
	Color color;
	DataType data;
	TreeNode *left;
	TreeNode *right;
	TreeNode *par; // 父节点
	TreeNode *sentinel; // 哨兵节点

	TreeNode(DataType _data, TreeNode *_sentinel) : color(RED), data(_data)
	{
		sentinel = _sentinel;
		left = right = par = _sentinel;
	}
	~TreeNode()
	{
		if (left != sentinel)
			delete left;
		if (right != sentinel)
			delete right;

		sentinel->data--; // 树中的节点个数
		//std::cout << "remove node ok" << std::endl; // 显示释放节点记录
	}
};

class Rbtree
{
public:
	Rbtree();
	~Rbtree();

	void insert(DataType data);
	void remove(DataType data);

	const TreeNode *find(DataType data) const;
	TreeNode *find(DataType data) { return const_cast<TreeNode *>(((const Rbtree *)this)->find(data)); }
	int size() const { return nil->data; }
	void print() const { print_internal(root); }

private:
	// 左旋操作和右旋操作
	void rotateLeft(TreeNode *pnode);
	void rotateRight(TreeNode *pnode);

	// 插入后的修正函数
	void insert_internal(TreeNode *pnode);
	// 删除后的修正函数
	void remove_internal(TreeNode *pnode);
	// 调整两个节点关系，其中一个替换另一个，newnode要替换oldnode，在删除节点操作中用到
	void transplant(TreeNode *oldnode, TreeNode *newnode)
	{
		if (oldnode->par == nil) // 此时oldnode为根节点
			root = newnode;
		else if (oldnode == oldnode->par->left)
			oldnode->par->left = newnode;
		else
			oldnode->par->right = newnode;

		newnode->par = oldnode->par;
	}

	void print_internal(TreeNode *pnode) const;
	TreeNode *min(TreeNode *pnode) const;

	TreeNode *root; // 根节点
	TreeNode *nil; // 哨兵节点，nil.data作为rbtree的节点个数
};

#endif