#include <climits>
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>
#include <list>

using std::cout;
using std::pair;
using std::string;
using std::vector;
using std::list;

/**
 * Hashmap implementation using Linear Probing
 */
class HashMap {
private:
	static const int TABLE_SIZE = 10007;
	vector<list<pair<int, int>>> table;

	int hash(int key) {
		int h = key % TABLE_SIZE;
		return h < 0 ? h + TABLE_SIZE : h;
	}
public:
	HashMap(): table(TABLE_SIZE) {}

	void add(int key, int value) {
		int idx = hash(key);

		for(auto& p: table[idx]) {
			if(p.first == key) {
				p.second = value;
				return;
			}
		}

		table[idx].push_back({key, value});
	}

	bool contains(int key) {
		int idx = hash(key);

		for(auto& p: table[idx]) {
			if(p.first == key) return true; 
		}

		return false;
	}

	int get(int key) {
		int idx = hash(key);

		for(auto& p: table[idx]) {
			if(p.first == key) return p.second; 
		}
		
		return INT_MAX;
	}

	void remove(int key) {
		int idx = hash(key);
		
		for(auto it = table[idx].begin(); it != table[idx].end(); it++) {
			if((*it).first == key) {
				table[idx].erase(it);
				return;
			} 
		}
		
		return;
	}
	
};

int main() {

	HashMap mp;

	mp.add(4, 2);
	cout << mp.get(4) << ' ' <<mp.contains(4)<< '\n';

	mp.remove(4);
	cout << mp.get(4) << '\n';

	return 0;
}

