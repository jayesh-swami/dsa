#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <utility>
#include <string>
#include <random>

using std::cout;
using std::vector;
using std::max;
using std::stack;
using std::pair;
using std::string;

/**
 * Naive way, considering each day as a selling opportunity
 * and checking the first min elements to the left and booking 
 * the profit. This solution keeps a padding in profitUntilN array
 *
 * Comp -> O(n^2) time and O(n) memory
 */
int maxProfit(vector<int>& prices) {
	vector<int> profitUntilN(prices.size() + 1, 0);

	for(int i = 0; i < (int)prices.size(); i++) {
		for(int j = i; j > 0; j--) {
			// buy on day j-1, sell on day i
			if(prices[j - 1] < prices[i]) {
				profitUntilN[i + 1] = max(profitUntilN[i + 1], profitUntilN[j] + prices[i] - prices[j - 1]);
			}
			// don't sell on day i, keep the best seen so far
			profitUntilN[i + 1] = max(profitUntilN[i + 1], profitUntilN[j + 1]);
		}
	}

	return profitUntilN[prices.size()];
}

/**
 * Optimizations we can do here -> Keep a stack to keep track of smallest to left
 * Pop until the top of stack is smaller than current element or stack is empty and then push
 * Use the top of stack to create the small to the right array so that instead of the loop we
 * do a O(1) (well not O(1) but the loop in total would be 2 * N) lookup and keep an array still to store max profit until N
 *
 * Note -> DO REMEMBER TO ALWAYS UPDATE THE CURRENT MAX PROFIT EVEN IF YOU DON'T SELL ON THAT DAY!!
 */
int maxProfitOptimized(vector<int>& prices) {
	vector<int> profitUntilN(prices.size() + 1, 0);
	stack<pair<int, int>> s; // (price, day), prices non-decreasing from bottom to top
	int maxPro = 0;

	for(int i = 0; i < (int)prices.size(); i++) {
		// drop everything more expensive than today, it can never be a better buy than today
		while(!s.empty() && s.top().first > prices[i]) s.pop();

		// top is now the nearest day to the left with price <= today, buy there and sell today
		if(!s.empty()) profitUntilN[i+1] = max(maxPro, profitUntilN[s.top().second + 1] + prices[i] - s.top().first);
		profitUntilN[i+1] = max(profitUntilN[i+1], maxPro);

		s.push({prices[i], i});

		maxPro = max(maxPro, profitUntilN[i+1]);
	}

	return maxPro;
}

/**
 * Greedy approach -> just buy every upward price move since we can always
 * buy and sell the same day. Always buy i -> i+1 jump
 */
int maxProfitGreedy(vector<int>& prices) {
	int profit = 0;

	for(int i = 1; i < (int)prices.size(); i++) {
		if(prices[i] > prices[i-1]) profit += prices[i] - prices[i-1];
	}

	return profit;
}

// ---- minimal test harness ----

int failures = 0;

void check(const string& name, int got, int expected) {
	if (got == expected) {
		cout << "PASS  " << name << '\n';
	} else {
		cout << "FAIL  " << name << "  (expected " << expected << ", got " << got << ")\n";
		failures++;
	}
}

// runs the same case against all three implementations
void checkAll(const string& name, vector<int> prices, int expected) {
	check(name + " [naive]",     maxProfit(prices),          expected);
	check(name + " [stack]",     maxProfitOptimized(prices), expected);
	check(name + " [greedy]",    maxProfitGreedy(prices),    expected);
}

// random arrays, naive O(n^2) used as the reference for the other two
void randomCrossCheck() {
	std::mt19937 rng(1);
	std::uniform_int_distribution<int> lenDist(0, 50);
	std::uniform_int_distribution<int> valDist(0, 20); // small range so there are lots of equal prices

	int mismatches = 0;
	for(int t = 0; t < 1000; t++) {
		vector<int> prices(lenDist(rng));
		for(int& p : prices) p = valDist(rng);

		int expected = maxProfit(prices);
		if(maxProfitOptimized(prices) != expected || maxProfitGreedy(prices) != expected) mismatches++;
	}

	if (mismatches == 0) {
		cout << "PASS  random cross-check (1000 arrays)\n";
	} else {
		cout << "FAIL  random cross-check  (" << mismatches << " mismatches)\n";
		failures++;
	}
}

void runTests() {
	checkAll("basic",                {7, 1, 5, 3, 6, 4},       7);
	checkAll("strictly increasing",  {1, 2, 3, 4, 5},          4);
	checkAll("strictly decreasing",  {7, 6, 4, 3, 1},          0);
	checkAll("empty",                {},                       0);
	checkAll("single day",           {5},                      0);
	checkAll("two days up",          {1, 5},                   4);
	checkAll("two days down",        {5, 1},                   0);
	checkAll("all same",             {3, 3, 3, 3},             0);
	checkAll("plateaus",             {1, 1, 3, 3, 2, 2, 5},    5);
	checkAll("zigzag",               {1, 5, 1, 5, 1, 5},       12);
	checkAll("dip then rise",        {5, 2, 2, 8},             6);
	checkAll("valley in the middle", {3, 3, 5, 0, 0, 3, 1, 4}, 8);
	randomCrossCheck();
}

int main() {
	runTests();

	cout << '\n' << (failures == 0 ? "All tests passed" : "Some tests failed") << '\n';
	return failures == 0 ? 0 : 1;
}
