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
	// This solution uses hashing
	int majorityElement(const vector<int>& nums) {
		unordered_map<int, int> numCount;

		for(int i: nums) {
			numCount[i]++;
			if(numCount[i] > nums.size()/2)
				return i;
		}

		return INT_MAX;
	}

	// Linear time and O(1) space
	// Boyer-Moore Voting Algorithm ->
	//
	// The idea is that we consider each element as a candidate for majority
	// and we keep a count. If the element is same as candidate, then we increase the count
	// and if the element is different, we decrease the count. We consider a new candidate
	// when the count gets to zero. Doing this, only the majority element will survive the 
	// procedure by the end.
	//
	// The catch with this algorithm is that it assumes that a majority exists
	int majorityElementBoyerMoore(const vector<int>& nums) {
		int candidate = nums[0];
		int count = 0;

		for(int n: nums) {
			if(n == candidate) {
				count++;
			} else {
				count--;
			}

			if(count == 0) {
				candidate = n;
				count++;
			}
		}

		return candidate;
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

	check("single element", sol.majorityElement({1}), 1);
	check("single element", sol.majorityElementBoyerMoore({1}), 1);
	check("multiple elements", sol.majorityElement({1, 2, 1}), 1);
	check("multiple elements", sol.majorityElementBoyerMoore({1, 2, 1}), 1);
	check("same element only", sol.majorityElement({1, 1, 1}), 1);
	check("same element only", sol.majorityElementBoyerMoore({1, 1, 1}), 1);
	check("majority at beginning of the list", sol.majorityElement({1, 1, 1, 2, 2}), 1);
	check("majority at the beginning of the list", sol.majorityElementBoyerMoore({1, 1, 1, 2, 2}), 1);
	check("majority at the end of the list", sol.majorityElement({2, 2, 2, 1, 1, 1, 1}), 1);
	check("majority at the end of the list", sol.majorityElementBoyerMoore({2, 2, 2, 1, 1, 1,1}), 1);
}

int main() {
	cout << std::boolalpha;   // print true/false instead of 1/0

	runTests();

	cout << '\n' << (failures == 0 ? "All tests passed" : "Some tests failed") << '\n';
	return failures == 0 ? 0 : 1;
}

