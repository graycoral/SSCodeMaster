#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct RMQ {
	int n;					// length of array
	vector<int> rangeMin;
	
	RMQ(const vector<int>& array) {
		n = array.size();
		rangeMin.resize(n * 4);
		init(array, 0, n - 1, 1);
	}

	int init(const vector<int>& array, int left, int right, int node)
	{
		if (left == right) {
			return rangeMin[node] = array[left];
		}

		int mid = (left + right) / 2;
		int leftMin = init(array, left, mid, node * 2);
		int rightMin = init(array, mid + 1, right,  node * 2  + 1);

		return rangeMin[node] = min(leftMin, rightMin);
	}

	//const int INF_MAX = numeric_limits::<int>::max();
	const int INF_MAX = 9878654321;

	int query(int left, int right, int node, int leftnode, int rightnode)
	{
		// ��ġ�� �ʴ±���
		if (right < leftnode || rightnode < left)	return INF_MAX;
		// ������ ���c �� ���
		if (left <= leftnode && rightnode <= right) return rangeMin[node];
		// ���� ������ ������ Ǭ �� ����� ���Ѵ�.
		int mid = (leftnode + rightnode) / 2;

		return min(	query(left, right, node * 2,	leftnode, mid), \
					query(left, right, node * 2 + 1,mid+1, rightnode));

	}
};