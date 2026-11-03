#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>

using std::vector;
using std::max;
using std::min;
using std::string;
using std::cout;

long long maxAreaNaive(const vector<int>& heights) {
	long long maxArea = 0;
	int n = heights.size();

	for(int i = 0; i < n; i++) {
		for(int j = i + 1; j < n; j++) {
			long long h = min(heights[i], heights[j]);
			maxArea = max(h * (j - i), maxArea);
		}
	}

	return maxArea;
}

long long maxAreaTwoPointers(const vector<int>& heights) {
	int l = 0, r = (int) heights.size() - 1;
	long long maxArea = 0;

	while(l < r) {
		long long h = min(heights[l], heights[r]);
		maxArea = max(h * (r - l), maxArea);

		// Optional speedup for not checking any bars with height
		// smaller or equal than height with which we have already recorded 
		// max area until now since it will never give us an area greater 
		// than current as width is being reduced with every step
		while (l < r && heights[l] <= h) l++;
		while (l < r && heights[r] <= h) r--;
	}

	return maxArea;
}

// ---- minimal test harness ----

int failures = 0;

void check(const string& name, long long got, long long expected) {
	if (got == expected) {
		cout << "PASS  " << name << '\n';
	} else {
		cout << "FAIL  " << name << "  (expected " << expected << ", got " << got << ")\n";
		failures++;
	}
}

// runs the same case against both implementations
void checkAll(const string& name, vector<int> heights, long long expected) {
	check(name + " [naive]",        maxAreaNaive(heights),       expected);
	check(name + " [two pointers]", maxAreaTwoPointers(heights), expected);
}

// random arrays, naive O(n^2) used as the reference
void randomCrossCheck() {
	std::mt19937 rng(1);
	std::uniform_int_distribution<int> lenDist(0, 30);
	std::uniform_int_distribution<int> valDist(0, 10); // small range so there are lots of equal heights

	int mismatches = 0;
	for(int t = 0; t < 5000; t++) {
		vector<int> heights(lenDist(rng));
		for(int& h : heights) h = valDist(rng);

		if(maxAreaTwoPointers(heights) != maxAreaNaive(heights)) mismatches++;
	}

	if (mismatches == 0) {
		cout << "PASS  random cross-check (5000 arrays)\n";
	} else {
		cout << "FAIL  random cross-check  (" << mismatches << " mismatches)\n";
		failures++;
	}
}

void runTests() {
	checkAll("leetcode example 1",    {1, 8, 6, 2, 5, 4, 8, 3, 7},  49);
	checkAll("leetcode example 2",    {1, 1},                       1);
	checkAll("empty",                 {},                           0);
	checkAll("single line",           {5},                          0);
	checkAll("all zeros",             {0, 0, 0},                    0);
	checkAll("all equal",             {3, 3, 3, 3},                 9);
	checkAll("strictly increasing",   {1, 2, 3, 4, 5},              6);
	checkAll("strictly decreasing",   {5, 4, 3, 2, 1},              6);
	checkAll("tall ends",             {10, 1, 1, 1, 10},            40);
	checkAll("tall middle pair",      {1, 10, 10, 1},               10);
	checkAll("equal ends, taller inside", {4, 1, 9, 9, 1, 4},       20);
	checkAll("area above INT_MAX",    {2000000000, 1, 1, 2000000000}, 6000000000LL);
	randomCrossCheck();
}

int main() {
	runTests();

	cout << '\n' << (failures == 0 ? "All tests passed" : "Some tests failed") << '\n';
	return failures == 0 ? 0 : 1;
}
