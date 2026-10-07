#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <utility>

using std::cout;
using std::vector;
using std::string;
using std::unordered_map;
using std::sort;
using std::move;

/**
 * The key idea to group anagrams is to sort the string characters so that every anagram becomes the same key
 * making it easier to hash. Another idea to explore might be using something like a custom hash function that
 * hashes based on the count of each character.
 *
 * Another very nice thing to know in cpp. The move function transfers the ownership of data allocated on heap
 * (and copies the ones it cannot transfer like int, char etc). This is how it natively works in java. So doing
 * push_back(s) on a vector for string s would actually copy the whole thing and that would O(len(s)) operation
 * whereas using the move from utility library would just transfer the ownership which is O(1) operation!
 */
vector<vector<string>> groupAnagrams(const vector<string>& strs) {
	unordered_map<string, vector<string>> groupedAnagrams;

	for(const string& s: strs) {
		string sc = s;
		sort(sc.begin(), sc.end());
		groupedAnagrams[move(sc)].push_back(s);
	}

	vector<vector<string>> ans;
	ans.reserve(groupedAnagrams.size());

	for(auto& [key, value]: groupedAnagrams) {
		ans.push_back(move(value));
	}

	return ans;
}

// ---- minimal test harness ----

int failures = 0;

// Sort inside each group, then sort the groups, so order doesn't matter.
vector<vector<string>> normalize(vector<vector<string>> groups) {
	for (auto& group : groups) {
		sort(group.begin(), group.end());
	}
	sort(groups.begin(), groups.end());
	return groups;
}

void printGroups(const vector<vector<string>>& groups) {
	cout << "[";
	for (size_t i = 0; i < groups.size(); i++) {
		cout << (i ? ", " : "") << "[";
		for (size_t j = 0; j < groups[i].size(); j++) {
			cout << (j ? ", " : "") << '"' << groups[i][j] << '"';
		}
		cout << "]";
	}
	cout << "]";
}

void check(const string& name, vector<vector<string>> got, vector<vector<string>> expected) {
	got = normalize(got);
	expected = normalize(expected);

	if (got == expected) {
		cout << "PASS  " << name << '\n';
	} else {
		cout << "FAIL  " << name << "\n  expected: ";
		printGroups(expected);
		cout << "\n  got:      ";
		printGroups(got);
		cout << '\n';
		failures++;
	}
}

void runTests() {
	check("basic", groupAnagrams({"eat", "tea", "tan", "ate", "nat", "bat"}),
	       {{"eat", "tea", "ate"}, {"tan", "nat"}, {"bat"}});

	check("all different catagories", groupAnagrams({"aa", "abc", "err", "ree"}), {{ "aa" }, {"abc"}, { "err" }, {"ree"}});
	check("all same catagories", groupAnagrams({"ere", "eer", "ree"}), {{ "ere", "eer", "ree"}});
}

int main() {
	runTests();

	cout << '\n' << (failures == 0 ? "All tests passed" : "Some tests failed") << '\n';
	return failures == 0 ? 0 : 1;
}


