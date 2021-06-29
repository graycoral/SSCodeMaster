#include <iostream>
using namespace std;

#define MIN(a,b) (a > b ? b: a)

const int INF = 987654321;
const int max_num = 51;
const int dr[] = { -1, 1, 0, 0 };
const int dc[] = { 0, 0, -1, 1 };
int ans = INF;
int arr[max_num][max_num];
int dp[max_num][max_num][4];
int visited[max_num][max_num];
int N;

bool vaildRange(int r, int c) {
	if (r< 0 || c < 0 || r > N-1 || c > N - 1)	return 0;
	if (arr[r][c] == 0 || visited[r][c] == 1)	return 0;
	
	return 1;
}

void DFS(int r, int c, int dir, int cnt)
{
	if (!vaildRange(r, c))	return;
	if (dp[r][c][dir] < cnt || ans  < cnt)	return;
	if (r == N - 1 && c == N - 1 && cnt != 1 && ((arr[r][c] == 1 && dir == 3) || (arr[r][c] == 6 && dir == 1))) {
		ans = MIN(ans, cnt);
		return;
	}

	dp[r][c][dir] = cnt;
	visited[r][c] = 1;

	if (arr[r][c] == 1 || arr[r][c] == 2) {
		int nr = r + dr[dir]; int nc = c + dc[dir];
		DFS(nr, nc, dir, cnt + 1);
	}
	else if (arr[r][c] >= 3 && arr[r][c] <= 6)
	{
		if (dir == 0 || dir == 1) {
			DFS(r, c + 1, 3, cnt + 1);
			DFS(r, c - 1, 2, cnt + 1);
		}
		else if (dir == 2 || dir == 3) {
			DFS(r + 1, c, 1, cnt + 1);
			DFS(r - 1, c, 0, cnt + 1);
		}
	}
	visited[r][c] = 0;
}

void init()
{
	ans = INF;
	for (int i = 0; i < max_num; i++) {
		for (int j = 0; j < max_num; j++) {
			visited[i][j] = 0;
			for (int d = 0; d < 4; d++) {
				dp[i][j][d] = INF;
			}
		}
	}
}

void input()
{
	ans = INF;
	for (int i = 0; i < max_num; i++) {
		for (int j = 0; j < max_num; j++) {
			arr[i][j] = 0; visited[i][j] = 0;
			for (int d = 0; d < 4; d++) {
				dp[i][j][d] = INF;
			}
		}
	}

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
		}
	}
}

int main()
{
	int test_case = 1;
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	//freopen("swea_4340_input.txt", "r", stdin);
	cin >> test_case;
	for (int i = 1; i <= test_case; i++) {
		input();
		DFS(0, 0, 3, 1);
		int a = ans;
		init();
		DFS(N - 1, N - 1, 2, 1);
		ans = MIN(a, ans);
		cout << "#" << i << " " << ans << endl;
	}
	return 0;
}