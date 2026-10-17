#include <iostream>
#include <vector>
#include <utility>
#include <unordered_set>

using std::vector;
using std::swap;
using std::cout;
using std::unordered_set;

/**
 * Put the unique elements as the first elements of the sorted input
 * and return the count of unique elements
 */
int removeDuplicates(vector<int>& nums) {
	unordered_set<int> s;
	int w = 0;
	
	for(int r = 0; r < (int) nums.size(); r++) {
		if(s.insert(nums[r]).second) {
			swap(nums[r], nums[w++]);
		}
	}

	return w;
}

int main() {
	vector<int> a = {1,1,1, 2, 2, 3,3, 4, 4, 4};
	int k = removeDuplicates(a);

	cout << k << '\n';

	for(int n: a) {
		cout << n << ' ';
	}
	cout << '\n';
	
	return 0;
}

