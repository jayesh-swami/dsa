/**
 * You are given an integer array nums of length n. 
 * Create an array ans of length 2n where ans[i] == nums[i] and ans[i + n] == nums[i] for 0 <= i < n (0-indexed).
 * Specifically, ans is the concatenation of two nums arrays.
 * Return the array ans.
*/

#include <iostream>
#include <vector>

using namespace std;

vector<int> get_concat(vector<int>& nums) {
	int n = nums.size();
	vector<int> ans;

	for(int i = 0; i < 2 * n ; i++) 
		ans.push_back(nums[i%n]);

	return ans;
}

// Leaves the allocation decision to the caller
void get_concat_native_with_out_buffer(int* arr, int n, int* out) {
	for(int i = 0; i < 2 * n ; i++) 
		out[i] = arr[i % n];

	return;
}

// The caller must manage the returned ans lifecycle
int* get_concat_native_new_array(int* arr, int n) {
	int* ans = new int[2 * n];

	for(int i = 0; i < 2 * n ; i++) 
		ans[i] = arr[i % n];

	return ans;
}

int main(int n, char** args) {
	vector<int> nums = {22,21,20,1};
	vector<int> ans = get_concat(nums);

	for(auto& i: ans) {
		cout << i << '\n';
	}

	return 0;
}
