#include <iostream>
#include <vector>
#include <queue>
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

/// 广度优先搜索图中从一个顶点到其他所有顶点路径
class BfsPaths
{
public:
	BfsPaths(const Graph &graph, size_t _start) : start(_start), paths(graph.vertax()), marked(graph.vertax())
	{
		for (int i = 0; i < graph.vertax(); i++)
			marked[i] = false;
		bfs(graph);
	}

	stack<size_t> pathTo(size_t v)
	{
		stack<size_t> sta; // 这里用栈保存结果更好

		for (size_t x = v; x != start; x = paths[x])
			sta.push(x);
		sta.push(start);
		return sta;
	}
	void printPathTo(size_t v)
	{
		stack<size_t> sta = pathTo(v);
		cout << start << "->" << v << ": ";
		while (!sta.empty())
		{
			cout << sta.top() << " ";
			sta.pop();
		}
		cout << endl;
	}

private:
	void bfs(const Graph &graph)
	{
		queue<size_t> que;
		vector<size_t> vec;

		paths[start] = start;
		que.push(start);
		marked[start] = true;
		while (!que.empty())
		{
			size_t v = que.front();
			que.pop();
			vec = graph.adj(v);

			for (int i = 0; i < vec.size(); i++)
			{
				if (!marked[vec[i]])
				{
					paths[vec[i]] = v;
					que.push(vec[i]);
					marked[vec[i]] = true;
				}
			}
		}
	}

	size_t start;		  // 起点
	vector<size_t> paths; // 到大该顶点已知路径上的最后一个顶点
	vector<bool> marked;  // 到达该顶点的最短路径已知吗？
};

int main(void)
{
	Graph graph(5);

	graph.addEdge(0, 1);
	graph.addEdge(0, 2);
	graph.addEdge(1, 3);
	graph.addEdge(2, 3);
	graph.addEdge(3, 4);
	graph.addEdge(4, 0);

	BfsPaths path(graph, 0);

	path.printPathTo(1);
	path.printPathTo(2);
	path.printPathTo(3);
	path.printPathTo(4);

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
		removeEdge(n, arr[n][0]); // 调用removeEdge函数，不用考虑分两次删除边了
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
