#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::string;
using std::vector;
using std::to_string;
using std::stoi;

string encode(vector<string>& strs) {
	string encodedString;

	for(const string& s: strs) {
		encodedString += to_string(s.size());
		encodedString += '#';
		encodedString += s;
	}

	return encodedString;
}

vector<string> decode(string str) {
	vector<string> decodedStrings;

	for(int i = 0; i < str.size(); ) {
		string strLen;

		while(str[i] != '#') { strLen += str[i]; i++; }
		i++;

		int len = stoi(strLen);

		string currString;

		while(len > 0) {
			currString += str[i];
			i++;
			len--;
		}

		decodedStrings.push_back(currString);
	}

	return decodedStrings;
}

int main() {
	vector<string> s = {"pls", "no", "this way"};

	cout << encode(s) << '\n';

	for(string& s: decode(encode(s))) {
		cout << s << '\n';
	}
	
	return 0;
}
