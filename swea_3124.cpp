#include <iostream>

using namespace std;

const int max_num = 2e6 + 10;

typedef struct Edge {
	long long dist;
	int x, y;
} Edge;

int V, E;
Edge edge[max_num];
int edge_size = 0;
int parent[max_num];

#define SWAP(a, b) {Edge t = a; a = b; b = t;}
void Sort(Edge* arr, int start, int end)
{
	if (start >= end)	return;
	int pivot = start;
	int i = start, j = end;
	while (i < j) {
		while (i < E && arr[i].dist <= arr[pivot].dist) {
			++i;
		}
		while (arr[j].dist > arr[pivot].dist) {
			--j;
		}
		if (i > j)	break;
		SWAP(arr[i], arr[j]);
	}
	SWAP(arr[j], arr[pivot]);
	Sort(arr, start, j - 1);
	Sort(arr, j + 1, end);
}

int FindParent(int A)
{
	if (A == parent[A]) return A;
	return parent[A] = FindParent(parent[A]);
}

bool SameParent(int A, int B)
{
	A = FindParent(A);
	B = FindParent(B);

	if (A == B) return true;
	return false;
}

int Min(int A, int B) { if (A < B) return A; return B; }
void Union(int A, int B)
{
	A = FindParent(A);
	B = FindParent(B);
	int Min_Parent = Min(A, B);
	parent[A] = Min_Parent;
	parent[B] = Min_Parent;
}

long long kruskal()
{
	long long ret = 0;
	for (int i = 1; i <= V; i++)	parent[i] = i;
	Sort(edge, 0, E);
	for (int i = 0; i < E; ++i) {
		if (SameParent(edge[i].x, edge[i].y) == false) {
			Union(edge[i].x, edge[i].y);
			ret += edge[i].dist;
		}
	}

	return ret;
}

void input()
{
	cin >> V >> E;
	for (int i = 0; i < E; ++i) {
		cin >> edge[i].x >> edge[i].y >> edge[i].dist;
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int test_case = 1;
	//freopen("swea_3124_input.txt", "r", stdin);
	cin >> test_case;
	for (int i = 1; i <= test_case; i++) {
		input();
		long long ans = kruskal();
		cout << "#" << i << " " << ans << endl;
	}
	return 0;
}