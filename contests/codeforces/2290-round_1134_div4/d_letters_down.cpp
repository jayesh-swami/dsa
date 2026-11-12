#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::min;
using std::max;

int main() {
	int n;
	
	cin >> n;

	for(int i = 0; i < n; i++) {
		int len;
		string s;

		cin >> len;
		cin >> s;
		
		int l = 0, r = len - 1;

		vector<bool> range(26, false);

		while(r > l) {
			if(s[l] != s[r]) {
				int m1 = min(s[l] - 'a', s[r] - 'a');
				int m2 = max(s[l] - 'a', s[r] - 'a');

				for(int j = m1; j < m2; j++) range[j] = true;
			}
			l++;
			r--;
		}

		int res = 0;

		for(int j = 0; j < 26; j++) if(range[j]) res++;

		cout << res << '\n';
	}

	return 0;
}
