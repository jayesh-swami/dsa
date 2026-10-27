#include <algorithm>
#include <climits>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <utility>

using std::vector;
using std::string;
using std::cout;
using std::swap;

int removeDuplicates(vector<int>& nums) {
	int l = 0, r = 1;

	if(nums.size() == 0) return 0;

	while(r < nums.size()) {
		if(nums[l] != nums[r]) {
			l++;
			swap(nums[l], nums[r]);
		}
		r++;
	}

	return l + 1;
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

// runs removeDuplicates on a copy and returns the first k elements,
// so a wrong k and a wrong prefix both show up as a mismatch
vector<int> deduped(vector<int> nums) {
	int k = removeDuplicates(nums);
	if (k < 0 || k > (int) nums.size()) return {INT_MIN, k};   // k out of range: force a failure that shows k
	return vector<int>(nums.begin(), nums.begin() + k);
}

// random sorted arrays with values in a small range so runs of duplicates are common,
// std::unique used as the reference
void randomCrossCheck() {
	std::mt19937 rng(1);
	std::uniform_int_distribution<int> lenDist(0, 20);
	std::uniform_int_distribution<int> valDist(-5, 5);

	int mismatches = 0;
	for(int t = 0; t < 5000; t++) {
		vector<int> nums(lenDist(rng));
		for(int& x : nums) x = valDist(rng);
		std::sort(nums.begin(), nums.end());

		vector<int> expected = nums;
		expected.erase(std::unique(expected.begin(), expected.end()), expected.end());

		if(deduped(nums) != expected) mismatches++;
	}

	if (mismatches == 0) {
		cout << "PASS  random cross-check (5000 arrays)\n";
	} else {
		cout << "FAIL  random cross-check  (" << mismatches << " mismatches)\n";
		failures++;
	}
}

void runTests() {
	check("empty",                  deduped({}),                                {});
	check("single element",         deduped({7}),                               {7});
	check("two equal",              deduped({1, 1}),                            {1});
	check("two different",          deduped({1, 2}),                            {1, 2});
	check("all the same",           deduped({3, 3, 3, 3, 3}),                   {3});
	check("all unique",             deduped({1, 2, 3, 4, 5}),                   {1, 2, 3, 4, 5});
	check("leetcode example 1",     deduped({1, 1, 2}),                         {1, 2});
	check("leetcode example 2",     deduped({0, 0, 1, 1, 1, 2, 2, 3, 3, 4}),    {0, 1, 2, 3, 4});
	check("duplicates at start",    deduped({1, 1, 1, 2, 3}),                   {1, 2, 3});
	check("duplicates at end",      deduped({1, 2, 3, 3, 3}),                   {1, 2, 3});
	check("runs of mixed lengths",  deduped({1, 1, 1, 2, 2, 3, 3, 4, 4, 4}),    {1, 2, 3, 4});
	check("negatives",              deduped({-3, -3, -1, 0, 0, 2}),             {-3, -1, 0, 2});
	check("INT_MIN and INT_MAX",    deduped({INT_MIN, INT_MIN, 0, INT_MAX, INT_MAX}), {INT_MIN, 0, INT_MAX});
	randomCrossCheck();
}

int main() {
	runTests();

	cout << '\n' << (failures == 0 ? "All tests passed" : "Some tests failed") << '\n';
	return failures == 0 ? 0 : 1;
}
