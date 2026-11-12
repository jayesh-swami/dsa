#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::cin;
using std::vector;
using std::max;
using std::min;

int main() {
	int t;
	cin >> t;

	for(int i = 0; i < t; i++) {
		int n, k;

		cin >> n;
		cin >> k;

		vector<long long> v;

		for(int j = 0; j < n; j++) {
			long long x;
			cin >> x;
			v.push_back(x);
		}

		long long moves = 0;
		long long toAdd = 0;

		for(int j = n - 1; j >= 0; j--) {
			if(j + k + 1 < n) toAdd -= v[j + k + 1];
			v[j] += toAdd;
			moves += v[j];

			toAdd += v[j];
		}

		if(moves % 2) cout << "Alice" << '\n';
		else cout << "Bob" << '\n';
	}

	return 0;
}
