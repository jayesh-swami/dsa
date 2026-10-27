#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <random>
#include <string>

using std::vector;
using std::unordered_map;
using std::sort;
using std::string;
using std::cout;

/**
 * Using hashmap O(n ^ 3)
 */
vector<vector<int>> fourSumHashed(vector<int>& nums, int target) {
	sort(nums.begin(), nums.end());
	
	// keyed by long long: the value looked up (target - sum) can fall outside int's range,
	// and converting it to an int key would wrap and could match a real value
	unordered_map<long long, int> mp; 
	
	vector<vector<int>> res;

	for(int num: nums) mp[num]++;
	
	int n = nums.size();

	// mp only ever holds the elements after k
	for(int i = 0; i < n; i++) {
		mp[nums[i]]--;
		if(i > 0 && nums[i] == nums[i-1]) continue;
		
		for(int j = i + 1; j < n; j++) {
			mp[nums[j]]--;
			if(j > i +1 && nums[j] == nums[j-1]) continue;

			for(int k = j + 1; k < n; k++) {
				mp[nums[k]]--;
				if(k > j +1 && nums[k] == nums[k-1]) continue;
				
				// cast before the first +, so every add is done in 64 bits
				long long sum = (long long) nums[i] + nums[j] + nums[k];
				auto it = mp.find(target - sum);
				if(it != mp.end() && it->second > 0) 
					res.push_back({nums[i], nums[j], nums[k], (int) (target - sum)});
			}

			for(int k = j + 1; k < n; k++) mp[nums[k]]++;
		}

		for(int j = i + 1; j < n; j++) mp[nums[j]]++;
	}
 
	return res;
}

/**
 * k-sum by recursion: fix one element and recurse with k - 1 on the rest,
 * until k == 2, which is the converging two pointers. O(n ^ (k - 1)), so O(n ^ 3) for 4Sum
 */
void kSumHelper(int k, const vector<int>& nums, long long target, int l, int r, vector<vector<int>>& res, vector<int>& currentVals) {
	if(k < 2 || l > r) return;

	// sorted, so k elements from [l, r] sum to at most nums[r] * k
	if((long long) nums[r] * k < target) return;

	if(k == 2) {
		while(l < r) {
			long long sum = (long long) nums[l] + nums[r];

			if(sum > target) r--;
			else if(sum < target) l++;
			else {
				currentVals.push_back(nums[l]);
				currentVals.push_back(nums[r]);
				res.push_back(currentVals);
				currentVals.pop_back();
				currentVals.pop_back();

				l++;
				while(l < r && nums[l] == nums[l-1]) l++;
			}
		}
	} else {
		for(int i = l; i < r; i++) {
			if(i > l && nums[i] == nums[i-1]) continue;

			// sorted, so k elements starting at i sum to at least nums[i] * k
			if((long long) nums[i] * k > target) break;

			currentVals.push_back(nums[i]);
			kSumHelper(k-1, nums, target - nums[i], i + 1, r, res, currentVals);
			currentVals.pop_back();
		}
	}
}

vector<vector<int>> fourSumTwoPointers(vector<int>& nums, int target) {
	sort(nums.begin(), nums.end());

	vector<vector<int>> res;
	vector<int> currentVals;
	currentVals.reserve(4);

	int n = nums.size();
	kSumHelper(4, nums, target, 0, n - 1, res, currentVals);

	return res;
}

// ---- minimal test harness ----

int failures = 0;

// sort inside each quadruplet, then sort the quadruplets, so order doesn't matter (duplicates still count)
vector<vector<int>> normalize(vector<vector<int>> v) {
	for (auto& q : v) sort(q.begin(), q.end());
	sort(v.begin(), v.end());
	return v;
}

void print(const vector<vector<int>>& v) {
	cout << "[";
	for (size_t i = 0; i < v.size(); i++) cout << (i ? ", " : "") << "[" << v[i][0] << ", " << v[i][1] << ", " << v[i][2] << ", " << v[i][3] << "]";
	cout << "]";
}

