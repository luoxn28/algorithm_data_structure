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

/// 使用深度优先遍历判断是否是二分图（双色问题，图中任意一条边的两个端点的颜色都不相同）
class TwoColor
{
public:
	TwoColor(const Graph &graph) : marked(graph.vertax()), color(graph.vertax()), is_twocolor(false)
	{
		for (size_t i = 0; i < graph.vertax(); i++)
			marked[i] = color[i] = false;
		for (size_t i = 0; i < graph.vertax(); i++)
		{
			if (!marked[i])
				dfs(graph, i);
		}
	}

	bool isTwoColor() const { return is_twocolor; }

private:
	void dfs(const Graph &graph, size_t v)
	{
		marked[v] = true;

		vector<size_t> vec = graph.adj(v);
		for (size_t i = 0; i < vec.size(); i++)
		{
			if (!marked[vec[i]])
			{
				color[vec[i]] = !color[vec[i]];
				dfs(graph, vec[i]);
			}
			else if (color[vec[i]] == color[v])
			{
				is_twocolor = true;
			}
		}
	}

	vector<bool> marked;
	vector<bool> color;
	bool is_twocolor;
};

int main(void)
{
	Graph graph(3);

	graph.addEdge(0, 1);
	graph.addEdge(0, 2);
	//graph.addEdge(1, 2); // 取消注释就不是二分图了

	cout << "vertax: " << graph.vertax() << endl;
	cout << "edge: " << graph.edge() << endl;
	graph.showGraph();
	cout << endl;

	TwoColor twoColor(graph);

	cout << "twoColor.isTwoColor(): ";
	if (twoColor.isTwoColor())
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