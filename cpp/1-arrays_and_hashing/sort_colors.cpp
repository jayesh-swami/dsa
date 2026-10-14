#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <chrono>

using std::cout;
using std::cin;
using std::ios;
using std::vector;
using std::unordered_map;
using std::pair;
using std::sort;

/**
 * Sorting only 3 colors - hardcoded
 */
void sortColors(vector<int>& nums) {
        int a = 0, b = 0, c = 0;

        for(int& i: nums) {
        	if(i == 0) a++;
        	else if(i == 1) b++;
        	else c++;
        }

        int k = 0;

        while(a > 0) { nums[k] = 0; a--; k++; }

        while(b > 0) { nums[k] = 1; b--; k++; }

        while(c > 0) { nums[k] = 2; c--; k++; }

        return;
}

/**
 * For a small N
 */
void sortColorsN(vector<int>& nums) {
	unordered_map<int, int> cnt;

	for(int& i: nums) cnt[i]++;

	vector<pair<int, int>> numCounts(cnt.begin(), cnt.end());
	sort(numCounts.begin(), numCounts.end());
	
	int k = 0;
	for(auto& item: numCounts) {
		for(int i = 0; i < item.second; i++) {
			nums[k] = item.first;
			k++;
		}
	}
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;
	vector<int> a(n);
	for(int& x: a) cin >> x;

	auto start = std::chrono::steady_clock::now();

	sortColorsN(a);

	auto end = std::chrono::steady_clock::now();

	cout << "Time taken (sortColorsN) - " << std::chrono::duration<double>(end - start).count() << '\n';

	int k = n > 0 ? 1 : 0;
	for(int i = 1; i < n; i++) if(a[i] != a[i - 1]) k++;

	cout << "n = " << n << ", k = " << k << '\n';
	cout << "sorted: " << (std::is_sorted(a.begin(), a.end()) ? "yes" : "no") << '\n';

	return 0;
}
