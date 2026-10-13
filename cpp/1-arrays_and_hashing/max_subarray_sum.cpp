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
using std::max;

/**
 * Given an array of n numbers, our task is to calculate the maximum subarray 
 * sum, i.e., the largest possible sum of a sequence of consecutive values 
 * in the array
 */
class Solution {
public:
	// O(n^2) - Checks all subarrays starting from a point
	int maxSubarraySumNaive(vector<int>& nums) {
		int res = INT_MIN;
		for(int i = 0; i < nums.size(); i++) {
			int sum = 0;
			for(int j = i; j < nums.size(); j++) {
				sum += nums[j];
				res = max(res, sum);
			}
		}
		return res;
	}
	
	// Also called Kadane's algo
	int maxSubarraySum(const vector<int>& nums) {
		int maxSum = INT_MIN / 2;
		int sumEndingAtK = INT_MIN / 2;

		for(int i = 0; i < nums.size(); i++) {
			// Can also be simply written as sumEndingAtK = max(sumEndingAtK, nums[i])			
			if(nums[i] > sumEndingAtK + nums[i]) sumEndingAtK = nums[i];
			else sumEndingAtK += nums[i];

			maxSum = max(maxSum, sumEndingAtK);
		}

		return maxSum;
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

	check("1 positive element", sol.maxSubarraySum({0, 0, 0, 1}), 1);
	check("entire array as subarray", sol.maxSubarraySum({1, 0, 0, 1}), 2);
	check("Counting one negative element", sol.maxSubarraySum({0, 2, -1, 4}), 5);
	check("All negative elements", sol.maxSubarraySum({-3, -3, -3, -3}), -3);

}

int main() {
	cout << std::boolalpha;   // print true/false instead of 1/0

	runTests();

	cout << '\n' << (failures == 0 ? "All tests passed" : "Some tests failed") << '\n';
	return failures == 0 ? 0 : 1;
}

