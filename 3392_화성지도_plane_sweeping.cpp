#include <iostream>

using namespace std;
#define MAX(a, b) (a > b ? a : b)
#define SWAP(a, b) {int t = a; a = b;  b= t;}


typedef struct rect {
	int r1, c1;
	int r2, c2;
}rect;

const int max_num = 1e4 + 10;

rect rec[max_num];
int N;
int ans = 0;
int max_c = 0;

typedef struct evt {
	int c;
	int delta;
	int idx;
} evt;

evt et[max_num];

#define SWAP_ET(a,b) { evt t = a; a =b ;  b=t; }

void qsort(int* arr, int start, int end)
{
	if (start >= end)	return;
	
	int pivot = start;
	int i = start; int j = end;
	while (i < j) {
		while (arr[i] <= arr[pivot]) {
			++i;
		}
		while (arr[j] > arr[pivot]) {
			--j;
		}
		if (i > j)	break;
		SWAP(arr[i], arr[j]);
		qsort(arr, start, j - 1);
		qsort(arr, j +1, end);
	}
	SWAP(arr[j], arr[pivot]);
}

void sort_evt(evt* arr, int start, int end)
{
	if (start >= end)	return;

	int pivot = start;
	int i = start; int j = end;
	while (i < j) {
		while (arr[i].c <= arr[pivot].c) {
			++i;
		}
		while (arr[j].c > arr[pivot].c) {
			--j;
		}
		if (i > j)	break;
		SWAP_ET(arr[i], arr[j]);
		sort_evt(arr, start, j - 1);
		sort_evt(arr, j + 1, end);
	}
	SWAP_ET(arr[j], arr[pivot]);
}

int erase(int* arr, int size)
{
	int s = size;
	for (int i = 0; i < s; i++) {
		int idx = i + 1;
		int cnt = 1;
		while (arr[i] != arr[idx]) {
			++idx;
		}
		while (arr[idx + cnt] == arr[idx]) {
			++cnt;
		}

		int tmpIdx = idx;
		for (int j = idx + cnt; j < s; j++) {
			if (j > s - cnt)	arr[j] = 0;
			else arr[tmpIdx++] = arr[j];
		}
		size -= cnt;
	}

	return size;
}

int sol()
{
	int r_list[max_num] = { 0 };
	int r_list_idx = 0;
	int evt_idx = 0;
	ans = 0;

	for (int i = 0; i < max_c; i++) r_list[i] = 0;
	for (int i = 0; i < N; i++) {
		r_list[r_list_idx++] = rec[i].r1;
		r_list[r_list_idx++] = rec[i].r2;
		et[evt_idx].c = rec[i].c1; et[evt_idx].delta = 1; et[evt_idx++].idx = i;
		et[evt_idx].c = rec[i].c2; et[evt_idx].delta = -1; et[evt_idx++].idx = i;
	}

	qsort(r_list, 0, r_list_idx - 1);
	int r_list_idx = erase(r_list, r_list_idx);
	sort_evt(et, 0, evt_idx - 1);
	
	int count[max_num] = { 0 };
	for (int i = 0; i < max_c; i++) count[i] = 0;

	for (int i = 0; i < N; i++) {
		int c = et[i].c; int delta = et[i].delta; int idx = et[i].idx;
		int r1 = rec[idx].r1;  int r2 = rec[idx].r2;

		for (int j = 0; j < r_list_idx; j++) {
			if (r1 <= r_list[j] && r_list[j] < r2) {
				count[j] += delta;
			}
		}
		int cutLength = 0;

		for (int j = 0; j < r_list_idx - 1; j++) {
			if (count[j] > 0) {
				cutLength += (r_list[j + 1] - r_list[j]);
			}
		}
		if (i + 1 < N)	ans += (cutLength * (et[i+1].c - c));
	}
	return ans;

}

void input()
{
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> rec[i].c1 >> rec[i].r1 >> rec[i].c2 >> rec[i].r2;
		max_c = MAX(max_c, rec[i].c1);
		max_c = MAX(max_c, rec[i].c2);
	}
}

int rangeLen[max_num];

void initLen(int left, int right, int node)
{
	if(left == right)	rangeLen[node] = a
}

int main()
{
	freopen("3392_input.txt", "r", stdin);
	input();
	cout << sol() << endl;
	return 0;
}