/*
基于深度优先搜索实现Paths，使用一个变量edgeTo[]数组记录路径，这个数组可以找到每个与s连通的
顶点回到s的路径。它会记住每个顶点到起点的路径，而不是记录当前顶点到起点的路径。
*/
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

class Graph
{
public:
	Graph(size_t n) : arr(n), edges(0), vertaxs(n) {}
	void addEdge(size_t a, size_t b);
	void removeEdge(size_t a, size_t b);
	void addVertax(size_t n);
	void removeVertax(size_t n);

	vector<size_t> adj(size_t n) const;
	void showAdj(size_t n) const;
	void showGraph() const;

	size_t edge() const { return edges; }
	size_t vertax() const { return vertaxs; }

private:
	vector<vector<size_t>> arr;
	size_t edges;
	size_t vertaxs;
};

/// Graph使用深度优先搜索查找图中路径
class DepthFirstPaths
{
public:
	DepthFirstPaths(Graph &graph, size_t _s) : s(_s), edgeTo(graph.vertax()), marked(graph.vertax())
	{
		for (size_t i = 0; i < graph.vertax(); i++)
			marked[i] = false;
		dfs(graph, s);
	}

	bool hasPathTo(size_t v) { return (v < marked.size()) ? marked[v] : false; }
	stack<size_t> pathTo(size_t v)
	{
		stack<size_t> sta;
		for (size_t x = v; x != this->s; x = edgeTo[x])
			sta.push(x);
		sta.push(this->s);

		return sta;
	}

private:
	size_t s;
	vector<size_t> edgeTo;
	vector<bool> marked;
	
	void dfs(Graph &graph, size_t v)
	{
		marked[v] = true;

		vector<size_t> vec = graph.adj(v);
		for (size_t i = 0; i < vec.size(); i++)
		{
			if (!marked[vec[i]])
			{
				edgeTo[vec[i]] = v;
				dfs(graph, vec[i]);
			}
		}
	}
};

int main(void)
{
	Graph graph(5);

	graph.addEdge(0, 1);
	graph.addEdge(3, 4);
	graph.addEdge(1, 3);
	graph.addEdge(0, 4);
	graph.addEdge(2, 3);
	graph.addEdge(0, 2);

	cout << graph.vertax() << endl;
	cout << graph.edge() << endl;
	graph.showGraph();
	cout << endl;

	DepthFirstPaths dfp(graph, 0);
	stack<size_t> sta;

	// 打印所有的以0为起点的路径
	for (size_t i = 0; i < graph.vertax(); i++)
	{
		sta = dfp.pathTo(i);
		cout << "0->" << i << ": ";
		while (!sta.empty())
		{
			cout << sta.top() << " ";
			sta.pop();
		}
		cout << endl;
	}

	return 0;
}

void Graph::addEdge(size_t a, size_t b)
{
	if (!(a < arr.size() && b < arr.size()))
		return;

	arr[a].push_back(b);
	arr[b].push_back(a);
	edges++; // 无向图
}

void Graph::removeEdge(size_t a, size_t b)
{
	if (!(a < arr.size() && b < arr.size()))
		return;

	vector<size_t>::iterator iter;
	iter = find(arr[a].begin(), arr[a].end(), b);
	if (iter != arr[a].end())
	{
		arr[a].erase(iter);
		//edges--;
	}

	iter = find(arr[b].begin(), arr[b].end(), a);
	if (iter != arr[b].end())
	{
		arr[b].erase(iter);
		edges--;
	}
}
void Graph::addVertax(size_t n)
{
	if (n != arr.size())
		return;

	arr.push_back(vector<size_t>());
	vertaxs++;
}

void Graph::removeVertax(size_t n)
{
	if (n >= arr.size())
		return;

	while (!arr[n].empty())
		removeEdge(n, arr[n][0]);  // 调用removeEdge函数，不用考虑分两次删除边了
	//arr.erase(arr.begin() + n);
	vertaxs--;
}

vector<size_t> Graph::adj(size_t n) const
{
	if (n < arr.size())
		return arr[n];
	else
		return vector<size_t>();

}

void Graph::showAdj(size_t n) const
{
	if (n >= arr.size())
		return;

	vector<size_t> vec;
	vec = adj(n);
	for (size_t i = 0; i < vec.size(); i++)
		cout << vec[i] << " ";
	cout << endl;
}

void Graph::showGraph() const
{
	for (size_t i = 0; i < arr.size(); i++)
	{
		cout << i << ": ";
		showAdj(i);
	}
}
