#include "rbtree.h"
#include <iostream>

Rbtree::Rbtree() : nil(new TreeNode(0, NULL))
{
	nil->color = BLACK;
	nil->sentinel = nil;
	nil->left = nil->right = nil->par = nil;

	root = nil;
}

Rbtree::~Rbtree()
{
	if (root != nil)
		delete root;

	delete nil; // 释放哨兵节点内存
}

void Rbtree::insert(DataType data)
{
	if (root == nil)
	{
		root = new TreeNode(data, nil);
		root->color = BLACK;
		nil->data++;
	}
	else
	{
		TreeNode *pnode = root;
		TreeNode *prevnode = pnode; // prenode是pnode的父节点，初始化为pnode
		while (pnode != nil)
		{
			prevnode = pnode;
			if (data < pnode->data)
				pnode = pnode->left;
			else if (data > pnode->data)
				pnode = pnode->right;
			else
				return; // 此时插入的节点rbtree中已经存在了
		}

		TreeNode *insertnode = new TreeNode(data, nil);
		nil->data++;

		insertnode->par = prevnode;
		if (data < prevnode->data)
			prevnode->left = insertnode;
		else
			prevnode->right = insertnode;

		if (prevnode->color == RED)
			insert_internal(insertnode);
	}
}

void Rbtree::remove(DataType data)
{
	TreeNode *pz = find(data);
	if (pz == nil)
		return;

	TreeNode *px, *py;
	Color py_oldcolor;

	py = pz;
	py_oldcolor = py->color;
	if (pz->left == nil)
	{
		px = pz->right;
		transplant(pz, px);
	}
	else if (pz->right == nil)
	{
		px = pz->left;
		transplant(pz, px);
	}
	else
	{
		py = min(pz->right);
		py_oldcolor = py->color;
		px = py->right;

		if (py->par == pz)
		{
			px->par = py;
		}
		else
		{
			transplant(py, py->right);
			py->right = pz->right;
			py->right->par = py;
		}

		root = root;
		transplant(pz, py);
		py->left = pz->left;
		py->left->par = py;
		py->color = pz->color;
	}

	if (py_oldcolor == BLACK)
		remove_internal(px);

	pz->left = pz->right = nil; // 这样保证只是释放对应的一个节点，而不是释放以该节点为根节点的子树
	delete pz; // 删除一个节点的时候，节点数量会自动减少，nil->data--
}

const TreeNode *Rbtree::find(DataType data) const
{
	TreeNode *pnode = root;

	while (pnode != nil)
	{
		if (data < pnode->data)
			pnode = pnode->left;
		else if (data > pnode->data)
			pnode = pnode->right;
		else
			return pnode;
	}
	return nil;
}

void Rbtree::rotateLeft(TreeNode *px)
{
	TreeNode *py = px->right;

	px->right = py->left;
	if (py->left != nil)
		py->left->par = px;

	py->par = px->par;
	if (px == root)
		root = py;
	else if (px == px->par->left)
		px->par->left = py;
	else
		px->par->right = py;

	px->par = py;
	py->left = px;
}

void Rbtree::rotateRight(TreeNode *px)
{
	TreeNode *py = px->left;

	px->left = py->right;
	if (py->right != nil)
		py->right->par = px;

	py->par = px->par;
	if (px == root)
		root = py;
	else if (px == px->par->left)
		px->par->left = py;
	else
		px->par->right = py;

	px->par = py;
	py->right = px;
}

void Rbtree::insert_internal(TreeNode *px)
{
	while (px->par->color == RED)
	{
		if (px->par == px->par->par->left)
		{
			TreeNode *py = px->par->par->right;

			// Case1: px uncle node py is red
			if (py->color == RED)
			{
				py->color = BLACK;
				px->par->color = BLACK;
				px->par->par->color = RED;
				px = px->par->par;
			}
			else
			{
				// Case2: px uncle node py is black, but px is right node
				if (px == px->right)
				{
					px = px->par;
					rotateLeft(px);
				}

				// Case3: px uncle node py is black, but px is left node
				px->par->color = BLACK;
				px->par->par->color = RED;
				rotateRight(px->par->par);
			}
		}
		else  // px parent node is right node
		{
			TreeNode *py = px->par->par->left;

			if (py->color == RED)
			{
				py->color = BLACK;
				px->par->color = BLACK;
				px->par->par->color = RED;
				px = px->par->par;
			}
			else
			{
				if (px == px->par->left)
				{
					px = px->par;
					rotateRight(px);
				}

				px->par->color = BLACK;
				px->par->par->color = RED;
				rotateLeft(px->par->par);
			}
		}
	}

	root->color = BLACK;
}

/**
* @brief 修复因删除操作而引起的红黑树性质破坏
* @param [in] px:红黑树节点px
* @return void
* @note 在这四种情况中，1、2、3情况都不会引起px->par节点的左子树和右子树的黑节点路径长度变化
*		 px节点所在的子树黑节点长度比px->par的另一个子树黑节点长度小1，在情况4中会修复该状况
*/
void Rbtree::remove_internal(TreeNode *px)
{
	TreeNode *py = NULL;

	while (px != root && px->color == BLACK)
	{
		if (px == px->par->left)
		{
			py = px->par->right;
			if (py->color == RED) // 情况1：px的兄弟节点py是红色
			{
				py->color = BLACK;
				px->par->color = RED;
				rotateLeft(px->par);
				py = px->par->right;
			}

			if (py->left->color == BLACK && py->right->color == BLACK) //情况2:px的兄弟节点py是黑色，而且py的两个子节点都是黑色的
			{
				py->color = RED;
				px = px->par;
			}
			else
			{
				if (py->right->color == BLACK) // 情况3：px的兄弟节点w是黑色的，py的左孩子是红色的，py的右孩子是黑色的
				{
					py->left->color = BLACK;
					py->color = RED;
					rotateRight(py);
					py = px->par->right;
				}

				py->color = px->par->color; // 情况4：px的兄弟节点py是黑色的，且py的右孩子是红色的
				px->par->color = BLACK;
				py->right->color = BLACK;
				rotateLeft(px->par);
				px = root;
			}
		}
		else
		{
			py = px->par->left;
			if (py->color == RED)
			{
				py->color = BLACK;
				px->par->color = RED;
				rotateRight(px->par);
				py = px->par->left;
			}

			if (py->left->color == BLACK && py->right->color == BLACK)
			{
				py->color = RED;
				px = px->par;
			}
			else
			{
				if (py->left->color == BLACK)
				{
					py->right->color = BLACK;
					py->color = RED;
					rotateLeft(py);
					py = px->par->left;
				}

				py->color = px->par->color;
				px->par->color = BLACK;
				py->left->color = BLACK;
				rotateRight(px->par);
				px = root;
			}
		}
	}
	px->color = BLACK;
}

void Rbtree::print_internal(TreeNode *pnode) const
{
	if (pnode != nil)
	{
		print_internal(pnode->left);
		std::cout << pnode->data;
		std::cout << (pnode->color == BLACK ? " black" : " red") << std::endl;
		print_internal(pnode->right);
	}
}

TreeNode *Rbtree::min(TreeNode *pnode) const
{
	while (pnode->left != nil)
		pnode = pnode->left;
	return pnode;
}