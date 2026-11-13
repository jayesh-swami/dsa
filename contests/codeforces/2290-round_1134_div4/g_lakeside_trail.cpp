#include <iostream>
#include <queue>
#include <cstdlib>
#include <algorithm>
#include <vector>

using std::cout;
using std::cin;
using std::priority_queue;
using std::abs;
using std::min;
using std::vector;
using std::max;
using std::ios;

bool isSteepnessPossible(const vector<long long>& h, long long k, long long steep) {
	vector<long long> hn(h.begin(), h.end());
	long long soilNeeded = 0;
	int n = h.size();
	
	int hIdx = -1;
	long long maxH = 0;

	for(int i = 0; i < (int) h.size(); i++) {
		if(h[i] > maxH) {
			maxH = h[i];
			hIdx = i;
		}
	}

	long long lH = maxH;
	long long rH = maxH;

	int lIdx = hIdx;
	int rIdx = hIdx;
	
	for(int i = 0; i < n; i++) {
		lH -= steep;

		long long lSoilNeeded = max(0LL, lH - hn[lIdx]);
		
		hn[lIdx] += lSoilNeeded;

		lH = max(lH, hn[lIdx]);

		soilNeeded += lSoilNeeded;

		lIdx = (lIdx + 1) % n;
	}

	for(int i = 0; i < (int) h.size(); i++) {
		rH -= steep;

		long long rSoilNeeded = max(0LL,rH - hn[rIdx]);
		
		hn[rIdx] += rSoilNeeded;

		rH = max(rH, hn[rIdx]);

		soilNeeded += rSoilNeeded;

		rIdx = (rIdx + n - 1) % n;
	}

	return soilNeeded <= k;
}


long long findMinSteepness(const vector<long long>& h, long long k) {
	int n = h.size();
	long long steepness = 0;

	for(int i = 0; i < n; i++) {
		int curr = i;
		int next = (i + 1) % n;

		steepness = max(steepness, abs(h[curr] - h[next]));
	}

	long long l = 0, r = steepness;

	while (l <= r) {
		long long mid = l + (r - l) / 2;

		if(isSteepnessPossible(h, k, mid)) {
			steepness = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}

	return steepness;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int t;
	cin >> t;

	for(int i = 0; i < t; i++) {
		long long n, k;

		cin >> n;
		cin >> k;

		vector<long long> v;
		v.reserve(n);
		
		for(long long j = 0; j < n; j++) {
			int x; cin >> x;
			v.push_back(x);
		}
		
		cout << findMinSteepness(v, k) << '\n';
	}

	return 0;
}


