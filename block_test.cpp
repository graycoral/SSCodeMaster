#include <iostream>
#include <iomanip>

using namespace std;

const int max_num = 20;
int arr[max_num][max_num];
int N, W, H;

void show(int t)
{
	cout << "============================ " << (t == 1 ? "LEFT" : "RIGHT") << endl;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cout << setw(2) << arr[i][j];
		}
		cout << endl;
	}

	cout << "============================ " << (t == 1 ? "LEFT" : "RIGHT") << endl << endl;
}

void roateLeft()
{
	int tmpArr[max_num][max_num] = { 0 };
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			tmpArr[i][j] = arr[i][j];
			arr[i][j] = 0;
		}
	}

	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			arr[i][j] = tmpArr[j][W - 1 - i];
		}
	}

	int tmp = W;
	W = H;
	W = tmp;

	show(1);
}

void roateRight()
{
	int tmpArr[max_num][max_num] = { 0 };
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			tmpArr[i][j] = arr[i][j];
			arr[i][j] = 0;
		}
	}

	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			arr[i][j] = tmpArr[H-1-j][i];
		}
	}

	int tmp = W;
	W = H;
	W = tmp;

	show(0);
}

void input()
{
	cin >> N >> W >> H;

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cin >> arr[i][j];
		}
	}
}
int main()
{
	int test_case = 1;
	freopen("swea_5656_input.txt", "r", stdin);
	cin >> test_case;
	test_case = 1;
	for (int i = 1; i <= test_case; i++) {
		input();
		roateLeft();
		roateRight();
		roateLeft();
		cout << "************************" << endl << endl;
	}
	return 0;
}