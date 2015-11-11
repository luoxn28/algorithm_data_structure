#include <iostream>
using namespace std;

typedef int DataType;

class TreeNode
{
public:	
	DataType data;
	TreeNode *left;
	TreeNode *right;

	TreeNode(DataType _data) : data(_data), left(NULL), right(NULL) {}
	~TreeNode()
	{
		if (left)
			delete left;
		if (right)
			delete right;

	}
};

class BinaryTree
{
public:
	BinaryTree() : root(NULL), sizes(0) {}
	~BinaryTree() 
	{		
		if (root)
			delete root;
	}

	void insert(DataType data) { root = insert_internal(root, data); }
	void remove(DataType data) { root = remove_internal(root, data); }

	// 返回最小/最大节点的指针
	const TreeNode *min() const;
	const TreeNode *max() const;
	void print() const { print_internal(root); std::cout << std::endl; }
	size_t size() const { return sizes; }

	// 测试data是否在二叉查找树中
	bool find(DataType data) const { return find_internal(root, data); }

private:
	TreeNode *insert_internal(TreeNode *pnode, DataType data);
	TreeNode *remove_internal(TreeNode *pnode, DataType data);
	bool find_internal(TreeNode *pnode, DataType data) const;
	void print_internal(TreeNode *pnode) const;

	TreeNode *root; // 根节点
	size_t sizes; // 二叉查找树中节点的个数
};

int main(void)
{
	BinaryTree tree;

	tree.insert(12);
	tree.insert(6);
	tree.insert(24);

	cout << "size: " << tree.size() << endl;
	if (tree.find(24))
		cout << "find it" << endl;
	else
		cout << "not find it" << endl;

	const TreeNode *iter = NULL;
	iter = tree.min();
	if (iter)
		cout << "min: " << iter->data << endl;
	iter = tree.max();
	if (iter)
		cout << "max: " << iter->data << endl;

	tree.print();
	
	tree.remove(12);
	cout << "size: " << tree.size() << endl;
	tree.print();

	tree.remove(6);
	cout << "size: " << tree.size() << endl;
	tree.print();

	tree.remove(24);
	cout << "size: " << tree.size() << endl;
	tree.print();

	return 0;
}

const TreeNode *BinaryTree::min() const
{
	TreeNode *pnode = root;
	if (root)
	{
		while (pnode->left)
			pnode = pnode->left;
	}

	return pnode;
}

const TreeNode *BinaryTree::max() const
{
	TreeNode *pnode = root;
	if (root)
	{
		while (pnode->right)
			pnode = pnode->right;
	}

	return pnode;
}

TreeNode *BinaryTree::insert_internal(TreeNode *pnode, DataType data)
{
	if (!pnode)
	{
		pnode = new TreeNode(data);
		sizes++;
	}
	else if (data < pnode->data)
		pnode->left = insert_internal(pnode->left, data);
	else
		pnode->right = insert_internal(pnode->right, data);

	return pnode;
}

TreeNode *BinaryTree::remove_internal(TreeNode *pnode, DataType data)
{
	if (!pnode)
		return NULL;
	else if (data < pnode->data)
		pnode->left = remove_internal(pnode->left, data);
	else if (data > pnode->data)
		pnode->right = remove_internal(pnode->right, data);
	else if (pnode->left && pnode->right)
	{
		TreeNode *ptmp = pnode->right;
		while (ptmp->left != NULL)
			ptmp = ptmp->left;

		pnode->data = ptmp->data;
		pnode->right = remove_internal(pnode->right, ptmp->data);
	}
	else // 删除节点有一个child节点或者没有child节点
	{
		TreeNode *ptmp = pnode;
		if (pnode->left != NULL)
			pnode->left;
		else if (pnode->right != NULL)
			pnode->right;
		else // 表示现在删除的是root节点，并且此时二叉树中只有一个root节点
			pnode = NULL;

		delete ptmp; //ptmp所指内存已释放，pnode指向ptmp的子树节点，pnode和二叉查找树的连接是在函数返回时，因为函数是递归的
		sizes--;
	}

	return pnode;
}

bool BinaryTree::find_internal(TreeNode *pnode, DataType data) const
{
	if (!pnode)
		return false;
	else if (data < pnode->data)
		return find_internal(pnode->left, data);
	else if (data > pnode->data)
		return find_internal(pnode->right, data);
	else
		return true;
}

void BinaryTree::print_internal(TreeNode *pnode) const
{
	if (pnode)
	{
		print_internal(pnode->left);
		std::cout << pnode->data << " ";
		print_internal(pnode->right);
	}
}