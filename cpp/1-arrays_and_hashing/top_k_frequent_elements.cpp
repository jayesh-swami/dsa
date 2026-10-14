#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <utility>

using std::cout;
using std::vector;
using std::string;
using std::unordered_map;
using std::pair;
using std::sort;

/**
 * Count with a hashmap, then sort (count, value) pairs descending: O(n + u log u).
 *
 * Better: bucket sort by frequency. A count is always in [1, n], so bucket[f]
 * holds the values seen f times; walk from n down to collect k values. O(n).
 * Alternatives: min-heap of size k (O(n log k)), or partial_sort / nth_element.
 *
 * If the values lie in a small known range (e.g. [-1000, 1000]), a fixed array
 * of 2001 counts can replace the hashmap. That removes the hashing, not the sort.
 */
vector<int> topKFrequent(vector<int>& nums, int k) {
	unordered_map<int, int> elemCount;

	for(int& i: nums) elemCount[i]++;

	vector<pair<int, int>> countElem;

	for(auto& [key, value]: elemCount) countElem.push_back({value, key});

	sort(countElem.rbegin(), countElem.rend());

	vector<int> res;

	for(int i = 0; i < k; i++) res.push_back(countElem[i].second);
	return res;
}

/**
 * Bucket sort by frequency - O(n)
 */
vector<int> topKFrequentBucket(vector<int>& nums, int k) {
	unordered_map<int, int> elemCount;

	for(int& i: nums) elemCount[i]++;

	vector<vector<int>> bucket(nums.size() + 1);

	for(auto& [key, value]: elemCount) bucket[value].push_back(key);

	vector<int> res;

	for(int f = nums.size(); f > 0 && (int)res.size() < k; f--)
		for(int v: bucket[f]) if((int)res.size() < k) res.push_back(v);
	return res;
}

// ---- minimal test harness ----

int failures = 0;

void printVec(const vector<int>& v) {
	cout << "[";
	for (size_t i = 0; i < v.size(); i++) cout << (i ? ", " : "") << v[i];
	cout << "]";
}

// Answer order doesn't matter, so sort both before comparing.
void check(const string& name, vector<int> got, vector<int> expected) {
	sort(got.begin(), got.end());
	sort(expected.begin(), expected.end());

	if (got == expected) {
		cout << "PASS  " << name << '\n';
	} else {
		cout << "FAIL  " << name << "\n  expected: ";
		printVec(expected);
		cout << "\n  got:      ";
		printVec(got);
		cout << '\n';
		failures++;
	}
}

void runTests() {
	using Fn = vector<int> (*)(vector<int>&, int);

	for (auto [label, fn] : vector<pair<string, Fn>>{{"sort", topKFrequent}, {"bucket", topKFrequentBucket}}) {
		vector<int> a = {1, 1, 1, 2, 2, 3};
		check(label + " basic", fn(a, 2), {1, 2});

		vector<int> b = {1};
		check(label + " single element", fn(b, 1), {1});

		vector<int> c = {4, 4, -1, -1, -1, 7, 4, -1};
		check(label + " negatives", fn(c, 1), {-1});

		vector<int> d = {5, 3, 9};
		check(label + " k equals unique count", fn(d, 3), {3, 5, 9});

		vector<int> e = {2, 3, 3, 1, 1, 1, 4, 4, 4, 4};
		check(label + " distinct frequencies", fn(e, 3), {4, 1, 3});
	}
}

int main() {
	runTests();

	cout << '\n' << (failures == 0 ? "All tests passed" : "Some tests failed") << '\n';
	return failures == 0 ? 0 : 1;
}
