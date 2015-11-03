#include <iostream>
#include <vector>
#include <float.h>
using namespace std;

/// 加权有向边的数据结构
class DirectedEdge
{
public:
	DirectedEdge(size_t _v, size_t _w, double _weight) : v(_v), w(_w), weights(_weight) { }
	DirectedEdge() : v(0), w(0), weights(DBL_MAX) { } // 默认构造函数

	size_t from() const { return v; }
	size_t to()   const { return w; }
	double weight() const { return weights; }
	void print() const { cout << "(" << v << "->" << w << ": " << weights << ") "; }

private:
	size_t v, w;
	double weights;
};

/// 加权有向图的数据结构
class EdgeWeightDigraph
{
public:
	EdgeWeightDigraph(size_t v) : vertax(v), edge(0), arr(v) {}

	void addEdge(const DirectedEdge &e);

	vector<DirectedEdge> adj(size_t v) const;
	vector<DirectedEdge> edges() const;
	size_t getVertax() const { return vertax; }
	size_t getEdge() const { return edge; }
	size_t getArrSize() const { return arr.size(); }

	void printAdj(size_t v) const;
	void printGraph() const;

private:
	size_t vertax, edge;
	vector<vector<DirectedEdge>> arr;
};

/// 最短路径的加权有向图Dijkstra算法
/**
Dijkstra算法能够解决边权重非负的加权有向图的单起点最短路径问题。
Dijkstra算法和Prim算法比较：两种算法都会添加边的方式构造一棵树，Prim算法每次添加的都是离树最近的非树顶点，
Dijkstra算法每次添加的都是离起点最近的非树顶点。它们都不需要marked[]数组，因为条件!marked[i]等价于
条件distTo[i]无穷大
*/
class DijkstraSP
{
public:
	DijkstraSP(EdgeWeightDigraph &graph, size_t s) : edgeTo(graph.getArrSize()), distTo(graph.getArrSize())
	{
		for (size_t i = 0; i < graph.getArrSize(); i++)
			distTo[i] = DBL_MAX; // 默认无穷大
		distTo[s] = 0;

		que.push_back(pair<size_t, double>(s, 0.0));
		while (!que.empty())
		{
			size_t v = que[0].first;
			que.erase(que.begin());
			relax(graph, v);
		}
	}

	double getDistTo(size_t v) const { return (v < distTo.size()) ? distTo[v] : DBL_MAX; }
	bool hasPathTo(size_t v) const { return (v < distTo.size()) ? (distTo[v] != DBL_MAX) : false; }
	vector<DirectedEdge> getPathTo() const { return edgeTo; }

private:
	void relax(EdgeWeightDigraph &graph, size_t v)
	{
		vector<DirectedEdge> vec = graph.adj(v);

		for (size_t i = 0; i < vec.size(); i++)
		{
			size_t w = vec[i].to();

			// distTo[w]表示从s到w的最短路径的长度
			if (distTo[w] > distTo[v] + vec[i].weight())
			{
				distTo[w] = distTo[v] + vec[i].weight();
				edgeTo[w] = vec[i];

				size_t index = queHasVertax(w);
				if (index != que.size()) // 队列中包含节点w
					que[index].second = distTo[w];
				else
					que.push_back(pair<size_t, double>(w, distTo[w]));
			}
		}
	}

	size_t queHasVertax(size_t v)
	{
		for (size_t i = 0; i < que.size(); i++)
		{
			if (que[i].first == v)
				return i;
		}
		return que.size();
	}

	vector<DirectedEdge> edgeTo; // edgeTo[]中元素所对应的的可达顶点构成了一棵最短路径树
	vector<double> distTo; // distTo[]记录节点到起点的最短路径长度，初始化微无穷大
	vector<pair<size_t, double>> que; // 用vector来代替队列，队列pop相当于vec.erase(vec.begin())操作
};

int main(void)
{
	EdgeWeightDigraph graph(8);

	graph.addEdge(DirectedEdge(4, 5, 0.35));
	graph.addEdge(DirectedEdge(5, 4, 0.35));
	graph.addEdge(DirectedEdge(4, 7, 0.37));
	graph.addEdge(DirectedEdge(5, 7, 0.28));
	graph.addEdge(DirectedEdge(7, 5, 0.28));
	graph.addEdge(DirectedEdge(5, 1, 0.32));
	graph.addEdge(DirectedEdge(0, 4, 0.38));
	graph.addEdge(DirectedEdge(0, 2, 0.26));
	graph.addEdge(DirectedEdge(7, 3, 0.39));
	graph.addEdge(DirectedEdge(1, 3, 0.29));
	graph.addEdge(DirectedEdge(2, 7, 0.34));
	graph.addEdge(DirectedEdge(6, 2, 0.40));
	graph.addEdge(DirectedEdge(3, 6, 0.52));
	graph.addEdge(DirectedEdge(6, 0, 0.58));
	graph.addEdge(DirectedEdge(6, 4, 0.93));

	cout << graph.getVertax() << endl;
	cout << graph.getEdge() << endl;
	cout << "-------------------" << endl;
	graph.printGraph();
	cout << endl;

	// 输出起点0到图中所有点的最短路径的长度
	DijkstraSP dijk(graph, 0);
	for (size_t i = 0; i < graph.getArrSize(); i++)
	{
		cout << "0 -> " << i << ": " << dijk.getDistTo(i) << endl;
	}
	cout << endl;

	return 0;
}

void EdgeWeightDigraph::addEdge(const DirectedEdge &e)
{
	if (e.from() >= getArrSize())
		return;

	arr[e.from()].push_back(e);
	this->edge++; // 边的个数加1
}

vector<DirectedEdge> EdgeWeightDigraph::adj(size_t v) const
{
	if (v < getArrSize())
		return arr[v];
	else
		return vector<DirectedEdge>(); // a blank vector
}

vector<DirectedEdge> EdgeWeightDigraph::edges() const
{
	vector<DirectedEdge> vec;

	for (size_t i = 0; i < getArrSize(); i++)
	{
		for (size_t j = 0; j < arr[i].size(); j++)
			vec.push_back(arr[i][j]);
	}
	return vec;
}

void EdgeWeightDigraph::printAdj(size_t v) const
{
	if (v >= getArrSize())
		return;
	for (size_t i = 0; i < arr[v].size(); i++)
		arr[v][i].print();
	cout << endl;
}

void EdgeWeightDigraph::printGraph() const
{
	for (size_t i = 0; i < getArrSize(); i++)
		printAdj(i);
}