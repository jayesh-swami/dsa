#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using std::cout;
using std::vector;
using std::unordered_map;
using std::string;

vector<int> twoSum(const vector<int>& nums, int target) {
	unordered_map<int, int> numIndex;

	for(int i = 0; i < nums.size(); i++) {
		int secondNumber = target - nums[i];

		if(numIndex.contains(secondNumber)) {
			return {numIndex[secondNumber], i};
		}

		numIndex[nums[i]] = i;
	}

	return {};
}

int failures = 0;

void printVec(const vector<int>& v) {
	cout << '[';
	for (int i = 0; i < (int)v.size(); i++) {
		if (i > 0) cout << ", ";
		cout << v[i];
	}
	cout << ']';
}

void check(const string& name, const vector<int>& got, const vector<int>& expected) {
	if (got == expected) {
		cout << "PASS  " << name << '\n';
	} else {
		cout << "FAIL  " << name << "  (expected ";
		printVec(expected);
		cout << ", got ";
		printVec(got);
		cout << ")\n";
		failures++;
	}
}

void runTests() {
	check("empty list", twoSum({}, 10), {});
	check("distinct values in array", twoSum({2, 7, 11, 15}, 9), {0, 1});
	check("duplicate values in array", twoSum({2, 5, 2, 11, 15}, 4), {0, 2});
	check("non existing sum", twoSum({2, 7, 11, 15}, 10000), {});

}

int main() {
	runTests();

	cout << '\n' << (failures == 0 ? "All tests passed" : "Some tests failed") << '\n';
	return failures == 0 ? 0 : 1;
}
