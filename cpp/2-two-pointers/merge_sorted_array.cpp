#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include <utility>

using std::vector;
using std::string;
using std::cout;
using std::swap;

void mergeSortedArrays(vector<int>& nums1, int n, vector<int>& nums2, int m) {
        int p1 = n - 1, p2 = m - 1, curr = n + m - 1;

	while(p1 >= 0 && p2 >= 0) {
		if(nums1[p1] >= nums2[p2]) swap(nums1[p1--], nums1[curr]);
		else swap(nums2[p2--], nums1[curr]);
		curr--;
	}

	while(p2 >= 0) swap(nums1[curr--], nums2[p2--]);

	return;
}

// ---- minimal test harness ----

int failures = 0;

void print(const vector<int>& v) {
	cout << "[";
	for (size_t i = 0; i < v.size(); i++) cout << (i ? ", " : "") << v[i];
	cout << "]";
}

void check(const string& name, const vector<int>& got, const vector<int>& expected) {
	if (got == expected) {
		cout << "PASS  " << name << '\n';
	} else {
		cout << "FAIL  " << name << "\n  expected: ";
		print(expected);
		cout << "\n  got:      ";
		print(got);
		cout << '\n';
		failures++;
	}
}

// nums1 holds n real values followed by nums2.size() placeholder slots; merges in place and returns the result
vector<int> merged(vector<int> nums1, int n, vector<int> nums2) {
	mergeSortedArrays(nums1, n, nums2, nums2.size());
	return nums1;
}

// random sorted arrays with values in a small range (lots of duplicates and negatives),
// placeholder slots filled with garbage, std::merge used as the reference
void randomCrossCheck() {
	std::mt19937 rng(1);
	std::uniform_int_distribution<int> lenDist(0, 10);
	std::uniform_int_distribution<int> valDist(-5, 5);

	int mismatches = 0;
	for(int t = 0; t < 5000; t++) {
		int n = lenDist(rng), m = lenDist(rng);
		vector<int> a(n), b(m);
		for(int& x : a) x = valDist(rng);
		for(int& x : b) x = valDist(rng);
		std::sort(a.begin(), a.end());
		std::sort(b.begin(), b.end());

		vector<int> expected(n + m);
		std::merge(a.begin(), a.end(), b.begin(), b.end(), expected.begin());

		vector<int> nums1 = a;
		nums1.resize(n + m, 999);   // placeholders must not leak into the result
		if(merged(nums1, n, b) != expected) mismatches++;
	}

	if (mismatches == 0) {
		cout << "PASS  random cross-check (5000 pairs)\n";
	} else {
		cout << "FAIL  random cross-check  (" << mismatches << " mismatches)\n";
		failures++;
	}
}

void runTests() {
	check("nums2 empty",                merged({1, 2, 3}, 3, {}),                      {1, 2, 3});
	check("nums1 empty",                merged({0}, 0, {1}),                           {1});
	check("nums1 empty, several",       merged({0, 0, 0}, 0, {2, 5, 6}),               {2, 5, 6});
	check("both empty",                 merged({}, 0, {}),                             {});
	check("single each, nums2 smaller", merged({2, 0}, 1, {1}),                        {1, 2});
	check("single each, nums2 larger",  merged({1, 0}, 1, {2}),                        {1, 2});
	check("leetcode example",           merged({1, 2, 3, 0, 0, 0}, 3, {2, 5, 6}),      {1, 2, 2, 3, 5, 6});
	check("all nums2 smaller",          merged({4, 5, 6, 0, 0, 0}, 3, {1, 2, 3}),      {1, 2, 3, 4, 5, 6});
	check("all nums2 larger",           merged({1, 2, 3, 0, 0, 0}, 3, {4, 5, 6}),      {1, 2, 3, 4, 5, 6});
	check("interleaved",                merged({1, 3, 5, 0, 0, 0}, 3, {2, 4, 6}),      {1, 2, 3, 4, 5, 6});
	check("all equal",                  merged({2, 2, 0, 0}, 2, {2, 2}),               {2, 2, 2, 2});
	check("duplicates across arrays",   merged({1, 2, 2, 0, 0}, 3, {2, 3}),            {1, 2, 2, 2, 3});
	check("negatives, 0 placeholders",  merged({-3, -1, 0, 0}, 2, {-2, -2}),           {-3, -2, -2, -1});
	check("garbage placeholders",       merged({1, 4, 7, -9, 42}, 3, {2, 8}),          {1, 2, 4, 7, 8});
	check("nums2 longer than nums1",    merged({5, 0, 0, 0, 0}, 1, {1, 2, 6, 7}),      {1, 2, 5, 6, 7});
	randomCrossCheck();
}

int main() {
	runTests();

	cout << '\n' << (failures == 0 ? "All tests passed" : "Some tests failed") << '\n';
	return failures == 0 ? 0 : 1;
}
