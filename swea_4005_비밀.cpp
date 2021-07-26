#include <iostream>
#include <algorithm>

using namespace std;
const int max_num = 50;

typedef struct FR {
	int size;
	int friends[max_num];
} FR;

FR fr[11];
int N, K;
int ans;

int q[max_num];
int vistied[max_num];
int first, last;

void init()
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < fr[i].size; j++) {
			fr[i].friends[j] = 0;
		}
		fr[i].size = 0;
	}
	ans = 1;
}

void push(int id)
{
	q[last++] = id;
	vistied[id] = 1;
}

int pop()
{
	return q[first++];
}

void bfs(int start)
{
	int cnt = 1;
	first = last = 0;

	for (int i = 0; i < max_num; i++) vistied[i] = 0;
	push(start);

	while (first != last) {
		int cur = pop();
		for (int i = 0; i < fr[cur].size; i++) {
			if (vistied[fr[cur].friends[i]] == 0) {
				cnt++;
				push(fr[cur].friends[i]);
			}
		}
	}

	ans = max(ans, cnt);
}


void sol(int test_case)
{
	cin >> N >> K;
	for (int i = 0; i < K; i++) {
		int c, p, ch;
		cin >> c >> p;
		for (int j = 0; j < c -1; j++) {
			bool flag = true;
			cin >> ch;
			for (int k = 0; k < fr[p].size; k++) {
				if (fr[p].friends[k] == ch)  flag = false;
			}
			if (flag == true) {
				fr[p].friends[fr[p].size++] = ch;
			}
			p = ch;
			flag = true;
		}
	}
	cout << "#" << test_case;
	
	for (int i = 1; i <= N; i++) {
		cout << " " << fr[i].size;
		bfs(i);
	}
	cout<< " " << ans << endl;
}
	
int main()
{
	int test_case = 1;
	//freopen("swea_4005_input.txt", "r", stdin);
	cin >> test_case;

	for (int i = 1; i <= test_case; i++) {
		init();
		sol(i);
	}
	return 0;
}