#include <iostream>

using namespace std;

#define MIN(a, b) (a > b ? b:a)
#define SWAP(a, b) {int t = a; a = b; b=t;}
const int max_num = 16;
int N;
typedef struct Food {
	int protein;
	int fat;
	int carbon;
	int vitamin;
	int price;
} Food;

int min_price = 987654321;

Food food[max_num];
Food target;

void quickSort(int*input, int first, int last)
{
	int pivot;
	int i;
	int j;
	int temp;

	if (first < last)
	{
		pivot = first;
		i = first;
		j = last;

		while (i < j)
		{
			while (input[i] <= input[pivot] && i < last)
			{
				i++;
			}
			while (input[j] > input[pivot])
			{
				j--;
			}
			if (i < j)
			{
				temp = input[i];
				input[i] = input[j];
				input[j] = temp;
			}
		}

		temp = input[pivot];
		input[pivot] = input[j];
		input[j] = temp;

		quickSort(input, first, j - 1);
		quickSort(input, j + 1, last);
	}
}

void input()
{
	//freopen("19942_input.txt", "r", stdin);
	cin >> N;
	cin >> target.protein >> target.fat >> target.carbon >> target.vitamin;

	for (int i = 0; i < N; i++) {
		cin >> food[i].protein >> food[i].fat >> food[i].carbon >> food[i].vitamin >> food[i].price;
	}
}

void sol()
{
	int arr[max_num] = { 0 };
	int size = 0;

	for (int i = 0; i < (1 << N); i++) {
		int p = 0; int f = 0; int c = 0; int v = 0; int price = 0;
		int tmpArr[15] = { 0 }; int tmpsize = 0;

		for (int j = 0; j < N; j++) {
			if (i & (1 << j)) {
				p += food[j].protein;
				f += food[j].fat;
				c += food[j].carbon;
				v += food[j].vitamin;
				price += food[j].price;
				tmpArr[tmpsize++] = j;
			}
		}
		if (min_price > price && p >= target.protein && 
			f >= target.fat && c >= target.carbon &&
			v >= target.vitamin) {
			min_price = price;
			for (int i = 0; i < size; i++) {
				arr[i] = 0;
			}
			for (int i = 0; i < tmpsize; i++) {
				arr[i] = tmpArr[i] + 1;
			}
			size = tmpsize;
		}
		else if (min_price == price && p >= target.protein &&
			f >= target.fat && c >= target.carbon &&
			v >= target.vitamin) {
			bool changeFlag = false;
			for (int i = 0; i < tmpsize; i++) {
				if (arr[i] > tmpArr[i]) {
					changeFlag = true;
					break;
				}
			}
			if (changeFlag == true) {
				for (int i = 0; i < tmpsize; i++) {
					arr[i] = tmpArr[i] + 1;
				}
				size = tmpsize;
			}
		}
	}

	if (size == 0) {
		cout << -1 << endl;
	}
	else {
		cout << min_price << endl;
		quickSort(arr, 0, size - 1);
		for (int i = 0; i < size; i++) cout << arr[i] << " ";
		cout << endl;
	}
	
}

int main()
{
	input();
	sol();
	return 0;
}