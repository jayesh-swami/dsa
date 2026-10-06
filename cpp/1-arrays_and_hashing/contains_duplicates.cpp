#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <climits>

using std::vector;
using std::cout;
using std::unordered_set;
using std::string;

bool hasDuplicate(const vector<int>& nums) {
	unordered_set<int> numSet;

	for(const int& i: nums) {
		if(numSet.contains(i)) {
			return true;
		}

		numSet.insert(i);
	}

	return false;
}

// ---- minimal test harness ----
 
int failures = 0;
 
void check(const string& name, bool got, bool expected) {
	if (got == expected) {
		cout << "PASS  " << name << '\n';
	} else {
		cout << "FAIL  " << name << "  (expected " << expected << ", got " << got << ")\n";
		failures++;
	}
}
 
void runTests() {
	check("empty",              hasDuplicate({}),                   false);
	check("single element",     hasDuplicate({7}),                  false);
	check("all distinct",       hasDuplicate({1, 2, 3, 4}),         false);
	check("adjacent duplicate", hasDuplicate({1, 1}),               true);
	check("duplicate far apart",hasDuplicate({1, 2, 3, 1}),         true);
	check("all same",           hasDuplicate({5, 5, 5, 5}),         true);
	check("negatives and zero", hasDuplicate({-1, 0, 1, -1}),       true);
	check("int extremes",       hasDuplicate({INT_MIN, INT_MAX}), false);
}
 
int main() {
	cout << std::boolalpha;   // print true/false instead of 1/0
 
	runTests();
 
	cout << '\n' << (failures == 0 ? "All tests passed" : "Some tests failed") << '\n';
	return failures == 0 ? 0 : 1;   // non-zero exit code signals failure
}

