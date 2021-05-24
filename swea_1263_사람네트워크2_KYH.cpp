#include <iostream>

using namespace std;

const long long int INF = 0xfffe;
const int mam_num = 1000+1;

int map[mam_num][mam_num];
int N;

void input()
{
    cin >> N;

}

void dijkstra(int start)
{
    int dp[N+1];
    int visited[N+1];
    int min;
    int v;

    for(int i = 1; i <= N; i++) {
        min = INF;

        for(int j = 1; j<= N ;j++) {

        }
    }
}

void sol()
{
    for(int i=1; i<=)
}


int main()
{
    int test_case;
    freopen("swea_1263_input.txt", "r", stdin);

    for(int i = 1; i<=test_case; i++) {
        input();
        sol();
    }
    return 0;
}

