#include <iostream>

using namespace std;
#define MAX(a,b) (a > b ? a : b) 

const int max_num = 111;
const int dr[] = { -1, 1, 0, 0 };
const int dc[] = { 0, 0 , -1, 1};
const int changeDic[6][4] = {
			{0,0,0,0},
			{1,3,0,2},
			{3,0,1,2},
			{2,0,3,1},
			{1,2,3,0},
			{1,0,3,2}};

int arr[max_num][max_num];
int N;
int whIdx = 0;
int ans = 0;

int StartR = 0;
int StartC = 0;

typedef struct pos
{
	int r, c, v;
} pos;

pos wh[max_num];

void input()
{
	for (int i = 0; i <= N +1; i++) {
		for (int j = 0; j <= N + 1; j++) {
			arr[i][j] = 0;
		}
	}

	for (int i = 0; i < whIdx; i++)	wh[i].r = wh[i].c = wh[i].v = 0;
	whIdx = ans = StartR = StartC = 0;
	cin >> N;

	for (int i = 0; i <= N+1; i++) {
		for (int j = 0; j <= N + 1; j++) {
			if (i == 0 || j == 0 || i > N || j > N) {
				arr[i][j] = 5;
			}
			else {
				cin >> arr[i][j];
				if (arr[i][j] >= 6 && arr[i][j] <= 10) {
					wh[whIdx].r = i; wh[whIdx].c = j; wh[whIdx].v = arr[i][j];
					whIdx++;
				}
			}
		}
	}
}

pos findWH(int r, int c, int v) {
	pos tmp{ r,c,v };
	for (int i = 0; i < whIdx; i++) {
		if (wh[i].v == v && (wh[i].r != r || wh[i].c != c)) {
			return wh[i];
		}
	}

	return tmp;
}

int sol(int startR, int startC, int startD)
{
	int curR = startR; int curC = startC;
	int curD = startD;
	int blockSum = 0;

	while (1) {
		curR += dr[curD]; curC += dc[curD];
		
		if (arr[curR][curC] == -1 || (curR == StartR && curC == StartC)) {
			return blockSum;
		}
		else if (arr[curR][curC] >= 6 && arr[curR][curC] <= 10) {
			pos idx = findWH(curR, curC, arr[curR][curC]);
			curR = idx.r; curC = idx.c;
		}
		else if (arr[curR][curC] >= 1 && arr[curR][curC] <= 5) {
			curD = changeDic[arr[curR][curC]][curD];
			blockSum++;
		}
	}

	return blockSum;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int test_case = 1;
	//freopen("swea_5650_input.txt", "r", stdin);
	cin >> test_case;
	for (int i = 1; i <= test_case; i++) {
		input();

		for (int r = 1; r <= N; r++) {
			for (int c = 1; c <= N; c++) {
				if (arr[r][c] != 0)	continue;
				StartR = r;  StartC = c;
				for (int d = 0; d < 4; d++) {
					int tmAns = sol(r, c, d);
					ans = MAX(ans, tmAns);
				}
			}
		}
		cout << "#" << i << " " << ans << endl;
	}
	return 0;
}