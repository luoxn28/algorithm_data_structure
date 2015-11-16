#include <iostream>
#include <string>
#include <vector>
using namespace std;

/// 单词查找树的节点
struct Node
{
	static const int R = 26; // 总共有26个字母
	int value; // 存放编号，初始化为-1
	Node *arr[R];

	Node() : value(-1)
	{
		for (int i = 0; i < R; i++)
			arr[i] = NULL;
	}
	~Node()
	{
		for (int i = 0; i < R; i++)
		{
			if (arr[i])
			{
				delete arr[i];
				arr[i] = NULL;
			}
		}
	}
};

/// 单词查找树数据结构，单词全部是小写
class WordTree
{
public:
	WordTree() : root(new Node), word_size(0) {}
	~WordTree() { delete root; }

	// 往单词查找树中插入一个单词key，value为该单词的序号
	void insert(const string &key, int value) { insert_internal(root, key, value, 0); }

	// 查找key是否在单词查找树中
	bool find(string key) const { return find_internal(root, key, 0); }
	
	int size() const { return word_size; }
	void print() const
	{
		vector<char> vec;
		print_internal(root, vec);
	}

private:
	int getID(char c) const { return c - 'a'; }

	// 插入单词key，value为该单词序号，depth为当前插入的深度，当depth为key.size()时表示插入已经完成
	Node *insert_internal(Node *pnode, const string &key, int value, int depth);

	bool find_internal(Node *pnode, string &key, int depth) const;

	void print_internal(Node *pnode, vector<char> &vec) const;

	Node *root; // 根节点
	int word_size; // 单词查找树中存放单词的个数
};

int main(void)
{
	WordTree wtree;

	wtree.insert("sea", 2);
	wtree.insert("she", 0);
	wtree.insert("sells", 1);

	cout << wtree.size() << endl;
	if (wtree.find("she"))
		cout << "find it" << endl;
	else
		cout << "not find" << endl;

	wtree.print();

	return 0;
}

Node *WordTree::insert_internal(Node *pnode, const string &key, int value, int depth)
{
	if (!pnode)
	{
		pnode = new Node;
	}
	if (depth == key.size())
	{
		pnode->value = value;
		word_size++; // 完成插入一个单词了
		return pnode;
	}

	char c = key[depth];
	pnode->arr[getID(c)] = insert_internal(pnode->arr[getID(c)], key, value, depth + 1);

	return pnode;
}

bool WordTree::find_internal(Node *pnode, string &key, int depth) const
{
	if (!pnode)
		return false;
	if (depth == key.size())
		return true;

	char c = key[depth];
	return find_internal(pnode->arr[getID(c)], key, depth + 1);
}

void WordTree::print_internal(Node *pnode, vector<char> &vec) const
{
	if (!pnode)
		return;

	for (int i = 0; i < Node::R; i++)
	{
		if (pnode->arr[i])
		{
			vec.push_back(i + 'a');
			print_internal(pnode->arr[i], vec);

			if (pnode->arr[i]->value != -1) // 已经到达一个单词的终点，打印
			{
				cout << pnode->arr[i]->value << ": ";
				for (int i = 0; i < vec.size(); i++)
					cout << vec[i];
				cout << endl;
			}

			vec.pop_back();
		}
	}
}