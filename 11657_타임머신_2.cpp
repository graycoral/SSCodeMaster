#include <iostream>

using namespace std;

const int max_num = 6001;
const int INF = 987654321;
int upper[max_num];
int N, M;

int adj[max_num][max_num];
int ans = INF;


void input()
{
	for (int i = 0; i < max_num; i++) {
		for (int j = 0; j < max_num; j++) {
			adj[i][j] = INF;
		}
	}
	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		int u, v, c;
		cin >> u >> v >> c;
		adj[u][v] = c;
	}
}

#define MIN(a,b) (a > b ? b : a)
void bellmanFord(int src)
{
	bool updated = false;
	for (int i = 0; i < N; i++) upper[i] = INF;
	upper[src] = 0;

	for (int iter = 0; iter < N; iter++) {
		updated = false;
		for (int here = 0; here < N; here++) {
			for (int i = 0; i < N; i++) {
				if (upper[i] > upper[here] + adj[here][i]) {
					upper[i] = upper[here] + adj[here][i];
					updated = true;
					ans = MIN(ans, upper[i]);
				}
			}
		}
		if (!updated) break;
	}

	if (updated) {
		for (int i = 0; i < N; i++) upper[i] = INF;
		ans = INF;
	}
}

int main()
{
	freopen("11656_input.txt", "r", stdin);
	input();
	bellmanFord(1);

	cout << ans << endl;
	return 0;
}