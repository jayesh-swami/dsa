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

vector<vector<int>> threeSumHashed(vector<int>& nums) {
	unordered_map<int, int> mp;
	int n = nums.size();

	sort(nums.begin(), nums.end());
	
	for(int num: nums) mp[num]++;
	
	vector<vector<int>> res;

	// mp only ever holds the elements after j: nums[i] stays out for good,
	// and each nums[j] stays out until the j loop is done
	for(int i = 0; i < n; i++) {
		mp[nums[i]]--;
		if(i > 0 && nums[i] == nums[i-1]) continue;
		if(nums[i] > 0) break;
		
		for(int j = i+1 ; j < n; j++) {
			mp[nums[j]]--;
			if(j > i+1 && nums[j] == nums[j-1]) continue;

			int target = -(nums[i] + nums[j]);

			auto it = mp.find(target);
			if(it != mp.end() && it->second > 0) {
				res.push_back({nums[i], nums[j], target});
			}
		}

		for(int j = i+1; j < n; j++) mp[nums[j]]++;
	}

	return res;
}

vector<vector<int>> threeSumTwoPointers(vector<int>& nums) {
	int n = nums.size();

	sort(nums.begin(), nums.end());

	vector<vector<int>> res;

	for(int i = 0; i < n - 2; i++) {
		if(i > 0 && nums[i] == nums[i-1]) continue;
		if(nums[i] > 0) break;   // sorted, so everything from here on is positive

		int l = i+1, r = n-1;

		while(l < r) {
			long long sum = (long long) nums[i] + nums[l] + nums[r];

			if(sum > 0) r--;
			else if(sum < 0) l++;
			else {
				res.push_back({nums[i], nums[l], nums[r]});
				l++;
				r--;
				while(l < r && nums[l] == nums[l-1]) l++;
			}

		}
	}

	return res;
}

// ---- minimal test harness ----

int failures = 0;

// sort inside each triplet, then sort the triplets, so order doesn't matter (duplicates still count)
vector<vector<int>> normalize(vector<vector<int>> v) {
	for (auto& t : v) sort(t.begin(), t.end());
	sort(v.begin(), v.end());
	return v;
}

void print(const vector<vector<int>>& v) {
	cout << "[";
	for (size_t i = 0; i < v.size(); i++) cout << (i ? ", " : "") << "[" << v[i][0] << ", " << v[i][1] << ", " << v[i][2] << "]";
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
void checkAll(const string& name, vector<int> nums, vector<vector<int>> expected) {
	vector<int> a = nums, b = nums;
	check(name + " [hashed]",       threeSumHashed(a),      expected);
	check(name + " [two pointers]", threeSumTwoPointers(b), expected);
}

// brute force reference: every i < j < k, duplicates removed
vector<vector<int>> threeSumBrute(vector<int> nums) {
	int n = nums.size();
	vector<vector<int>> res;
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			for (int k = j + 1; k < n; k++)
				if (nums[i] + nums[j] + nums[k] == 0) res.push_back({nums[i], nums[j], nums[k]});

	res = normalize(res);
	res.erase(std::unique(res.begin(), res.end()), res.end());
	return res;
}

// random arrays with values in a small range so zero-sum triplets and duplicates are common
void randomCrossCheck() {
	std::mt19937 rng(1);
	std::uniform_int_distribution<int> lenDist(0, 12);
	std::uniform_int_distribution<int> valDist(-5, 5);

	int mismatches = 0;
	for(int t = 0; t < 5000; t++) {
		vector<int> nums(lenDist(rng));
		for(int& x : nums) x = valDist(rng);

		vector<vector<int>> expected = threeSumBrute(nums);
		vector<int> a = nums, b = nums;
		if(normalize(threeSumHashed(a)) != expected) mismatches++;
		if(normalize(threeSumTwoPointers(b)) != expected) mismatches++;
	}

	if (mismatches == 0) {
		cout << "PASS  random cross-check (5000 arrays)\n";
	} else {
		cout << "FAIL  random cross-check  (" << mismatches << " mismatches)\n";
		failures++;
	}
}

void runTests() {
	checkAll("empty",                    {},                            {});
	checkAll("one element",              {0},                           {});
	checkAll("two elements",             {0, 0},                        {});
	checkAll("three, sums to 0",         {-1, 0, 1},                    {{-1, 0, 1}});
	checkAll("three, no sum",            {0, 1, 1},                     {});
	checkAll("all zeros (3)",            {0, 0, 0},                     {{0, 0, 0}});
	checkAll("all zeros (6)",            {0, 0, 0, 0, 0, 0},            {{0, 0, 0}});
	checkAll("only two zeros",           {0, 0, 1},                     {});
	checkAll("all positive",             {1, 2, 3, 4},                  {});
	checkAll("all negative",             {-4, -3, -2, -1},              {});
	checkAll("needs a value twice",      {-2, 1, 1},                    {{-2, 1, 1}});
	checkAll("value present only once",  {-2, 1, 3},                    {});
	checkAll("leetcode example",         {-1, 0, 1, 2, -1, -4},         {{-1, -1, 2}, {-1, 0, 1}});
	checkAll("duplicate first elements", {-1, -1, -1, 0, 1, 2},         {{-1, -1, 2}, {-1, 0, 1}});
	checkAll("duplicate middle/last",    {-2, 0, 0, 2, 2},              {{-2, 0, 2}});
	checkAll("shared first element",     {-4, -1, 0, 1, 2, 3, 4},       {{-4, 0, 4}, {-4, 1, 3}, {-1, 0, 1}});
	checkAll("zeros after a skipped run", {-2, 0, 0, 0},                {{0, 0, 0}});
	checkAll("unsorted input",           {3, -2, 1, 0, -1, 2, -3},      {{-3, 0, 3}, {-3, 1, 2}, {-2, -1, 3}, {-2, 0, 2}, {-1, 0, 1}});
	randomCrossCheck();
}

int main() {
	runTests();

	cout << '\n' << (failures == 0 ? "All tests passed" : "Some tests failed") << '\n';
	return failures == 0 ? 0 : 1;
}
