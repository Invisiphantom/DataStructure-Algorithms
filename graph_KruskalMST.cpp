#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Subset {
 public:
	int* parent = nullptr;
	int* rank = nullptr;
	Subset(int n) {
		parent = new int[n];
		rank = new int[n];
		for (int i = 0; i < n; i++) {
			parent[i] = i;
			rank[i] = 0;
		}
	}
	int find(int x)
	{
		if (parent[x] != x) {
			parent[x] = find(parent[x]);
		}
		return parent[x];
	}
	void unionSet(int x, int y) {
		int xroot = find(x);
		int yroot = find(y);
		if (xroot == yroot) return;

		if (rank[xroot] < rank[yroot])
			parent[xroot] = yroot;
		else if (rank[xroot] > rank[yroot])
			parent[yroot] = xroot;
		else {
			parent[yroot] = xroot;
			rank[xroot]++;
		}
	}
};

class Edge {
 public:
	int src;
	int dest;
	int weight;
	Edge(int _src = 0, int _dest = 0, int _weight = 0)
			: src(_src), dest(_dest), weight(_weight) {}
	friend bool operator<(const Edge& x, const Edge& y) {
		return x.weight < y.weight;
	}
};

class Graph {
 public:
	int vert_num;
	vector<Edge> edge;
	Graph(int v = 0) : vert_num(v), edge(0) {}

	void Kruskal_MST() {
		vector<Edge> result;
		sort(edge.begin(), edge.end());
		Subset subsets(vert_num);

		for (int i = 0; i < edge.size(); i++) {
			int x = subsets.find(edge[i].src);
			int y = subsets.find(edge[i].dest);
			if (x != y) {
				subsets.unionSet(x, y);
				result.push_back(edge[i]);
			}
		}
		for (auto it : result) {
			cout << it.src << "-->" << it.dest << "   weight: " << it.weight << endl;
		}
	}
};

int main() {
	Graph g1(4);
	g1.edge.push_back(Edge(0, 1, 10));
	g1.edge.push_back(Edge(0, 2, 6));
	g1.edge.push_back(Edge(0, 3, 5));
	g1.edge.push_back(Edge(1, 3, 15));
	g1.edge.push_back(Edge(2, 3, 4));
	g1.Kruskal_MST();

	return 0;
}
