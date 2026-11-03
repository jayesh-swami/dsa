#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>

using std::vector;
using std::sort;
using std::min;
using std::string;
using std::cout;

void countSort(vector<int>& nums, int bucketSize);

/**
 * Assuming correct inputs like weight never exceeds the limit
 */
long long numRescueBoats(vector<int>& people, int limit) {
	sort(people.begin(), people.end());

	int l = 0, r = (int) people.size() - 1;

	long long boats = 0;

	while(l <= r) {
		long long totalWeight = (long long) people[l] + people[r];

		if(totalWeight > limit) {
			r--;
		} else {
			l++;
			r--;
		}
		boats++;
	}

	return boats;
}

long long numRescueBoatCountingSort(vector<int>& people, int limit) {
	countSort(people, limit);

		int l = 0, r = (int) people.size() - 1;

	long long boats = 0;

	while(l <= r) {
		long long totalWeight = (long long) people[l] + people[r];

		if(totalWeight > limit) {
			r--;
		} else {
			l++;
			r--;
		}
		boats++;
	}

	return boats;

}

void countSort(vector<int>& nums, int bucketSize) {
	vector<int> counts(bucketSize + 1, 0);

	for(int n: nums) counts[n]++;

	int i = 0;

	for(int j = 0; j <= bucketSize; j++) {
		while(counts[j]--) {
			nums[i] = j;
			i++;
		}
	}
}

// ---- minimal test harness ----

int failures = 0;

void check(const string& name, int got, int expected) {
	if (got == expected) {
		cout << "PASS  " << name << '\n';
	} else {
		cout << "FAIL  " << name << "  (expected " << expected << ", got " << got << ")\n";
		failures++;
	}
}

// runs the same case against both implementations, each on its own copy since both sort the input
void checkAll(const string& name, vector<int> people, int limit, int expected) {
	vector<int> a = people, b = people;
	check(name + " [sort]",          numRescueBoats(a, limit),            expected);
	check(name + " [counting sort]", numRescueBoatCountingSort(b, limit), expected);
}

// brute force reference: dp over subsets of people already rescued.
// The lowest-numbered person still waiting goes alone or with any one other person who fits
int numRescueBoatsBrute(const vector<int>& people, int limit) {
	int n = people.size();
	vector<int> dp(1 << n, n + 1);
	dp[0] = 0;
	for (int mask = 0; mask < (1 << n); mask++) {
		if (dp[mask] > n) continue;
		int i = 0;
		while (i < n && (mask >> i & 1)) i++;
		if (i == n) continue;

		int alone = mask | 1 << i;
		dp[alone] = min(dp[alone], dp[mask] + 1);
		for (int j = i + 1; j < n; j++) {
			if (!(mask >> j & 1) && people[i] + people[j] <= limit) {
				int pair = alone | 1 << j;
				dp[pair] = min(dp[pair], dp[mask] + 1);
			}
		}
	}
	return dp[(1 << n) - 1];
}

// random small groups (the brute force is exponential), every weight <= limit
void randomCrossCheck() {
	std::mt19937 rng(1);
	std::uniform_int_distribution<int> lenDist(0, 12);
	std::uniform_int_distribution<int> limitDist(1, 10);

	int mismatches = 0;
	for(int t = 0; t < 5000; t++) {
		int limit = limitDist(rng);
		std::uniform_int_distribution<int> weightDist(1, limit);
		vector<int> people(lenDist(rng));
		for(int& w : people) w = weightDist(rng);

		int expected = numRescueBoatsBrute(people, limit);
		vector<int> a = people, b = people;
		if(numRescueBoats(a, limit) != expected) mismatches++;
		if(numRescueBoatCountingSort(b, limit) != expected) mismatches++;
	}

	if (mismatches == 0) {
		cout << "PASS  random cross-check (5000 groups)\n";
	} else {
		cout << "FAIL  random cross-check  (" << mismatches << " mismatches)\n";
		failures++;
	}
}

void runTests() {
	checkAll("leetcode example 1",          {1, 2},                 3,     1);
	checkAll("leetcode example 2",          {3, 2, 2, 1},           3,     3);
	checkAll("leetcode example 3",          {3, 5, 3, 4},           5,     4);
	checkAll("empty",                       {},                     5,     0);
	checkAll("single person",               {4},                    5,     1);
	checkAll("pairs exactly at the limit",  {1, 2, 1, 2},           3,     2);
	checkAll("everyone over half the limit", {4, 4, 4},             7,     3);
	checkAll("all light, max two per boat", {1, 1, 1, 1},           10,    2);
	checkAll("odd number of light people",  {1, 1, 1},              10,    2);
	checkAll("heaviest equals the limit",   {5, 1, 4},              5,     2);
	checkAll("heaviest pairs with lightest", {1, 2, 2, 3},          4,     2);
	checkAll("max weight 30000",            {30000, 30000},         30000, 2);
	randomCrossCheck();
}

int main() {
	runTests();

	cout << '\n' << (failures == 0 ? "All tests passed" : "Some tests failed") << '\n';
	return failures == 0 ? 0 : 1;
}
