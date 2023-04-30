#include <iostream>
#include <limits>
#include <vector>

using namespace std;
const double D_INF = numeric_limits<double>::infinity();
class Graph {
	class Edge {
	 public:
		int src;
		int dest;
		double cost;
		Edge(int _src, int _dest, double _cost)
				: src(_src), dest(_dest), cost(_cost) {}
	};

 private:
	int vert_num;
	int edge_num;
	vector<Edge> edges;
	vector<double> minDist;
	using src_cost = pair<int, double>;
	vector<src_cost> parent_path;

 public:
	Graph(int _vert)
			: vert_num(_vert),
				edge_num(0),
				minDist(_vert, D_INF),
				parent_path(_vert) {}
	void BellmanFord(int _start);
	void addEdge(int u, int v, double cost);
	void display(int _start) {
		for (int i = 0; i < vert_num; i++)
			printf("The cost from node %d to %d is %.2f\n", _start, i, minDist[i]);
		for (int i = 0; i < vert_num; i++)
			if (parent_path[i].second != 0)
				printf("The cheapest path is from node %d to %d with cost: %.2f\n",
							 parent_path[i].first, i, parent_path[i].second);
	}
};

void Graph::addEdge(int u, int v, double cost) {
	Edge newEdge(u, v, cost);
	edges.push_back(newEdge);
	edge_num++;
}

void Graph::BellmanFord(int _start) {
	minDist[_start] = 0;
	bool relaxedAnEdge = true;

	for (int k = 0; k < vert_num - 1 && relaxedAnEdge == true; k++) {
		relaxedAnEdge = false;
		for (auto edge : edges)
			if (minDist[edge.src] + edge.cost < minDist[edge.dest]) {
				minDist[edge.dest] = minDist[edge.src] + edge.cost;
				parent_path[edge.dest] = make_pair(edge.src, edge.cost);
				relaxedAnEdge = true;
			}
	}

	relaxedAnEdge = true;
	for (int k = 0; k < vert_num - 1 && relaxedAnEdge == true; k++) {
		relaxedAnEdge = false;
		for (auto edge : edges)
			if (minDist[edge.src] + edge.cost < minDist[edge.dest]) {
				minDist[edge.dest] = -D_INF;
				parent_path[edge.dest] = make_pair(edge.dest, 0);
				relaxedAnEdge = true;
			}
	}
};

int main() {
	int start = 0;
	Graph g(8);
	g.addEdge(0, 1, 1);
	g.addEdge(1, 2, 1);
	g.addEdge(2, 4, 1);
	g.addEdge(4, 3, -3);
	g.addEdge(3, 2, 1);
	g.addEdge(1, 5, 4);
	g.addEdge(1, 6, 4);
	g.addEdge(5, 6, 5);
	g.addEdge(6, 7, 4);
	g.addEdge(5, 7, 3);
	g.BellmanFord(start);
	g.display(start);

	return 0;
}
