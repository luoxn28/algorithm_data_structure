#include <iostream>
#include <vector>
using namespace std;

/// 加权有向边的数据结构
class DirectedEdge
{
public:
	DirectedEdge(size_t _v, size_t _w, double _weight) : v(_v), w(_w), weights(_weight) { }

	size_t from() const { return v; }
	size_t to()   const { return w; }
	double weight() const { return weights; }
	void print() const { cout << "(" << v << "->" << w << ": " << weights << ") "; }

private:
	size_t v, w; // 两个顶点
	double weights; // 权重
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
	size_t vertax, edge; // 顶点个数，边的个数
	vector<vector<DirectedEdge>> arr; // 临界表
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
