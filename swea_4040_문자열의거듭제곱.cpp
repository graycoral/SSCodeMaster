#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int max_num = 1000001;
int pi[max_num];
char arr[max_num];
int ans = 0;

void getPartailMatch(const char* N)
{
	int n = strlen(N);
	int begin = 1, matched = 0;

	for (int i = 0; i <= n; i++)	pi[i] = 0;	
	while (begin + matched < n) {
		if (N[begin + matched] == N[matched]) {
			matched++;
			pi[begin + matched - 1] = matched;
		}
		else {
			if (matched == 0)	begin++;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
}

void sol(const char* arr)
{
	getPartailMatch(arr);
	if (strlen(arr) / (strlen(arr) - pi[strlen(arr) - 1]) != 0) {
		ans = strlen(arr) / (strlen(arr) - pi[strlen(arr) - 1]);
	}
	else {
		ans = 1;
	}
}

int main()
{
	int test_case = 1;
	//freopen("swea_4040_input.txt", "r", stdin);
	cin >> test_case;

	for (int i = 1; i <= test_case; i++) {
		for (int j = 0; j < strlen(arr); j++) arr[j] = 0;
		cin >> arr;
		sol(arr);
		cout << "#" << i << " " << ans << endl;
	}
	return 0;
}