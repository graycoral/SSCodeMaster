#include <iostream>

using namespace std;

const int max_num = 5e5 + 10;

typedef struct BT {
	int depth;
	int idx;
	int parent; int child[20];
} BT;

BT bt[max_num];
int V, E;
int M;
int child1, child2;
int ans, tree_size;
int q[max_num];

#define SWAP(a, b) {int t = a; a =b; b= t;}
void input()
{
	for (int i = 0; i < max_num; i++) {
		bt[i].parent = bt[i].child[0] = bt[i].child[1] = 0;
		bt[i].idx = 0; bt[i].depth = 1;
	}
	ans = 0;
	cin >> V;
	E = V - 1;

	for (int i = 0; i < E; i++) {
		int p, c;
		cin >> p >> c;
		if (p > c) {
			SWAP(p, c);
		}
		int& idx = bt[p].idx;
		bt[p].child[idx++] = c;
		bt[c].parent = p;
	}

	bt[1].depth = 1;
}

void makeDepth(int cur)
{
	for (int i = 0; i < bt[cur].idx; i++) {
		int ch = bt[cur].child[i];
		bt[ch].depth = bt[cur].depth + 1;
		makeDepth(ch);
	}
}

#define MAX(a,b) ( a> b ?  a: b) 
#define MIN(a,b) ( a> b ?  b: a)

void sol()
{
	int u, v;
	cin >> u >> v;
	if (bt[u].depth > bt[v].depth)	SWAP(u, v);

	int lowDepth = bt[v].depth;

	while (lowDepth != bt[u].depth) {
		v = bt[v].parent;
	}

	while (u != v) {
		u = bt[u].parent; 
		v = bt[v].parent;
	}

	ans = u;
}

int main()
{
	//freopen("11437_input.txt", "r", stdin);

	input();
	makeDepth(1);
	cin >> M;
	for (int i = 0; i < M; i++) {
		sol();
		cout << ans << endl;
	}

	return 0;
}