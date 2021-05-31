#include <iostream>

using namespace std;

const int max_num = 51;
const int dr[] = {-1, 1, 0, 0};
const int dc[] = {0, 0, -1, 1};
int map[max_num][max_num];
int visted[max_num][max_num];
int N, M;
int startR , startC, L;
int ans =0;

typedef struct Pos {
    int r,c;
} Pos;

Pos q[max_num * max_num];
int front, last;

int direction[7][4] = {
    {0, 1, 2, 3},
    {0, 1, -1, -1},
    {-1, -1, 2, 3},
    {-1, 1, 2, -1},
    {0, -1, 2, -1},
    {0, -1, -1, 3},
    {-1, 1, -1, 3}
};

void input()
{
    for(int i = 0; i <= N ;i++) {
        for(int j = 0; j<= N; j++) {
            map[i][j] = visted[i][j] = 0;
        }
    }

    front = last = 0;
    cin >> N >> M >> startR >> startC >> L;

    for(int r = 0 ; r < N; r++) {
        for(int c= 0; c <M; c++) {
            cin >> map[r][c];
        }
    }
}

void push(int r, int c, int t)
{
    if(r >= N || c >= M || r <0 || c< 0)    return;
    if(visted[r][c])    return;
    if(map[r][c] == 0)  return;

    q[front].r = r;
    q[front++].c= c;
    visted[r][c] = t;
}

Pos pop()
{
    return q[last++];
}

int empty()
{
    return front == last ? 1 : 0;
}

void sol()
{
    int t = 0;
    push(startR, startC, t++);
    while(!empty() || t < L) {
        int timlFlag = 0;
        Pos cur = pop();

        if(map[cur.r][cur.r] == 1) {
            for(int i = 0; i < 4; i++) {
                int nr = cur.r+dr[i];
                int nc = cur.c+dc[i];
                if(direction[map[cur.r][cur.r]][i] == -1)   continue;
                push(nr, nc, t);
                timlFlag =1;
            }
            if(timlFlag) t++;
        }
        else if(map[cur.r][cur.r] == 2) {
           for(int i = 0; i < 2; i++) {
                int nr = cur.r+dr[i];
                int nc = cur.c+dc[i];
                if(direction[map[cur.r][cur.r]][i] == -1)   continue;
                push(nr, nc, t);
            }
            if(timlFlag) t++;
        }
        else if(map[cur.r][cur.r] == 3) {
            for(int i = 2; i < 4; i++) {
                int nr = cur.r+dr[i];
                int nc = cur.c+dc[i];
                if(direction[map[cur.r][cur.r]][i] == -1)   continue;
                push(nr, nc, t);
            }
            if(timlFlag) t++;
        }
        else if(map[cur.r][cur.r] == 4) {

            if(direction[map[cur.r][cur.r]][0]) {
                push(cur.r + dr[0], cur.c + dc[0], t);
                timlFlag =1;
            }

            if(direction[map[cur.r][cur.r]][3]){
                push(cur.r + dr[3], cur.c + dc[3], t);
                timlFlag =1;
            }
            if(timlFlag) t++;


        }
        else if(map[cur.r][cur.r] == 5) {
            if(direction[map[cur.r][cur.r]][1]) {
                push(cur.r + dr[1], cur.c + dc[1], t);
                timlFlag =1;
            }

            if(direction[map[cur.r][cur.r]][3]){
                push(cur.r + dr[3], cur.c + dc[3], t);
                timlFlag =1;
            }
            if(timlFlag) t++;
        }
        else if(map[cur.r][cur.r] == 6) {
           if(direction[map[cur.r][cur.r]][1]) {
                push(cur.r + dr[1], cur.c + dc[1], t);
                timlFlag =1;
            }

            if(direction[map[cur.r][cur.r]][2]){
                push(cur.r + dr[2], cur.c + dc[2], t);
                timlFlag =1;
            }
            if(timlFlag) t++;
        }
        else if(map[cur.r][cur.r] == 7) {
                     if(direction[map[cur.r][cur.r]][0]) {
                push(cur.r + dr[0], cur.c + dc[0], t);
                timlFlag =1;
            }

            if(direction[map[cur.r][cur.r]][2]){
                push(cur.r + dr[2], cur.c + dc[2], t);
                timlFlag =1;
            }
            if(timlFlag) t++;
        }
    }
    ans =t ;
}

int main()
{
    int test_case = 1;

    freopen("탈주범검거_input.txt", "r", stdin);
    cin >> test_case;
    for(int i = 1; i<=test_case; i++){
        input();
        sol();
        cout << "#" << i << " " << ans <<endl;
    }
    return 0;
}