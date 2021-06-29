#include <iostream>

using namespace std;
const int al_num = 27;
int cnt = 0;
bool findFlag = false;
int K;
char arr[410];

struct TRIE
{
	bool finish;
	TRIE* node[al_num];

	TRIE() : finish(false) {
		for (int i = 0; i < al_num; i++) {
			node[i] = 0;
		}
	}

	void insert(char* s)
	{
		//if (s == s+end)	return;
		if (*s == 0) {
			finish = true;
			return;
		}

		int cur = *s -'a';
		if (node[cur] == 0) {
			node[cur] = new TRIE();
		}

		node[cur]->insert(s + 1);
	}

	void IsSorting(TRIE* n, char str[], int idx, int target)
	{
		if (n == 0)	return;
		if (n->finish == true) {
			cnt++;
			if (cnt == target) {
				cout << str << endl;
				findFlag = true;
				return;
			}
		}

		for (int i = 0; i < al_num; i++) {
			if (n->node[i]) {
				char c = i + 'a';
				str[idx] = c;
				n->IsSorting(n->node[i], str, idx+1, target);
				str[idx] = 0;
			}
		}
	}
};

void del(TRIE* n)
{
	if (n == 0)	return;
	for (int i = 0; i < al_num; i++) {
		if (n->node[i]) {
			del(n->node[i]);
		}
	}
	delete n;
}

int main()
{
	int test_case = 1;

	freopen("swea_1257_input.txt", "r", stdin);
	cin >> test_case;

	for (int i = 1; i <= test_case; i++) {
		for (int i = 0; i < 410; i++) {
			arr[i] = 0;
		}
		cin >> K >> arr;
		TRIE* node = new TRIE();
		for (int len = 1; len < strlen(arr); len++) {
			for (int pos = 0; pos + len <= strlen(arr); pos++) {
				char tmp[410] = { NULL};
				int idx = 0;
				for (int c = pos; c < pos + len; c++) {
					tmp[idx++] = arr[c];
				}
				node->insert(tmp);
			}
		}
		node->insert(arr);

		cout << "#" << i << " ";
		char str[410];
		for (int j = 0; j < al_num; j++) {
			if (node->node[j]) {
				str[0] = j + 'a';
				node->IsSorting(node->node[j], str, 1, K);
			}
		}
		if (findFlag == false) cout << "none" << endl;
		del(node);
		cnt = 0; findFlag = false;
	}
	return 0;
}