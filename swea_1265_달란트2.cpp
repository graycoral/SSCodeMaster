#include <iostream>

using namespace std;

long long N, C;
long long ans;

void sol()
{
	ans = 1;
	cin >> N >> C;
	long long num = N;
	long long cnt = C;
	long long tmp = 0;

	long long x = N / C;
	long long y = N % C;
	
	for (int i = 0; i < C - y; i++) {
		ans *= x;
	}
	x++;
	for (int i = 0; i < y; i++) {
		ans *= x;
	}
}

int main()
{
	int test_case = 1;
	//freopen("swea_1265_input.txt", "r", stdin);
	cin >> test_case;
	for (int i = 1; i <= test_case; i++) {
		sol();
		cout << "#" << i << " " << ans << endl;
	}
}