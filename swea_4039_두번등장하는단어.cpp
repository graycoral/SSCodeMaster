#include <iostream>
#include <algorithm>

using namespace std;

const int max_num = 2e5 + 1;

char H[max_num];
int pi[max_num];
char tmp[max_num] = { 0 };
int len;
int ans;

void input()
{
	for (int i = 0; i < len; i++) {
		H[i] = pi[i] = 0;
	}
	ans = 0, len = 0;

	cin >> len >> H;
}

void getPartialSearch(const char* N, int l)
{
	int n = l;
	int begin = 1, matched = 0;

	while (begin + matched < n) {
		if (N[begin + matched] == N[matched]) {
			matched++;
			pi[begin + matched - 1] = matched;
			//ans = max(ans, pi[begin + matched - 1]);

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

void getPrefixSuffix(const char* N, int len) 
{
	getPartialSearch(N, len);
	int k = len;
	while (k > 0) {
		ans = max(k, pi[len - 1]);
		k = pi[k - 1];
	}
}

int main()
{
	int test_case = 1;
	freopen("swea_4039_input.txt", "r", stdin);
	cin >> test_case;
	for (int i = 1; i <= test_case; i++) {
		input();
		int idx = 0;
		getPrefixSuffix(tmp, len);
		cout << "#" << i << " " << ans << endl;
	}
	return 0;
}