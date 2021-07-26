#include <iostream>

using namespace std;

const int max_num = 5e5 + 10;

typedef struct BT {
	int value;
	int depth;
	int idx;
	int parent; int child[2];
} BT;

BT bt[max_num];
int V, E;
int child1, child2;
int ans, tree_size;

void input()
{
	for (int i = 0; i < V; i++) {
		bt[i].value = bt[i].parent = bt[i].child[0] = bt[i].child[1] = 0;
		bt[i].idx = 0; bt[i].depth = 0;
	}
	ans = 0, tree_size = 0;
	cin >> V;// >> E >> child1 >> child2;
	E = V - 1;

	for (int i = 0; i < E; i++) {
		int p, c;
		cin >> p >> c;
		int& idx = bt[p].idx;
		bt[p].child[idx++] = c;
		bt[c].parent = p;
	}
	
	bt[1].depth = 1;
}

void makeDepth(int cur)
{
	int ch1 = bt[cur].child[0];
	int ch2 = bt[cur].child[1];

	if (ch1 != 0) {
		bt[ch1].depth = bt[cur].depth + 1;
		makeDepth(ch1);
	}
	if (ch2 != 0) {
		bt[ch2].depth = bt[cur].depth + 1;
		makeDepth(ch2);
	}
}

#define MAX(a,b) ( a> b ?  a: b) 
#define MIN(a,b) ( a> b ?  b: a) 

int countTree(int lca)
{
	int retVal = bt[lca].idx;
	for (int i = 0; i < bt[lca].idx; i++) {
		retVal += countTree(bt[lca].child[i]);
	}
	return retVal;
}

void sol()
{
	makeDepth(1);
	int lowDepth = MIN(bt[child1].depth, bt[child2].depth);

	while (lowDepth != bt[child1].depth) {
		child1 = bt[child1].parent;
	}
	while (lowDepth != bt[child2].depth) {
		child2 = bt[child2].parent;
	}

	while (bt[child1].parent != bt[child2].parent) {
		child1 = bt[child1].parent;
		child2 = bt[child2].parent;
	}

	ans = bt[child1].parent;
	//tree_size = countTree(ans);
}

int main()
{
	int test_case = 1;
	//freopen("swea_1248_input.txt", "r", stdin);
	
	//cin >> test_case;

	for (int i = 1; i <= test_case; i++) {
		input();
		sol(); 
		//cout << "#"<<i << " " << ans << " " << tree_size << endl;
		cout << ans << endl;
	}
	return 0;
}