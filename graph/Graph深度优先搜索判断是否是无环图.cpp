#include <iostream>
#include <vector>
//#include <queue>
//#include <stack>
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

/// 使用深度优先遍历判断是否是无环图
class Cycle
{
public:
	Cycle(const Graph &graph) : marked(graph.vertax()), has_cycle(false)
	{
		for (size_t i = 0; i < graph.vertax(); i++)
			marked[i] = false;
		for (size_t i = 0; i < graph.vertax(); i++)
		{
			if (!marked[i])
				dfs(graph, i, i);
		}
	}

	bool hasCycle() const { return has_cycle; }

private:
	void dfs(const Graph &graph, size_t v, size_t u)
	{
		marked[v] = true;

		vector<size_t> vec = graph.adj(v);
		for (size_t i = 0; i < vec.size(); i++)
		{
			if (!marked[vec[i]])
				dfs(graph, vec[i], v);
			else if (vec[i] != u) // 无环图其实就是树，此时v是树中一个节点，其父节点为u，当marked[vec[i]]==true时，表示v的父节点一定为u，否则图中有环
				has_cycle = true;
		}
	}

	vector<bool> marked;
	bool has_cycle;
};

int main(void)
{
	Graph graph(13);

	graph.addEdge(0, 1);
	graph.addEdge(0, 2);
	graph.addEdge(0, 5);
	graph.addEdge(0, 6);
	//graph.addEdge(3, 4);
	graph.addEdge(3, 5);
	graph.addEdge(4, 5);
	//graph.addEdge(4, 6);

	graph.addEdge(7, 8);

	graph.addEdge(9, 10);
	graph.addEdge(9, 11);
	graph.addEdge(9, 12);
	//graph.addEdge(11, 12);
	// 把以上3个注释行取消就成为了有环图

	cout << "vertax: " << graph.vertax() << endl;
	cout << "edge: " << graph.edge() << endl;
	graph.showGraph();
	cout << endl;

	Cycle cycle(graph);

	cout << "cycle.hasCycle(): ";
	if (cycle.hasCycle())
		cout << "true" << endl;
	else
		cout << "false" << endl;

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