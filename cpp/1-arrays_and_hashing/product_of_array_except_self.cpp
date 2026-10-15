#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::cout;
using std::string;

/**
 * Prefix and suffix arrays to store product to left and right 
 * excluding itself.
 */
vector<int> productExceptSelf(vector<int>& nums) {
	vector<int> left(nums.size(), 1), right(nums.size(), 1);

	for(int i = 1; i < nums.size(); i++) {
		left[i] = left[i-1] * nums[i-1];
	}

	for(int i = nums.size() - 2; i >= 0; i--) {
		right[i] = right[i+1] * nums[i+1];
	}

	vector<int> res(nums.size());

	for(int i = 0; i < nums.size(); i++) {
		res[i] = left[i] * right[i];
	}

	return res;
} 

/**
 * Memory Optimized way to just do it in O(1) space where we just 
 * use the res array and pass it left to right and then right to
 * left over the array
 */
vector<int> productExceptSelfMemoryOptimized(vector<int>& nums) {
	vector<int> res(nums.size(), 1);

	for(int i = 1; i < nums.size(); i++) {
		res[i] = res[i-1] * nums[i-1];
	}

	int productUntilNow = 1;
 
	for(int i = nums.size() - 2; i >= 0; i--) {
		productUntilNow *= nums[i+1];
		res[i] *= productUntilNow;
	}

	return res;
}

// ---- minimal test harness ----

int failures = 0;

void printVec(const vector<int>& v) {
	cout << '[';
	for (int i = 0; i < (int)v.size(); i++) {
		if (i > 0) cout << ", ";
		cout << v[i];
	}
	cout << ']';
}

void check(const string& name, const vector<int>& got, const vector<int>& expected) {
	if (got == expected) {
		cout << "PASS  " << name << '\n';
	} else {
		cout << "FAIL  " << name << "  (expected ";
		printVec(expected);
		cout << ", got ";
		printVec(got);
		cout << ")\n";
		failures++;
	}
}

// runs the same case against both implementations
void checkBoth(const string& name, vector<int> nums, const vector<int>& expected) {
	check(name + " [prefix/suffix]", productExceptSelf(nums), expected);
	check(name + " [O(1) space]", productExceptSelfMemoryOptimized(nums), expected);
}

void runTests() {
	checkBoth("basic",                {1, 2, 3, 4},       {24, 12, 8, 6});
	checkBoth("two elements",         {3, 5},             {5, 3});
	checkBoth("single zero",          {-1, 1, 0, -3, 3},  {0, 0, 9, 0, 0});
	checkBoth("multiple zeros",       {0, 2, 0, 4},       {0, 0, 0, 0});
	checkBoth("zero at start",        {0, 1, 2, 3},       {6, 0, 0, 0});
	checkBoth("zero at end",          {1, 2, 3, 0},       {0, 0, 0, 6});
	checkBoth("negatives",            {-1, -2, -3, -4},   {-24, -12, -8, -6});
	checkBoth("all ones",             {1, 1, 1, 1},       {1, 1, 1, 1});
}

int main() {
	runTests();

	cout << '\n' << (failures == 0 ? "All tests passed" : "Some tests failed") << '\n';
	return failures == 0 ? 0 : 1;
}
