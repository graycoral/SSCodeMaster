#include <iostream>

using namespace std;

int in[4];
int out[4];
int sol;

#define MAX(a, b) (a > b ? a : b)
int main(void)
{
	int i;

	// �Է¹޴� �κ�
	for (i = 0; i < 4; i++)
	{
		cin >> out[i] >> in[i];
	}

	// ���⼭���� �ۼ�
	int inPeople = 0;
	for (int i = 0; i < 4; i++) {
		inPeople += (in[i] - out[i]);
		sol = MAX(sol, inPeople);
	}

	// ����ϴ� �κ�
	cout << sol << endl;

	return 0;
}