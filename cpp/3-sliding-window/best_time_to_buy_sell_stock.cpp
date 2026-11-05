#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using std::vector;
using std::max;
using std::min;

// [1, 2, 10]
int maxProfit(vector<int>& prices) {
	int maxProfit = 0;
	int minUntilNow = INT_MAX / 2;

	for(int p: prices) {
		maxProfit = max(maxProfit, p - minUntilNow);

		minUntilNow = min(minUntilNow, p);
	}

	return maxProfit;
}
