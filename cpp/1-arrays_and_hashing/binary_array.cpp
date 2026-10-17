#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using std::vector;
using std::unordered_map;
using std::max;
using std::cout;

/**
 * To calculate the longest subarray with equal zeroes and ones
 * in a binary array (with only 0/1)
 *
 * Idea is to keep a currSum increment when 1 and decrement when 0
 * Check for longest sub-array with sum = 0
 */
int longestEqualBinarySubarray(vector<int>& nums) {
	int currSum = 0;
	int longestSubArrayLen = 0;
	unordered_map<int, int> mp;
	mp[0] = -1;

	for(int i = 0; i < (int) nums.size(); i++) {
		if(nums[i]) currSum++;
		else currSum--;
		if(!mp.contains(currSum)) mp[currSum] = i;

		longestSubArrayLen = max(longestSubArrayLen, i - mp[currSum]);
	}

	return longestSubArrayLen;
}

int main() {
	vector<int> a = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1};

	cout << longestEqualBinarySubarray(a) << '\n';

	return 0;
}
