#include <iostream>
#include <string>
#include <unordered_map>

using std::string;
using std::cout;
using std::unordered_map;

bool isAnagram(string s, string t) {

	if(s.size() != t.size()) {
		return false;
	}

	unordered_map<char, int> sCount, tCount;

	for(int i = 0; i < s.size(); i++) {
		sCount[s.at(i)]++;
		tCount[t.at(i)]++;
	}

	for(auto& [key, value]: sCount) {
		if(!tCount.contains(key) || value != tCount[key]) {
			return false;
		}
	}

	return true;
}


// Test cases
//

int failures = 0;
 
void check(const string& name, bool got, bool expected) {
	if (got == expected) {
		cout << "PASS  " << name << '\n';
	} else {
		cout << "FAIL  " << name << "  (expected " << expected << ", got " << got << ")\n";
		failures++;
	}
}
 
void runTests() {
	check("empty strings", isAnagram("", ""), true);
	check("single character strings", isAnagram("a", "a"), true);
	check("unequal length strings", isAnagram("ab", "aaaaaa"), false);
	check("same strings", isAnagram("test", "test"), true);
	check("different order anagram", isAnagram("ttaat", "tatat"), true);
}
 
int main() {
	cout << std::boolalpha;   // print true/false instead of 1/0
 
	runTests();
 
	cout << '\n' << (failures == 0 ? "All tests passed" : "Some tests failed") << '\n';
	return failures == 0 ? 0 : 1;   // non-zero exit code signals failure
}

