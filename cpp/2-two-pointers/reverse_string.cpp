// Compile: g++ -std=c++20 -Wall -Wextra -g -fsanitize=address,undefined reverse_string.cpp -o reverse_string

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <type_traits>
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

// ---- test harness ----

int failures = 0;

template <typename T>
void show(const T& x) {
	cout << x;
}

void show(const string& s) {
	cout << '"' << s << '"';
}

void show(char c) {
	cout << '\'' << c << '\'';
}

template <typename T>
void show(const vector<T>& v) {
	cout << "[";
	for (size_t i = 0; i < v.size(); i++) {
		if (i) cout << ", ";
		show(v[i]);
	}
	cout << "]";
}

template <typename T>
void check(const string& name, const T& got, const std::type_identity_t<T>& expected) {
	if (got == expected) {
		cout << "PASS  " << name << '\n';
		return;
	}

	cout << "FAIL  " << name << "\n  expected: ";
	show(expected);
	cout << "\n  got:      ";
	show(got);
	cout << '\n';
	failures++;
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

// Edge cases:
// - empty and single char: the loop must not run (n / 2 == 0)
// - two chars: smallest case with exactly one swap
// - odd length: the middle char stays where it is
// - even length: no middle, every char moves
// - palindrome / all same chars: output equals input
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
