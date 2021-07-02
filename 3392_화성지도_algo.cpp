#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N;

typedef struct rec {
	int x1, y1, x2, y2;
} rec;

vector<struct rec> rect;

int unionArea(const vector<rec>& rets) {
	if (rets.empty())	return 0;

	typedef pair<int, pair<int, int >> Events;
	vector<Events> events;
	vector<int> ys;

	for (int i = 0; i < rets.size(); i++) {
		ys.push_back(rets[i].y1);
		ys.push_back(rets[i].y2);
		events.push_back(Events(rets[i].x1, make_pair(1, i)));
		events.push_back(Events(rets[i].x2, make_pair(-1, i)));
	}

	sort(ys.begin(), ys.end());
	ys.erase(unique(ys.begin(), ys.end()), ys.end());
	sort(events.begin(), events.end());

	int ret = 0;

	vector<int> count(ys.size() - 1, 0);

	for (int i = 0; i < events.size(); i++) {
		int x = events[i].first, delta = events[i].second.first;
		int retangle = events[i].second.second;

		int y1 = rets[retangle].y1, y2 = rets[retangle].y2;
		for (int j = 0; j < ys.size(); j++) {
			if (y1 <= ys[j] && ys[j] < y2) {
				count[j] += delta;
			}
		}
		int cutLength = 0;
		for (int j = 0; j < ys.size() - 1; j++) {
			if (count[j] > 0) {
				cutLength += ys[j + 1] - ys[j];
			}
		}
		if (i + 1 < events.size()) {
			ret += cutLength * (events[i + 1].first - x);
		}
	}

	return ret;
}

void input()
{
	cin >> N;

	for
		(int i = 0; i < N; i++) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		rect.push_back({ x1, y1, x2, y2 });
	}
}

int main()
{
	//freopen("3392_input.txt", "r", stdin);
	input();
	cout << unionArea(rect) << endl;
	return 0;
}