#include <iostream>
#include <vector>
#include <utility>
#include <chrono>
#include <algorithm>
#include <random>

using std::vector;
using std::cout;
using std::cin;
using std::swap;
using std::ios;
using std::sort;
using std::min;
using std::max;
using std::swap;

// Setting a fixed seed
std::mt19937 rng(45);

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

void mergeSort(vector<int>& nums, int start, int end) {
	if(end < start) return;

	if(end - start < 2) {
		nums[start] = min(nums[start], nums[end - 1]);
		nums[end - 1] = max(nums[start], nums[end - 1]);
		return;
	}
	
	int mid = (end + start) / 2;

	mergeSort(nums, start, mid);
	mergeSort(nums, mid, end);

	// Merge step
	vector<int> merged;
	
	int l = start;
	int r = mid;

	while(l < mid && r < end) {
		if(nums[l] <= nums[r]) {
			merged.push_back(nums[l]);
			l++;
		} else {
			merged.push_back(nums[r]);
			r++;
		}
	}

	while(l < mid) { merged.push_back(nums[l]); l++; }
	while(r < end) { merged.push_back(nums[r]); r++; }

	for(int i = start; i < end; i++) {
		nums[i] = merged[i - start];
	}

	return;
}

/**
 * Quick Sort section 
 */
int randomBetween(int start, int end) {
	std::uniform_int_distribution<int> dist(start, end);
	return dist(rng);
}

int partitionQuickSort(vector<int>& nums, int start, int end) {
	int pivotIdx = randomBetween(start, end);
	int pivot = nums[pivotIdx];

	swap(nums[pivotIdx], nums[end]);

	int i = start;
	for(int j = start; j < end; j++) {
		if(nums[j] < pivot) {
			swap(nums[i], nums[j]);
			i++;
		}
	}

	swap(nums[i], nums[end]);

	return i;
}

void quickSort(vector<int>& nums, int start, int end) {
	if(end < start) return;
	int partition = partitionQuickSort(nums, start, end);

	quickSort(nums, start, partition - 1);
	quickSort(nums, partition + 1, end);
}



int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	vector<int> a = {1, 4, 7, -1, 2, 4, 4, 3};
	quickSort(a, 0, a.size() - 1);

	for(int& i: a) {
		cout << i << '\n';
	}

	vector<int> big;
	int n;
	cin >> n;

	for(int i = 0; i < n; i++) {
		int k;
		cin >> k;
		big.push_back(k);
	}

	auto start = std::chrono::steady_clock::now();
	
	//bubbleSort(big);
	quickSort(big, 0, (int)big.size() - 1);
	//sort(big.begin(), big.end());

	auto end = std::chrono::steady_clock::now();
	
	cout << "Time taken (bubbleSort) - " << std::chrono::duration<double>(end - start).count() << '\n';

	for(int i = 0; i < big.size() - 1; i++) {
		if(big[i] > big[i + 1]) cout << "sort failure!";
	}

	return 0;
}
