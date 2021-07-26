#include <iostream>
#include <string>

using namespace std;

const int MAX_N = 1e4 + 1;
const string ack = "ACK";
const string disc = "DIS";

int parennt[MAX_N], ranking[MAX_N], enemy[MAX_N], Size[MAX_N];
int N, M;

int find(int x)
{
	if (parennt[x] == x)	return x;
	else return parennt[x] = find(parennt[x]);
}

bool same_parent(int x, int y)
{
	if (find(x) == find(y))	return true;
	else return false;
}

#define SWAP_INT(a, b) {int t= a; a =b; b= t;}
int Union(int x, int y)
{
	x = find(x); y = find(y);
	if (ranking[x] > ranking[y]) {
		SWAP_INT(x, y);
	}
	if (ranking[x] == ranking[y]) ranking[y]++;
	parennt[x] = y;
	Size[y] += Size[x];

	return y;
}

void sol()
{
	for (int i = 0; i <= N; i++) {
		parennt[i] = i;
		ranking[i] = 0;
		enemy[i] = -1; Size[i] = 1;
	}
}

bool Dis(int x, int y)
{
	x = find(x); y = find(y);
	if (x == y)	return false;

	int a = Union(x, enemy[y]), b = Union(y, enemy[x]);
	enemy[a] = b; enemy[b] = a;

	return true;
}

bool Ack(int x, int y)
{
	x = find(x); y = find(y);
	if (x == enemy[y])	return false;

	int a = Union(x, y), b = Union(enemy[x], enemy[y]);
	enemy[a] = b;

	return true;
}

#define MAX(a, b) (a > b ? a: b)
int maXParty()
{
	int ret = 0;
	for (int node = 0; node < N; node++) {
		if (parennt[node] == node) {
			int e = enemy[node];

			if (e > node)	continue;
			int mySize = Size[node];
			int enemySize = (e == -1 ? 0 : Size[e]);

			ret += MAX(mySize, enemySize);
		}
	}

	return ret;
}

int main()
{
	int test_case = 1;
	int retLine = -1;
	for (int i = 1; i <= test_case; i++) {
		for (int i = 0; i < N; i++) {
			parennt[i] = ranking[i] = enemy[i] = Size[i] = 0;
		}
		cin >> N >> M;
		bool makesense = true;
		for (int j = 0; j < M; j++) {
			string tmp; int u, v;
			cin >> tmp >> u >> v;
			if (makesense == false)	continue;

			if (tmp == ack) makesense = Ack(u, v);
			else makesense = Dis(u, v);

			if (makesense == false)	retLine = j + 1;
		}
		cout << maXParty() << endl;
	}
	return 0;
}