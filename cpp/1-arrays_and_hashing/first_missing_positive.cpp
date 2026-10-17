#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <string>
#include <random>

using std::vector;
using std::cout;
using std::abs;
using std::string;
using std::swap;

/**
 * One way would be to keep a boolean array of max possible len (1e6) of
 * the input. And then at the end iterate over it to check the first false
 */
int firstMissingPositive(vector<int>& nums) {
	vector<bool> present(nums.size() + 1, false);

	for(int n: nums) {
		if(n > 0 && n <= nums.size()) present[n] = true;
	}

	for(int i = 1; i <= nums.size(); i++) {
		if(!present[i]) return i;
	}

	return nums.size() + 1;
}

/**
 * The idea here is to use the existing array as a hashmap if we are allowed to
 * make changes to the input array. 
 *
 * Things to keep in mind for this ->
 * 1. 	Make sure to use absolute value of the entry to not go out of bounds.
 * 2.	Convert all less than equal to zero to n + 2 (n+1 works too), so that those places 
 * 	can be used for indexing (as multiplying with zero will not give negative and negatives
 * 	will be misread).
 * 3.	Only multiply with -1 if the value is positive (i.e. for the first time)
 * 	so that our usage of array as set is not affected by -1 * -1 = 1 errors :D
 * 4.	Even for INT_MIN, this code holds up as we would convert it to n + 1/2
 * 5. 	VERY IMP -> Only works if we can change the initial input, otherwise if
 * 	we create a copy, we make it O(n) aux space
 */
int firstMissingPositiveInPlace(vector<int>& nums) {
	int n = nums.size();

	for(int i = 0; i < n; i++) {
		if(nums[i] <= 0) nums[i] = n + 2;
	}

	for(int i = 0; i < n; i++) {
		int val = abs(nums[i]);
		if(val <= n && nums[val - 1] > 0) nums[val - 1] *= -1; 
	}

	for(int i = 0; i < n; i++) {
		if(nums[i] > 0) return i + 1;
	}


	return n + 1;
}

/**
 * Using the cycle sort technique. Not the actual sort but just using the
 * technique to store nums[i] at index nums[i] - 1 if 0 < nums[i] <= n. Keep
 * swapping while the value is in range and its target slot doesn't already
 * hold it (that check also stops duplicates like {1, 1} from looping forever).
 *
 * Although it is a while loop inside for loop, the actual complexity is going
 * to be linear since the once an element is at its correct index, it will never
 * be moved, so only once.
 */
int firstMissingPositiveCyclic(vector<int>& nums) {
	int n = nums.size();

	for(int j = 0; j < n; j++) {
		while(nums[j] > 0 && nums[j] <= n && nums[nums[j] - 1] != nums[j]) {
			swap(nums[j], nums[nums[j] - 1]);
		}
	}
	
	for(int i = 0; i < n; i++) {
		if(nums[i] != i + 1) return i + 1;
	}

	return n + 1;
}

// ---- minimal test harness ----

int failures = 0;

void check(const string& name, int got, int expected) {
	if (got == expected) {
		cout << "PASS  " << name << '\n';
	} else {
		cout << "FAIL  " << name << "  (expected " << expected << ", got " << got << ")\n";
		failures++;
	}
}

// runs the same case against all implementations, each on its own copy
// since the in-place and cyclic versions overwrite the input
void checkAll(const string& name, vector<int> nums, int expected) {
	vector<int> a = nums, b = nums, c = nums;
	check(name + " [bool array]", firstMissingPositive(a),        expected);
	check(name + " [in-place]",   firstMissingPositiveInPlace(b), expected);
	check(name + " [cyclic]",     firstMissingPositiveCyclic(c),  expected);
}

// random arrays, bool array version used as the reference for the other two
void randomCrossCheck() {
	std::mt19937 rng(1);
	std::uniform_int_distribution<int> lenDist(0, 30);
	std::uniform_int_distribution<int> valDist(-5, 35); // values around 1..n, with negatives, zeros and duplicates

	int mismatches = 0;
	for(int t = 0; t < 1000; t++) {
		vector<int> nums(lenDist(rng));
		for(int& x : nums) x = valDist(rng);

		vector<int> copy = nums, copy2 = nums;
		int expected = firstMissingPositive(nums);
		if(firstMissingPositiveInPlace(copy) != expected) mismatches++;
		if(firstMissingPositiveCyclic(copy2) != expected) mismatches++;
	}

	if (mismatches == 0) {
		cout << "PASS  random cross-check (1000 arrays)\n";
	} else {
		cout << "FAIL  random cross-check  (" << mismatches << " mismatches)\n";
		failures++;
	}
}

void runTests() {
	checkAll("basic",                {1, 2, 0},                 3);
	checkAll("gap in the middle",    {3, 4, -1, 1},             2);
	checkAll("nothing small",        {7, 8, 9, 11, 12},         1);
	checkAll("empty",                {},                        1);
	checkAll("single 1",             {1},                       2);
	checkAll("single 2",             {2},                       1);
	checkAll("all negatives/zero",   {-3, 0, -1},               1);
	checkAll("1..n permutation",     {5, 3, 1, 2, 4},           6);
	checkAll("duplicates",           {1, 1, 2, 2},              3);
	checkAll("value equal to n",     {2, 3, 1, 4},              5);
	checkAll("value n + 1",          {2, 3, 4},                 1);
	checkAll("value n + 2",          {1, 5, 2},                 3);
	checkAll("int limits",           {INT_MIN, INT_MAX, 1},     2);
	randomCrossCheck();
}

int main() {
	runTests();

	cout << '\n' << (failures == 0 ? "All tests passed" : "Some tests failed") << '\n';
	return failures == 0 ? 0 : 1;
}
