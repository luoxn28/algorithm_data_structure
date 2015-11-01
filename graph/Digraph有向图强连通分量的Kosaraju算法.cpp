#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

class Digraph
{
public:
	Digraph(size_t nvertax) : arr(nvertax), vertaxs(nvertax), edges(0) {}
	void addEdge(size_t a, size_t b);
	void removeEdge(size_t a, size_t b);
	void addVertax(size_t v);
	void removeVertax(size_t v);
	Digraph reverse() const;

	vector<size_t> adj(size_t v) const;
	void showAdj(size_t v) const;
	void showDigraph() const;

	size_t edge() const { return edges; }
	size_t vertax() const { return vertaxs; }
	size_t arrSize() const { return arr.size(); }

private:
	vector<vector<size_t>> arr; // 邻接表
	size_t vertaxs; // 顶点个数
	size_t edges;	// 边的个数
};

/// 使用深度优先遍历在有向图中寻找有向环
class DirectedCycle
{
public:
	DirectedCycle(const Digraph &graph) : marked(graph.arrSize()), edgeto(graph.arrSize()), on_stack(graph.arrSize())
	{
		for (size_t i = 0; i < graph.arrSize(); i++)
			marked[i] = on_stack[i] = false;
		for (size_t i = 0; i < graph.arrSize(); i++)
		{
			if (!marked[i])
				dfs(graph, i);
		}
	}

	bool hasCycle() const { return !sta.empty(); }
	stack<size_t> cycle() const { return sta; }

private:
	void dfs(const Digraph &graph, size_t v)
	{
		on_stack[v] = true;
		marked[v] = true;

		vector<size_t> vec = graph.adj(v);
		for (size_t i = 0; i < vec.size(); i++)
		{
			if (this->hasCycle())
				return;
			else if (!marked[vec[i]])
			{
				edgeto[vec[i]] = v;
				dfs(graph, vec[i]);
			}
			else if (on_stack[vec[i]])
			{
				for (size_t x = v; x != vec[i]; x = edgeto[x])
					sta.push(x);
				sta.push(vec[i]);
				sta.push(v);
			}
		}
		on_stack[v] = false;
	}

	vector<bool> marked;
	vector<size_t> edgeto;
	vector<bool> on_stack;
	stack<size_t> sta;
};

/// 有向图中基于深度优先遍历的顶点排序，保证图中没有有向环
class DepthFirstOrder
{
public:
	DepthFirstOrder(const Digraph &graph) : marked(graph.arrSize())
	{
		for (size_t i = 0; i < marked.size(); i++)
			marked[i] = false;
		for (size_t i = 0; i < graph.arrSize(); i++)
		{
			if (!marked[i])
				dfs(graph, i);
		}
	}

	vector<size_t> getPre() const { return pre; }
	vector<size_t> getPost() const { return post; }
	stack<size_t>  getReversePost() const { return reverse_post; }

private:
	void dfs(const Digraph &graph, size_t v)
	{
		marked[v] = true;
		pre.push_back(v);

		vector<size_t> vec = graph.adj(v);
		for (size_t i = 0; i < vec.size(); i++)
		{
			if (!marked[vec[i]])
				dfs(graph, vec[i]);
		}
		post.push_back(v);
		reverse_post.push(v);
	}

	vector<bool> marked;
	vector<size_t> pre;			// 所有顶点的前序排列
	vector<size_t> post;		// 所有顶点的后序排列
	stack<size_t> reverse_post; // 所有顶点的逆后序排列
};

/// 计算强连通分量的Kosaraju算法
class KosarajuSCC
{
public:
	KosarajuSCC(const Digraph &graph) : marked(graph.arrSize()), id(graph.arrSize()), count(0)
	{
		for (size_t i = 0; i < marked.size(); i++)
			marked[i] = false;

		DepthFirstOrder dforder(graph);
		stack<size_t> sta = dforder.getReversePost();
		while (!sta.empty())
		{
			size_t v = sta.top();
			sta.pop();
			if (!marked[v])
			{
				dfs(graph, v);
				count++;
			}
		}
	}

