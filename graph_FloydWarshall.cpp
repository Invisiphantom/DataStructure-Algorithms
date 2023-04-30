#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;
const double D_INF = numeric_limits<double>::infinity();
class Graph {
 private:
	static const int V = 6;
	double minDist[V][V];
	int parent_path[V][V];
	double graph[V][V] = {
			{0, D_INF, 10, D_INF, 30, 100},		{D_INF, 0, 5, D_INF, D_INF, D_INF},
			{D_INF, D_INF, 0, 50, D_INF, 1},	{D_INF, D_INF, D_INF, 0, D_INF, 10},
			{D_INF, D_INF, D_INF, 20, 0, 60}, {D_INF, D_INF, D_INF, 0, D_INF, 0},
	};

 public:
	void floydWarshall();
	void display();
	void printSolution();
};
void Graph::floydWarshall() {
	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++) {
			minDist[i][j] = graph[i][j];
			parent_path[i][j] = i;
		}

	for (int k = 0; k < V; k++)
		for (int i = 0; i < V; i++)
			for (int j = 0; j < V; j++)
				if (minDist[i][k] + minDist[k][j] < minDist[i][j]) {
					minDist[i][j] = minDist[i][k] + minDist[k][j];
					parent_path[i][j] = parent_path[k][j];
				}
}

void Graph::display() {
	cout << "minDist:" << endl;
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			cout << minDist[i][j] << '\t';
		}
		cout << endl;
	}
	cout << "parent_path:" << endl;
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			cout << parent_path[i][j] << " ";
		}
		cout << endl;
	}
}

void Graph::printSolution() {
	cout << "打印任一对顶点间的最短路径,"
			 << "若weight为INF和dist[i][j]为INF则表示i->j无路径" << endl;
	for (int i = 0; i < V; i++) {
		cout << "----从" << i << "出发的最短路径:----" << endl;
		for (int j = 0; j < V; j++) {
			cout << parent_path[i][j] << " --> " << j << " \t weight is :";
			int parent = parent_path[i][j];
			if (graph[parent][j] == D_INF)
				cout << "INF\t";
			else
				cout << graph[parent][j] << "\t";
			cout << " minDist[" << i << "][" << j << "] is ";
			if (minDist[i][j] == D_INF)
				cout << "INF" << endl;
			else
				cout << minDist[i][j] << endl;
		}
		cout << endl;
	}
}
int main() {
	Graph g;
	g.floydWarshall();
	g.display();
	g.printSolution();
	return 0;
}
