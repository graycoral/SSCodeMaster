#include <iostream>

using namespace std;
int V, E;
const int max_num = 1e6 + 10;
const long long INF = 987654321;

long long weight[10001][10001] = { INF };

void input()
{
	cin >> V >> E;
	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++)
			weight[i][j] = INF;

	for (int i = 0; i < E; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		//cin >> edge[i].x >> edge[i].y >> edge[i].dist;
		weight[a - 1][b - 1] = c;
		weight[b - 1][a - 1] = c;
	}
}


bool added[max_num];
int parent[max_num];
long long minWeight[max_num];

void prim()
{
	long long ret = 0;
	for (int i = 0; i < V; ++i) {
		minWeight[i] = INF; added[i] = false; parent[i] = -1;
	}

	minWeight[0] = 0; parent[0] = 0;

	for (int i = 0; i < V; ++i) {
		int u = -1;
		for (int v = 0; v < V; v++) {
			if (!added[v] && (u == -1 || minWeight[u] > minWeight[v]))	u = v;
		}

		ret += minWeight[u];
		added[u] = true;

		for (int i = 0; i < V; ++i) {
			if (added[i] == false && weight[u][i] < minWeight[i]) {
				minWeight[i] = weight[u][i];
				parent[i] = u;
			}
		}
	}
	cout << ret << endl;
}

int main()
{
	//freopen("1197_input.txt", "r", stdin);
	input();
	prim();
	return 0;
}