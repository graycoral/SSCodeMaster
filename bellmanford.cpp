#include <iostream>
#include <vector>
#include <algorithm>

const int MAX_V = 10000;
const int INF = 0xfffe;

using namespace std;
int V;
vector<pair<int, int>> adj[MAX_V];

vector<int> bellmanford(int src)
{
	vector<int> upper(V, INF);
	upper[src] = 0;
	bool updated;

	for (int iter = 0; iter < V; ++iter) {
		updated = false;
		for (int here = 0; here < V; ++here) {
			for (int i = 0; i < adj[here].size(); ++i) {
				int there = adj[here][i].first;
				int cost = adj[here][i].second;
				if (upper[there] > upper[here] + cost) {
					upper[there] = upper[there] + cost;
					updated = true;
				}
			}
		}
		if (!updated)	break;
		upper.clear();
		return upper;
	}
}

struct edge {
	int there;
	int cost;
};

edge adj[MAX_V][[MAX_V]];

void bf(int src)
{
	int upper[MAX_V] = { INF };
	bool updated = false;
	upper[src] = 0;

	for (int i = 0; i < V; i++) {
		updated = false;
		for (int here = 0; here < V; here++) {
			for (int j = 0; j < adj[here,].size(); j++) {

			}
		}
	}
}
