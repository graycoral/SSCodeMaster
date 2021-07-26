#include <iostream>

using namespace std;
const int max_num = 1e6 + 10;

typedef struct Edge {
	int dist;
	int x, y;
} Edge;

Edge edge[max_num];
int parent[max_num];
int ranking[max_num];
int N, M;

void input()
{
	//freopen("1922_input.txt", "r", stdin);
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> edge[i].x >> edge[i].y >> edge[i].dist;
	}
}

#define SWAP(a, b) {Edge t =a; a= b ;b= t;}
void sort(Edge* arr, int start, int end)
{
	if (start >= end)	return;

	int pivot = start; int i = start, j = end;
	while (i < j) {
		while (arr[i].dist <= arr[pivot].dist) ++i;
		while (arr[j].dist > arr[pivot].dist) --j;
		if (i > j)	break;
		SWAP(arr[i], arr[j]);
	}
	SWAP(arr[j], arr[pivot]);
	sort(arr, start, j - 1);
	sort(arr, j + 1, end);
}


int findParent(int x)
{
	if (parent[x] == x)	return x;
	else return parent[x] = findParent(parent[x]);
}

#define MIN(a,b) (a > b ? b : a)
void Union(int x, int y)
{
	x = findParent(x);
	y = findParent(y);

	if (x != y) {
		parent[y] = x;
	}
}
bool sampe_parent(int x, int y)
{
	x = findParent(x);
	y = findParent(y);
	if (x == y)	return true;
	else return false;
}

void Kruskal()
{
	long long ret = 0;
	sort(edge, 0, M);
	for (int i = 1; i <= M; i++) parent[i] = i;

	for (int iter = 0; iter < M; iter++) {
		int x = edge[iter].x; int y = edge[iter].y;
		if (sampe_parent(x, y) == false) {
			ret += edge[iter].dist;
			Union(x, y);
		}
	}

	cout << ret << endl;

}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL); 	cout.tie(NULL);
	input();
	Kruskal();

	return 0;
}