#include <iostream>
#include <random>
#include <string>
#include <cctype>

using std::cout;
using std::string;

bool validPalindrome(const string& s, int l, int r) {
	while(l < r) {
		if(s[l++] != s[r--]) return false;
	}
	return true;
}

bool validPalindrome(const string& s) {
	int l = 0, r = s.size() - 1;

	while(l < r) {
		if(s[l] != s[r]) {
			return validPalindrome(s, l + 1, r) || validPalindrome(s, l, r - 1);
		}
		l++;
		r--;
	}

	return true;
}

// ---- minimal test harness ----

int failures = 0;

void check(const string& name, bool got, bool expected) {
	if (got == expected) {
		cout << "PASS  " << name << '\n';
	} else {
		cout << "FAIL  " << name << "  (expected " << expected << ", got " << got << ")\n";
		failures++;
	}
}

bool isPalindrome(const string& s) {
	return s == string(s.rbegin(), s.rend());
}

// brute force reference: the string itself, or the string with any one char removed
bool validPalindromeBrute(const string& s) {
	if (isPalindrome(s)) return true;
	for (size_t i = 0; i < s.size(); i++) {
		if (isPalindrome(s.substr(0, i) + s.substr(i + 1))) return true;
	}
	return false;
}

// random strings over "abc" so near-palindromes come up often
void randomCrossCheck() {
	std::mt19937 rng(1);
	std::uniform_int_distribution<int> lenDist(0, 12);
	std::uniform_int_distribution<int> charDist('a', 'c');

	int mismatches = 0;
	for(int t = 0; t < 5000; t++) {
		string s(lenDist(rng), ' ');
		for(char& c : s) c = charDist(rng);

		if(validPalindrome(s) != validPalindromeBrute(s)) mismatches++;
	}

	if (mismatches == 0) {
		cout << "PASS  random cross-check (5000 strings)\n";
	} else {
		cout << "FAIL  random cross-check  (" << mismatches << " mismatches)\n";
		failures++;
	}
}

void runTests() {
	check("empty",                          validPalindrome(""),          true);
	check("single char",                    validPalindrome("a"),         true);
	check("two different chars",            validPalindrome("ab"),        true);
	check("three different chars",          validPalindrome("abc"),       false);
	check("already palindrome (odd)",       validPalindrome("aba"),       true);
	check("already palindrome (even)",      validPalindrome("abba"),      true);
	check("delete in the middle",           validPalindrome("abca"),      true);
	check("delete first char",              validPalindrome("xaba"),      true);
	check("delete last char",               validPalindrome("abax"),      true);
	check("only the right skip works",      validPalindrome("abbab"),     true);
	check("only the left skip works",       validPalindrome("babba"),     true);
	check("needs two deletions",            validPalindrome("abxyzba"),   false);
	check("both ends wrong",                validPalindrome("tebbem"),    false);
	check("second mismatch after the skip", validPalindrome("abcdeca"),   false);
	check("all same chars",                 validPalindrome("aaaa"),      true);
	check("long true case",                 validPalindrome("ebcbbececabbacecbbcbe"), true);
	randomCrossCheck();
}

int main() {
	cout << std::boolalpha;   // print true/false instead of 1/0

	runTests();

	cout << '\n' << (failures == 0 ? "All tests passed" : "Some tests failed") << '\n';
	return failures == 0 ? 0 : 1;
}
