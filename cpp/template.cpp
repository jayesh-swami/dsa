// Compile: g++ -std=c++20 -Wall -Wextra -g -fsanitize=address,undefined file.cpp -o file

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

	// Format: check("test name", sol.method(args), expected);
	// Examples:
	// check("basic", sol.twoSum({2, 7, 11, 15}, 9), {0, 1});
	// check("basic", sol.longestCommonPrefix({"flower", "flow"}), "fl");

}

int main() {
	cout << std::boolalpha;   // print true/false instead of 1/0

	runTests();

	cout << '\n' << (failures == 0 ? "All tests passed" : "Some tests failed") << '\n';
	return failures == 0 ? 0 : 1;
}
