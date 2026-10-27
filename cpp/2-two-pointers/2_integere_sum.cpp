#include <iostream>
#include <vector>

using std::vector;

vector<int> twoSum(vector<int>& v, int t) {
	int l = 0, r = (int) v.size() - 1;

	while(l < r) {
        if(v[l] + v[r] < t) l++;
		else if(v[l] + v[r] == t) return vector({l + 1, r + 1});
		else r--;
	}

	return vector({-1, -1});
}
