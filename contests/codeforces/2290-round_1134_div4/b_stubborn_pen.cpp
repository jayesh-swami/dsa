#include <iostream>
#include <string>

using std::cout;
using std::ios;
using std::cin;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;

	cin >> n;

	for(int i = 0; i < n; i++) {
		int l;
		cin >> l;

		char pen = 'R';
		char c;

		int switches = 0;

		for(int i = 0; i < l; i++) {
			cin >> c;
			
			if(c != pen) {
				switches++;
			}

			if(c == 'R') pen = 'B';
			else pen = 'R';
		}

		cout << switches << '\n';
	}

	return 0;
}

