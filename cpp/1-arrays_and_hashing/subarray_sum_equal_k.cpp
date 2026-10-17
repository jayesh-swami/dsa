#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <random>

using std::vector;
using std::unordered_map;
using std::cout;
using std::string;

int subarraySum(vector<int>& nums, int k) {
	// Map to store count of [array sum from start] : [how many times that sum appeared]
	unordered_map<int, int> mp;
	int currSum = 0;
	int totalCountOfSubarrays = 0;
	
	// Setting this here so that if nums[i] == k, it is automatically to the total count
	// Basically this acts as a null set being added initially
	mp[0] = 1;

	for(int& n: nums) {
		currSum += n;
		totalCountOfSubarrays += mp[currSum - k];
		mp[currSum]++;
	}

	return totalCountOfSubarrays;
}

// ---- minimal test harness ----

int failures = 0;

// O(n^2) reference: try every start index and extend to the right
int subarraySumBrute(vector<int>& nums, int k) {
	int count = 0;
	for(int i = 0; i < (int)nums.size(); i++) {
		int sum = 0;
		for(int j = i; j < (int)nums.size(); j++) {
			sum += nums[j];
			if(sum == k) count++;
		}
	}
	return count;
}

void check(const string& name, vector<int> nums, int k, int expected) {
	int got = subarraySum(nums, k);
	if (got == expected) {
		cout << "PASS  " << name << '\n';
	} else {
		cout << "FAIL  " << name << "  (expected " << expected << ", got " << got << ")\n";
		failures++;
	}
}

// random arrays, brute force used as the reference
void randomCrossCheck() {
	std::mt19937 rng(1);
	std::uniform_int_distribution<int> lenDist(0, 50);
	std::uniform_int_distribution<int> valDist(-3, 3); // negatives and zeros so prefix sums repeat
	std::uniform_int_distribution<int> kDist(-5, 5);

	int mismatches = 0;
	for(int t = 0; t < 1000; t++) {
		vector<int> nums(lenDist(rng));
		for(int& x : nums) x = valDist(rng);
		int k = kDist(rng);

		if(subarraySum(nums, k) != subarraySumBrute(nums, k)) mismatches++;
	}

	if (mismatches == 0) {
		cout << "PASS  random cross-check (1000 arrays)\n";
	} else {
		cout << "FAIL  random cross-check  (" << mismatches << " mismatches)\n";
		failures++;
	}
}

void runTests() {
	check("basic",                   {1, 1, 1},               2, 2);
	check("basic 2",                 {1, 2, 3},               3, 2);
	check("empty",                   {},                      0, 0);
	check("single equal to k",       {5},                     5, 1);
	check("single not equal to k",   {5},                     3, 0);
	check("no match",                {1, 2, 3},               7, 0);
	check("whole array",             {1, 2, 3},               6, 1);
	check("negatives",               {1, -1, 1, -1},          0, 4);
	check("k = 0 with zeros",        {0, 0, 0},               0, 6);
	check("negative k",              {-1, -1, 1},            -1, 3);
	check("prefix sum repeats",      {3, 4, 7, 2, -3, 1, 4, 2}, 7, 4);
	randomCrossCheck();
}

int main() {
	runTests();

	cout << '\n' << (failures == 0 ? "All tests passed" : "Some tests failed") << '\n';
	return failures == 0 ? 0 : 1;
}
