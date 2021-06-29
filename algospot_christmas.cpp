#include <iostream>

using namespace std;

const int MOD = 20091101;
const int max_num = 1e5 + 10;
int N, K;
int arr[max_num];
long long pSum[max_num];
long long dp[max_num];


int waytoBuy(const long long* sum, int k)
{
	int ret = 0;
	long long count[max_num];
	for (int i = 0; i < max_num; i++)	count[i] = 0;
	for (int i = 0; i < k; i++)	count[sum[i]]++;

	for (int i = 0; i < k; i++) {
		if (count[i] >= 2) {
			ret = (ret + (count[i] * (count[i] - 1) / 2)) % MOD;
		}
	} 

	return ret;
}

int maxBuys()
{

}

void add(int n, int size, long long value)
{
	while (n < size) {
		pSum[n] = value;
		n += (n & -n);
	}
}

long long sum(long long* tree, int i)
{
	long long retValue = 0;
	while (i > 0) {
		retValue += pSum[i];
		i -= (i & -i);
	}

	return retValue;
}


void input()
{
	cin >> N, K;

	for (int i = 0; i < N; i++) {
		cin >> arr[i];
		sum(pSum, i);
	}
}

int main()
{
	int test_case;
	freopen("algospot_christmas.txt", "r", stdin);
	cin >> test_case;

	for (int i = 1; i <= test_case; i++) {
		input();
		int wB = waytoBuy(pSum, K);
		int maxBuy = maxBuys();
		cout << wB << " " << maxBuy << endl;
	}

	return 0;
}