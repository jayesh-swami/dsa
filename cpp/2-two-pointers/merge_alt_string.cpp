#include <algorithm>
#include <iostream>
#include <random>
#include <string>

using std::string;
using std::cout;

string mergeAlternateStrings(string s1, string s2) {
	int p1 = 0, p2 = 0;
	string res;

	int i = 0;
	while(p1 < s1.size() && p2 < s2.size()) {
		if(i % 2 == 0) res += s1[p1++];
		else res += s2[p2++];
		i++;
	}

	while(p1 < s1.size()) res += s1[p1++];
	while(p2 < s2.size()) res += s2[p2++];

	return res;
}

// ---- minimal test harness ----

int failures = 0;

void check(const string& name, const string& got, const string& expected) {
	if (got == expected) {
		cout << "PASS  " << name << '\n';
	} else {
		cout << "FAIL  " << name << "  (expected \"" << expected << "\", got \"" << got << "\")\n";
		failures++;
	}
}

// brute force reference: one index over the longer length, take from each string if it still has a char
string mergeAlternateBrute(const string& a, const string& b) {
	string res;
	for (size_t i = 0; i < std::max(a.size(), b.size()); i++) {
		if (i < a.size()) res += a[i];
		if (i < b.size()) res += b[i];
	}
	return res;
}

// random lengths 0..10 each, so both "s1 longer" and "s2 longer" come up often
void randomCrossCheck() {
	std::mt19937 rng(1);
	std::uniform_int_distribution<int> lenDist(0, 10);
	std::uniform_int_distribution<int> charDist('a', 'z');

	int mismatches = 0;
	for(int t = 0; t < 5000; t++) {
		string a(lenDist(rng), ' '), b(lenDist(rng), ' ');
		for(char& c : a) c = charDist(rng);
		for(char& c : b) c = charDist(rng);

		if(mergeAlternateStrings(a, b) != mergeAlternateBrute(a, b)) mismatches++;
	}

	if (mismatches == 0) {
		cout << "PASS  random cross-check (5000 pairs)\n";
	} else {
		cout << "FAIL  random cross-check  (" << mismatches << " mismatches)\n";
		failures++;
	}
}

void runTests() {
	check("both empty",              mergeAlternateStrings("", ""),          "");
	check("first empty",             mergeAlternateStrings("", "xyz"),       "xyz");
	check("second empty",            mergeAlternateStrings("abc", ""),       "abc");
	check("single chars",            mergeAlternateStrings("a", "b"),        "ab");
	check("equal length",            mergeAlternateStrings("abc", "pqr"),    "apbqcr");
	check("second longer",           mergeAlternateStrings("ab", "pqrs"),    "apbqrs");
	check("first longer",            mergeAlternateStrings("abcd", "pq"),    "apbqcd");
	check("first longer by one",     mergeAlternateStrings("abc", "pq"),     "apbqc");
	check("second longer by one",    mergeAlternateStrings("ab", "pqr"),     "apbqr");
	check("one char vs long",        mergeAlternateStrings("a", "pqrstu"),   "apqrstu");
	check("long vs one char",        mergeAlternateStrings("abcdef", "p"),   "apbcdef");
	check("repeated chars",          mergeAlternateStrings("aaa", "bbbbb"),  "abababbb");
	randomCrossCheck();
}

int main() {
	runTests();

	cout << '\n' << (failures == 0 ? "All tests passed" : "Some tests failed") << '\n';
	return failures == 0 ? 0 : 1;
}
