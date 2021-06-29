#include <iostream>

using namespace std;
const int max_num = 120000;
int N; int M;
int arr[max_num];
int rangeMin[500000];
int rangeMax[500000];
int Left[120000]; 
int Right[120000];

#define MIN(a, b) ( a > b ? b: a)
#define MAX(a, b) ( a > b ? a: b);

int initMin(int left, int right, int node) {
	if (left == right) {
		return rangeMin[node] = arr[left];
	}

	int mid = (left + right) / 2;
	int leftMin = initMin(left, mid, node * 2);
	int rightMin = initMin(mid + 1, right, node * 2 + 1);

	rangeMin[node] = MIN(leftMin, rightMin);

	return rangeMin[node];
}

int initMax(int left, int right, int node) {
	if (left == right) {
		return rangeMax[node] = arr[left];
	}

	int mid = (left + right) / 2;
	int leftMax = initMax(left, mid, node * 2);
	int rightMax = initMax(mid + 1, right, node * 2 + 1);

	rangeMax[node] = MAX(leftMax, rightMax);

	return rangeMax[node];
}

//const int INF_NUM = std::numeric_limits<int>::max();
const int INF_NUM = 987654321;
const int MIN_NUM = 0;

int queryMin(int left, int right, int node, int start, int end) {
	if (left > end || right < start)	return INF_NUM;
	if (left <= start && end <= right)	return rangeMin[node];

	int mid = (start + end) / 2;
	int leftMin = queryMin(left, right, node * 2, start, mid);
	int rightMin = queryMin(left, right, node * 2 + 1, mid + 1, end);

	return MIN(leftMin, rightMin);
}

int queryMax(int left, int right, int node, int leftNode, int rightNode) {
	if (left > rightNode || right < leftNode)	return MIN_NUM;
	if (left <= leftNode && rightNode <= right)	return rangeMax[node];

	int mid = (leftNode + rightNode) / 2;

	int leftMax = queryMax(left, right, node * 2, leftNode, mid);
	int rightMax = queryMax(left, right, node * 2 + 1, mid + 1, rightNode);

	return MAX(leftMax, rightMax);
}

void input()
{
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	for (int i = 0; i < M; i++) {
		cin >> Left[i] >> Right[i];
	}
}

void sol()
{
	input();

	initMin(0, N - 1, 1);
	initMax(0, N - 1, 1);

	for (int i = 0; i < M; i++) {
		int raggeMin_num = queryMin(Left[i] - 1, Right[i] - 1, 1, 0, N - 1);
		int raggeMax_num = queryMax(Left[i] - 1, Right[i] - 1, 1, 0, N - 1);

		cout << raggeMin_num << " " << raggeMax_num << endl;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL); 	cout.tie(NULL);

	freopen("2357_input.txt", "r", stdin);
	
	sol();

	return 0;
}