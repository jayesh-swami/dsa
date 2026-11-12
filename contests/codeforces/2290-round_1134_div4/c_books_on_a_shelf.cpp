#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

using std::vector;
using std::cout;
using std::ios;
using std::cin;
using std::sort;
using std::list;
using std::max;
using std::reverse;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;

	cin >> n;

	for(int i = 0; i < n; i++) {
		long long h;
		cin >> h;
		
		vector<long long> v;
		v.reserve(h);

		for(int j = 0; j < h; j++) {
			long long x;
			cin >> x;
			v.push_back(x);
		}

		sort(v.rbegin(), v.rend());

		list<long long> dll;

		for(int j = 0; j < h; j++) {
			if(j % 2 == 0) dll.push_front(v[j]);
			else dll.push_back(v[j]);
		}

		long long res = 0;
		
		long long maxUntilNow = 0;

		v = vector<long long>(dll.begin(), dll.end());

		for(int j = 0; j <= h / 2; j++) {
			if(v[j] > maxUntilNow) res++;
			maxUntilNow = max(v[j], maxUntilNow);
		}
		
		maxUntilNow = 0;

		for(int j = h - 1; j >= h/2 + h%2 ; j--) {
			if(v[j] > maxUntilNow) res++;
			maxUntilNow = max(v[j], maxUntilNow);
		}

		cout << res << '\n';

		for(long long el: v) cout << el << ' ';

		cout << '\n';
	}

	return 0;
}
