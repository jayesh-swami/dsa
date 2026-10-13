#include <iostream>
#include <vector>
#include <utility>

using std::vector;
using std::cout;
using std::swap;

void bubbleSort(vector<int>& nums) {
	for(int i = 0; i < nums.size(); i++) {
		int swaps = 0;

		for(int j = 0; j < nums.size() - 1; j++) {
			if(nums[j] > nums[j+1]) {
				swap(nums[j], nums[j+1]);
				swaps++;
			}
		}

		if(swaps == 0) return;
	}

	return;
}

int main() {
	vector<int> a = {1, 4, 7, -1, 2, 4, 4, 3};
	bubbleSort(a);

	for(int& i: a) {
		cout << i << '\n';
	}

	return 0;
}