void check(const string& name, vector<vector<int>> got, vector<vector<int>> expected) {
	got = normalize(got);
	expected = normalize(expected);

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

// runs the same case against both implementations, each on its own copy since both sort the input
void checkAll(const string& name, vector<int> nums, int target, vector<vector<int>> expected) {
	vector<int> a = nums, b = nums;
	check(name + " [hashed]",       fourSumHashed(a, target),      expected);
	check(name + " [two pointers]", fourSumTwoPointers(b, target), expected);
}

// brute force reference: every i < j < k < m summed in long long, duplicates removed
vector<vector<int>> fourSumBrute(vector<int> nums, int target) {
	int n = nums.size();
	vector<vector<int>> res;
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			for (int k = j + 1; k < n; k++)
				for (int m = k + 1; m < n; m++)
					if ((long long) nums[i] + nums[j] + nums[k] + nums[m] == target)
						res.push_back({nums[i], nums[j], nums[k], nums[m]});

	res = normalize(res);
	res.erase(std::unique(res.begin(), res.end()), res.end());
	return res;
}

// random arrays with values in a small range so matches and duplicates are common
void randomCrossCheck() {
	std::mt19937 rng(1);
	std::uniform_int_distribution<int> lenDist(0, 10);
	std::uniform_int_distribution<int> valDist(-5, 5);
	std::uniform_int_distribution<int> targetDist(-6, 6);

	int mismatches = 0;
	for(int t = 0; t < 5000; t++) {
		vector<int> nums(lenDist(rng));
		for(int& x : nums) x = valDist(rng);
		int target = targetDist(rng);

		vector<vector<int>> expected = fourSumBrute(nums, target);
		vector<int> a = nums, b = nums;
		if(normalize(fourSumHashed(a, target)) != expected) mismatches++;
		if(normalize(fourSumTwoPointers(b, target)) != expected) mismatches++;
	}

	if (mismatches == 0) {
		cout << "PASS  random cross-check (5000 arrays)\n";
	} else {
		cout << "FAIL  random cross-check  (" << mismatches << " mismatches)\n";
		failures++;
	}
}

void runTests() {
	checkAll("empty",                      {},                        0,  {});
	checkAll("three elements",             {0, 0, 0},                 0,  {});
	checkAll("four, hits target",          {1, 2, 3, 4},              10, {{1, 2, 3, 4}});
	checkAll("four, misses target",        {1, 2, 3, 4},              11, {});
	checkAll("all equal (4)",              {2, 2, 2, 2},              8,  {{2, 2, 2, 2}});
	checkAll("all equal (6)",              {2, 2, 2, 2, 2, 2},        8,  {{2, 2, 2, 2}});
	checkAll("leetcode example 1",         {1, 0, -1, 0, -2, 2},      0,  {{-2, -1, 1, 2}, {-2, 0, 0, 2}, {-1, 0, 0, 1}});
	checkAll("negative target",            {-3, -2, -1, 0, 1},        -6, {{-3, -2, -1, 0}});
	checkAll("shared first element",       {-3, -1, 0, 1, 2, 3},      0,  {{-3, -1, 1, 3}, {-3, 0, 1, 2}});
	checkAll("shared last element",        {-3, -2, -1, 0, 1, 4},     0,  {{-3, -2, 1, 4}, {-3, -1, 0, 4}});
	checkAll("gap inside",                 {-5, -4, 0, 0, 4, 9},      0,  {{-5, -4, 0, 9}, {-4, 0, 0, 4}});
	checkAll("same first, different last", {-2, -1, 0, 2, 2, 3},      2,  {{-2, -1, 2, 3}, {-2, 0, 2, 2}});
	checkAll("overflow",                   {1000000000, 1000000000, 1000000000, 1000000000}, -294967296, {});
	randomCrossCheck();
}

int main() {
	runTests();

	cout << '\n' << (failures == 0 ? "All tests passed" : "Some tests failed") << '\n';
	return failures == 0 ? 0 : 1;
}
