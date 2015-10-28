#include <iostream>
#include <vector>
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

	graph.removeEdge(0, 4);
	cout << endl;
	cout << graph.vertax() << endl;
	cout << graph.edge() << endl;
	graph.showGraph();

	graph.addVertax(5);
	cout << endl;
	cout << graph.vertax() << endl;
	cout << graph.edge() << endl;
	graph.showGraph();

	graph.removeVertax(3);
	cout << endl;
	cout << graph.vertax() << endl;
	cout << graph.edge() << endl;
	graph.showGraph();

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
