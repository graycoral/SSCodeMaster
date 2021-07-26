#include <iostream>
#include <iomanip>

using namespace std;

const int max_num = 1001;
char map[max_num][max_num];
int v[max_num][max_num];
int dir[max_num][max_num];
int ans = 0;
int W, H;
int dr[] = {1, -1, 0, 0};
int dc[] = {0, 0, 1, -1};

void showV(int cnt)
{
	for (int i = 0; i < W; i++) {
		cout << "#";
	}
	cout << endl;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cout << setw(2) << v[i][j];
		}
		cout << endl;
	}
	for (int i = 0; i < W; i++) {
		cout << "#";
	}
	cout << endl<< cnt << endl;
}

void input()
{
	for (int i = 0; i < max_num; i++) {
		for (int j = 0; j < max_num; j++) {
			map[i][j] = '.';
			v[i][j] = 0; dir[i][j] = -1;
		}
	}
	v[0][0] = 1;
	ans = 0;
	cin >> W >> H;
	for (int i = 0; i < H; i++) {
		char tmp[100];
		cin >> tmp;
		for (int j = 0; j < W; j++) {
			if (tmp[j] != '.') {
				map[i][j] = tmp[j];
			}
		}
	}
}

const int ndc[] = {1, 1, -1, -1};
const int ndr[] = {1, -1, -1, 1};

int calDist(int r, int c, int tr, int tc, int len) {
	
	int retLen = 0;
	while ((r == tr && c == tc) && retLen < 3 ) {
		int fixR = r; int fixC = c;
		r += dr[dir[fixR][fixC]];
		c += dc[dir[fixR][fixC]];
		retLen++;
	}
	return retLen;
}

bool checkMap(int r, int c, int pr, int pc)
{
	if (c < 0 || r < 0 || r >= H || c >= W)	return false;
	for (int i = 0; i < 4; i++) {
		int nr = ndr[i] + r;
		int nc = ndc[i] + c;
		
		if (v[nr][nc] == 0)	continue;
		if (nr == pr && nc == pc) continue;
		if (calDist(nr, nc, r, c, 0) >= 3)	return false;
	}

	return true;
}

bool checkMap2(int r, int c, int pr, int pc)
{
	if (c < 0 || r < 0 || r >= H || c >= W)	return false;
	for (int i = 0; i < 4; i++) {
		int nr = dr[i] + r;
		int nc = dc[i] + c;

		if (nr == pr && nc == pc) continue;
		if (v[nr][nc] == 1)	return false;
	}

	return true;
}

#define MAX(a, b) (a > b ? a : b)
void DFS(int r, int c, int cnt)
{
	if (r == H - 1 && c == W - 1) {
		if (ans < cnt) {
			//showV(cnt);
			ans = cnt;
		}
		return;
	}
	
	v[r][c] = 1;

	for (int i = 0; i < 4; i++) {
		int nr = r + dr[i];
		int nc = c + dc[i];
		if (map[nr][nc] == 'X')	continue;
		if (v[nr][nc] == 1) continue;
		if (checkMap2(nr, nc, r, c) == false) continue;
		if (checkMap(nr, nc, r, c) == true) {
			dir[nr][nc] = i;
			DFS(nr, nc, cnt +1);
		}
	}
	v[r][c] = 0;
}

int main()
{
	int test_case = 1;
	freopen("swea_2021_0710_input.txt", "r", stdin);
	cin >> test_case;

	for (int i = 1; i <= test_case; i++) {
		input();
		DFS(0, 0, 1);
		cout << "#" << test_case << " " << ans << endl;
	}
	return 0;
}