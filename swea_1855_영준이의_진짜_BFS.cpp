#include <iostream>
#include <algorithm>

using namespace std;
const int max_num = 1e5 + 10;
const int INF = 987654321;
const int max_log_2 = 18;
int seg_tree[max_num * 4];
int arr[max_num];
int trip[max_num];
int tripSize = 0;

int no2Serial[max_num];
int serail2no[max_num];
int locInTrip[max_num];
int nextSerial;
int depth[max_num];
int N, Q;

typedef struct Child {
	int size;
	int child[max_log_2];
} Child;

Child ch[max_num];

#define MIN(a, b) (a >b ? b: a)

int init_seg(int left, int right, int node)
{
	if (left == right)	seg_tree[node] = trip[left];

	int mid = (left + right) / 2;
	int leftMin = init_seg(left, mid, node * 2);
	int rightMin = init_seg(mid + 1, right, node * 2 + 1);

	return seg_tree[node] = MIN(leftMin, rightMin);
}

int seg_query(int left, int right, int node, int leftNode, int rightNode)
{
	if (right < leftNode || rightNode < left)	return INF;
	if (left <= leftNode && rightNode <= right)	return seg_tree[node];

	int mid = (left + right) / 2;
	int leftMin = seg_query(left, mid, node * 2, leftNode, rightNode);
	int rightMin = seg_query(mid+1, right, node * 2 + 1, leftNode, rightNode);

	return seg_tree[node] = MIN(leftMin, rightMin);
}

void Traverse(int here, int d)
{
	no2Serial[here] = nextSerial;
	serail2no[nextSerial++] = here;
	depth[here] = d;
	locInTrip[here] = tripSize;
	trip[tripSize++] = no2Serial[here];
	for (int i = 0; i < ch[here].size; i++) {
		Traverse(ch[here].child[i], d + 1);
 		trip[tripSize++] = no2Serial[here];
	}
}

#define SWAP(a, b) {int t =a; a =b; b=t;}
void preprocess()
{
	nextSerial = 0;
	Traverse(0, 0);
	init_seg(0, tripSize, 1);
}
int distance(int u, int v)
{
	int lu = locInTrip[u], lv = locInTrip[v];
	if (lu > lv) swap(lu, lv);
	int lca = serail2no[seg_query(lu, lv, 1, 0, tripSize)];
	return depth[u] + depth[v] - (2 * depth[lca]);
}

long long sol()
{
	long long ret = 0;
	preprocess();

	int left, right;
	cin >> left >> right;
	ret = distance(left, right);

	return ret;
}

void input()
{
	for (int i = 0; i <= N; i++) {
		ch[i].size = 0;
		locInTrip[i] = serail2no[i] = no2Serial[i] = 0;
	}

	for (int i = 0; i < max_log_2; i++)	depth[i] = 0;
	cin >> N;

	for (int i = 1; i < N; i++) {
		int parent;
		cin >> parent;
		ch[parent].child[ch[parent].size++] = i;
	}
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	int test_case = 1;
	freopen("swea_1855_input.txt", "r", stdin);
	cin >> test_case;

	for (int i = 1; i <= test_case; i++) {
		input();
		sol();
	}
	return 0;
}