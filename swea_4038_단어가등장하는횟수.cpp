#include <iostream>
#include <cstring>

using namespace std;
const int max_num = 5e5 + 1;
long long pi[max_num];
char arr[max_num];
char N[max_num];

long long ans = 0;
void input()
{
	for (int i = 0; i < strlen(arr); i++) {
		N[i] = arr[i] = pi[i] = 0;
	}
	ans = 0;

	cin >> arr >> N;
}

void getPartialMatch()
{
	int m = strlen(N);
	int begin = 1; int matched = 0;

	for (int i = 0; i <m; i++) {
		pi[i] = 0;
	}

	while (begin + matched < m) {
		if (N[begin + matched] == N[matched]) {
			matched++;
			pi[begin + matched - 1] = matched;
		}
		else {
			if (matched == 0) begin++;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
}

void kmpSearch()
{
	int n = strlen(arr);
	int m = strlen(N);
	int begin = 0; int matched = 0;

	getPartialMatch();

	while (begin <= n - m) {
		if (matched < m && arr[begin + matched] == N[matched]) {
			matched++;
			if (matched == m)	ans++;
		}
		else {
			if (matched == 0) begin++;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
}

int main()
{
	int test_case = 1;
	//freopen("swea_4038_input.txt", "r", stdin);
	cin >> test_case;
	for (int i = 1; i <= test_case; i++) {
		input();
		kmpSearch();
		cout << "#" << i << " " << ans << endl;
	}
	return 0;
}