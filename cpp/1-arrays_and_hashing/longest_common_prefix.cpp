#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::cout;

string longestCommonPrefix(const vector<string>& strs) {
	if(strs.size() == 0) {
		return "";
	}
	
	string first = strs.front();

	for(int i = 0; i < first.size() ; i++) {
		for(int j = 1; j < strs.size(); j++)  {
			if(i >= strs[j].size() || strs[j].at(i) != first.at(i)) {
				return first.substr(0, i);
			}
		}

	}

	return first;
}

int failures = 0;

void check(const string& name, const string& got, const string& expected) {
	if (got == expected) {
		cout << "PASS  " << name << '\n';
	} else {
		cout << "FAIL  " << name << "  (expected \"" << expected << "\", got \"" << got << "\")\n";
		failures++;
	}
}

void runTests() {
	check("2 letter common", longestCommonPrefix({"flower", "flow", "flight"}), "fl");
	check("same strings", longestCommonPrefix({"aab", "aab", "aab"}), "aab");
	check("all empty", longestCommonPrefix({"", "", ""}), "");
	check("no strings", longestCommonPrefix({}), "");
	check("empty and non empty string", longestCommonPrefix({"", "flow", "flight"}), "");
	check("whole first word", longestCommonPrefix({"fly", "flyer", "flying"}), "fly");

}

int main() {
	runTests();

	cout << '\n' << (failures == 0 ? "All tests passed" : "Some tests failed") << '\n';
	return failures == 0 ? 0 : 1;
}
