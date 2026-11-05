#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using std::vector;
using std::unordered_map;
using std::unordered_set;

bool containsDuplicateHashMap(vector<int>& nums, int k) {
	unordered_map<int, int> mp;

	for(int i = 0; i < (int) nums.size(); i++) {
		int n = nums[i];

		if(mp.contains(n) && i - mp[n] <= k) return true;

		mp[n] = i;
	}

	return false;
}

bool containsDuplicateNaive(vector<int>& nums, int k) {
	for(int i = 1; i <= k; i++) {
		for(int j = i; j < (int) nums.size(); j++) {
			if(nums[j] == nums[j-i]) return true;
		}
	}

	return false;
}

// [1, 2, 3, 4, 1] 3
bool containsDuplicateSpaceOptimized(vector<int>& nums, int k) {
	unordered_set<int> s;

	for(int i = 0; i < (int) nums.size(); i++) {
		if(i > k) {
			s.erase(nums[i - k - 1]);
		}

		if(s.contains(nums[i])) return true;

		s.insert(nums[i]);
	}

	return false;
}
