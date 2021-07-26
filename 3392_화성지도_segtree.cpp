#include <iostream>

using namespace std;

#define MAX(a, b) (a > b ? a : b)
#define SWAP(a, b) {int t = a; a = b;  b= t;}
#define SWAP_ET(a,b) { evt t = a; a =b ;  b=t; }

typedef struct rect {
	int r1, c1;
	int r2, c2;
}rect;

const int max_num = 1e4 + 10;
const int max_rec_num = 3e4 + 10;

rect rec[max_rec_num];
int N;
int ans = 0;
int max_c = 0;

typedef struct evt {
	int c;
	int delta;
	int idx;
} evt;

evt et[max_rec_num];
int r_list[max_rec_num] = { 0 };
int r_list_idx = 0;
int evt_idx = 0;

int segTree[max_rec_num * 4];

void qsort(int* arr, int start, int end)
{
	if (start >= end)	return;

	int pivot = start;
	int i = start; int j = end;
	while (i < j) {
		while (arr[i] <= arr[pivot] && i < end) {
			++i;
		}
		while (arr[j] > arr[pivot]) {
			--j;
		}
		if (i > j)	break;
		SWAP(arr[i], arr[j]);
	}
	SWAP(arr[j], arr[pivot]);
	qsort(arr, start, j - 1);
	qsort(arr, j + 1, end);
}

void sort_evt(evt* arr, int start, int end)
{
	if (start >= end)	return;

	int pivot = start;
	int i = start; int j = end;
	while (i < j) {
		while (arr[i].c <= arr[pivot].c && i < end) {
			++i;
		}
		while (arr[j].c > arr[pivot].c) {
			--j;
		}
		if (i > j)	break;
		SWAP_ET(arr[i], arr[j]);
	}
	SWAP_ET(arr[j], arr[pivot]);
	sort_evt(arr, start, j - 1);
	sort_evt(arr, j + 1, end);
}

int erase(int* arr, int size)
{
	int s = size;
	for (int i = 0; i < s; i++) {
		int cnt = 0;
		while (i + cnt < size && arr[i] == arr[i + cnt]) {
			cnt++;
		}
		if (cnt <= 1)	continue;

		for (int j = i + 1; j < size; j++) {
			if (j > size - cnt)	arr[j] = 0;
			arr[j] = arr[j + cnt - 1];
		}
		size -= (cnt - 1);
	}

	return size;
}

int sum(int left, int right, int node, int rectSum)
{
	if (left == right) {
		return segTree[node] = rectSum;
	}

	int addSum = 0;
	int mid = (left + right) / 2;

	int leftSum = sum(left, mid, node * 2, rectSum + addSum);
	int rightSum = sum(mid + 1, right, node * 2 + 1, rectSum + addSum);

	return segTree[node] = leftSum + rightSum;
}


int main()
{
	return 0;
}