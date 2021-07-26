#include <iostream>
#include <algorithm>

using namespace std;

int film[13][20];
int c_film[13][20];
int visited[20];
int D, W, K;
int ans = 987654321;

void input()
{
	for (int r = 0; r < D; r++) {
		for (int c = 0; c < W; c++) {
			c_film[r][c] = film[r][c] = 0;
			visited[c] = 0;
		}
	}
	ans = 987654321;
	cin >> D >> W >> K;

	for (int r = 0; r < D; r++) {
		for (int c = 0; c < W; c++) {
			cin >> film[r][c];
			c_film[r][c] = film[r][c];
		}
	}
}

bool checkFab(int arr[][20])
{
	for (int i = 0; i < W; i++) {
		int a_cnt = 0, b_cnt = 0;
		bool flag = false;

		for (int j = 0; j < D; j++) {
			if (arr[j][i] == 0) {
				b_cnt = 0;
				a_cnt++;
			}
			else {
				a_cnt = 0;
				b_cnt++;
			}

			if (a_cnt == K || b_cnt == K) {
				flag = true;
				break;
			}
		}
		if (flag == false) return false;
	}

	return true;
}

#define MIN(a,b) (a > b ? b :a)

void DFS(int idx, int cnt)
{
	if (cnt >= ans || cnt > K)	return;
	if (checkFab(c_film) == true) {
		ans = MIN(ans, cnt);
	}

	for (int i = idx; i < D; i++) {
		if (visited[i] == 1) continue;
		visited[i] = 1;
		for (int j = 0; j < 2; j++) {
			for (int c = 0; c < W; c++) {
				c_film[i][c] = j;
			}

			DFS(i, cnt + 1);
			
			for (int c = 0; c < W; c++) {
				c_film[i][c] = film[i][c];
			}
		}
		visited[i] = 0;
	}
}

void sol()
{
	if (checkFab(film) == true || K == 1) {
		ans = 0;
		return;
	}
	DFS(0, 0);
}

int main()
{
	int test_case = 1;
	//freopen("swea_2112_input.txt", "r", stdin);
	cin >> test_case;

	for (int i = 1; i <= test_case; i++) {
		input();
		sol();
		cout << "#" << i << " " << ans << endl;
	}
	return 0;
}