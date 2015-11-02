#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>

using namespace std;

class Edge
{
public:
	Edge(size_t _v, size_t _w, double _weight) : v(_v), w(_w), weight(_weight) {}

	double getWeight() const { return weight; }
	size_t either() const { return v; }
	size_t other(size_t v) const
	{
		if (v == this->v)
			return this->w;
		else if (v == this->w)
			return this->v;
		else
		{
			cout << "error in Edge::other()" << endl;
			exit(1);
		}
	}
	void print() const{ cout << "(" << v << ", " << w << ", " << weight << ") "; }

private:
	size_t v, w; // 两个顶点
	double weight; // 权重
};

/// 加权无向图
class EdgeWeithtedGraph
{
public:
	EdgeWeithtedGraph(size_t vertax_nums) : vertaxs(vertax_nums), edges(0), arr(vertax_nums) {}

	void addEdge(const Edge e);

	vector<Edge> adj(size_t v) const { return v < arrSize() ? arr[v] : vector<Edge>(); }
	vector<Edge> allEdges() const;		// 返回加权无向图的所有边
	size_t arrSize() const { return arr.size(); }
	size_t vertax() const { return vertaxs; }
	size_t edge() const { return edges; }
	void printVertax(size_t v) const;
	void printGraph() const;

private:
	size_t vertaxs; // 顶点个数
	size_t edges; // 边的个数
	vector<vector<Edge>> arr; // 邻接表
};

/// 无向图数据结构，用于测试Kruskal算法中的边是否能构成环
class Graph
{
public:
	Graph(size_t n) : arr(n), edges(0), vertaxs(n) {}
	void addEdge(size_t a, size_t b)
	{
		if (!(a < arr.size() && b < arr.size()))
			return;

		arr[a].push_back(b);
		arr[b].push_back(a);
		edges++;
	}

	vector<size_t> adj(size_t n) const
	{
		if (n < arr.size())
			return arr[n];
		else
			return vector<size_t>();
	}
	/// 返回顶点个数
	size_t vertax() const { return arr.size(); }

private:
	vector<vector<size_t>> arr; // 邻接表
	size_t edges;	// 边的个数
	size_t vertaxs; // 顶点个数
};

/// 使用深度优先遍历判断Graph是否是无环图
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

/// 判断最小生成树中是否有环，在Kruskal算法算法中被调用
bool hasCycle(vector<Edge> vec, size_t nvextax)
{
	if (vec.size() == 0)
		return false;

	Graph graph(nvextax);
	for (size_t i = 0; i < vec.size(); i++)
	{
		size_t v = vec[i].either();
		size_t w = vec[i].other(v);
		graph.addEdge(v, w);
	}

	Cycle cycle(graph);
	return cycle.hasCycle();
}

/// 为了存放Kruskal算法过程中的边，这些边按照权值从小到大排列
template <typename T>
struct greator
{
	bool operator()(const T &x, const T &y)
	{
		return x.getWeight() < y.getWeight();
	}
};

/// 最小生成树的Kruskal算法
class KruskalMST
{
public:
	KruskalMST(const EdgeWeithtedGraph &graph)
	{
		set<Edge, greator<Edge>> pq; // 计算过程保存边的set
		vector<Edge> vec = graph.allEdges();
		set<Edge>::iterator miniter;

		for (size_t i = 0; i < vec.size(); i++) // 将所有的边存到pq中
			pq.insert(vec[i]);

		while (!pq.empty() && mst.size() < graph.arrSize() - 1) // graph.arrSize()可替换为变量
		{
			miniter = pq.begin();

			mst.push_back(*miniter);
			if (hasCycle(mst, graph.arrSize()))
				removeEdge(*miniter);
			pq.erase(miniter);
		}
	}

	vector<Edge> edges() const { return mst; }
	void printEdges() const
	{
		for (size_t i = 0; i < mst.size(); i++)
		{
			mst[i].print();
		}
		cout << endl;
	}

private:
	void removeEdge(Edge e)
	{
		size_t v = e.either();
		size_t w = e.other(v);
		for (size_t i = 0; i < mst.size(); i++)
		{
			size_t iv = mst[i].either();
			size_t iw = mst[i].other(iv);
			if (v == iv && w == iw)
			{
				mst.erase(mst.begin() + i);
				return;
			}
		}
	}

	vector<Edge> mst;
};

int main(void)
{
	EdgeWeithtedGraph graph(8);

	graph.addEdge(Edge(0, 7, 0.16));
	graph.addEdge(Edge(0, 2, 0.26));
	graph.addEdge(Edge(0, 4, 0.38));
	graph.addEdge(Edge(0, 6, 0.58));
	graph.addEdge(Edge(1, 7, 0.19));
	graph.addEdge(Edge(5, 7, 0.28));
	graph.addEdge(Edge(2, 7, 0.34));
	graph.addEdge(Edge(4, 7, 0.37));
	graph.addEdge(Edge(1, 3, 0.29));
	graph.addEdge(Edge(1, 5, 0.32));
	graph.addEdge(Edge(1, 2, 0.36));
	graph.addEdge(Edge(2, 3, 0.17));
	graph.addEdge(Edge(6, 2, 0.40));
	graph.addEdge(Edge(3, 6, 0.52));
	graph.addEdge(Edge(4, 5, 0.35));
	graph.addEdge(Edge(6, 4, 0.93));

	cout << "arrSize: " << graph.arrSize() << endl;
	cout << "vertax: " << graph.vertax() << endl;
	cout << "edge: " << graph.edge() << endl;
	cout << "----------------" << endl;

	graph.printGraph();
	cout << endl;

	// 输出无向图的所有边
	vector<Edge> vec = graph.allEdges();
	for (size_t i = 0; i < vec.size(); i++)
		vec[i].print();
	cout << endl << endl;

	// Kruskal算法
	KruskalMST prim(graph);
	prim.printEdges();

	return 0;
}

void EdgeWeithtedGraph::addEdge(const Edge e)
{
	size_t v = e.either();
	size_t w = e.other(v);
	if (!(v < arrSize() && w < arrSize()))
		return;

	arr[v].push_back(e);
	arr[w].push_back(e);
	this->edges++;
}

vector<Edge> EdgeWeithtedGraph::allEdges() const
{
	vector<Edge> vec;

	for (size_t i = 0; i < arrSize(); i++)
	{
		for (size_t j = 0; j < arr[i].size(); j++)
		{
			if (arr[i][j].other(i) > i) // 所有边的权重各不不同，可以这样判断，每个边只保留一个
				vec.push_back(arr[i][j]);
		}
	}
	return vec;
}

void EdgeWeithtedGraph::printVertax(size_t v) const
{
	if (v >= arrSize())
		return;

	for (size_t i = 0; i < arr[v].size(); i++)
		arr[v][i].print();
	cout << endl;
}

void EdgeWeithtedGraph::printGraph() const
{
	for (size_t i = 0; i < arrSize(); i++)
	{
		cout << i << ": ";
		printVertax(i);
	}
}