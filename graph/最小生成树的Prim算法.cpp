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

/// 为了存放Prim算法过程中的边，这些边按照权值从小到大排列
template <typename T>
struct greator
{
	bool operator()(const T &x, const T &y)
	{
		return x.getWeight() < y.getWeight();
	}
};

/// 最小生成树的Prim算法的延时实现
class LazyPrimMST
{
public:
	LazyPrimMST(const EdgeWeithtedGraph &graph) : marked(graph.arrSize())
	{
		if (graph.arrSize() == 0) // 防止为空图
			return;
		for (size_t i = 0; i < marked.size(); i++)
			marked[i] = false;

		visit(graph, 0);
		set<Edge>::iterator miniter;
		while (!pq.empty())
		{
			miniter = pq.begin();
			size_t v = miniter->either();
			size_t w = miniter->other(v);

			if (marked[v] && marked[w])
			{
				pq.erase(miniter);
				continue;
			}

			mst.push_back(*miniter);
			pq.erase(miniter);
			if (!marked[v])
				visit(graph, v);
			if (!marked[w])
				visit(graph, w);
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
	void visit(const EdgeWeithtedGraph &graph, size_t v)
	{
		marked[v] = true;

		vector<Edge> vec = graph.adj(v);
		for (size_t i = 0; i < vec.size(); i++)
		{
			if (!marked[vec[i].other(v)])
				pq.insert(vec[i]);
		}
	}

	vector<bool> marked;
	vector<Edge> mst; // 最小生成树的边
	set<Edge, greator<Edge>> pq; // 计算过程保存边的set
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

	// prim算法
	LazyPrimMST prim(graph);
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