#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <random>
#include <algorithm>
#include <string>

using std::cout;
using std::vector;
using std::unordered_set;
using std::string;

/**
 * Generates inputs for sort_colors.cpp to test the O(n + klogk) running time.
 *
 * n is fixed, k (number of unique elements) goes 10, 100, ..., 10^6.
 * Every one of the k values appears at least once.
 *
 * Run from 1-arrays_and_hashing/:
 *     g++ -O2 tests/gen_sort_colors.cpp -o gen && ./gen && rm gen
 *     g++ -O2 sort_colors.cpp && ./a.out < tests/sort_colors_k1e6.txt
 */

const unsigned SEED = 1;
const int N = 1000000;

int main() {
	std::mt19937 rng(SEED);
	std::uniform_int_distribution<int> valDist(-1000000000, 1000000000);

	int k = 1;
	for(int e = 1; e <= 6; e++) {
		k *= 10;

		unordered_set<int> seen;
		vector<int> a;
		a.reserve(N);
		while((int)a.size() < k) {
			int v = valDist(rng);
			if(seen.insert(v).second) a.push_back(v);
		}

		std::uniform_int_distribution<int> idxDist(0, k - 1);
		while((int)a.size() < N) a.push_back(a[idxDist(rng)]);

		std::shuffle(a.begin(), a.end(), rng);

		string path = "tests/sort_colors_k1e" + std::to_string(e) + ".txt";
		std::ofstream out(path);
		if(!out) {
			cout << "could not open " << path << " (run from 1-arrays_and_hashing/)\n";
			return 1;
		}

		out << N << '\n';
		for(int i = 0; i < N; i++) out << a[i] << (i + 1 < N ? ' ' : '\n');

		cout << "wrote " << path << " (n = " << N << ", k = " << k << ")\n";
	}

	return 0;
}
