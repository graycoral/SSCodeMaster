#include <iostream>
#include <iomanip>

using namespace std;

#define MIN(a, b) (a > b ? b : a)
const int max_num = 20;
int arr[max_num][max_num];

int N, W, H;
int ans = 987654321;

void show()
{
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cout << setw(2) << arr[i][j];
		}
		cout << endl;
	}
}

void input()
{
	cin >> N >> W >> H;

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cin >> arr[i][j];
		}
	}
	ans = 987654321;
}

int target(int c)
{
	for (int r = 0; r < H; r++) {
		if (arr[r][c])	return r;
	}
	 
	return 0;
}

bool vaildRange(int num, int size)
{
	if (num < 0 || num >= size)	return false;
	return true;
}

void arrange()
{
	int tmpArr[max_num][max_num];

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			tmpArr[i][j] = arr[i][j];
		}
	}

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			arr[i][j] = 0;
		}
	}

	for (int i = 0; i < W; i++) {
		int idx = H-1;
		for (int j = H-1; j >= 0; j--) {
			if (tmpArr[j][i]) {
				arr[idx--][i] = tmpArr[j][i];
			}
		}
	}
}

void removeNode(int r, int c)
{
	if (arr[r][c] == 0)		return;
	int len = arr[r][c];
	
	arr[r][c] = 0;
	for (int i = 1; i < len; i++) {
		if (vaildRange(r + i, H)) {
			removeNode(r + i, c);
		}
		if (vaildRange(r - i, H)) {
			removeNode(r - i, c);
		}
		if (vaildRange(c + i, W)) {
			removeNode(r, c + i);
		}
		if (vaildRange(c - i, W)) {
			removeNode(r, c - i);
		}
	}
}

void bomb(int cnt)
{
	int tmpArr[max_num][max_num];

	if (cnt == 0) {
		int tmpArrCnt = 0;
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				if (arr[i][j])	tmpArrCnt++;
			}
		}
		//show();
		ans = MIN(ans, tmpArrCnt);
		return;
	}

	for (int c = 0; c < W; c++) {
		// find target
		int r = target(c);

		// Copy
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				tmpArr[i][j] = arr[i][j];
			}
		}

		// remove nodes
		removeNode(r, c);
		arrange();
		bomb(cnt - 1);

		// revert 
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				arr[i][j] = tmpArr[i][j];
			}
		}
	}
}

int main()
{
	int test_case = 1;
	freopen("swea_5656_input.txt", "r", stdin);
	cin >> test_case;
	for (int i = 1; i <= test_case; i++) {
		input();
		bomb(N);
		cout << "#" << i << " " << ans << endl;
	}
	return 0;
}