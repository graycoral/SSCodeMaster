#include <iostream>

using namespace std;
const int NUM = 10;

typedef struct CallNum {
	bool finish;
	CallNum* node[10];

	CallNum() : finish(false) {
		for (int i = 0; i < 10; i++) {
			node[i] = 0;
		}
	}
} CallNum;

bool check = true;

void input(CallNum* node, const char* N)
{
	if (*N == 0) {
		node->finish = true;
		return;
	}

	int cur = *N - '0';
	if (node->node[cur] == 0) {
		node->node[cur] = new CallNum();
	}
	input(node->node[cur], N + 1);
}

bool find(CallNum* node, const char* N)
{
	if (*N == 0) {
		return true;
	}

	if (node->finish) {
		return false;
	}
	
	int cur = *N - '0';
	return find(node->node[cur], N + 1);
}

void sol()
{
	int N;
	char strs[10000][11];
	cin >> N;
	check = false;
	CallNum* callNum = new CallNum();

	for (int i = 0; i < N; i++) {
		cin >> strs[i];
		input(callNum, strs[i]);
	}

	for (int i = 0; i < N; i++) {
		check = find(callNum, strs[i]);
		if (check == false) break;
	}
}

int main()
{
	int test_case = 1;
	//freopen("5052_input.txt", "r", stdin);
	cin >> test_case;
	for (int i = 0; i < test_case; i++) {
		sol();
		if (check == true) {
			cout << "YES" << endl;
		}
		else {
			cout << "NO" << endl;
		}
	}
	return 0;
}