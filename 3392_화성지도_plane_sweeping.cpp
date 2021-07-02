#include <iostream>
#include <algorithm>

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
		while (i+cnt < size && arr[i] == arr[i + cnt]) {
			cnt++;
		}
		if (cnt <= 1)	continue;
		
		for (int j = i + 1; j < size; j++) {
			if (j > size - cnt)	arr[j] = 0;
			arr[j] = arr[j + cnt - 1];
		}
		size -= (cnt-1);
	}

	return size;
}

int sol()
{
	for (int i = 0; i < max_c; i++) r_list[i] = 0;
	for (int i = 0; i < N; i++) {
		r_list[r_list_idx++] = rec[i].r1;
		r_list[r_list_idx++] = rec[i].r2;
		et[evt_idx].c = rec[i].c1; et[evt_idx].delta = 1; et[evt_idx++].idx = i;
		et[evt_idx].c = rec[i].c2; et[evt_idx].delta = -1; et[evt_idx++].idx = i;
	}

	//qsort(r_list, 0, r_list_idx - 1);
	sort(r_list, r_list + r_list_idx - 1);
	r_list_idx = erase(r_list, r_list_idx);
	sort_evt(et, 0, evt_idx - 1);
	//sort(et, et + evt_idx - 1);
	
	int count[max_num] = { 0 };
	for (int i = 0; i < evt_idx; i++)	count[i] = 0;

	for (int i = 0; i < evt_idx; i++) {
		int c = et[i].c; int delta = et[i].delta; int idx = et[i].idx;
		int r1 = rec[idx].r1; int r2 = rec[idx].r2;

		for (int j = 0; j < r_list_idx; j++) {
			if (r1 <= r_list[j] && r_list[j] < r2) {
				count[j] += delta;
			}
		}
		
		int cutLength = 0;
		for (int j = 0; j < r_list_idx -1; j++) {
			if (count[j] > 0) {
				cutLength += (r_list[j + 1] - r_list[j]);
			}
		}

		if (i + 1 < evt_idx)	ans += cutLength * (et[i + 1].c - c);
	}

	return ans;
}

void input()
{
	cin >> N;

	for
		(int i = 0; i < N; i++) {
		cin >> rec[i].c1 >> rec[i].r1 >> rec[i].c2 >> rec[i].r2;
		max_c = MAX(max_c, rec[i].c1);
		max_c = MAX(max_c, rec[i].c2);
	}
}

int main()
{
	//freopen("3392_input.txt", "r", stdin);
	input();
	cout << sol() << endl;
	return 0;
}