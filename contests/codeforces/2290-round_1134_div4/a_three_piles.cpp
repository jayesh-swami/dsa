#include <algorithm>
#include <iostream>

using std::cout;
using std::min;
using std::max;
using std::ios;
using std::cin;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;

	cin >> n;

	for(int i = 0; i < n; i++) {
		int a,b,c;
		
		cin >> a;
		cin >> b;
		cin >> c;

		int aa = min(min(a, b), c);
		int bb = max(max(a, b), c);
		int cc = max(min(a,b), min(max(a,b),c));
		
		if(bb - aa == 2 && cc - aa == 1) {
			cout << "YES\n";
		} else {
			cout << "NO\n";
		}
	}

	return 0;
}

