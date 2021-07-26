#include <iostream>

using namespace std;
int V, E;
const int max_num = 1e6 + 10;

typedef struct Edge {
	long long dist;
	int x, y;
};

Edge edge[max_num];
int parent[max_num];
int ranking[max_num];

void input()
{
	cin >> V >> E;

	for (int i = 0; i < E; ++i) {
		cin >> edge[i].x >> edge[i].y >> edge[i].dist;
	}
}

#define SWAP(a,b) {Edge t = a; a = b; b= t;}

void Sort(Edge* arr, int start, int end)
{
	if (start >= end)	return;
	int pivot = start;
	int i = start, j = end;
	while (i < j) {
		while (arr[i].dist <= arr[pivot].dist) ++i;
		while (arr[j].dist > arr[pivot].dist) --j;
		if (i > j)	break;
		SWAP(arr[i], arr[j]);
	}
	SWAP(arr[j], arr[pivot]);
	Sort(arr, start, j - 1);
	Sort(arr, j + 1, end);
}

int findParent(int x)
{
	if (parent[x] == x)	return x;
	else return parent[x] = findParent(parent[x]);
}

bool same_parent(int x, int y)
{
	if (findParent(x) == findParent(y)) return true;
	else return false;
}

#define MIN(a, b) (a >b ? b:a)
void Union(int x, int y)
{
	x = findParent(x);
	y = findParent(y);
	if (ranking[x] > ranking[y]) {
		int t = x; x = y; y = t;
	}
	parent[x] = MIN(x, y);
	parent[y] = MIN(x, y);
	if (ranking[x] == ranking[y]) ++ranking[y];
}

void kruskal()
{
	long long ret = 0;
	Sort(edge, 0, E);
	for (int i = 1; i <= E; i++) {
		parent[i] = i;
		ranking[i] = 1;
	}


	for (int iter = 0; iter < E; ++iter) {
		int x = edge[iter].x; int y = edge[iter].y;
		if (same_parent(x, y) == false) {
			ret += edge[iter].dist;
			Union(x, y);
		}
	}
	cout << ret << endl;
}

int main()
{
	//freopen("1197_input.txt", "r", stdin);
	input();
	kruskal();
	return 0;
}