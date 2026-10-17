#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
#include <algorithm>
#include <string>
#include <random>

using std::cout;
using std::vector;
using std::unordered_map;
using std::string;

/**
 * Keep count of the occurences and insert once the count crosses n/3.
 * To prevent re-insertion, set the count to INT_MIN just to avoid duplicates.
 */
vector<int> majorityElement(vector<int>& nums) {
	unordered_map<int, int> mp;
	vector<int> res;

	for(int& n: nums) {
		mp[n]++;
		if(mp[n] > (int) nums.size() / 3) {
			res.push_back(n);
			mp[n] = INT_MIN;
		}
	}

	return res;
}

/**
 * Another one with Boyer-Moore voting algorithm. It gave the same 
 * runtime on neetcode and similarish memory.
 */
vector<int> majorityElementBoyerMoore(vector<int>& nums) {
	int cd1 = INT_MIN, cd2 = INT_MIN, c1 = 0, c2 = 0;

	for(int& n: nums) {
		if(c1 == 0 && n != cd2) {
			cd1 = n;
			c1++;
		} else if (c2 == 0 && n != cd1) {
			cd2 = n;
			c2++;
		} else {
			if(n == cd1) {
				c1++;
			} else if (n == cd2) {
				c2++;
			} else {
				c1--;
				c2--;
			}
		}
	}

	c1 = 0, c2 = 0;

	for(int& n: nums) {
		if(n == cd1) c1++;
		else if(n == cd2) c2++;
	}

	vector<int> res;

	if(c1 > (int) nums.size() / 3) res.push_back(cd1);
	if(c2 > (int) nums.size() / 3) res.push_back(cd2);

	return res;
}

// ---- minimal test harness ----

int failures = 0;

// the answer can come back in any order, so compare sorted copies
void check(const string& name, vector<int> got, vector<int> expected) {
	std::sort(got.begin(), got.end());
	std::sort(expected.begin(), expected.end());

	if (got == expected) {
		cout << "PASS  " << name << '\n';
	} else {
		cout << "FAIL  " << name << "  (expected [";
		for(int x : expected) cout << ' ' << x;
		cout << " ], got [";
		for(int x : got) cout << ' ' << x;
		cout << " ])\n";
		failures++;
	}
}

// runs the same case against both implementations
void checkAll(const string& name, vector<int> nums, vector<int> expected) {
	check(name + " [hashmap]",     majorityElement(nums),           expected);
	check(name + " [boyer-moore]", majorityElementBoyerMoore(nums), expected);
}

// random arrays, hash map version used as the reference for Boyer-Moore
void randomCrossCheck() {
	std::mt19937 rng(1);
	std::uniform_int_distribution<int> lenDist(0, 30);
	std::uniform_int_distribution<int> valDist(-2, 3); // small range so some values cross n/3, includes -1

	int mismatches = 0;
	for(int t = 0; t < 1000; t++) {
		vector<int> nums(lenDist(rng));
		for(int& x : nums) x = valDist(rng);

		vector<int> expected = majorityElement(nums);
		vector<int> got = majorityElementBoyerMoore(nums);
		std::sort(expected.begin(), expected.end());
		std::sort(got.begin(), got.end());
		if(got != expected) mismatches++;
	}

	if (mismatches == 0) {
		cout << "PASS  random cross-check (1000 arrays)\n";
	} else {
		cout << "FAIL  random cross-check  (" << mismatches << " mismatches)\n";
		failures++;
	}
}

void runTests() {
	checkAll("basic",                    {3, 2, 3},                      {3});
	checkAll("other one at exactly n/3",  {1, 2, 2, 2, 1, 1, 1, 1, 1, 1}, {1});
	checkAll("two answers",              {1, 2, 2, 2, 1, 1, 1, 1, 2},    {1, 2});
	checkAll("two answers interleaved",  {1, 2, 1, 2, 3},                {1, 2});
	checkAll("empty",                    {},                             {});
	checkAll("single",                   {1},                            {1});
	checkAll("two different",            {1, 2},                         {1, 2});
	checkAll("all same",                 {4, 4, 4, 4},                   {4});
	checkAll("none above n/3",           {1, 2, 3, 4, 5, 6},             {});
	checkAll("exactly n/3 is not enough",{1, 1, 2, 2, 3, 3},             {});
	checkAll("negatives",                {-5, -5, 7, -5},                {-5});
	checkAll("single -1",                {-1},                           {-1});
	checkAll("single INT_MIN",           {INT_MIN},                      {INT_MIN});
	checkAll("all -1",                   {-1, -1, -1},                   {-1});
	checkAll("int limits",               {INT_MIN, INT_MAX, INT_MIN, INT_MAX}, {INT_MIN, INT_MAX});
	randomCrossCheck();
}

int main() {
	runTests();

	cout << '\n' << (failures == 0 ? "All tests passed" : "Some tests failed") << '\n';
	return failures == 0 ? 0 : 1;
}
