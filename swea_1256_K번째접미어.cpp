#include <iostream>
#include <cstring>

using namespace std;

const int al_num = 27;
int N;
char arr[400];
int cnt = 0;
bool ansFlag = false;

typedef struct TRIE {
	bool finish;
	TRIE* Node[al_num];

	TRIE() : finish(false) {
		for (int i = 0; i < al_num; i++) {
			Node[i] = NULL;
		}
	}

	void Insert(char* s)
	{
		if (*s == NULL) {
			finish = true;
			return;
		}

		int cur = *s - 'a';
		if (Node[cur] == NULL) {
			Node[cur] = new TRIE();
		}
		Node[cur]->Insert(s + 1);
	}

	void isSorting(TRIE* N, char s[], int idx, int target)
	{
		if (N->finish == true) {
			cnt++;
			if (cnt == target) {
				//cout << "cnt : "<<cnt <<" ans : " << s << endl;
				cout << s << endl;
				ansFlag = true;
				return;
			}
			/*else {
				cout << "cnt : " << cnt << " " << s << endl;
			}*/
		}
		
		for (int i = 0; i < al_num; i++) {
			if (N->Node[i] == NULL)	continue;
			char c = i + 'a';
			s[idx] = c;
			N->isSorting(N->Node[i], s, idx + 1, target);
			s[idx] = 0;
		}
	}

}TRIE;

void deltrie(TRIE* root)
{
	TRIE* tmp = root;
	for (int i = 0; i < 27; i++)
		if (tmp->Node[i]) deltrie(tmp->Node[i]);
	
	delete tmp;
	tmp = 0;
}
void input()
{
	for (int i = 0; i < N; i++) arr[i] = 0;
	cin >> N;
	cin >> arr;
}

void sol()
{
	TRIE* node = new TRIE();

	for (int i = strlen(arr); i > 0; i--) {
		//cout << "Insert : " << arr + i -1 << endl;
		node->Insert(arr + i - 1);
	}

	cnt = 0; ansFlag = false;
	for (int i = 0; i < al_num; i++) {
		if (node->Node[i] == NULL)	continue;
		char s[401] = {};
		s[0] = i + 'a';
		node->isSorting(node->Node[i], s, 1, N);
	}

	if (ansFlag == false) {
		cout << "none" << endl;
	}

	deltrie(node);
}

int main()
{
	int test_case = 1;
	freopen("swea_1256_input.txt", "r", stdin);
	cin >> test_case;

	for (int i = 1; i <= test_case; i++) {
		input();
		cout << "#" << i << " ";
		sol();
		//cout << "==================================" << endl;
	}
	return 0;
}