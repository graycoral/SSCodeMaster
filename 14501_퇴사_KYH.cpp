#include <iostream>
#include <iomanip>

using namespace std;

#define MAX(a,b) (a > b ? a : b) 

typedef struct Counsel {
	int time;
	int cost;
} Counsel;

const int max_num = 20;
Counsel counsel[max_num];
int visited[max_num];
int N, ans;

int dp[max_num];

void input()
{
	for (int i = 0; i < N; i++) {
		counsel[i].time = counsel[i].cost = 0;
	}

	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> counsel[i].time >> counsel[i].cost;
	}
	ans = 0;
}

int sol()
{
	int ans = 0;
	for (int i = 0; i < (1 << N); i++) {
		int tmpSum = 0;
		for (int j = 0; j < N; j++) {
			if ((i & (1 << j)))
			{
				int cost = counsel[j].cost;
				j += (counsel[j].time - 1);
				
				if (j < N) {
					tmpSum += cost;
					cout << setw(3) << counsel[j].cost;
				}
			}
		}
		ans = MAX(ans, tmpSum);
		cout << endl;
	}

	return ans;
}


void DFS(int idx, int sum)
{
	if (idx > N) {
		return;
	}

	ans = MAX(ans, sum);

	for (int i = idx; i < N; i++) {
		DFS(i + counsel[i].time, sum + counsel[i].cost);
	}
}

void dp_sol()
{

}

int main()
{
	int test_case = 1;

	freopen("14501_input.txt", "r", stdin);
	cin >> test_case;

	for (int i = 1; i <= test_case; i++) {
		input();
		/*DFS(0, 0);
		cout << ans << endl;*/
		cout << sol() << endl;
	}
	return 0;
}