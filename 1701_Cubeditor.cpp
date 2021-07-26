#include <iostream>
#include <cstring>

using namespace std;

char arr[5001];
int ans = 0;
int len = 0;
int pi[5001] = { 0 };

void getPartialMatch(const char* N)
{
	int n = strlen(N);
	int begin = 1, matched = 0;
	
	for (int i = 0; i < n; i++)	pi[i] = 0;

	while (begin + matched < n) {
		if (N[begin + matched] == N[matched]) {
			matched++;
			pi[begin + matched -1] = matched;
			if (ans < pi[begin + matched - 1]) ans = pi[begin + matched - 1];
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

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(); cout.tie();

	cin >> arr;
	for (int i = 0; i < strlen(arr); i++) {
		char tmp[5001];
		int idx = 0;
		for (int i = 0; i < strlen(arr); i++) tmp[i] = 0;
		for (int j = i; j < strlen(arr); j++) {
			tmp[idx++] = arr[j];
		}
		getPartialMatch(tmp);
	}
	
	cout << ans << endl;

	
	return 0;
}