#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

using std::vector;
using std::unordered_set;
using std::cout;
using std::string;
using std::max;

int longestConsecutive(vector<int>& nums) {
	unordered_set<int> s;
	int res = 0;

	for(int& n: nums) s.insert(n);
	
	vector<int> candidates;
	for(const int& n: s) {
		if(!s.contains(n-1)) {
			candidates.push_back(n);
		}
	}

	for(int& n: candidates) {
		int i = n;
		while(s.contains(i)) i++;
		res = max(res, i - n);
	}

	return res;
}

int failures = 0;

void check(const string& name, vector<int> nums, int expected) {
	int got = longestConsecutive(nums);
	if (got == expected) {
		cout << "PASS  " << name << '\n';
	} else {
		cout << "FAIL  " << name << "  (expected " << expected << ", got " << got << ")\n";
		failures++;
	}
}

void runTests() {
	check("basic",                {100, 4, 200, 1, 3, 2},             4);
	check("longer",               {0, 3, 7, 2, 5, 8, 4, 6, 0, 1},     9);
	check("empty",                {},                                 0);
	check("single",               {5},                                1);
	check("duplicates",           {1, 2, 0, 1},                       3);
	check("all same",             {7, 7, 7, 7},                       1);
	check("negatives",            {-1, -2, -3, 5, 6},                 3);
	check("crosses zero",         {-2, -1, 0, 1, 2},                  5);
	check("no consecutive",       {10, 20, 30},                       1);
	check("two equal runs",       {1, 2, 3, 10, 11, 12},              3);
	check("large values",         {1000000000, -1000000000, 999999999}, 2);
}

int main() {
	runTests();

	cout << '\n' << (failures == 0 ? "All tests passed" : "Some tests failed") << '\n';
	return failures == 0 ? 0 : 1;
}
