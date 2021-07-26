#include <iostream>

using namespace std;

const int max_num = 5e4+10;

int N, M, X;
int ans = 0;

typedef struct Edge {
	int u,v, dist;
} Edge;

Edge edge[max_num];

void input()
{
	for (int i = 0; i < N; i++) {
		edge[i].u = edge[i].v = edge[i].dist = 0;
	}

	cin >> N >> M >> X;

	for (int i = 0; i < M; i++) {
		int s, e, d;
		cin >> s >> e >> d;
		edge[i].u = s;
		edge[i].v = e;
		edge[i].dist = d;
	}
}

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a > b ? b : a)

const int INF = 987654321;

#define SWAP_EDGE(a, b) {Edge t= a; a =b; b= t;}
void Sort(Edge* arr, int start, int end)
{
	if (start >= end)	return;
	int pivot = start;
	int i = start, j = end;
	while (i < j) {
		while (i < end && arr[i].u <= arr[pivot].u) ++i;
		while (arr[j].u > arr[pivot].u) --j;
		SWAP_EDGE(arr[i], arr[j]);
	}
	SWAP_EDGE(arr[j], arr[pivot]);
	Sort(arr, start, j - 1);
	Sort(arr, j + 1, end);
}

#define MIN(a, b) (a> b ? b : a)
#define MAX(a, b) (a> b ? a : b)

void dijsktra(int start, int end)
{
	int dist[max_num];
	int visitied[max_num];
	const int INF = 987654321;
	
	Sort(edge, 0, N - 1);
	
	int min = INF;
	int minv = 0;
	int idx = 0;

	for (int i = 0; i < N; i++) {
		dist[i] = INF;
		visitied[i] = 0;
	}

	for (int i = 0; i <= N; i++) {
		if (edge[i].u == start) {
			idx = start;
			break;
		}
	}
	while (edge[idx].u == start) {
		dist[edge[idx].v] = edge[idx].dist;
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (visitied[j] != 0 && min > dist[j])	min = dist[j];
			minv = j;
		}
		visitied[minv] = 1;

		int minvIdx = 0;
		for (int j = 0; j <= N; j++) {
			if (edge[i].u == minv) {
				minvIdx = start;
				break;
			}
		}

		while (edge[minvIdx].u == minv) {
			dist[edge[idx].v] = MIN(dist[edge[idx].v], dist[minv] + edge[minvIdx].dist);
			ans = MAX(ans, dist[edge[idx].v]);
			minvIdx++;
		}
	}
}

int main()
{
	int test_case = 1;
	//freopen("swea_4007_input.txt", "r", stdin);
	cin >> test_case;
	for (int i = 1; i <= test_case; i++) {
		input();
		dijsktra(1, N);
		cout << "#" << i <<" "<< ans << endl;
	}
	return 0;
}