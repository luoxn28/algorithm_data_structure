
/**
	Huffman实际上会生成二进制流，这里把输入字符串翻译为二进制的字符串，比如"AAB"翻译为“001”，'A'为'0'，‘B’为'1'
	这样使用输出时更以观察生成的结果
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

struct HuffNode
{
	char data;
	size_t freq;
	HuffNode *left;
	HuffNode *right;

	HuffNode() : data('\0'), freq(0), left(NULL), right(NULL) {}
	~HuffNode()
	{
		if (left)
			delete left;
		if (right)
			delete right;
	}
};

class HuffTree
{
public:
	HuffTree(const char *str) : rawStr(str), root(NULL), freqVec(N)   { init(); }
	HuffTree(const string &str) : rawStr(str), root(NULL), freqVec(N) { init(); }
	~HuffTree();

	void printCodingVec();
	void setBinStr();
	void printBinStr();
	void printRawStr() { cout << rawStr << endl; }
	
private:
	static const size_t N = 256;
	string rawStr;
	string binStr;
	HuffNode *root; // Huffman tree
	vector<pair<char, size_t>> freqVec;
	vector<pair<char, string>> codingVec;

	void init();
	void makeFreqVec();
	void makeTree();
	void makeCodingVec(HuffNode *root);
};

int main(void)
{
	HuffTree tree("ABCACAABF");

	tree.printCodingVec();

	tree.setBinStr();
	tree.printRawStr();
	tree.printBinStr();

	return 0;
}


HuffTree::~HuffTree()
{
	if (root)
		delete root;
}

void HuffTree::printCodingVec()
{
	for (size_t i = 0; i < codingVec.size(); i++)
	{
		cout << codingVec[i].first << ": " << codingVec[i].second << endl;
	}
}

void HuffTree::setBinStr()
{
	for (size_t i = 0; i < rawStr.size(); i++)
	{
		for (size_t j = 0; j < codingVec.size(); j++)
		{
			if (rawStr[i] == codingVec[j].first)
				binStr += codingVec[j].second;
		}
	}
}

void HuffTree::printBinStr()
{
	cout << binStr << endl;
}

template <typename T>
struct greator
{
	bool operator()(const T &x, const T &y)
	{
		return (x->freq > y->freq); // 建立的是小堆
	}
};

void HuffTree::init()
{
	makeFreqVec();
	makeTree();
	makeCodingVec(root);
}

void HuffTree::makeFreqVec()
{
	if (rawStr.empty())
		return;
	
	for (size_t i = 0; i < rawStr.size(); i++)
	{
		freqVec[(size_t)rawStr[i]].second++;
	}
}

void HuffTree::makeTree()
{
	if (rawStr.empty())
		return;
	
	vector<HuffNode *> treeVec;
	for (size_t i = 0; i < N; i++)
	{
		if (freqVec[i].second)
		{
			HuffNode *pnode = new HuffNode;

			pnode->data = (char)i;
			pnode->freq = freqVec[i].second;
			treeVec.push_back(pnode);
		}
	}

	make_heap(treeVec.begin(), treeVec.end(), greator<HuffNode *>());
	size_t length = treeVec.size();

	for (size_t i = 0; i < length - 1; i++)
	{
		pop_heap(treeVec.begin(), treeVec.end(), greator<HuffNode *>());
		HuffNode *pnode1 = treeVec.back();
		treeVec.pop_back();

		pop_heap(treeVec.begin(), treeVec.end(), greator<HuffNode *>());
		HuffNode *pnode2 = treeVec.back();
		treeVec.pop_back();

		HuffNode *pnode = new HuffNode;
		pnode->data = -1; // 表示为内部节点
		pnode->freq = pnode1->freq + pnode2->freq;
		pnode->left = pnode1;
		pnode->right = pnode2;

		treeVec.push_back(pnode);
		push_heap(treeVec.begin(), treeVec.end(), greator<HuffNode *>());
	}

	root = treeVec.front();
}

void HuffTree::makeCodingVec(HuffNode *pnode)
{
	if (!pnode)
		return;

	static vector<char> cvec;

	if ((int)pnode->data > 0) // 内部节点的data域为-1，初始化为0
	{
		string s(cvec.begin(), cvec.end());
		pair<char, string> tmp(pnode->data, s);

		codingVec.push_back(tmp);
	}

	cvec.push_back('0');
	makeCodingVec(pnode->left);
	cvec.pop_back();

	cvec.push_back('1');
	makeCodingVec(pnode->right);
	cvec.pop_back();
}
