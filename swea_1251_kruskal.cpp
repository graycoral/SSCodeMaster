#include <iostream>

using namespace std;

const int MAX_N = 1e3 + 10;

int N;
long long x[MAX_N];
long long y[MAX_N];
double rate;

typedef struct Edge {
	long long dist,x ,y;
} Edge;

Edge edge[MAX_N];
int edge_idx = 0;
int parent[MAX_N] = { 0 };

void input()
{
	for (int i = 0; i <= N; i++) {
		x[i] = y[i] = 0;
		edge[i].dist = edge[i].x = edge[i].y = 0;
	}

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> x[i];
	}
	for (int i = 0; i < N; i++) {
		cin >> y[i];
	}
	cin >> rate;
	edge_idx = 0;

	for (int i = 0; i < N; ++i) {
		for (int j = i + 1; j < N; ++j) {
			edge[edge_idx].dist = (x[i] - x[j]) * (y[i] - y[j]);
			edge[edge_idx].x = i; edge[edge_idx++].y = j;
		}
	}
}

#define SWAP(a, b) {Edge t = a; a = b; b= t;}
void Sort(Edge* e, int start, int end)
{
	if (start >= end) return;
	int pivot = start;
	int i = pivot, j = end;

	while (i < j) {
		while (e[i].dist <= e[pivot].dist) {
			++i;
		}
		while (e[pivot].dist > e[j].dist) {
			--j;
		}
		if (i > j)	break;
		SWAP(e[i], e[j]);
	}
	SWAP(e[j], e[pivot]);
	Sort(e, start, j - 1);
	Sort(e, j + 1, end);
}

int find_parent(int x)
{
	if (parent[x] == x)	return x;
	else return parent[x] = find_parent(parent[x]);
}

#define MIN(a, b) (a > b ?  b:a)
void Union(int x, int y)
{
	x = find_parent(x);
	y = find_parent(y);

	parent[x] = MIN(x, y);
	parent[y] = MIN(x, y);
}

bool same_parent(int x, int y)
{
	if (find_parent(x) != find_parent(y))	return true;
	else return false;
}

long long kruskal()
{
	long long ret = 0;
	Sort(edge, 0, edge_idx);
	for (int i = 1; i <= N; i++) parent[i] = i;

	for (int i = 0; i < edge_idx; ++i) {
		if (same_parent(edge[i].x, edge[i].y) == false) {
			Union(edge[i].x, edge[i].y);
			ret += edge[i].dist;
		}
	}

	return ret;
}


int main()
{
	int test_case = 1;
	//freopen("swea_1251_input.txt", "r", stdin);

	cin >> test_case;
	for (int i = 1; i <= test_case; i++) {
		input();
		cout << "#" << i << " " << static_cast<double>(kruskal())  *  rate << endl;
	}
	return 0;
}