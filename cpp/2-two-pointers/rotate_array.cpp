#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>

using std::vector;
using std::reverse;
using std::rotate;
using std::string;
using std::cout;
using std::swap;

void rotateCyclic(vector<int>& nums, int k) {
	int n = nums.size();
	if(n == 0) return;

	k = k % n;
	
	if(k < 0) k += n;

	if(k == 0) return;

	int count = 0;

	for(int i = 0; count < n; i++) {
		int prev = nums[i];
		int curr = i;

		do { 
			curr = (curr + k) % n;
			swap(prev, nums[curr]);
			count++;
		} while (curr != i);
	}

	return;
}

void rotateByReversing(vector<int>& nums, int k) {
	int n = nums.size();
	if(n == 0) return;

	k = k % n;
	
	if(k < 0) k += n;

	reverse(nums.begin(), nums.end());
	reverse(nums.begin(), nums.begin() + k);
	reverse(nums.begin() + k, nums.end());
}

void rotateUsingSTLFunction(vector<int>& nums, int k) {
	int n = nums.size();
	if(n == 0) return;

	k = k % n;
	
	if(k < 0) k += n;
	rotate(nums.begin(), nums.end() - k, nums.end());
}

// ---- minimal test harness ----

int failures = 0;

void print(const vector<int>& v) {
	cout << "[";
	for (size_t i = 0; i < v.size(); i++) cout << (i ? ", " : "") << v[i];
	cout << "]";
}

void check(const string& name, const vector<int>& got, const vector<int>& expected) {
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

// runs the same case against all three implementations, each on its own copy since they rotate in place
void checkAll(const string& name, vector<int> nums, int k, vector<int> expected) {
	vector<int> a = nums, b = nums, c = nums;
	rotateCyclic(a, k);
	rotateByReversing(b, k);
	rotateUsingSTLFunction(c, k);
	check(name + " [cyclic]",    a, expected);
	check(name + " [reversing]", b, expected);
	check(name + " [std::rotate]", c, expected);
}

// brute force reference: element i moves to (i + k) % n in a new array
vector<int> rotateBrute(const vector<int>& nums, int k) {
	int n = nums.size();
	vector<int> res(n);
	for (int i = 0; i < n; i++) res[(i + k) % n] = nums[i];
	return res;
}

// random lengths 1..20 and k up to 50, so k > n, k == n and gcd(n, k) > 1 all come up
void randomCrossCheck() {
	std::mt19937 rng(1);
	std::uniform_int_distribution<int> lenDist(1, 20);
	std::uniform_int_distribution<int> kDist(0, 50);
	std::uniform_int_distribution<int> valDist(-100, 100);

	int mismatches = 0;
	for(int t = 0; t < 5000; t++) {
		vector<int> nums(lenDist(rng));
		for(int& x : nums) x = valDist(rng);
		int k = kDist(rng);

		vector<int> expected = rotateBrute(nums, k);
		vector<int> a = nums, b = nums, c = nums;
		rotateCyclic(a, k);
		rotateByReversing(b, k);
		rotateUsingSTLFunction(c, k);
		if(a != expected) mismatches++;
		if(b != expected) mismatches++;
		if(c != expected) mismatches++;
	}

	if (mismatches == 0) {
		cout << "PASS  random cross-check (5000 arrays)\n";
	} else {
		cout << "FAIL  random cross-check  (" << mismatches << " mismatches)\n";
		failures++;
	}
}

void runTests() {
	checkAll("leetcode example 1",      {1, 2, 3, 4, 5, 6, 7},  3,  {5, 6, 7, 1, 2, 3, 4});
	checkAll("leetcode example 2",      {-1, -100, 3, 99},      2,  {3, 99, -1, -100});
	checkAll("single element",          {1},                    5,  {1});
	checkAll("k = 0",                   {1, 2, 3},              0,  {1, 2, 3});
	checkAll("k = n",                   {1, 2, 3},              3,  {1, 2, 3});
	checkAll("k > n",                   {1, 2, 3},              4,  {3, 1, 2});
	checkAll("k much larger than n",    {1, 2, 3, 4},           10, {3, 4, 1, 2});
	checkAll("k = n - 1",               {1, 2, 3, 4},           3,  {2, 3, 4, 1});
	checkAll("two elements",            {1, 2},                 1,  {2, 1});
	checkAll("gcd(n, k) = 2",           {1, 2, 3, 4, 5, 6},     2,  {5, 6, 1, 2, 3, 4});
	checkAll("gcd(n, k) = 3",           {1, 2, 3, 4, 5, 6},     3,  {4, 5, 6, 1, 2, 3});
	checkAll("half of even n",          {1, 2, 3, 4},           2,  {3, 4, 1, 2});
	checkAll("duplicates",              {1, 1, 2, 2},           1,  {2, 1, 1, 2});
	checkAll("empty",                   {},                     3,  {});
	checkAll("negative k (left by 1)",   {1, 2, 3, 4},           -1, {2, 3, 4, 1});
	checkAll("negative k, |k| > n",      {1, 2, 3, 4},           -6, {3, 4, 1, 2});
	randomCrossCheck();
}

int main() {
	runTests();

	cout << '\n' << (failures == 0 ? "All tests passed" : "Some tests failed") << '\n';
	return failures == 0 ? 0 : 1;
}
