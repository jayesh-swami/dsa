#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using std::cout;
using std::move;
using std::pair;
using std::sort;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

class Solution {
public:
	int removeElement(vector<int>& nums, int val) {
        	int fptr = 0;

        	for(int i: nums) {
            		if(i != val) {
                		nums[fptr] = i;
                		fptr++;
            		}
        	}

		return fptr;
	}

};

// ---- test harness ----

int failures = 0;

template <typename T>
void show(const T& x) {
	cout << x;
}

void show(const string& s) {
	cout << '"' << s << '"';
}

template <typename T>
void show(const vector<T>& v) {
	cout << "[";
	for (size_t i = 0; i < v.size(); i++) {
		if (i) cout << ", ";
		show(v[i]);
	}
	cout << "]";
}

template <typename T>
void check(const string& name, const T& got, const std::type_identity_t<T>& expected) {
	if (got == expected) {
		cout << "PASS  " << name << '\n';
		return;
	}

	cout << "FAIL  " << name << "\n  expected: ";
	show(expected);
	cout << "\n  got:      ";
	show(got);
	cout << '\n';
	failures++;
}

void runTests() {
	Solution sol;
	
	vector<int> test = {1,1,2,2,3,4};
	check("basic", sol.removeElement(test, 1), 4);
	test = {1,1,2,2,3,4};
	check("no removals", sol.removeElement(test, 5), 6);
	test = {1,1,2,2,3,4};
	check("val at end", sol.removeElement(test, 4), 5);
	test = {1,1,2,2,3,4};
	check("val at mid", sol.removeElement(test, 2), 4);
	test = {7,1,2,2,3,7};
	check("val at extremes", sol.removeElement(test, 7), 4);
}

int main() {
	cout << std::boolalpha;   // print true/false instead of 1/0

	runTests();

	cout << '\n' << (failures == 0 ? "All tests passed" : "Some tests failed") << '\n';
	return failures == 0 ? 0 : 1;
}

