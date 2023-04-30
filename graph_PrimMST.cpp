#include <iostream>
#include <limits>
#include <list>
#include <queue>
#include <vector>

using namespace std;
const double D_INF = numeric_limits<double>::infinity();

class Graph {
 private:
	int vertex_num = 0;
	vector<list<pair<int, double>>> Adj_Table;

 public:
	Graph(int _num) : vertex_num(_num), Adj_Table(_num) {}
	void add_edge(int u, int v, double cost) {
		Adj_Table[u].emplace_back(make_pair(v, cost));
		Adj_Table[v].emplace_back(make_pair(u, cost));
	}
	void PrimMST(int _start = 0);
};

void Graph::PrimMST(int _start) {
	using Path = pair<double, int>;	 // doubel->Path Distance, int->Target Node
	priority_queue<Path, vector<Path>, greater<Path>> Alter_Path;
	vector<bool> inMST(vertex_num, false);
	vector<int> parent(vertex_num, -1);
	vector<double> minDist(vertex_num, D_INF);

	minDist[_start] = 0;
	Alter_Path.push(make_pair(0, _start));
	while (!Alter_Path.empty()) {
		auto new_node = Alter_Path.top().second;
		inMST[new_node] = true;
		Alter_Path.pop();

		for (auto Iter : Adj_Table[new_node]) {
			auto vert = Iter.first;
			auto cost = Iter.second;

			if (inMST[vert] == false && cost < minDist[vert]) {
				minDist[vert] = cost;
				Alter_Path.push(make_pair(minDist[vert], vert));
				parent[vert] = new_node;
			}
		}
	}
	for (int i = 1; i < vertex_num; i++) {
		cout << parent[i] << "->" << i << ", min cost is " << minDist[i] << endl;
	}
}

int main() {
	int V = 9;
	Graph g(V);
	g.add_edge(0, 1, 4);
	g.add_edge(0, 7, 8);
	g.add_edge(1, 2, 8);
	g.add_edge(1, 7, 11);
	g.add_edge(2, 3, 7);
	g.add_edge(2, 8, 2);
	g.add_edge(2, 5, 4);
	g.add_edge(3, 4, 9);
	g.add_edge(3, 5, 14);
	g.add_edge(4, 5, 10);
	g.add_edge(5, 6, 2);
	g.add_edge(6, 7, 1);
	g.add_edge(6, 8, 6);
	g.add_edge(7, 8, 7);

	g.PrimMST();

	return 0;
}
