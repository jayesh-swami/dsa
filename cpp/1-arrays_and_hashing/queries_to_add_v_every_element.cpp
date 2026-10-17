#include <iostream>
#include <vector>
#include <utility>

using std::vector;
using std::pair;
using std::cout;

/**
 * You get an array of `n` zeros and `q` updates of the form "add `v` to 
 * every element in `a[l..r]`". After all updates, print the array. 
 * `n, q ≤ 2·10⁵`. Doing each update in a loop is O(n·q), 
 * which is too slow. Give an O(n + q) approach.
 *
 * queries are of form {v , {l, r}}
 *
 */
vector<int> getArrayAfterQueries(int n, vector<pair<int, pair<int, int>>>& queries) {
	vector<int> res(n, 0), add_k(n, 0);

	for(auto& p: queries) {
		add_k[p.second.first] += p.first;
		if(p.second.second + 1< n)
			add_k[p.second.second + 1] -= p.first;
	}

	int currVal = 0;

	for(int i = 0; i < n; i++) {
		currVal += add_k[i];
		res[i] = currVal;
	}

	return res;
}

int main() {
	vector<pair<int, pair<int, int>>> q = { {1, {2,4} }, { 5, {0, 7}} };
	
	vector<int> res = getArrayAfterQueries(5, q);

	for(int n: res) {
		cout << n << ' ';
	}

	cout << '\n';

	return 0;
}

