#include <iostream>

using namespace std;

const int max_num = 110 + 1;
const int wall = 8;
const int apple = 1;
const int snake = 2;
const int dr[] = {-1, 0, 1, 0};
const int dc[] = { 0, 1,  0, -1};
int map[max_num][max_num];

typedef struct Pos {
	int r, c;
} Pos;

typedef struct Dic {
	int time;
	char d;
} Dic;

Pos ap[max_num];
Pos sn [max_num];
Dic dic[max_num];

int front = 0;
int last = 0;
int N, K, L;
int sLen = 0;

void push(int r, int c)
{
	sn[last].r = r;
	sn[last++].c = c;
}

Pos pop()
{
	return sn[front++];
}

void input()
{
	for (int r = 0; r <= N+1; r++) {
		for (int c = 0; c <= N+1; c++) {
			map[r][c] = 0;
		}
	}

	for (int i = 0; i < max_num; i++) {
		sn[i].r = sn[i].c = 0;
		dic[i].d = dic[i].time = 0;
		ap[i].c = ap[i].r = 0;
	}
	front = last = 0;
	cin >> N >> K;

	// apple
	for (int i = 0; i < K; i++) {
		cin >> ap[i].r >> ap[i].c;
		map[ap[i].r][ap[i].c] = apple;
	}

	// wall
	for (int i = 0; i <= N; i++) {
		map[0][i] = map[i][0] = map[N + 1][i] = map[i][N + 1] = wall;
	}

	sLen = 0;

	cin >> L;
	
	for (int i = 0; i < L; i++) {
		cin >> dic[i].time >> dic[i].d;
	}
}


void sol()
{
	int curR = 1; int curC = 1;
	int curD = 1;
	int retTime = 0; int time = 1; int dicIdx = 0;
	
	map[curR][curC] = snake;
	time = dic[dicIdx].time;
	push(curR, curC);
	while (1) {
		int nr = curR + dr[curD]; int nc = curC + dc[curD];

		if (nr < 0 || nc < 0 || nr > N + 1 || nc > N + 1)	break;
		sLen++;
		if (map[nr][nc] == wall) break;
		if ((map[nr][nc] == snake)  && !(nr = sn[last].r && sn[last].c == nc))	break;
		
		if (map[nr][nc] != apple) {	
			Pos tail = pop();
			map[tail.r][tail.c] = 0;
		}

		map[nr][nc] = snake;
		push(nr, nc);

		if (time == sLen) {
			char nd = dic[dicIdx++].d;
			time = dic[dicIdx].time;
			
			if (nd == 'D') ++curD %= 4;
			else if (nd == 'L') curD = (curD+3) % 4;
		}

		curR = nr; curC = nc;
	}
}

int main()
{
	int test_case = 1;
	freopen("3130_input.txt", "r", stdin);
	cin >> test_case;

	for (int i = 1; i <= test_case; i++) {
		input();
		sol();
		cout << sLen << endl;
		// cout << "#" << " " << sLen << endl;
	}
	return 0;
}