	bool strongConnected(int v, int w) const { return id[v] == id[w]; }
	size_t getId(size_t v) const { return id[v]; }
	size_t getCount() const { return count; }

private:
	void dfs(const Digraph &graph, size_t v)
	{
		marked[v] = true;
		id[v] = count;

		vector<size_t> vec = graph.adj(v);
		for (size_t i = 0; i < vec.size(); i++)
		{
			if (!marked[vec[i]])
				dfs(graph, vec[i]);
		}
	}

	vector<bool> marked;
	vector<size_t> id;
	size_t count;
};

int main(void)
{
	Digraph graph(13);

	graph.addEdge(0, 1); graph.addEdge(0, 5); graph.addEdge(0, 6);
	graph.addEdge(2, 0); graph.addEdge(2, 3);
	graph.addEdge(3, 5);
	graph.addEdge(5, 4);
	graph.addEdge(6, 4); graph.addEdge(6, 9);
	graph.addEdge(7, 6);
	graph.addEdge(8, 7);
	graph.addEdge(9, 10); graph.addEdge(9, 11); graph.addEdge(9, 12);
	graph.addEdge(11, 12);

	cout << graph.vertax() << endl;
	cout << graph.edge() << endl;
	graph.showDigraph();
	cout << endl;
	
	DepthFirstOrder dep(graph);
	stack<size_t> sta = dep.getReversePost();
	while (!sta.empty())
	{
		cout << sta.top() << " ";
		sta.pop();
	}
	cout << endl;

	KosarajuSCC kosa(graph);
	cout << kosa.getCount() << endl;

	return 0;
}


void Digraph::addEdge(size_t a, size_t b)
{
	if (!(a < vertax() && b < vertax()))
		return;
	arr[a].push_back(b);
	edges++;
}

void Digraph::removeEdge(size_t a, size_t b)
{
	if (!(a < vertax() && b < vertax()))
		return;

	vector<size_t>::iterator iter = find(arr[a].begin(), arr[a].end(), b);
	if (iter != arr[a].end())
	{
		arr[a].erase(iter);
		edges--;
	}
}

void Digraph::addVertax(size_t v)
{
	if (v != arrSize())
		return;
	arr.push_back(vector<size_t>());
	vertaxs++;
}

void Digraph::removeVertax(size_t v)
{
	if (v >= arrSize())
		return;
	vector<size_t>::iterator iter;

	for (size_t i = 0; i < arrSize(); i++)
	{
		if (i == v)
		{
			edges -= arr[i].size(); // 减去头部是v的边的个数
			arr[i].clear();
			vertaxs--;
		}
		else
		{
			iter = find(arr[i].begin(), arr[i].end(), v);
			if (iter != arr[i].end())
			{
				arr[i].erase(iter);
				edges--;
			}
		}
	}
}

Digraph Digraph::reverse() const
{
	Digraph graph(vertax());
	vector<size_t> vec;

	for (size_t i = 0; i < arrSize(); i++)
	{
		vec = adj(i);
		for (size_t j = 0; j < vec.size(); j++)
		{
			graph.addEdge(vec[j], i); // 取得该图的反向图
		}
	}

	return graph;
}

vector<size_t> Digraph::adj(size_t v) const
{
	if (v < arrSize())
		return arr[v];
	else
		vector<size_t>();
}

void Digraph::showAdj(size_t v) const
{
	if (v >= arrSize())
		return;

	vector<size_t> vec = adj(v);
	for (size_t i = 0; i < vec.size(); i++)
		cout << vec[i] << " ";
	cout << endl;
}

void Digraph::showDigraph() const
{
	for (size_t i = 0; i < arr.size(); i++)
	{
		cout << i << ": ";
		showAdj(i);
	}
}
