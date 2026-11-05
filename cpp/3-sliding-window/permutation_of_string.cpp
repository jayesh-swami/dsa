#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;

/**
* s1		: "clear"		"aaa"
* s2		: "aer"			"b"
*
* k		: 3			1
* s1Count	: {a: 1, r: 1, e: 1}	{a: 1}
* s2Count	: {a: 1, e: 1, r: 1}	{b: 1}
* i		: 4			3
*
* return	: true			
*
* O(26n)
*/
bool checkInclusion(const string& s1, const string& s2) {
	if(s1.size() < s2.size()) return false;
	
	vector<int> s1Count(26,0), s2Count(26, 0);
	int k = s2.size();
	int i = 0;

	for(; i < k; i++) {
		s1Count[s1[i] - 'a']++;
		s2Count[s2[i] - 'a']++;
	}
	
	if(s1Count == s2Count) return true;

	for(; i < (int) s1.size(); i++) {
		s1Count[s1[i-k] - 'a']--;
		s1Count[s1[i] - 'a']++;

		if(s1Count == s2Count) return true;
	}
	return false;
}

/**
* s1		: "abec"	
* s2		: "ce"
*
* s1Count	: {a:1}		{a:1, b:1}	{e:1, c:1}
* s2Count	: {c:1}		{c:1, e:1}	{c:1, e:1}
* matches	: 0		0		26
* i		: 0		1		3
* k		: 2				2
* 
* return	:
*/
bool checkInclusionOpti(const string& s1, const string& s2) {
	if(s1.size() < s2.size()) return false;

	vector<int> s1Count(26,0), s2Count(26, 0);
	int k = s2.size();
	int i = 0;
	int matches = 0;

	for(; i < k; i++) {
		s1Count[s1[i] - 'a']++;
		s2Count[s2[i] - 'a']++;
	}
	
	for(int j = 0; j < 26; j++) {
		if(s1Count[j] == s2Count[j]) matches++;
	}

	for(; i < (int) s1.size(); i++) {
		if(matches == 26) return true;
		
		int idx = s1[i - k] - 'a';
		s1Count[idx]--;
		if(s1Count[idx] == s2Count[idx]) matches++;
		else if(s1Count[idx] + 1 == s2Count[idx]) matches--;

		idx = s1[i] - 'a';
		s1Count[idx]++;
		if(s1Count[idx] == s2Count[idx]) matches++;
		else if(s1Count[idx] - 1 == s2Count[idx]) matches--;
	}

	return matches == 26;
}
