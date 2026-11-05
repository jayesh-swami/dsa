#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>

using std::string;
using std::unordered_set;
using std::max;
using std::vector;

int lenLongestSubstr(string str) {
	int n = str.size();
	int maxLen = 0;
	int l = 0, r = 0;
	unordered_set<char> s;

	while(r < n) {
		while(r < n && s.insert(str[r]).second) { maxLen = max(r - l + 1, maxLen); r++;}
		while(l < r && r < n && s.contains(str[r])) { s.erase(str[l]); l++; }
	}

	return maxLen;
}

/**
* str		: ""
* 
* n		: 3
* maxLen	: 2
* l		: 2
* r		: 3
* s 		: {b}
* return	: 2
*/

// Assumes ASCII string
// Otherwise use unordered_map<char, int>
//
int lenLongestSubstrOpt(string s) {
	vector<int> charMap(128, -1);
	
	int l = 0, maxLen = 0;

	for(int r = 0; r < (int) s.size(); r++) {
		if(charMap[s[r]] != -1) {
			l = max(l, charMap[s[r]] + 1);
		}

		charMap[s[r]] = r;
		maxLen = max(maxLen, r - l + 1);
	}

	return maxLen;
}

/**
* str 		: "abba"
* 
* maxLen	: 2
* l		: 2
* r		: 3
* charMap	: {a: 0, b: 2}
*
* return	: 
*/

