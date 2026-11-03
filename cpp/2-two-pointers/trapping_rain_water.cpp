#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <random>
#include <string>

using std::vector;
using std::min;
using std::max;
using std::string;
using std::cout;

int trapPrefixArrays(const vector<int>& heights) {
	int n = heights.size();
	vector<int> maxGrid(n, INT_MAX);
	int trappedWater = 0;
	int maxUntilNow = 0;

	for(int i = 0; i < n; i++) {
		maxUntilNow = max(maxUntilNow, heights[i]);
		maxGrid[i] = min(maxUntilNow, maxGrid[i]);
	}
	maxUntilNow = 0;
	for(int i = n - 1; i >= 0; i--) {
		maxUntilNow = max(maxUntilNow, heights[i]);
		maxGrid[i] = min(maxUntilNow, maxGrid[i]);
		trappedWater += maxGrid[i] - heights[i];
	}
	return trappedWater;
}

int trapTwoPointers(const vector<int>& heights) {
	int n = heights.size();
	int trappedWater = 0;
	int l = 0, r = n - 1;
	int leftMax = 0, rightMax = 0;

	while(l <= r) {
		leftMax = max(heights[l], leftMax);
		rightMax = max(heights[r], rightMax);

		if(heights[l] < heights[r]) {
			trappedWater += min(leftMax, rightMax) - heights[l];
			l++;
		} else {
			trappedWater += min(leftMax, rightMax) - heights[r];
			r--;
		}
	}

	return trappedWater;
}

// ---- minimal test harness ----

// O(n^2) reference: water above i is min(tallest on the left, tallest on the right) - heights[i]
int trapNaive(const vector<int>& heights) {
	int n = heights.size();
	int trappedWater = 0;

	for(int i = 0; i < n; i++) {
		int leftMax = 0, rightMax = 0;
		for(int j = 0; j <= i; j++) leftMax = max(leftMax, heights[j]);
		for(int j = i; j < n; j++) rightMax = max(rightMax, heights[j]);
		trappedWater += min(leftMax, rightMax) - heights[i];
	}

	return trappedWater;
}

int failures = 0;

void check(const string& name, int got, int expected) {
	if (got == expected) {
		cout << "PASS  " << name << '\n';
	} else {
		cout << "FAIL  " << name << "  (expected " << expected << ", got " << got << ")\n";
		failures++;
	}
}

// runs the same case against both implementations
void checkAll(const string& name, const vector<int>& heights, int expected) {
	check(name + " [prefix arrays]", trapPrefixArrays(heights), expected);
	check(name + " [two pointers]",  trapTwoPointers(heights),  expected);
}

// random arrays, naive O(n^2) used as the reference
void randomCrossCheck() {
	std::mt19937 rng(1);
	std::uniform_int_distribution<int> lenDist(0, 20);
	std::uniform_int_distribution<int> valDist(0, 6); // small range so there are lots of equal heights

	int mismatches = 0;
	for(int t = 0; t < 5000; t++) {
		vector<int> heights(lenDist(rng));
		for(int& h : heights) h = valDist(rng);

		int expected = trapNaive(heights);
		if(trapPrefixArrays(heights) != expected || trapTwoPointers(heights) != expected) mismatches++;
	}

	if (mismatches == 0) {
		cout << "PASS  random cross-check (5000 arrays)\n";
	} else {
		cout << "FAIL  random cross-check  (" << mismatches << " mismatches)\n";
		failures++;
	}
}

void runTests() {
	checkAll("leetcode example 1",      {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}, 6);
	checkAll("leetcode example 2",      {4, 2, 0, 3, 2, 5},                   9);
	checkAll("empty",                   {},                                   0);
	checkAll("single bar",              {5},                                  0);
	checkAll("two bars",                {3, 1},                               0);
	checkAll("all zeros",               {0, 0, 0},                            0);
	checkAll("all equal",               {2, 2, 2, 2},                         0);
	checkAll("strictly increasing",     {1, 2, 3, 4, 5},                      0);
	checkAll("strictly decreasing",     {5, 4, 3, 2, 1},                      0);
	checkAll("equal walls",             {2, 1, 2},                            1);
	checkAll("unequal walls",           {5, 0, 3},                            3);
	checkAll("flat pool",               {2, 0, 0, 2},                         4);
	checkAll("valley",                  {3, 2, 1, 2, 3},                      4);
	checkAll("two pools, equal walls",  {3, 0, 3, 0, 3},                      6);
	checkAll("bump inside a pool",      {5, 1, 3, 1, 5},                      10);
	checkAll("tallest in the middle",   {0, 2, 0, 4, 0, 2, 0},                4);
	randomCrossCheck();
}

int main() {
	runTests();

	cout << '\n' << (failures == 0 ? "All tests passed" : "Some tests failed") << '\n';
	return failures == 0 ? 0 : 1;
}
