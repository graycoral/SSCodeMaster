#include <iostream>

using namespace std;
const int max_num = 27;
int N;

struct TRIE {
	bool finish;
	TRIE* node[max_num];

	TRIE() : finish(false) {
		for (int i = 0; i < max_num; i++)	node[i] = 0;
	}

	void insert(char* s) {
		if (*s == 0) {
			finish = true;
			return;
		}

		int cur = *s - 'a';
		if (node[cur] == 0) {
			node[cur] = new TRIE();
		}

		node[cur]->insert(s + 1);
	}

	int query(int buffer_size, char* buff, int idx) {
		int retCnt = 0;
		if (finish == true && buffer_size <= idx) {
			retCnt++;
		}

		if (buffer_size <= idx) {
			for (int i = 0; i < max_num; i++) {
				if (node[i]) {
					return retCnt += node[i]->query(buffer_size, buff, idx + 1);
				}
			}
		}
		else {
			int cur = *buff - 'a';
			if (node[cur]) {
				return retCnt += node[cur]->query(buffer_size, buff + 1, idx + 1);
			}
			else {
				return retCnt;
			}
		}

		return retCnt;
	}

	
};

void del(TRIE* n)
{
	if (n->finish)	return;

	for (int i = 0; i < max_num; i++) {
		if (n->node[i])	del(n->node[i]);
	}

	delete n;
}

int main()
{
	int test_case = 1;
	//freopen("swea_3135_input.txt", "r", stdin);
	cin >> test_case;

	for (int i = 1; i <= test_case; i++) {
		cin >> N;
		TRIE* tree = new TRIE();
		cout << "#" << i;
		for (int j = 0; j < N; j++) {
			int p; char tmp[20] = {0};
			cin >> p >> tmp;
			if (p == 1) {
				tree->insert(tmp);
			}
			else {
				int cnt = tree->query(strlen(tmp), tmp, 0);
				cout << " " << cnt;
			}
		}
		cout << endl;
		del(tree);
	}
	return 0;
}