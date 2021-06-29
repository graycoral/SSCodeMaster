#include <iostream>

using namespace std;

const int alphabat_num = 26;

char String0[] = "ZYX";
char String1[] = "BCG";
char String2[] = "ABC";
char String3[] = "BDE";
char String4[] = "ABCD";

struct TRIE
{
	bool finish;
	TRIE* Node[alphabat_num];

	TRIE()
	{
		finish = false;
		for (int i = 0; i < alphabat_num; i++) {
			Node[i] = NULL;
		}
	}

	void Insert(char* str)
	{
		if (*str == NULL) {
			finish = true;
			return;
		}

		int cur = *str - 'A';
		if (Node[cur] == NULL) {
			Node[cur] = new TRIE();
		}
		Node[cur]->Insert(str + 1);
	}

	bool Find(char* str)
	{
		if (*str == NULL) {
			if (finish == false) return false;
			else return true;
		}

		int cur = *str - 'A';
		if (Node[cur] == NULL)	return false;
		return Node[cur]->Find(str + 1);
	}

	void IsSorting(TRIE* N, char Str[], int idx)
	{
		if (N->finish == true)	cout << Str << endl;

		for (int i = 0; i < alphabat_num; i++) {
			if (N->Node[i] == NULL)	continue;
			char c = i + 'A';
			Str[idx] = c;
			N->IsSorting(N->Node[i], Str, idx + 1);
		}  
	}
};

int main()
{
	TRIE* Root = new TRIE();

	Root->Insert(String0);
	Root->Insert(String1);
	Root->Insert(String2);
	Root->Insert(String3);
	Root->Insert(String4);


	for (int i = 0; i < 26; i++)
	{
		if (Root->Node[i] != NULL)
		{
			char Str[5] = { NULL };
			Str[0] = i + 'A';
			Root->IsSorting(Root->Node[i], Str, 1);
		}
	}
	return 0;
}