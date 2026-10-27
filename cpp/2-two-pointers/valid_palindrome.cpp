#include <iostream>
#include <random>
#include <string>
#include <cctype>

using std::cout;
using std::string;

bool validPalindrome(const string& s) {

	int l = 0, r = s.size() - 1;

	while(l < r) {
		if(!isalnum(s[l])) l++;
		else if(!isalnum(s[r])) r--;
		else if(tolower(s[l++]) != tolower(s[r--])) return false;
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

// brute force reference: keep the lowercased alphanumerics, compare with the reverse
bool validPalindromeBrute(const string& s) {
	string t;
	for (char c : s) {
		if (isalnum(c)) t += tolower(c);
	}
	return t == string(t.rbegin(), t.rend());
}

// random strings from a small alphabet so palindromes come up often
void randomCrossCheck() {
	const string alphabet = "aAbB0 ,.:";
	std::mt19937 rng(1);
	std::uniform_int_distribution<int> lenDist(0, 12);
	std::uniform_int_distribution<int> charDist(0, alphabet.size() - 1);

	int mismatches = 0;
	for(int t = 0; t < 5000; t++) {
		string s(lenDist(rng), ' ');
		for(char& c : s) c = alphabet[charDist(rng)];

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
	check("empty",                    validPalindrome(""),                               true);
	check("single char",              validPalindrome("a"),                              true);
	check("only spaces",              validPalindrome("   "),                            true);
	check("only punctuation",         validPalindrome(".,:!"),                           true);
	check("classic true",             validPalindrome("A man, a plan, a canal: Panama"), true);
	check("classic false",            validPalindrome("race a car"),                     false);
	check("mixed case",               validPalindrome("Aa"),                             true);
	check("digit vs letter",          validPalindrome("0P"),                             false);
	check("digits only",              validPalindrome("12321"),                          true);
	check("digits not palindrome",    validPalindrome("1231"),                           false);
	check("punctuation at both ends", validPalindrome(".a."),                            true);
	check("punctuation on one end",   validPalindrome("ab,"),                            false);
	check("one char and punctuation", validPalindrome("a."),                             true);
	check("underscore skipped",       validPalindrome("ab_a"),                           true);
	check("underscore between diff",  validPalindrome("a_b"),                            false);
	check("quotes and spaces",        validPalindrome("No 'x' in Nixon"),                true);
	check("mismatch in the middle",   validPalindrome("abca"),                           false);
	randomCrossCheck();
}

int main() {
	cout << std::boolalpha;   // print true/false instead of 1/0

	runTests();

	cout << '\n' << (failures == 0 ? "All tests passed" : "Some tests failed") << '\n';
	return failures == 0 ? 0 : 1;
}
