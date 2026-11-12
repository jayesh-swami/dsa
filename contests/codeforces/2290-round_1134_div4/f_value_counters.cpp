#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::ios;
using std::vector;

void printPermutation(const vector<int>& v);

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int t;
	cin >> t;

	for(int i = 0; i < t; i++) {
		int n;
		cin >> n;
		vector<int> v(n);

		for(auto& x: v) cin >> x;

		printPermutation(v);
	}
	
	return 0;
}

void printPermutation(const vector<int>& v) {
	int n = v.size();
	vector<int> p(n, -1);
	bool pass = true;

	for(int i = 0; i < n; i++) {
		int posx = n + v[i] - (i + 1);
		if(posx >= n || posx < 0 || p[posx] != -1) { pass = false; break; }

		p[posx] = i + 1;
	}

	if(pass) {
		for(int i = 0; i < n; i++) {
			cout << p[i] << ' ';
		}
	} else {
		cout << -1;
	}

	cout << '\n';
}
