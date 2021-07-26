#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

int N, M;
int u, v;
queue<int> q;
vector<int> node[50001];
bool check[50001];
int parent[50001];
int depth[50001];

int LCA(int u, int v)
{
	// v�� u���� �� ���� ���� ����
	if (depth[u] > depth[v]) swap(u, v);

	// �� ����� ���̰� ������������ v���� ���� �Ž��� �ö�
	while (depth[u] != depth[v]) v = parent[v];

	// �� ��尡 �������� ���� ���� �Ž��� �ö�
	while (u != v)
	{
		u = parent[u];
		v = parent[v];
	}
	return u; // LCA ����
}


int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;
	// �ش��忡 ����� ��� push
	for (int i = 0; i < N - 1; i++)
	{
		cin >> u >> v;
		node[u].push_back(v);
		node[v].push_back(u);
	}

	check[1] = true;
	q.push(1); // Ʈ���� ��Ʈ 

	while (!q.empty())
	{
		int x = q.front(); // �θ� ���
		q.pop();

		for (int i = 0; i < node[x].size(); i++)
		{
			if (!check[node[x][i]]) // �����带 �湮���� ���ٸ�
			{
				depth[node[x][i]] = depth[x] + 1; // ���� +1
				check[node[x][i]] = true; // �湮ǥ��
				parent[node[x][i]] = x; // �θ��� �Է�
				q.push(node[x][i]); // ť�� �߰�
			}
		}
	}

	cin >> M;

	for (int i = 0; i < M; i++)
	{
		cin >> u >> v;
		cout << LCA(u, v) << '\n';
	}

}