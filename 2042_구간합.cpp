#if 0
#include <iostream>

using namespace std;

const int max_num = 1e6 + 1;

int N, M, K;
long long int arr[max_num];
long long int rangeSum[max_num * 4];

void input()
{
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}
}

const int INF = 987654321;

int initRangeSum(int left, int right, int node)
{
	//if(left > right) return 0;
	if (left == right)	return rangeSum[node] = arr[left];

	int mid = (left + right) / 2;

	long long int leftSum = initRangeSum(left, mid, node*2);
	long long int rightSum = initRangeSum(mid+1, right, node*2 + 1);

	return rangeSum[node] = leftSum + rightSum;
}

void updateSum(int idx, long long int diff, int node, int leftNode, int rightNode)
{
	if (idx > rightNode || idx < leftNode)	return;
	rangeSum[node] += diff;
	
	if (leftNode != rightNode) {
		int mid = (leftNode + rightNode) / 2;

		updateSum(idx, diff, node * 2, leftNode, mid);
		updateSum(idx, diff, node * 2 + 1, mid + 1, rightNode);
	}
}

int querySum(int left, int right, int node, int leftNode, int rightNode)
{
	if (left > rightNode || right < leftNode)	return 0;
	if (left <= leftNode &&  rightNode <= right)	return rangeSum[node];

	int mid = (leftNode + rightNode) / 2;

	long long int leftSum = querySum(left, right, node * 2, leftNode, mid);
	long long int rightSum = querySum(left, right, node * 2 + 1, mid + 1, rightNode);

	return leftSum + rightSum;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	//freopen("2042_input.txt", "r", stdin);

	input();
	initRangeSum(0, N-1, 1);

	for (int i = 0; i < M + K; i++) {
		int order; 
		cin >> order;
		if (order == 1) {
			//update
			int idx;
			long long val;
			cin >> idx >> val;
			int diff = val - arr[idx - 1];
			arr[idx - 1] = val;
			updateSum(idx -1, diff, 1, 0, N-1);
		}
		else if (order == 2) {
			//sum
			int start, end;
			cin >> start >> end;
			long long int ans = querySum(start -1, end -1, 1, 0, N - 1);
			cout << ans << endl;
		}
	}

	return 0;
}

#else 
#include <iostream>

using namespace std;
typedef long long int ll;

const int max_num = 1e6 + 1;
ll arr[max_num];
ll inputArr[max_num];
int N, M, K;

long long sum(long long* tree, int i)
{
	long long ans = 0;
	while (i > 0) {
		ans += tree[i];
		i -= (i & -i);
	}

	return ans;
}

void UpdateTree(long long* tree, int size, int i, long long diff)
{
	while (i < size) {
		tree[i] += diff;
		i += (i & -i);
	}
}

int main()
{
	//freopen("2042_input.txt", "r", stdin);
	cin >> N >> M >> K;

	for (int i = 1; i <= N; i++) {
		cin >> inputArr[i];
		UpdateTree(arr, N + 1, i, inputArr[i]);
	}

	for (int i = 0; i < M + K; i++) {
		int a, b;
		long long c;
		cin >> a >> b >> c;

		if (a == 1) {
			long long diff = c - inputArr[b];
			inputArr[b] = c;
			UpdateTree(arr, N + 1, b, diff);
		}
		else {
			long long ans = sum(arr, c) - sum(arr, b-1);
			cout << ans << endl;
		}
	}
	return 0;
}
#endif