#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <utility>

using std::cout;
using std::vector;
using std::string;
using std::swap;

void reverseString(vector<char>& str) {
	int n = str.size();

	for(int i = 0; i < n / 2; i++) {
		swap(str[i], str[n - i - 1]);
	}

	return;
}

// ---- minimal test harness ----

int failures = 0;

void check(const string& name, const vector<char>& got, const vector<char>& expected) {
	if (got == expected) {
		cout << "PASS  " << name << '\n';
	} else {
		cout << "FAIL  " << name << "  (expected \"" << string(expected.begin(), expected.end())
		     << "\", got \"" << string(got.begin(), got.end()) << "\")\n";
		failures++;
	}
}

// reverses a copy, since reverseString works in place
vector<char> reversed(vector<char> s) {
	reverseString(s);
	return s;
}

// random lengths 0..50, std::reverse used as the reference
void randomCrossCheck() {
	std::mt19937 rng(1);
	std::uniform_int_distribution<int> lenDist(0, 50);
	std::uniform_int_distribution<int> charDist('a', 'z');

	int mismatches = 0;
	for(int t = 0; t < 1000; t++) {
		vector<char> s(lenDist(rng));
		for(char& c : s) c = charDist(rng);

		vector<char> expected = s;
		std::reverse(expected.begin(), expected.end());
		if(reversed(s) != expected) mismatches++;
	}

	if (mismatches == 0) {
		cout << "PASS  random cross-check (1000 arrays)\n";
	} else {
		cout << "FAIL  random cross-check  (" << mismatches << " mismatches)\n";
		failures++;
	}
}

void runTests() {
	check("empty",           reversed({}),                         {});
	check("single char",     reversed({'a'}),                      {'a'});
	check("two chars",       reversed({'a', 'b'}),                 {'b', 'a'});
	check("odd length",      reversed({'h', 'e', 'l', 'l', 'o'}),  {'o', 'l', 'l', 'e', 'h'});
	check("even length",     reversed({'H', 'a', 'n', 'n', 'a', 'h'}), {'h', 'a', 'n', 'n', 'a', 'H'});
	check("palindrome",      reversed({'r', 'a', 'c', 'e', 'c', 'a', 'r'}), {'r', 'a', 'c', 'e', 'c', 'a', 'r'});
	check("all same",        reversed({'z', 'z', 'z', 'z'}),       {'z', 'z', 'z', 'z'});
	check("non-letters",     reversed({'1', ' ', '!', 'A'}),       {'A', '!', ' ', '1'});
	randomCrossCheck();
}

int main() {
	runTests();

	cout << '\n' << (failures == 0 ? "All tests passed" : "Some tests failed") << '\n';
	return failures == 0 ? 0 : 1;
}
