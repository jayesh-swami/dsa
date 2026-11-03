#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>

using std::vector;
using std::string;
using std::cout;

vector<int> twoSum(vector<int>& v, int t) {
	int l = 0, r = (int) v.size() - 1;

	while(l < r) {
        if(v[l] + v[r] < t) l++;
		else if(v[l] + v[r] == t) return vector({l + 1, r + 1});
		else r--;
	}

	return vector({-1, -1});
}

// ---- minimal test harness ----

int failures = 0;

void check(const string& name, const vector<int>& got, const vector<int>& expected) {
	if (got == expected) {
		cout << "PASS  " << name << '\n';
	} else {
		cout << "FAIL  " << name << "  (expected [" << expected[0] << ", " << expected[1]
		     << "], got [" << got[0] << ", " << got[1] << "])\n";
		failures++;
	}
}

// twoSum takes a non-const reference, so it can't take a braced list directly
vector<int> run(vector<int> v, int t) {
	return twoSum(v, t);
}

// random sorted arrays; there can be several valid pairs, so check the answer
// is a valid pair rather than comparing it to one fixed pair
void randomCrossCheck() {
	std::mt19937 rng(1);
	std::uniform_int_distribution<int> lenDist(0, 15);
	std::uniform_int_distribution<int> valDist(-10, 10);

	int mismatches = 0;
	for(int t = 0; t < 5000; t++) {
		vector<int> v(lenDist(rng));
		for(int& x : v) x = valDist(rng);
		std::sort(v.begin(), v.end());
		int target = valDist(rng) * 2;
		int n = v.size();

		bool exists = false;
		for(int i = 0; i < n; i++)
			for(int j = i + 1; j < n; j++)
				if(v[i] + v[j] == target) exists = true;

		vector<int> got = run(v, target);
		bool ok;
		if(got == vector<int>{-1, -1}) {
			ok = !exists;
		} else {
			int i = got[0] - 1, j = got[1] - 1;   // back to 0-indexed
			ok = 0 <= i && i < j && j < n && v[i] + v[j] == target;
		}
		if(!ok) mismatches++;
	}

	if (mismatches == 0) {
		cout << "PASS  random cross-check (5000 arrays)\n";
	} else {
		cout << "FAIL  random cross-check  (" << mismatches << " mismatches)\n";
		failures++;
	}
}

void runTests() {
	check("leetcode example 1",       run({2, 7, 11, 15}, 9),    {1, 2});
	check("leetcode example 2",       run({2, 3, 4}, 6),         {1, 3});
	check("leetcode example 3",       run({-1, 0}, -1),          {1, 2});
	check("pair at both ends",        run({1, 3, 4, 9}, 10),     {1, 4});
	check("pair at the end",          run({1, 2, 3, 9}, 12),     {3, 4});
	check("pair at the start",        run({-5, -3, 0, 4}, -8),   {1, 2});
	check("equal values",             run({0, 0, 3, 4}, 0),      {1, 2});
	check("no pair",                  run({1, 2, 5}, 10),        {-1, -1});
	check("can't reuse one element",  run({3, 4, 5}, 6),         {-1, -1});
	check("empty",                    run({}, 0),                {-1, -1});
	check("single element",           run({5}, 10),              {-1, -1});
	randomCrossCheck();
}

int main() {
	runTests();

	cout << '\n' << (failures == 0 ? "All tests passed" : "Some tests failed") << '\n';
	return failures == 0 ? 0 : 1;
}
