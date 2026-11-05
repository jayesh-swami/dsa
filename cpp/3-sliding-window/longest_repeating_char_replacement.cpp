#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

using std::string;
using std::vector;
using std::max;
using std::unordered_set;
using std::unordered_map;

/**
* s		: "AAB"			"ABCC"
* k		: 1			0
*
* n		: 3			4
* l		: 0			2
* r		: 3			4
* maxLen	: 3			2
* charCount	: {A: 2, B: 1}		{C: 1}
*
* return	: 3			2
*/
int characterReplacement(const string& s, int k) {
	vector<int> charCount(26, 0);
	int l = 0;
	int n = s.size();
	int maxLen = 0;

	for(int r = 0; r < n; r++) {
		charCount[s[r] - 'A']++;

		if(substrIsValid(k, charCount)) {
			maxLen = max(r - l + 1, maxLen);
			continue;
		} else {
			while(l < r && !substrIsValid(k, charCount)) {
				charCount[s[l] - 'A']--;
				l++;
			}
		}
	}

	return maxLen;
}


bool substrIsValid(int k, const vector<int>& charCount) {
	for(int i = 0; i < 26; i++) {
	int replacementsNeeded = 0;
	char replacementChar = 'A' + i;
	if(charCount[i] == 0) continue;

		for(int j = 0; j < (int) charCount.size(); j++) {
			if(replacementChar - 'A' == j) continue;

			replacementsNeeded += charCount[j];
		}

		if(replacementsNeeded <= k) return true;
	}

	return false;
}


/**
* Below is the O(m * n) approach. m is unique number of chars in s and n is len(s)
*/
int charReplacementMaxLen(string& s, int k, char c) {
	int replFreq = 0;
	int l = 0;
	int maxLen = 0;
	int n = s.size();
		
	for(int r = 0; r < n; r++) {
		if(s[r] != c) replFreq++;

		if(replFreq <= k) {
			maxLen = max(maxLen, r - l + 1);
		} else {
			while(l < r && replFreq > k) {
				if(s[l] != c) replFreq--;
				l++;
			}
		}
	}

	return maxLen;
}

int charReplacement26(string& s, int k) {
	unordered_set<char> se(s.begin(), s.end());
	int maxLen = 0;

	for(char c: se) maxLen = max(maxLen, charReplacementMaxLen(s, k, c));

	return maxLen;
}

/**
* below is the O(n) approach
*/
int charReplON(string& s, int k) {
	unordered_map<char, int> mp;

	int l = 0;
	int n = s.size();
	int maxf = 0;
	int res = 0;

	for(int r = 0; r < n; r++) {
		mp[s[r]]++;
		maxf = max(maxf, mp[s[r]]);

		while((r - l + 1) - maxf > k) {
			mp[s[l]]--;
			l++;
		}
		res = max(res, r-l+1);
	}

	return res;
}
