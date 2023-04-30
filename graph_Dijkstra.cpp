#include <cstdio>
#include <iostream>
#include <limits>
#include <list>
#include <queue>
#include <set>

using namespace std;
const double D_INF = numeric_limits<double>::infinity();
class Graph {
 private:
	int vert_num = 0;
	int start = 0;
	vector<list<pair<int, double>>> Adj_Table;
	vector<double> minDist;
	using src_cost = pair<int, double>;
	vector<src_cost> parent_path;

 public:
	Graph(int _num, int _start)
			: vert_num(_num),
				start(_start),
				Adj_Table(_num),
				minDist(_num, D_INF),
				parent_path(_num, make_pair(0,0.0)) {}
	void addEdge(int src, int dst, double cost) {
		Adj_Table[src].emplace_back(make_pair(dst, cost));
	}
	void Dijkstra();
	void dispaly() {
		for (int i = 0; i < vert_num; i++)
			printf("The cost from node %d to %d is %.2f\n", start, i, minDist[i]);
		for (int i = 0; i < vert_num; i++)
			if (parent_path[i].second != 0)
				printf("The cheapest path is from node %d to %d with cost: %.2f\n",
							 parent_path[i].first, i, parent_path[i].second);
	}
};

void Graph::Dijkstra() {
	using Path = pair<double, int>;	 // doubel->Path Distance, int->Target Node
	priority_queue<Path, vector<Path>, greater<Path>> Alter_Path;

	Alter_Path.push(make_pair(0, start));
	minDist[start] = 0;
	while (!Alter_Path.empty()) {
		auto new_node = Alter_Path.top().second;
		Alter_Path.pop();

		for (auto Iter : Adj_Table[new_node]) {
			int vert = Iter.first;
			double cost = Iter.second;
			if (minDist[vert] > minDist[new_node] + cost) {
				minDist[vert] = minDist[new_node] + cost;
				parent_path[vert].first = new_node;
				parent_path[vert].second = cost;
				Alter_Path.push(make_pair(minDist[vert], vert));
			}
		}
	}
}
int main() {
	int vert_num = 9, start = 0;
	Graph g(vert_num, start);
	g.addEdge(0, 1, 4);
	g.addEdge(0, 7, 8);
	g.addEdge(1, 2, 8);
	g.addEdge(1, 7, 11);
	g.addEdge(2, 3, 7);
	g.addEdge(2, 8, 2);
	g.addEdge(2, 5, 4);
	g.addEdge(3, 4, 9);
	g.addEdge(3, 5, 14);
	g.addEdge(4, 5, 10);
	g.addEdge(5, 6, 2);
	g.addEdge(6, 7, 1);
	g.addEdge(6, 8, 6);
	g.addEdge(7, 8, 7);
	g.Dijkstra();
	g.dispaly();
	return 0;
}
