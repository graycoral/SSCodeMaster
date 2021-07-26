#include <iostream>

using namespace std;

int N, M;

const int max_num = 2e5 + 10;

typedef struct Edge {
	long long dist;
	int x, y;
} Edge;

Edge edge[max_num];

#define SWAP(a, b) { Edge t =a; a= b; b= t;}
void sort_edge(Edge* arr, int start, int end)
{
	if (start >= end)    return;
	int pivot = start;
	int i = start, j = end;

	while (i < j) {
		while (arr[i].dist <= arr[pivot].dist && i < end) ++i;
		while (arr[j].dist > arr[pivot].dist&& j > start) --j;
		if (i > j)  break;
		SWAP(arr[i], arr[j]);
	}
	SWAP(arr[j], arr[pivot]);
	sort_edge(arr, start, j - 1);
	sort_edge(arr, j + 1, end);
}

void input()
{
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> edge[i].x >> edge[i].y >> edge[i].dist;
	}
}

int parent[max_num];
int ranking[max_num];

int findParent(int x) {
	if (parent[x] == x) return x;
	else parent[x] = findParent(parent[x]);
}

bool same_parent(int x, int y)
{
	if (findParent(x) == findParent(y))  return true;
	else return false;
}

#define SWAP_P(a, b) {int t= a; a= b; b=t;}
void Union(int x, int y)
{
	x = findParent(x);
	y = findParent(y);

	if (ranking[x] > ranking[y])  SWAP_P(x, y);
	parent[x] = y;
	if (ranking[x] == ranking[y])    ranking[y]++;
}

long long kruskal()
{
	long long ret = 0;
	sort_edge(edge, 0, M - 1);
	for (int i = 1; i <= N; i++) {
		parent[i] = i; ranking[i] = 1;
	}

	for (int i = 0; i < M; i++) {
		int x = edge[i].x, y = edge[i].y;
		if (!same_parent(x, y)) {
			ret += edge[i].dist;
			Union(x, y);
		}
	}

	return ret;
}

int main()
{
	int test_case = 1;
	//freopen("swea_4006_input.txt", "r", stdin);
	cin >> test_case;
	for (int i = 1; i <= test_case; i++) {
		input();
		cout << "#" << i << " " << kruskal() << endl;
	}
	return 0;
}