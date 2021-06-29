#include <iostream>
#include <cstring>
using namespace std;

char arr[400 + 1];
int k;

typedef struct Node {
	bool check;
	struct Node* next[27];
}Node;
int T, K, cnt, flag;

char q[401 * 10];
int front, last;

void push(char d)
{
	q[front++] = d;
}

char pop()
{
	return q[last++];
}

Node* makeNode()
{
	Node* tmp = new(Node);
	for (int i= 0; i < 27; i++) {
		tmp->next[i] = 0;
	}
	tmp->check = false;

	return tmp;
}

void insert(Node* root, char* buff, int st, int ed)
{
	Node* tmpRoot = root;
	if (st == ed)	return;
	if (!tmpRoot->next[buff[st] - 'a']) {
		tmpRoot->next[buff[st] - 'a'] = makeNode();
	}
	insert(tmpRoot->next[buff[st] - 'a'], buff, st + 1, ed);
}

void find(Node* root)
{
	Node* tmpRoot = root;
	if (cnt == k) {
		flag = 1;
		cout << q << endl;
		return;
	}

	for (int i = 0; i < 27; i++) {
		if (tmpRoot->next[i]) {
			push(i + 'a');
			if (!tmpRoot->next[i]->check)	cnt++;
			find(tmpRoot->next[i]);
			if (flag)	return;
			pop();
		}
	}
}

void delNode(Node* root)
{
	Node* tmp = root;
	for (int i = 0; i < 27; i++) {
		if (tmp->next[i]) delNode(tmp->next[i]);
	}
	free(tmp);
}

int main()
{
	int test_case = 1;

	freopen("swea_1257_input.txt", "r", stdin);
	cin >> test_case;
	for (int i = 1; i <= test_case; i++) {
		cin >> k >> arr;
		Node* node = makeNode();

		for (int len = 1; len < strlen(arr); len++) {
			for (int pos = 0; pos < strlen(arr); pos++) {
				insert(node, arr, pos, pos + len);
			}
		}
		cout << "#" << i << " ";
		find(node);

		delNode(node);
		
	}
	return 0;
}